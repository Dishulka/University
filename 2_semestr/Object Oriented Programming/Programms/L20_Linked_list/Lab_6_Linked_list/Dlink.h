#ifndef DLINK
#define DLINK

#include <cstdio>


class  Dlink
{
protected:
	Dlink* _next;
	Dlink* _prev;
public:
	Dlink();
	void exclusion();
	Dlink* after(Dlink*);
	Dlink* before(Dlink*);
	Dlink* get_next();
	Dlink* get_prev();
};


#endif