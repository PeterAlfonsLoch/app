#pragma once


template < class T >
class thread_pointer :
   public thread_data
{
public:

   inline operator T *() { return (T *)get(); }
   inline T * operator ->() { return operator T *(); }
   inline thread_pointer & operator = (T * pt) { set(pt); return *this; }

};


template < class T >
class thread_int_ptr :
   public thread_data
{
public:

   operator T () { return (T)(int_ptr)get(); }
   thread_int_ptr & operator = (T t) { set((void *)(int_ptr)t); return *this; }

   bool operator == (int_ptr i)
   {
      return ((int_ptr)get()) == i;
   }

};

template < class T >
class thread_object :
	public thread_data
{
public:

	inline operator T *() { if (get() == NULL) { set(new T()); } return (T *)get(); }
	inline T * operator ->() { return operator T *(); }

};



