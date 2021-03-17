#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "lab2.h"

static XVertex vertex[NVERT];
static XFace face[(NFACE + 1)];
static XEdge edge[NEDGE];

static XPoint face3[NF3][(3 + 1)];
static XPoint scale;

int assoc(XPolyGraph* pg) {
	pg->vertex = vertex;
	pg->edge = edge;
	pg->face = face;
	return(0);
}

int resize(unsigned w, unsigned h) {
	static XRectangle bak = { 0, 0, 0, 0 };
	if ((bak.width == w) && (bak.height == h))
		return(0);
	bak.width = w; bak.height = h;
	return(NFACE);
}

int rescale(unsigned w, unsigned h) {
	int x, y;
	x = w / NUNIT; y = h / NUNIT;
	if ((scale.x == x) && (scale.y == y))
		return(0);
	scale.x = x; scale.y = y;
	return(NFACE);
}

int rebuild() {
	static XPoint vconf[] = {
	  {1, 11}, {6, 1}, {11, 11}, {6, 7}
	};
	static int fconf3[NF3][(3 + 1)] = {
	  {0, 1, 3, 0},
	  {0, 2, 3, 0},
	  {1, 2, 3, 1},
	};

	static int econf[NEDGE][2] = {
	  {0, 1}, {0, 2}, {0, 3},
	  {1, 2}, {1, 3},
	  {2, 3},
	};
	int i, j;                    
	for (i = 0; i < NVERT; i++) { 
		vertex[i].x = scale.x * vconf[i].x;
		vertex[i].y = scale.y * vconf[i].y;
	} 
	for (i = 0; i < NEDGE; i++) { 
		edge[i].x1 = vertex[econf[i][0]].x;
		edge[i].y1 = vertex[econf[i][0]].y;
		edge[i].x2 = vertex[econf[i][1]].x;
		edge[i].y2 = vertex[econf[i][1]].y;
	} 
	for (i = 0; i < NF3; i++)             
		for (j = 0; j < (3 + 1); j++) {   
			face3[i][j].x = vertex[fconf3[i][j]].x;
			face3[i][j].y = vertex[fconf3[i][j]].y;
		} 
	return(0);
}

int retrace() { /* depending on graph ! */
	int i = 0;  /* total face index */
	int j;    /* n-top face index */
	for (j = 0; j < NF3; j++, i++) {    /* fix 3-top faces in face array */
		face[i].top = face3[j];       /* fix 3-top face array address */
		face[i].Cn = 3;                /* fix 3-top face top number=3 */
		face[i].tone = DEFTONE;        /* set face default tone color */
		face[i].regi = XCreateRegion();      /* Empty region for face */
	} /* face3 */

	return(0);
} /* retrace */

/* Reconfigure graph when window resize & rescale */

int reconf(unsigned w, unsigned h) {
	if (resize(w, h) == 0)
		return(0);
	if (rescale(w, h) != 0)
		rebuild();
	return(NFACE);
}

int zotone(int x, int y) {
	static XPoint past = { 0, 0 }; 
	int f = 0;                  
	if ((past.x == scale.x) && (past.y == scale.y))
		f = NFACE;    
	for (; f < NFACE; f++) {    
		XDestroyRegion(face[f].regi);
		face[f].regi = XPolygonRegion(face[f].top, face[f].Cn, 0);
	} 
	past.x = scale.x;
	past.y = scale.y;          
	for (f = 0; f < NFACE; f++) 
		if (XPointInRegion(face[f].regi, x, y) == True)
			break;
	face[f].tone = (face[f].tone + 1) % NCOLOR;   
	return(f);                  
}