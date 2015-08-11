//* Dynamic array
// Basic packags: data structure
// Program of Computer Graphics
// Cornell University
// Waldemar Celes
// Feb 1997

#ifndef ps_array_h
#define ps_array_h

#include <string.h>
#include <gpos/defines.h>

//* Dynamic array
// When creating, the client specifies the type of the items
// to be hold. If the type is a user-defined one (i.e., not pointer
// or basic type) be aware that the copy constructor will be used
// each time the array is redimensioned or copied.
template <class TYPE> class RESH_API PSArray
{
 int    d_nmax;		// current allocated number of items
 double d_incr;		// increment used to reallocate
 int    d_n;		// current number of items in use
 TYPE*  d_v;		// set of items 

public:

 //* Creators
		//* Array constructor
		// The client can specify a initial dimension (to avoid
		// unnecessary reallocation) and the increasing rate when
		// reallocating. Anyway, the array is dynamic and will never,
		// as long as there is available memory, overflow.
 PSArray(int nmax=4, double incr=2.0) 
 : d_nmax(nmax), d_incr(incr)
 {
  d_n = 0;
  d_v = new TYPE[d_nmax];
 }

		//* Array destructor.
		// The items are not destroyed, only the array is.
 virtual ~PSArray()
 {
  delete [] d_v;
 }


 //* Accessors

		//* Access the i-th item.
 TYPE operator[] (int i) const
 {
  return d_v[i];
 }

		//* Size
		// Gets the number of items currently stored in the array.
 int size (void) const
 { 
  return d_n; 
 }



 //* Manipulators

		//* Get item reference
		// Returns a reference to the i-th item.
 TYPE& operator[] (int i)
 {
  return d_v[i];
 }
		//* Set i-th item.
		// Expands the array if necessary.
 void set (int i, TYPE value)
 {
  while (i>=d_nmax)
   expand();
  if (i>=d_n)
   d_n = i+1;
  d_v[i] = value; 
 } 
		//* Insert a new item into the array
		// If necessary, the array dimension is automatically adjusted.
 int insert (TYPE item, int at=-1)
 {
  if (d_n == d_nmax) expand();
  if (at < 0 || at >= d_n)
   d_v[d_n++] = item;
  else
  {
   for (int i=d_n-1; i>=at; i--)
    d_v[i+1] = d_v[i];
   d_v[at] = item;
   d_n++;
  }
  return d_n-1;
 }

		//* Release the at-th item
		// The item itself is not deleted.
		// Be aware, it is an O(n) operation.
		// Return 0 on failure.
 int erase (int at)
 {
  if (at < 0 || at > d_n-1)
   return 0;
  for(int i=at; i<d_n-1; i++)
   d_v[i] = d_v[i+1];
  d_n--;
  return 1;
 }

		//* CALOMENI
		// Release the given item
		// The item itself is not deleted.
		// O(n) operation.
		// Returns 0 if item not found.
 int erase (TYPE item)
 {
	 for (int i = 0; i < d_n; i++)
	 {
		 if (d_v[i] == item)
		 {
			 erase(i);
			 return 1;
		 }
	 }
	 return 0;
 }

		//* Release all items of the array.
 void empty (void)
 {
  d_n = 0;
 }

		//* Invert the order of items
 void invert (void)
 {
  for (int i=0, j=d_n-1; i<j; i++, j--)
  {
   TYPE t = d_v[i]; d_v[i] = d_v[j]; d_v[j] = t;
  }
 }


private:

		// Expand array, reallocating it.
 void expand (void)
 {
  int nnew = (int)(d_nmax*d_incr) + 1;
  TYPE *vnew = new TYPE[nnew];
  for (int i=0; i<d_nmax; i++)
   vnew[i] = d_v[i];
  delete [] d_v;
  d_v = vnew;
  d_nmax = nnew;
 }

};


#endif

