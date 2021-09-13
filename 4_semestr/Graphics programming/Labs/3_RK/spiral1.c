/* 2 centred spiral implementation */

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include "spiral.h"

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)>(b))?(b):(a))


/* задание начальной конфигурации структуры */

int configure_circle(XArrow* pr, int w, int h) {
    pr->R = 1;
    pr->c.x = w / 2;
    pr->c.y = h / 2;
    pr->dR = 1;
    pr->h = h;
    pr->w = w;
    pr->Rm = MIN(h, w) / 2;
    return 0;
}


/*рисование одного шага окружности*/
int draw_circle(Display *dpy, Window win, GC gc, XArrow *pr){
    XClearWindow(dpy, win);
    XFillArc(dpy, win, gc, pr->c.x - pr->R, pr->c.y - pr->R, pr->R * 2, pr->R * 2, 0, 360 * 64);
    XFlush(dpy);
    return step_radius(pr);
}

/*перерисовка потерянного изображения в окне*/

int redraw(XEvent* ev, GC gc, XArrow* pr) {
    static XRectangle clip[32];     /* clip rectangles buffer */
    static int n = 0;               /* clip rectangles number */
    clip[n].x = ev->xexpose.x;
    clip[n].y = ev->xexpose.y;
    clip[n].width =  ev->xexpose.width;
    clip[n].height =  ev->xexpose.height;
    n++;
    if((ev->xexpose.count > 0) && (n < 32))
        return(0);
    XSetClipRectangles(ev->xexpose.display, gc, 0, 0, clip, n, Unsorted);

    draw_circle(ev->xexpose.display, ev->xexpose.window, gc, pr);

    XSetClipMask(ev->xexpose.display, gc, None);
    return(n=0);
} /* redraw */


/*изменение направления изменения радиуса окружности*/

int reverse(XArrow* pr) {
    pr->dR = -pr->dR;
    return 0;
} /* reverse */


/*увеличение/уменьшение радиуса пульсирующей окружности*/

int step_radius(XArrow* pr) {
    pr->R += pr->dR;
    if (pr->R == 0) {
        reverse(pr);
    }
    else
    if (pr->R == pr->Rm) {
        reverse(pr);
    }
    return 0;
} /* step_radius */


/* проверка окна на частичное или полное заслонение, для торможения отображения окружности*/

int overlap(XEvent* ev) {
    if(ev->xvisibility.state != VisibilityUnobscured)
        return(-32);
    return(0);
} /* overlap */


/* ответ на события нажатия на клавиши клавиатуры */

int key_check(XEvent* ev) {
    static int state = 1;
    KeySym ks = XLookupKeysym((XKeyEvent*) ev, 1);
    if(ks == XK_Break)
        return state = 2;
    if(ks == XK_Return)
        return state = 1;
    if((ks == XK_C) && (ev->xkey.state == ControlMask))
        return 0;  /*код выхода*/
    return state;
} /* rapid */
