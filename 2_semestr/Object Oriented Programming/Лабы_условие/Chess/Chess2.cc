// Check fairy chess 2 Figure can attack 
// Plus (+) 1 ortogonal square
// Cross (x) 1 diagonal square
// Print White safety move with Black input 

#include <iostream>
#include <ios>
  using std::cout;
 
  class Figure { // Any chessman class 
    protected:
      char pos[2]; // board position [a-h][1-8]
   public:
    Figure(char*);                 // Figure pos constructor
    Figure() {};                   // to multy inherit
     virtual int attack(char*) = 0; // pure attack
     virtual char isa() = 0;        // virtual type
	operator char*();              // convert to get position
     static int deskout(char*);     // check desk out
     Figure& dodge(Figure*);        // scan desk to safety move
     int repos(char*);              // move to pos
     int city(char*);               // distance to pos
     Figure& operator=(char*);      // as repos
    int operator!=(char*);         // no busy pointed position
    int operator==(char*);         // busy pointed position
    friend std::ostream& operator<<(std::ostream&, Figure&);    //
    friend std::istream& operator>>(std::istream&, Figure&);    //
}; // Figure

class Plus : public Figure { // fairy chess Plus (+) class
  public:
    Plus(char* p) : Figure(p) {};
    Plus() {};
    virtual char isa() { return 'P'; };
     virtual int attack(char*);
 }; // Plus
 
 class Star : public Figure { // fairy chess Star (x) class
   public:
    Star(char* p) : Figure(p) {};
     Star() {};
     virtual char isa() { return 'S'; };
     virtual int attack(char*);
 }; // Star
 
// Figure constructor

 Figure::Figure(char* p) {
 pos[0] = p[0]; pos[1] = p[1]; 
 } // Figure
 
// Covert Figure to char* position

 Figure::operator char*() {
 return(pos);
} // char*
 
// this reposition

 int Figure::repos(char* p) {
 pos[0] = p[0]; pos[1] = p[1];
return(0);
 } // repos
 
// operator this reposition

 Figure& Figure::operator=(char* p) {
 pos[0] = p[0]; pos[1] = p[1];
 return(*this);
 } // operator=

// check distance in city-block metric

 int Figure::city(char* p) {
 int dx, dy;
 if((dx = pos[0] - p[0]) < 0)
  dx = -dx;
 if((dy = pos[1] - p[1]) < 0)
   dy = -dy;
 return(dx + dy);
 } // city
 
// Scan desk squares for this to dodge from other

 Figure& Figure::dodge(Figure* f) {
 char s[2];             // current square
 char p[2];             // best safety square
 char q[2];             // any attacked (possible danger) square
 short d;               // distance from square to other figure
 short dm = 16;         // min distance (max dm=0, if need retire )
 short i,j;             // desk horison & vertical indexs
 p[0] = p[1] = 0;       // purge safety square
 for(i=8; i > 0; i--) {         // desk horison scan
   s[1] = '0' + i;              // new square by horison
   for(j=0; j < 8; j++) {       // desk vertical scan
     s[0] = 'a' + j;            // new square by vertical
     if(*this == s)             // ignore square busy by this
       continue;
     if(!attack(s))             // ignore no this attack square
       continue;
     q[0] = s[0]; q[1] = s[1];  // fix this attacked square 
     if(f->attack(s))           // other figure attack square
       continue;
     if((d = f->city(s)) > dm)  // safety come to other figure
       continue;                // (< dm, if retire from other) 
     dm = d; p[0] = s[0]; p[1] = s[1]; // fix better square
 } // for-j
 } // for-i
 *this = p[0] ? p : q;         // move safety or danger square
 return(*this);
 } // Figure::dodge

// Check Figure busy pointed position

 int Figure::operator==(char* p) {
 return((pos[0] == p[0]) && (pos[1] == p[1]));
 } // operator==
 
// Check Figure no busy pointed position 

 int Figure::operator!=(char* p) {
 return((pos[0] != p[0]) || (pos[1] != p[1]));
} // operator!=
 
// Print Figure name & position by chess notation

 std::ostream& operator<<(std::ostream& out, Figure& f) {
 return(out << f.isa() << f.pos[0] << f.pos[1]);
 } // operator<<

// Input Figure position by chess notation

std::istream& operator>>(std::istream& in, Figure& f) {
 char s[2];           // to new position control
in.unsetf(std::ios::skipws); // veto input spaces
 in >> s[0] >> s[1];  // input position
 in.ignore(64, '\n'); // purge more 2 char input
 if((f.attack(s) == 0) || (f == s)) // move control
   in.clear(std::ios::failbit | in.rdstate()); // set fail state
 f = s; // f.repos(s);
return in;
 } // operator>>

// Check position out from the desk
 int Figure::deskout(char* p) {
 return((p[0] > 'h') || (p[0] < 'a') || (p[1] < '1') || (p[1] > '8'));
 } // deskout

// Plus attack square *p (as King ortogonal only: + )

 int Plus::attack(char* p) {
 if(deskout(p) > 0)      // control pointed position
   return(0);            // square outside the desk
 int x = p[0] - pos[0];  // alpha shift by row
 int y = p[1] - pos[1];  // digit shift by col
 if(x < 0) x = -x;       // abs delta by x
 if(y < 0) y = -y;       // abs delta by y
if((x + y) < 2)         // this attack to p
  return(1);
return(0);     
} // Plus::attack

// Star attack square *p (as King diagonal only: x)

int Star::attack(char* p) {
if(deskout(p) > 0)      // control pointed position
  return(0);            // square outside the desk
int x = p[0] - pos[0];  // alpha shift by row
int y = p[1] - pos[1];  // digit shift by col
if(x < 0) x = -x;       // abs delta by x
if(y < 0) y = -y;       // abs delta by y
if(((x + y) > 2) || ( x != y))  
 return(0);             // this no attack to p
return(1);              // this attack to p 
} // Star::attack

// main function 

int main(int argc, char* argv[]) {
int a=0;                      // attack result
int i = (argc < 3) ? 2 : 0;   // figure index
Figure* f[2] = { NULL, NULL}; // figure address
Plus p[2];  // Plus instanse for white[0] & black[1]
Star s[2];  // Star instanse for white[0] & black[1]
char* v;                      // argument address
for( ; i < 2; i++) { // init parser
  v = argv[i+1];     // cosmetic assigment
  if((*v != p->isa()) && (*v != s->isa())) { // type control 
    cout << "Unknown Figure " << *v << "\n";
    continue;
  } // if
  if(Figure::deskout(v+1)) { // check figure desk position
    cout << "Unboard Position " << v << "\n";
    continue;
  } // if
  if(*v == p[i].isa())  // Plus init position & color
    f[i] = &(p[i] = (v+1));
  if(*v == s[i].isa())  // Star init position & color
    f[i] = &(s[i] = (v+1));
} // for
if((f[0] == NULL) || (f[1] == NULL)) {
  cout << "Usage example: chess2 Pa1 Sh8" << "\n";
  return(1);
} // if
while((a = f[0]->attack(*f[1])) == 0) { // party moves
  cout << f[0]->dodge(f[1]) << ' '; // white move
  cout << f[1]->isa();              // black query
  if((std::cin >> *f[1]) == 0)      // black move
    break;
} // while
if(a) // white capture black
  cout << *f[0] << ':' << *f[1] << std::endl;
return(0);
} // main
