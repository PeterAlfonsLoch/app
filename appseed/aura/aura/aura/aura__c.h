#pragma once




#ifdef memory_size_t

inline int is_ptr_null(const void * p, memory_size_t s)
{
   return (((int_ptr)p) < s);
}

#endif
