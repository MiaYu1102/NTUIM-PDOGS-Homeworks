#include <bits/stdc++.h>
using namespace std;

// ===========================================================================
// class definition of MyVector
class MyVector
{
friend const MyVector operator+(const MyVector& v, double d);
private:
  int n; 
  double* m; 
public:
  MyVector();
  MyVector(int n, double m[]);  
  MyVector(const MyVector& v);
  ~MyVector();
  void print() const; 
  
  bool operator==(const MyVector& v) const;
  bool operator==(double d) const;
  bool operator!=(const MyVector& v) const;
  bool operator<(const MyVector& v) const;
  double operator[](int i) const;
  double& operator[](int i);
  const MyVector& operator=(const MyVector& v);
  const MyVector& operator+=(const MyVector& v);

  const MyVector operator-() const;
};
// end of class definition of MyVector

// global function headers
const MyVector operator+(const MyVector& v, double d);
const MyVector operator+(double d, const MyVector& v);
const MyVector operator+(const MyVector& v1, const MyVector& v2);

bool operator==(double d, const MyVector& v);




// MyVector's instance functions
MyVector::MyVector(): n(0), m(NULL) 
{
}
MyVector::MyVector(int n, double m[])
{
  this->n = n;
  this->m = new double[n];
  for(int i = 0; i < n; i++)
    this->m[i] = m[i];
}
MyVector::MyVector(const MyVector& v)
{
  this->n = v.n;
  this->m = new double[n];
  for(int i = 0; i < n; i++)
    this->m[i] = v.m[i];	
}
MyVector::~MyVector() 
{ 
  delete [] m; 
}
void MyVector::print() const 
{
  cout << "(";
  for(int i = 0; i < n - 1; i++)
    cout << m[i] << ", ";
  cout << m[n-1] << ")\n";
}
// end of MyVector's instance functions

// MyVector's overloaded operators

bool MyVector::operator==(const MyVector& v) const
{
  if(this->n != v.n)
    return false;
  else
  {
    for(int i = 0; i < n; i++)
    {
      if(this->m[i] != v.m[i])
      return false;
    }
  }	
  return true;
}

bool MyVector::operator==(double d) const
{
    for(int i = 0; i < n; i++)
    {
      if(abs(this->m[i]- d)>0.00001) return false;
    }
    return true;
}

bool operator==(double d, const MyVector& v)
{
    return (v==d);
}

bool MyVector::operator!=(const MyVector& v) const
{
  return !(*this == v);
}
bool MyVector::operator<(const MyVector& v) const
{
  if(this->n != v.n)
    return false;
  else
  {
  	for(int i = 0; i < n; i++)
  	{
  	  if(this->m[i] >= v.m[i])
  	    return false;
  	}
  }	
  return true;
}
double MyVector::operator[](int i) const
{
  if(i < 0 || i >= n)
    exit(1);
  return m[i];
}
double& MyVector::operator[](int i) 
{
  if(i < 0 || i >= n)
    exit(1);
  return m[i];
}
const MyVector& MyVector::operator=(const MyVector& v)
{
  if(this != &v)
  {
    if(this->n != v.n)
    {
      delete [] this->m;
      this->n = v.n;
      this->m = new double[this->n];
    }
    for(int i = 0; i < n; i++)
      this->m[i] = v.m[i];
  }  
  return *this;
}
const MyVector& MyVector::operator+=(const MyVector& v)
{
  if(this->n == v.n)
  {
    for(int i = 0; i < n; i++)
      this->m[i] += v.m[i]; 
  }
  return *this;
}

// end of MyVector's overloaded operators

// global functions
const MyVector operator+(const MyVector& v, double d)
{
  MyVector sum(v);
  for(int i = 0; i < v.n; i++)
    sum[i] += d;
  return sum;
}
const MyVector operator+(double d, const MyVector& v)
{
  return v + d;
}
const MyVector operator+(const MyVector& v1, const MyVector& v2)
{
  MyVector sum(v1); 
  sum += v2;
  return sum;
}
const MyVector MyVector::operator-() const
{
    MyVector negat(*this);
    for(int i = 0; i < n; i++)
      negat.m[i]=-(negat.m[i]);
    return negat;
}
// end of global functions
// ===========================================================================

int main(){
    double d = 1.23;
    double m[3] = {d,d,d+1};
    MyVector v(3,m);
    if(v == d) cout<<"yes";
    else cout<<"no";

    return 0;
}