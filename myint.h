// starter file for MyInt class header
#include <iomanip>

using namespace std;
class MyInt
{
   // these overload starters are declared as friend functions
	friend ostream& operator<<(ostream &os, const MyInt &o);
	friend istream& operator>>(istream& is, MyInt& ist);

    friend MyInt operator+ (const MyInt& x, const MyInt& y);
    //friend MyInt operator-(const MyInt&, const MyInt& );
    friend MyInt operator* (const MyInt& x, const MyInt& y);
   // add in multiplication, as well

   friend bool operator< (const MyInt& x, const MyInt& y);
   friend bool operator>=(const MyInt&, const MyInt&);
	friend bool operator<=(const MyInt&, const MyInt&);
	friend bool operator>(const MyInt&, const MyInt&);
	friend bool operator!=(const MyInt&, const MyInt&);
	friend bool operator==(const MyInt&, const MyInt&);
  
   // add in the other comparison overloads, as well

   // declare overloads for input and output (MUST be non-member functions)
   //  you may make them friends of the class

public:
   MyInt(int n = 0);	
   MyInt(const char *);
  ~MyInt();
   
   MyInt(const MyInt &L);
   MyInt& operator=(const MyInt & L);
   void Grow();
   MyInt& operator++();
   MyInt operator++(int);
   MyInt& operator--();
   MyInt operator--(int);// first constructor

   // be sure to add in the second constructor, and the user-defined 
   //  versions of destructor, copy constructor, and assignment operator

private:
	int * Numlist;
	int Maxsize;
	int currentSize;
   // member data (suggested:  use a dynamic array to store the digits)

};
