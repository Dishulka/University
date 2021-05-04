#include <X11/Xlib.h>
#include "xsort.h"

typedef XRectangle XFig;

#define REFIG(F) (F->rec)

int fragon(XFragment* ff, int x, int y, int t) {
  XFig* f = REFIG(ff);
  if((x < (f->x - 1)) || (x > (f->x + f->width + 1)) ||
     (y < (f->y - 1)) || (y > (f->y + f->height + 1)))
    return(0);   
  return(1);
}

int fragover(XFragment* ff1, XFragment* ff2) {
  XFig* f1 = REFIG(ff1);
  XFig* f2 = REFIG(ff2);
  if((f1->x > f2->x + f2->width) || (f2->x > f1->x + f1->width) ||
     (f1->y > f2->y + f2->height) || (f2->y > f1->y + f1->height)) return(0);
  else return(1);
}

int difrag(XFragment* ff1, XFragment* ff2) { 
  XFig* f1 = REFIG(ff1);
  XFig* f2 = REFIG(ff2);
  return(f1->width * f1->height - f2->width * f2->height);
}

int tinyfrag(XFragment* ff) {
  XFig* f = REFIG(ff);
  if((f->width < MINSIZEX) || (f->height < MINSIZEY))
    return(1);
  return(0);
}

int fragsize(XFragment* ff) {
  XFig* f = REFIG(ff);
  return(f->width * f->height);
}

int frag0(XFragment* ff, int x, int y) {
  XFig* f = REFIG(ff);
  f->x = x; f->y = y;
  f->width = f->height = 0;
  return(0);
}

int fragvar(XFragment* ff, int x, int y) {
  XFig* f = REFIG(ff);
  static int fx0, fy0;
  
  if(f->width == 0)
    fx0 = f->x;
  if(f->height == 0)
    fy0 = f->y;
    
  if(x < fx0) {
    f->x = x;
    f->width = fx0 - x;
  } else {
    f->x = fx0;
    f->width = x - fx0;
  }
  if(y < fy0) {
    f->y = y;
    f->height = fy0 - y;
  } else {
    f->y = fy0;
    f->height = y - fy0;
  }
  
  return(0);
}

int fragmaxix(XFragment* ff) {
  XFig* f = REFIG(ff);
  return(f->x + f->width);
}

int fragmaxiy(XFragment* ff) {
  XFig* f = REFIG(ff);
  return(f->y + f->height);
}

int XContour(Display* dpy, Window win, GC gc, XFragment* ff) {
  XFig* f = REFIG(ff);
  XDrawRectangles(dpy, win, gc, f, 1);
  return(0);
}

int XFix(Display* dpy, Window win, GC gc, XFragment* ff, GC fillGC) {
  XFig* f = REFIG(ff);
  XFillRectangles(dpy, win, fillGC, f, 1);
  XDrawRectangles(dpy, win, gc, f, 1);
  return(0);
}
