#include <X11/Xlib.h>
#include <unistd.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <stdlib.h>
#include "xchess.h"

static  Display  *dpy;  		//Адрес  дисплейной  структуры 
static GC gc;
static  Window  desk;  			//Окно  игрового  поля  программы 
static cell** box; 		    	//Адрес массива NYxNX клеток 
static int  done  =  0;

static unsigned long colors[2];

//Настройка  графических  параметров
int  xcustom()  {
    int  x,  y;  								//Позиции  окон 
    unsigned  w,  h;  							//Габариты  окон
    int  depth  =  DefaultDepth(dpy,  0);  		//Глубина  экрана  0
    Window  root;  								//Корневое  окно  экрана 
    XSetWindowAttributes  attr;  				//Атрибуты  окон
    unsigned  long  amask;  					//Маска  оконных  атрибутов 
    XSizeHints  hint;  							//Геометрия  оконного  менеджмента 
    int  i,  j;  								//Индексы  окон
    Colormap colormap;  						//Карта цветов

	//Настройка  графических  контекстов 
    root  =  DefaultRootWindow(dpy);  			//Корневое  окно  экрана 
    gc = XCreateGC(dpy, root, 0, NULL);

	//Настройка цветов палитры
    colormap = XDefaultColormap(dpy, DefaultScreen(dpy));
    XColor RGBpixel;
    XParseColor(dpy, colormap, "#ffffff", &RGBpixel);       //White
    XAllocColor(dpy, colormap, &RGBpixel);
    colors[0] = RGBpixel.pixel;
    XParseColor(dpy, colormap, "#8A8BEE", &RGBpixel);       //Pink
    XAllocColor(dpy, colormap, &RGBpixel);
    colors[1] = RGBpixel.pixel;

	//Настройка  игрового  окна  программы
    attr.override_redirect  =  False;  						//WM  обрамление  окна
    attr.background_pixel  =  colors[0];					//0xFFFFFF - white
    amask  =  (CWOverrideRedirect  |  CWBackPixel );
	//Габариты игрового  окна
    w  = COLS * CELLSIZE;   
    h  = ROWS * CELLSIZE;   
	//Начальные  координаты  окна  игры
    x  =  0;  
	y  =  0;  									
    desk  =  XCreateWindow(dpy,  root,  x,  y,  w,  h, 1, depth, InputOutput,
                           CopyFromParent, amask, &attr); //Геометрические  рекомендации  оконного  менеджера
    hint.flags  =  (PMinSize  |  PMaxSize  |  PPosition);
	//Фиксируем габариты  и позицию  окна  игрового  поля в  свойстве  WM
    hint.min_width  =  hint.max_width  =  w; 
    hint.min_height  =  hint.max_height  =  h; 
    hint.x  =  x;  
	hint.y  =  y;
    XSetNormalHints(dpy,  desk,  &hint);
    XStoreName(dpy,  desk,  "xchess");  //Заголовок  окна


	//Настройка  окон  клеток 
    amask  =  CWOverrideRedirect  |  CWBackPixel  |  CWEventMask | CWBackingStore;
    attr.override_redirect = True;  //Отмена обрамления окна
    attr.background_pixel = XWhitePixel(dpy, XDefaultScreen(dpy));
    attr.backing_store = Always;        //Сохранение конфигурации окна при заслонении
    attr.event_mask  =  (KeyPressMask  |  ExposureMask | ButtonPressMask);
	//Габариты  окна  клетки
    w = CELLSIZE;
    h = CELLSIZE;
    x = 0;
    y = 0;
    box = (cell **)calloc(ROWS, sizeof(cell*));
    for(i = 0; i < ROWS; i++) { 						//Цикл  по  рядам  клеток
        box[i] = (cell *) calloc(COLS, sizeof(cell));
        x = 0;
        for (j = 0; j < COLS; j++) { 					//Создать окна клеток
            box[i][j].window = XCreateWindow(dpy, desk, x, y, w-1, h-1, 1, depth,
                                             InputOutput, CopyFromParent, amask,
                                             &attr);	//Отображение  всех  окон  на  экране */
            box[i][j].type = NOTUNDERRATACK;    //Значение по умолчанию не под атакой
            box[i][j].figure = 0;
            x += CELLSIZE;
        }
        y += CELLSIZE;
    }

    XMapWindow(dpy,  desk);
    XMapSubwindows(dpy,  desk);
    return(0)
;}


//Диспетчер  событий
int  dispatch()  
{ 
    XEvent  *event = calloc(1, sizeof(XEvent));  //Структура  событий

	//Флаг  выхода
    while(done  ==  0)  {  			//Цикл  обработки  событий 
       XNextEvent(dpy,  event);  	//Чтение  событий
        switch(event->type)  {
            case  Expose:
                redraw();  //Перерисовка
                break;
            case  ButtonPress:
                done = do_step(event);
                break;  	//Позиционирование 
            case  KeyPress:
                done = key_analiz(event);
                break;  //Прерывание
            default:  break;
        } 
    } 
    free(event);
    return(0);
}


//Ход  игры  или  корректировка  позиций
int  do_step(XEvent*  ev) 
{
    int cur_time = CurrentTime;

    Window root, child;
    int root_x_return, root_y_return, win_x_return, win_y_return;
    unsigned mask_return;

	//Опрос позиции курсора
    XQueryPointer(dpy, desk, &root, &child, &root_x_return, &root_y_return, &win_x_return, &win_y_return, &mask_return);
    int start_y = win_y_return / CELLSIZE;
    int start_x = win_x_return / CELLSIZE;
    if (box[start_y][start_x].figure == 0){
        return 1;
    }

    XGrabPointer(dpy, desk, True, 0
            , GrabModeAsync, GrabModeAsync, desk, None, cur_time);

	//Создание окна фигуры
    XSetWindowAttributes attr;
    unsigned long amask  =  CWOverrideRedirect  |  CWBackPixel  |  CWEventMask;
    attr.override_redirect = True;  /* Отмена обрамления окна */
    attr.background_pixel = XBlackPixel(dpy, XDefaultScreen(dpy));
    attr.event_mask  =  (KeyPressMask  |  ExposureMask | ButtonPressMask);
    Window Figure = XCreateWindow(dpy, desk, win_x_return - FIGURESIZE/2, win_y_return - FIGURESIZE/2, FIGURESIZE, FIGURESIZE, 0, DefaultDepth(dpy, DefaultScreen(dpy)),
                  InputOutput, CopyFromParent, amask,
                  &attr);

	//Создание фигуры для drag&drop
    XMapWindow(dpy, Figure);
	unsigned long mask_return_past = mask_return;
	while (mask_return == mask_return_past){
        XQueryPointer(dpy, desk, &root, &child, &root_x_return, &root_y_return, &win_x_return, &win_y_return, &mask_return);
        XMoveWindow(dpy, Figure, win_x_return - FIGURESIZE/2, win_y_return - FIGURESIZE/2);
    }
    XDestroyWindow(dpy, Figure);

	//Проверка правил
    CheckRules(start_x, start_y, win_x_return/CELLSIZE, win_y_return/CELLSIZE);

    XUngrabPointer(dpy, cur_time);
    return 0;
}


//Перерисовка состояния игры на карте
int  redraw(){
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
        {
            XSetForeground(dpy, gc, colors[box[i][j].type]);
            XFillRectangle(dpy, box[i][j].window, gc, 0, 0, CELLSIZE, CELLSIZE);
            if (box[i][j].figure != 0) {
                XSetForeground(dpy, gc, BlackPixel(dpy, DefaultScreen(dpy)));
                XFillRectangle(dpy, box[i][j].window, gc, 20, 20, FIGURESIZE, FIGURESIZE);
            }
        }
    return 0;
}

//Анализ нажатых клавиш
int  key_analiz(XEvent*  ev){
    if (ev->xkey.keycode == XKeysymToKeycode(dpy, XK_Escape)) {
        desk_setter();
        redraw();
        return 0;;
    }
    return 0;
}


int main() {
    dpy  =  XOpenDisplay(NULL);

    xcustom();
    relink(box);
    desk_setter();
    dispatch();

	XFreeGC(dpy, gc);
    XDestroySubwindows(dpy, desk);
    XDestroyWindow(dpy, desk);

    XCloseDisplay(dpy);
    for(int i = 0; i < ROWS; ++i)
		free(box[i]);
	free(box);
    return(0);
}
