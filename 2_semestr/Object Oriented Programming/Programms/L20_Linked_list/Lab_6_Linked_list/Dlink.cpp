#include "Dlink.h"


Dlink::Dlink()
{
	_next = NULL;
	_prev = NULL;
}


Dlink* Dlink::after(Dlink* p)
{
	p->_next = _next;
	p->_prev = this;
	if (_next != NULL) {
		_next->_prev = p;
	}
	_next = p;
	return p->_next;
}


Dlink* Dlink::before(Dlink* p)
{
	p->_next = this;
	p->_prev = _prev;
	if (_prev != NULL) {
		_prev->_next = p;
	}
	_prev = p;
	return p->_prev;
}


Dlink * Dlink::get_next()
{
	return _next;
}


Dlink * Dlink::get_prev()
{
	return _prev;
}


void Dlink::exclusion()
{
	if (_next != NULL)
		_next->_prev = _prev;
	if (_prev != NULL)
		_prev->_next = _next;
}

