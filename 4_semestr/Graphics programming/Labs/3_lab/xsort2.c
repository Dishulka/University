#include <X11/Xlib.h>
#include <X11/Xresource.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <string.h>
#include <stdio.h>
#include "xsort.h"

static Display* dpy;
static GC gc[NGC];
static Window win;
    static char* spector[] = {    /* Cпектр кодов (имен) цветов */
			      "#FFFFFF",
                              "#FFDAB9",
                              "#ABCFDE",
                              "#6495ED",
                              "#00BFFF",
                              "#00FFFF",
			      "#006400",
			      "#7CFC00",
			      "#EEE8AA",
			      "#FFFF00",
			      "#CD5C5C",
			      "#D2691E",
			      "#FF0000",
			      "#FF1493",
			      "#FFFFFF"
                             };  
int resmng(int argc, char* argv[]) {
  int scr;
  Window root;
  Colormap cmap;
  XColor rgb, exact;
  int i;
  XrmDatabase rdb=NULL;
  char restype[64];
  char* rtype = restype;
  XrmValue resval;
  XrmValue* rval = &resval;
  static char* rname[] = {
    "xsort.foreground",
    "xsort.rubbground",
    "xsort.background"
  };
  static char* rdef[] = {
    "black",
    "grey",
    "white"
  };
  static XrmOptionDescRec rtab[] = {
    {"-fg ", ".foreground", XrmoptionSepArg, NULL},
    {"-rg ", ".rubbground", XrmoptionSepArg, NULL},
    {"-bg ", ".background", XrmoptionSepArg, NULL},
    {"-xrm ", NULL, XrmoptionResArg, NULL}
  };

  dpy = XOpenDisplay(NULL);
  scr = DefaultScreen(dpy);
  cmap = DefaultColormap(dpy, scr);
  root = DefaultRootWindow(dpy); 

  XrmInitialize();                          
  rdb = XrmGetFileDatabase("xsort.res");
  XrmParseCommand(&rdb, rtab, NGC+1, "xsort", &argc, argv);

  puts("\nColor resources:");
  for(i=0; i < NGC; i++) {
    /*if(XrmGetResource(rdb, rname[i], NULL, &rtype, rval) == False)
      rval->addr = rdef[i];
    if(XParseColor(dpy, cmap, rval->addr, &rgb) == 0)
      if(XLookupColor(dpy, cmap, (rval->addr = rdef[i]), &rgb, &exact) == 0)
        memcpy(&rgb, &exact, sizeof(XColor));
    printf("%s(%s): %s\n", rname[i], rtab[i].option, rval->addr); /* Echo */
    fflush(stdout);
    XAllocColor(dpy, cmap, &rgb);
    XParseColor(dpy, cmap, spector[i], &rgb);
    gc[i] = XCreateGC(dpy, root, 0, 0);
    XSetForeground(dpy, gc[i], rgb.pixel);
    
  }
  if(rdb != NULL) XrmDestroyDatabase(rdb);

  for(i=0; i < NGC; i++) XSetBackground(dpy, gc[i], rgb.pixel);
  return(0);
}

int gcing() {
  XGCValues gval;
  unsigned long gmask = GCLineWidth;
  int i; 
  gval.line_width = 2;
  for(i=0; i < NGC; i++) XChangeGC(dpy, gc[i], gmask, &gval);
  gmask = (GCFunction | GCLineWidth | GCLineStyle);
  gval.line_width = 1;   
  gval.function = GXxor;
  gval.line_style = LineOnOffDash;
  XChangeGC(dpy, gc[RGC], gmask, &gval);
  return(0);
}

int canvas() {
  XSetWindowAttributes attr;
  unsigned long amask;
  unsigned long emask; 
  Window root;
  XGCValues gval;
  XGetGCValues(dpy, gc[BGC], GCBackground, &gval);
  attr.background_pixel = gval.background;
  attr.override_redirect = False;
  attr.bit_gravity = NorthWestGravity;
  amask = (CWOverrideRedirect | CWBackPixel | CWBitGravity);
  root = DefaultRootWindow(dpy);
  win = XCreateWindow(dpy, root, 0, 0, STARTSIZEX, STARTSIZEY, 1, CopyFromParent,
                      InputOutput, CopyFromParent, amask, &attr);
  XStoreName(dpy, win, "xsort");
  emask = (ButtonPressMask | ButtonReleaseMask | Button1MotionMask |
           ExposureMask | KeyPressMask);
  XSelectInput(dpy, win, emask);
  XMapWindow(dpy, win);
  return(0);
}

int rekey(XEvent* ev) {
  KeySym ks = XLookupKeysym((XKeyEvent*) ev, 1);
  if((ks == XK_R) && (ev->xkey.state & ControlMask)) 
  return('R');
  return(0);
}

int dispatch() {
  int done = 0;
  XEvent event;
  while(done == 0) {
    XNextEvent(dpy, &event);
    switch(event.type) {
      case Expose: if(event.xexpose.count > 1) break;
                   refrag();
                   break;
      case ButtonPress:
                        if(rubin(&event) != Button1) rubout(&event);
                        break;
      case MotionNotify: rerub(&event);
                         break;
      case ButtonRelease: fix(&event);
                          refrag();
                          miniwin();
                          break;
      case KeyPress: done = rekey(&event); 
                     break;
      default: break;
    }
  }
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return(0);
}

int main(int argc, char* argv[]) {
  resmng(argc, argv);
  gcing();
  canvas();
  pass1(dpy, win, gc);
  dispatch();
  return(0);
}
