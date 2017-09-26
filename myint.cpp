#include<iomanip>
#include <cctype>
#include <cstring>
#include <cmath>
#include <iostream>
#include "myint.h"

using namespace std;

int C2I(char c)
// converts character into integer (returns -1 for error)
{
   if (c < '0' || c > '9')	return -1;	// error
   return (c - '0');				// success
}

char I2C(int x)
// converts single digit integer into character (returns '\0' for error)
{
	if (x < 0 || x > 9)		return '\0';	// error
   return (static_cast<char>(x) + '0'); 	// success
}
MyInt::MyInt(const MyInt& L)
{
	currentSize=L.currentSize;
	Maxsize=L.Maxsize;
	Numlist = new int[L.Maxsize];
	for(int i=0; i<currentSize; i++)
	{
		Numlist[i]= L.Numlist[i];
	}
}
MyInt&MyInt::operator= (const MyInt& L)
{
	if(this != &L)
	{	
		delete [] Numlist; 
		Maxsize=L.Maxsize;
		currentSize=L.currentSize;
		
		Numlist= new int[Maxsize];
		for(int i= 0; i<L.currentSize; i++)
			Numlist[i]=L.Numlist[i];
		
	}
	return*this;
	
}
MyInt::MyInt(int n)
{
	/*uses dynamic allocation to create a variable sized array that holds each tens 
		place in a different array slot */
	unsigned int use;
	unsigned int temp;
	Maxsize=5;
	currentSize=0;
	//if(n>4294967295)
	//{
	//	use = 4294967295;
	//}
	if(n<=0)
	{
		use=0;
		currentSize = 1;
	}
	else 
		use=n;
	
	temp = use;
	while(temp>0)
	{
		temp=temp/10;
		currentSize++;
	}
	
	Numlist=new int[currentSize];
	
	for(int i=0; i<currentSize; i++)
		{
			Numlist[currentSize-i-1]=use%10; 
			use=use/10;
		}
	
	
}

MyInt::MyInt(const char *nstring)
{
	/*sets the array based on the passed in char variable using cstring functions*/
	bool correct= true; 
	
	currentSize=strlen(nstring);
	
	int temp=0;
	
	for(int i=0; i<strlen(nstring); i++) 
	{
		if(!isdigit(nstring[i]))
		{
			
			correct= false;
			
		}
	}
	if(!(correct))
	{
		currentSize=1;
		Numlist= new int [1];
		Numlist[0]='\0';
		correct=false;
	}
		
		else
		{
			currentSize=strlen(nstring);
			Numlist= new int [currentSize];
			for(int i=0; i<(currentSize); i++)
			{
				
				Numlist[i]= C2I(nstring[i]);
			
			}
		}
	
}
MyInt::~MyInt()
/*This destructor function for class Directory
 deallocates the directory's pointer to its entry list.*/
{
	delete [] Numlist;
}
ostream& operator<<(ostream &os, const MyInt &o)
{/*prints out the list of numbers*/
	for(int i=0; i<o.currentSize; i++)
	{
		os<<o.Numlist[i];
		
	}
	return os;
}
istream& operator>>(istream& is, MyInt& ist)
{
	 // fill with null if char gives garbage
	delete [] ist.Numlist;
	ist.Numlist=new int[5];
	ist.Maxsize=5;
	ist.currentSize=0;
	
	is >> std::ws;
		// eats white space
	while(isdigit(is.peek()))
	{
		ist.Numlist[ist.currentSize++] = C2I(is.get());
		if(ist.currentSize== ist.Maxsize)
			ist.Grow();
	}
	
	
	return is;
	
}
MyInt operator+ (const MyInt& x, const MyInt& y)
{
	/*adds the variables by ensuring which ever variable is largest is on top
		so addition is easier.
		then carries the tens place if neccessary while deleting the previous 10*/
	MyInt temp1, temp2, finl;
	int a, b,z;
	if(x >= y)
	{
		temp1 = x;
		temp2 = y;
		
	}
	else
	{
		temp1 = y;
		temp2 = x;
	}
	
	finl=temp1;
	
	int carry =0;
	int tracker1 = 0, tracker2=0;
	for(int i=0; i<temp1.currentSize; i++)
	{
		if(temp1.currentSize-1-i>=0)
		{a=temp1.Numlist[temp1.currentSize-1-i];
		}
		else
			a=0;
		if(temp2.currentSize-1-i>=0)
			b=temp2.Numlist[temp2.currentSize-1-i];
		else
			b=0;
		
			z=a+b+carry;
			if(z>9)
			{
				z=z-10;
				carry= 1;
			}
			else
				carry=0; 
		 finl.Numlist[finl.currentSize-1-i]=z;
		 
	}
	return finl;
}
MyInt operator* (const MyInt& x, const MyInt& y)
{
	MyInt a3;
	MyInt B,S;
	int decimalplace=0 ;
	if(x.currentSize>=y.currentSize)
	{
		
		B= x;
		S= y;
	}
	else
	{
		B=y;
		S=x;
		
	}
	
	for(int t= S.currentSize-1; t>=0;t--)
	{
		for(int z= B.currentSize-1; z>=0; z--)
		{	a3.Numlist[z]+=((S.Numlist[t]*B.Numlist[z])+decimalplace)%10;
			decimalplace=((S.Numlist[t]*B.Numlist[z])+decimalplace)/10;
		}
		if(decimalplace!=0)
		{
			MyInt a4; 
			a4.currentSize=a3.currentSize+1;
			a4.Numlist= new int [a4.currentSize];

			for(int x= a4.currentSize; x>0; x--)
			{
				a4.Numlist[x]=a3.Numlist[x-1];
			}
			a4.Numlist[0]=decimalplace;
			a3=a4;
		}
		
	}
	return a3;
	
}
/*MyInt operator- (const MyInt& x, const MyInt& y)
{
	
}*/
MyInt& MyInt::operator--()
{
	
	
	
}

MyInt MyInt::operator--(int)
{
	
	
	
}
MyInt& MyInt::operator++()
{
	*this = *this + 1;
	return *this;
}
MyInt MyInt::operator++(int)
{
	MyInt temp = *this;
	*this = *this +1;
	return temp;
}	
bool operator< (const MyInt& x, const MyInt& y)
{
	if(x.currentSize<y.currentSize)
	{
		return true;
	}
	else if(x.currentSize==y.currentSize)
	{
		return x.Numlist[x.currentSize-1]<y.Numlist[y.currentSize-1];
		
	}
	else
	{
		return false;
	}
}
bool operator>(const MyInt& x, const MyInt& y)
{
	return y<x;
}
bool operator>=(const MyInt& x, const MyInt& y)
{
	return !(x<y);
}
bool operator<=(const MyInt& x, const MyInt& y)
{
	return !(x>y);
}
bool operator==(const MyInt& x, const MyInt& y)
{
	return((x>=y)&&(x<=y));
		
}
bool operator!=(const MyInt& x, const MyInt& y)
{
	return(!(x==y));
}

 void MyInt::Grow()
   {
		Maxsize = currentSize + 5;			/* Determine a new size.*/
		int * newList = new int[Maxsize];		/*// Allocate a new array.*/
	
			for (int i = 0; i < currentSize; i++)	// /*Copy each entry into*/
				newList[i] = Numlist[i];		// /*the new array.*/
		
			delete [] Numlist;	
					// /*Remove the old array*/
			Numlist= newList;		
   }





