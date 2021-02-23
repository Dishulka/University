#include <iostream>
#include <sstream>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int done = 0;
using namespace std;
namespace con
{
	int comax()
	{
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		return(w.ws_col);
	}

	int romax()
	{
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		return(w.ws_row);
	}

	ostream& ED(ostream& s)
	{
		return s << string("\033[2J");
	}

	ostream& EL(ostream& s)
	{
		return s << string("\033[K");
	}

	class estream
	{
	private:
		string escape;
	public:
		estream(string e) : escape(e) {};
		friend ostream& operator<<(ostream&, estream);
	};

	ostream& operator<<(ostream& s, estream e)
	{
		s << e.escape << flush;
		return s;
	}

	estream CUP(int y, int x)
	{
		ostringstream sout;
		sout << "\033[" << y << ";" << x << "H";
		return estream(sout.str());
	}

	estream SGR(int r)
	{
		ostringstream sout;
		sout << "\033[" << r << "m";
		return estream(sout.str());
	}
}
using con::SGR;
using con::CUP;

void interruptor(int signo)
{
	done = signo;
	return;
}

int kbin()
{
	char buf[512];
	int n = 0;
	int flags = fcntl(0, F_GETFL);
	usleep(1);
	fcntl(0, F_SETFL, flags | O_NONBLOCK);
	n = read(0, buf, 512);
	fcntl(0, F_SETFL, flags /* & ~O_NONBLOCK */);
	return(n);
}

int parser(int n, char** v)
{
	int p = 0;
	int opt;
	while ((opt = getopt(n, v, "-baf")) != EOF)
	{
		switch (opt)
		{
		case 'a': p |= 1;
			break;
		case 'f': p |= 2;
			break;
		case 'b': p |= 4;
			break;
		case '?': break;
		}
	}
	return(p);
}

int usage()
{
	cout << "Usage: E33 -afb" << endl;
	cout << "-a RANDOM ALPHA" << endl;
	cout << "-f RANDOM FOREGROUND" << endl;
	cout << "-b RANDOM BACKGROUND" << endl;
	return(0);
}

int main(int argc, char** argv)
{
	int m;
	if ((argc = parser(argc, argv)) == 0)
		return(usage());
	cout << SGR(30 + 7); // white=7, foreground=30
	cout << SGR(40 + 4); // blue=4, background=40
	cout << SGR(1); // bold=1

	cout << con::CUP(24, 1);
	cout << con::ED << "^C or Enter to exit" << flush;

	cout << con::CUP(23, 1);
	cout << con::romax() << "x" << con::comax() << flush;

	int x, y;
	char a;
	int f, b;
	srand(getpid());
	signal(SIGINT, interruptor);
	a = 32; b = (40 + 4); f = (30 + 7);
	while (done < 1)
	{
		x = rand() % (80 + 1);
		y = rand() % (24 - 1);
		if (argc & 1)
			a = 'A' + rand() % 26;
		if (argc == (2 + 1))
			f = 30 + rand() % 8;
		if (argc & 4)
			b = 40 + rand() % 8;
		cout << SGR(b) << CUP(y, x);
		cout << SGR(f) << a << flush;
		if (kbin() > 0)
			break;
	}

	cout << CUP(24, 1) << SGR(0) << con::EL;

	/* {
	int x, y;
	char a;
	struct termios t[2];
	tcgetattr(0, &t[0]);
	tcgetattr(0, &t[1]);
	t[0].c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSAFLUSH, &t[0]);
	cout << "\033[512;512H" << flush;
	cout << "\033[6n" << flush;
	cin >> a >> a >> y >> a >> x >> a;
	cout << endl << "info:" << y << ';' << x << endl;
	tcsetattr(0, TCSAFLUSH, &t[1]);
	} */
	return(m);
}