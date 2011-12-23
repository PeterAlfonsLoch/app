#pragma once


#include "primitive/numeric_info.h"


template < typename T >
class c_number
{
public:

   typedef T TYPE;

   T  m_number;

   inline c_number()
   {
      m_number = (T) 0;
   }

   inline c_number(T number)
   {
      m_number = number;
   }

   inline operator T &()
   {
      return m_number;
   }

   inline operator const T &() const
   {
      return m_number;
   }

/*   bool operator == (const c_number & n) const;
   bool operator > (const c_number & n) const;
   bool operator < (const c_number & n) const;
   bool operator >= (const c_number & n) const;
   bool operator <= (const c_number & n) const;
   bool operator != (const c_number & n) const;

   c_number & operator = (const c_number & n);
   c_number & operator += (const c_number & n);
   c_number & operator -= (const c_number & n);*/


   inline static T max_value()
   {
      return ::numeric_info::get_maximum_value < T > ();
   }

   inline static T min_value()
   {
      return ::numeric_info::get_minimum_value < T > ();
   }

   inline static T allset_value()
   {
      return ::numeric_info::get_allset_value < T > ();
   }

};


/*template < typename T >
inline bool c_number<T> ::operator == (const c_number < T > & n) const
{
   return m_number == n.m_number;
}

template < typename T >
inline bool c_number<T> ::operator > (const c_number < T > & n) const
{
   return m_number > n.m_number;
}

template < typename T >
inline bool c_number<T> ::operator < (const c_number < T > & n) const
{
   return m_number < n.m_number;
}

template < typename T >
inline bool c_number<T> ::operator >= (const c_number < T > & n) const
{
   return m_number >= n.m_number;
}

template < typename T >
inline bool c_number<T> ::operator <= (const c_number < T > & n) const
{
   return m_number <= n.m_number;
}

template < typename T >
inline bool c_number<T> ::operator != (const c_number < T > & n) const
{
   return m_number != n.m_number;
}

template < typename T >
inline c_number<T> & c_number<T> ::operator = (const c_number < T > & n)
{
   m_number = n.m_number;
   return *this;
}

template < typename T >
inline c_number<T> & c_number<T> ::operator += (const c_number<T> & n)
{
   m_number += n.m_number;
   return *this;
}

template < typename T >
inline c_number<T> & c_number<T> ::operator -= (const c_number<T> & n)
{
   m_number -= n.m_number;
   return *this;
}

template < typename T >
inline c_number<T> operator + (const c_number<T> & n1, const c_number<T> & n2)
{
   return n1.m_number + n2.m_number;
}

template < typename T >
inline c_number<T> operator - (const c_number<T> & n1, const c_number<T> & n2)
{
   return n1.m_number - n2.m_number;
}

*/











#ifdef _WINDOWS


#define DEFINE_C_NUMBER(e, c, T) \
   class e c : \
      public c_number < T > \
   { \
   public: \
      c() \
      { \
      } \
      \
      c(const c & c) : \
         c_number < T > ((const c_number < T > &) c) \
      { \
      } \
      \
      c(char ch) : \
         c_number < T > (throw_cast < T > (ch)) \
      { \
      } \
      \
      c(unsigned char uch) : \
         c_number < T > (throw_cast < T > (uch)) \
      { \
      } \
      \
      c(short sh) : \
         c_number < T > (throw_cast < T > (sh)) \
      { \
      } \
      \
      c(unsigned short ush) : \
         c_number < T > (throw_cast < T > (ush)) \
      { \
      } \
      \
      c(int i) : \
         c_number < T > (throw_cast < T > (i)) \
      { \
      } \
      \
      c(unsigned int ui) : \
         c_number < T > (throw_cast < T > (ui)) \
      { \
      } \
      \
      c(long l) : \
         c_number < T > (throw_cast < T > (l)) \
      { \
      } \
      \
      c(unsigned long ul) : \
         c_number < T > (throw_cast < T > (ul)) \
      { \
      } \
      \
      c(int64_t i64) : \
         c_number < T > (throw_cast < T > (i64)) \
      { \
      } \
      \
      c(uint64_t ui64) : \
         c_number < T > (throw_cast < T > (ui64)) \
      { \
      } \
      \
      c(float f) : \
         c_number < T > (throw_cast < T > (f)) \
      { \
      } \
      \
      c(double d) : \
         c_number < T > (throw_cast < T > (d)) \
      { \
      } \
      \
   };

#else

#define DEFINE_C_NUMBER(e, c, T) \
   class e c : \
      public c_number < T > \
   { \
   public: \
      c() \
      { \
      } \
      \
      c(const c & c) : \
         c_number < T > ((const c_number < T > &) c) \
      { \
      } \
      \
      c(char ch) : \
         c_number < T > (throw_cast < T > (ch)) \
      { \
      } \
      \
      c(unsigned char uch) : \
         c_number < T > (throw_cast < T > (uch)) \
      { \
      } \
      \
      c(short sh) : \
         c_number < T > (throw_cast < T > (sh)) \
      { \
      } \
      \
      c(unsigned short ush) : \
         c_number < T > (throw_cast < T > (ush)) \
      { \
      } \
      \
      c(int i) : \
         c_number < T > (throw_cast < T > (i)) \
      { \
      } \
      \
      c(unsigned int ui) : \
         c_number < T > (throw_cast < T > (ui)) \
      { \
      } \
      \
      c(int64_t i64) : \
         c_number < T > (throw_cast < T > (i64)) \
      { \
      } \
      \
      c(uint64_t ui64) : \
         c_number < T > (throw_cast < T > (ui64)) \
      { \
      } \
      \
      c(float f) : \
         c_number < T > (throw_cast < T > (f)) \
      { \
      } \
      \
      c(double d) : \
         c_number < T > (throw_cast < T > (d)) \
      { \
      } \
      \
   };


#endif

//#ifdef _WINDOWS
DEFINE_C_NUMBER(CLASS_DECL_ca, os_lock_duration, DWORD)
//#endif

//DEFINE_C_NUMBER(CLASS_DECL_ca, file_size        , uint64_t)
//DEFINE_C_NUMBER(CLASS_DECL_ca, file_position    , uint64_t)
//DEFINE_C_NUMBER(CLASS_DECL_ca, file_offset      ,  int64_t)

typedef uint64_t  file_size;
typedef uint64_t  file_position;
typedef int64_t   file_offset;


namespace primitive
{


#if defined(_M_X64)  // X64


//DEFINE_C_NUMBER(CLASS_DECL_ca, memory_size         , uint64_t)
//DEFINE_C_NUMBER(CLASS_DECL_ca, memory_position     , uint64_t)
//DEFINE_C_NUMBER(CLASS_DECL_ca, memory_offset       ,  int64_t)

typedef uint64_t  memory_size;
typedef uint64_t  memory_position;
typedef int64_t   memory_offset;


#else

//DEFINE_C_NUMBER(CLASS_DECL_ca,   memory_size         , uint32_t)
//DEFINE_C_NUMBER(CLASS_DECL_ca,   memory_position     , uint32_t)
//DEFINE_C_NUMBER(CLASS_DECL_ca,   memory_offset       ,  int32_t)

typedef uint32_t  memory_size;
typedef uint32_t  memory_position;
typedef int32_t   memory_offset;


#endif


} // namespace primitive



/*namespace numeric_info
{


   template <>
   inline file_size get_maximum_value < file_size > ()
   {
      return static_cast < file_size > (0xffffffffffffffff);
   }

   template <>
   inline file_size get_minimum_value < file_size > ()
   {
      return static_cast < uint64_t > (0);
   }

   template <>
   inline file_size get_allset_value < file_size > ()
   {
      return static_cast < file_size > (0xffffffffffffffff);
   }

   template <>
   inline file_size get_null_value < file_size > ()
   {
      return 0;
   }

   template <>
   inline file_size get_unitary_value < file_size >()
   {
      return 1;
   }


} // namespace numeric_info



*/