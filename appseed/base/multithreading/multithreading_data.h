#pragma once


template < class T >
class thread_pointer :
   public thread_data
{
public:

   operator T *() { return (T *)get(); }
   T * operator ->() { return operator T *(); }
   thread_pointer & operator = (T * pt) { set(pt); return *this; }

};


template < class T >
class thread_int_ptr :
   public thread_data
{
public:

   operator T () { return (T)(int_ptr)get(); }
   thread_int_ptr & operator = (T t) { set((void *)(int_ptr)t); return *this; }

};




