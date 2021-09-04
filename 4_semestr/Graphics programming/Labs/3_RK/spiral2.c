/* 2 centred spiral main function */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include "spiral.h"

/* Main function */

int main(int argc, char* argv[]) {
    Display* dpy;              /* Graphic Display */
    Window win;                /* programm main window */
    GC gc;                  /* Black & White Graphic Context */
    int scr;                   /* screen number = 0 */
    XArrow r;                  /* spiral structure */

    { /* Display Block */
        unsigned long tone;       /* Light drawing tone */
        dpy = XOpenDisplay(NULL);
        scr = DefaultScreen(dpy);
        win = DefaultRootWindow(dpy);
        scr = DefaultScreen(dpy);
        gc = XCreateGC(dpy, win, 0, 0);

        //работа с цветом
	    XColor pix;
        Colormap cmap = DefaultColormap(dpy, scr); /* экранная палитра */
        XParseColor(dpy, cmap, "#FFFFFF", &pix); /* −> RGB */
        XAllocColor(dpy, cmap, &pix);
        XSetForeground(dpy, gc, pix.pixel);     //цвет переднего фона

        XParseColor(dpy, cmap, "#000000", &pix); /* −> RGB */
        XAllocColor(dpy, cmap, &pix);
        XSetBackground(dpy, gc, pix.pixel);     //цвет заднего фона
        //работа с цветом

    } /* Display block */

    { /* Window block  */
        unsigned w, h;             /* main window width & height */
        XSetWindowAttributes attr; /* window attributes structure */
        XGCValues gval;            /* GC structure */
        unsigned long amask;       /* window attributes mask */
        Window root=win;            /* Display root window */
        XSizeHints hint;           /* Geometry WM hints */
        if(argc < 2)
            argv[1] = "640x480";
        int empty;                      /* for x & y */

        XParseGeometry(argv[1], &empty, &empty, &w, &h);        //получение исходной конфигурации окна из строки
        if((h < DisplayHeight(dpy, scr)) && (w < DisplayWidth(dpy, scr)) && (h >= 480) && (w >= 480))
            configure_circle(&r, w, h);         //конфигурация структуры
        else
        {
            argv[1] = "640x480";
            XParseGeometry(argv[1], &empty, &empty, &w, &h);        //получение исходной конфигурации окна из строки
            configure_circle(&r, w, h);
        }

        printf("Now: %s %s (RxN)\n", argv[0], argv[1]); fflush(stdout);
        amask = (CWOverrideRedirect | CWBackPixel);
        XGetGCValues(dpy, gc, GCBackground, &gval);
        attr.background_pixel = gval.background; /* = 0x0 */
        attr.override_redirect = False;
        win = XCreateWindow(dpy, root, 0, 0, w, h, 1, CopyFromParent,
                            InputOutput, CopyFromParent, amask, &attr);

        hint.flags = (PMinSize | PMaxSize);
        hint.min_width = hint.max_width = w;
        hint.min_height = hint.max_height = h;
        XSetNormalHints(dpy, win, &hint);
        XStoreName(dpy, win, "spiral");
        XMapWindow(dpy, win);
    } /* window block */

    { /* Multi Block */
        unsigned long emask;       /* window event mask */
        XEvent event;              /* graphic event structure */
        int freeze = 1;              /* window visibility stop state */
        unsigned delay=(1<<15);    /* multi delay period = 2^rate */
        int multi=(1<<12);         /* multi code */
        int count = 0;               /* delay count */

        emask = ( KeyPressMask | ExposureMask | VisibilityChangeMask);
        XSelectInput(dpy, win, emask);

        while(multi != 0) { /* Async dispatch event with multic ground */
            event.type = 0;
            XCheckWindowEvent(dpy, win, emask,  &event);
            switch (event.type) {
                case Expose:
                    redraw(&event, gc, &r);
                    break;
                case VisibilityNotify:
                    freeze = overlap(&event);
                    break;
                case KeyPress:
                    multi = key_check(&event);
                    break;
                default:
                    break;
            } /* switck */


            if((freeze < 0) || (multi == 2))     /* окно заслонено или была нажата клавиша pouse */
                continue;
            if(count++ < delay)                 /* увеличение и проверка счетчика для отрисовки */
                continue;
            count = 0;                    /* сброс счетчика */
            draw_circle(dpy, win, gc, &r);       /*отрисовка нового положения окружности*/
        } /* while event */
    } /* multi block */

    { /* Exit block */
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
        return(0);
    } /* exit block */

} /* main */
