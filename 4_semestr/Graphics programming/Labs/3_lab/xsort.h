typedef union {
  XSegment seg[1];
  XRectangle rec[1];
  XArc arc[1];
} XFragment; 

#define NGC 16
#define FGC 5
#define RGC 2
#define BGC 1

#define MINSIZEX 4
#define MINSIZEY 4

#define STARTSIZEX 640
#define STARTSIZEY 480

int pass1(Display*, Window, GC*);   
int rubin(XEvent*);
int rubout(XEvent*);
int rerub(XEvent*);
int fix(XEvent*);
int widewin();
int miniwin();
int refrag();
int near(int, int);
int cancet();
int reggc(int);

int fragon(XFragment*, int, int, int);
int difrag(XFragment*, XFragment*);
int tinyfrag(XFragment*);
int fragsize(XFragment*);
int frag0(XFragment*, int, int);
int fragvar(XFragment*, int, int);
int fragmaxix(XFragment*);
int fragmaxiy(XFragment*);
int fragover(XFragment*, XFragment*);

int XFixes(Display*, Window, GC, XFragment*, int);
int XContour(Display*, Window, GC, XFragment*);
int XFix(Display*, Window, GC, XFragment*, GC);

int resmng(int, char*[]);
int canvas();
int gcing();
int dispatch();
int rekey(XEvent*);
