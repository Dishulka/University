#include <cstdio>
#include <cstdlib>
#include <cctype>
#include "Dlink.h"
using namespace std;


class SymLink : public Dlink
{
private:
	unsigned char _sym;
public:
	SymLink(unsigned char ch) : Dlink(), _sym(ch) {};
	void print();
	unsigned char getsym() { return _sym; };
	SymLink* get_next() { return (SymLink*)Dlink::get_next(); };
	SymLink* get_prev() { return (SymLink*)Dlink::get_prev(); };
};


void SymLink::print()
{
	SymLink* p = this;
	p = (SymLink*)p->_next;

	printf("Link:\n");
	while ((p->_next) != NULL)
	{
		printf("%c", p->_sym);
		p = (SymLink*)p->_next;
	}
	printf("\n");
}


int main()
{
	SymLink* head;
	SymLink* tail;
	SymLink* sep;

	head = new SymLink('\n');
	tail = new SymLink('\n');
	sep = tail;

	tail->before(head);

	SymLink* p;
	unsigned char ch;
	int len = 0;
	printf("Input string and click enter:\n");
	while ((ch = getchar()) != '\n')
	{
		if (isalnum(ch) || ispunct(ch))
		{
			p = new SymLink(ch);
			sep->before(p);
			++len;
		}
		else
			printf("\"%c\" is not correct symbol.\n", ch);
	}

	p = head->get_next();
	int countNum = 0, countPunct = 0;
	for (int i = 0; i < len; ++i)
	{
		ch = p->getsym();
		if (isdigit(ch))
		{
			SymLink* q;
			q = p;
			p = p->get_next();
			q->exclusion();
			sep->before(q);
			++countNum;
		}
		else if (ispunct(ch))
		{
			SymLink* q;
			q = p;
			p = p->get_next();
			q->exclusion();
			tail->before(q);
			if (!countPunct)
				sep = q;
			++countPunct;
		}
		else
			p = p->get_next();
	}

	head->print();

	if ((len - countNum - countPunct) > 0)
		printf("^");
	if (countNum != 0)
		printf("%*c", (len - countNum - countPunct), '^');
	if (countPunct != 0)
		printf("%*c", (countNum > 0) ? (countNum) : (len - countPunct), '^');
	printf("\n");

	SymLink* q;
	p = tail;
	while (p != NULL)
	{
		q = p->get_prev();
		p->exclusion();
		delete p;
		p = q;
	}


	return 0;
}