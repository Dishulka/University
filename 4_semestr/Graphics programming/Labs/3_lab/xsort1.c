#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>
#include <stdlib.h>
#include "xsort.h"

#define FRAGSIZ sizeof(XFragment)

static Display* dpy;
static Window win;
static GC* gc;

static XFragment ftmp[1];
static XFragment bak[2];
static XFragment* frag;
static int nfrag=0;
static int GGC=FGC;

//static int building = 0;

int pass1(Display* d, Window w, GC* g) {
  dpy = d; win = w; gc = g;
  return(0);
}

int XFixes(Display* dpy, Window win , GC _gc, XFragment* f, int n) {
  int i;
  for(i = 0; i < n; i++, f++) XFix(dpy, win, _gc, f, gc[(i%10)+3]);
  return(0);
}

int rubin(XEvent* ev) {
  int i;
  XGrabPointer(dpy, win, False, (ButtonReleaseMask | Button1MotionMask), 
               GrabModeAsync, GrabModeAsync, win, None, CurrentTime);
  if(ev->xbutton.button != Button1) return(~Button1);
  //if((i = near(ev->xbutton.x, ev->xbutton.y)) == -1) {
    //building = 1;
    frag0(ftmp, ev->xbutton.x, ev->xbutton.y);
  //}
  return(Button1);
}

int near(int x, int y) {
  int i;
  for(i = nfrag-1; i >= 0; --i)
    if(fragon(frag+i, x, y, 0) > 0) break;
  return(i);
}

int rubout(XEvent* ev) {
  int i;
  if(nfrag < 1) return(0);
  if((i = near(ev->xbutton.x, ev->xbutton.y)) == -1) return(nfrag);
  XFix(dpy, win, gc[1], frag+i, gc[1]);
  XFlush(dpy);
  if(--nfrag > i) memmove((frag + i), (frag + i + 1), (nfrag - i)*FRAGSIZ);
  frag = realloc(frag, nfrag*FRAGSIZ);
  if(nfrag == 0) frag = NULL;
  return(nfrag);
}

int rerub(XEvent* ev) {
  static int x, y;
  //if(!building) return(nfrag);
  XContour(dpy, win, gc[RGC], ftmp);
  if(fragvar(ftmp, ev->xmotion.x, ev->xmotion.y) < 0) {
    XContour(dpy, win, gc[RGC], ftmp);
    return(XWarpPointer(dpy, None, win, 0, 0, 0, 0, x, y));
  }
  XContour(dpy, win, gc[RGC], ftmp);
  x = ev->xmotion.x; y =  ev->xmotion.y;
  return(0);
}

int reggc(int g) {
  return(GGC = g);
}

int refrag() {
  XFixes(dpy, win, gc[0], frag, nfrag);
  return(nfrag);
}

int widewin() {
  int w, h;
  XWindowAttributes attr;
  XGetWindowAttributes(dpy, win, &attr);
  w = fragmaxix(ftmp); 
  h = fragmaxiy(ftmp);
  if((w < attr.width) && (h < attr.height)) return(0);
  if(w < attr.width) w = attr.width;
  if(h < attr.height) h = attr.height;
  XResizeWindow(dpy, win, w, h); 
  return(0);
}

int cancet() {
  int i;
  if(tinyfrag(ftmp) > 0) return(1);
  return(0);
}

int fix(XEvent* ev) {
  int w, h;
  XUngrabPointer(dpy, CurrentTime);
  if(ev->xbutton.button != Button1) return(nfrag);
  //if(!building) return(nfrag);
  //building = 0;
  fragvar(ftmp, ev->xbutton.x, ev->xbutton.y);
  XContour(dpy, win, gc[RGC], ftmp);
  XFlush(dpy);
  if(cancet() > 0) return(0);
  widewin(w, h);
  frag = realloc(frag, (nfrag + 1)*FRAGSIZ);
  memcpy((frag+nfrag), ftmp, FRAGSIZ);
  ++nfrag;
  return(nfrag);
}

int miniwin() {
  XSizeHints hint;
  int i=0;
  unsigned w=128;
  unsigned h=128;
  int xm, ym;
  for(i=0; i < nfrag; i++) {
    if((xm = fragmaxix(frag+i)) > w) w = xm;
    if((ym = fragmaxiy(frag+i)) > h) h = ym;
  }
  hint.min_width = w; hint.min_height = h;
  hint.flags = PMinSize;
  XSetNormalHints(dpy, win, &hint);
  return(0);
} 
