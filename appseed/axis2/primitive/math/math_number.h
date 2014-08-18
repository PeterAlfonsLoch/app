#pragma once



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

   inline c_number(const string & str)
   {
      from(str);
   }

   inline operator T &()
   {
      return m_number;
   }

   inline operator const T &() const
   {
      return m_number;
   }

   inline c_number < T > & from(const string & str);

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

   inline void set_maximum()
   {
      m_number = max_value();
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











#ifdef WINDOWS


#define DEFINE_C_NUMBER(e, ca, T) \
   class e ca : \
      public c_number < T > \
   { \
   public: \
      ca() \
      { \
      } \
      \
      ca(const ca & ca) : \
         c_number < T > ((const c_number < T > &) ca) \
      { \
      } \
      \
      ca(char ch) : \
         c_number < T > (throw_cast < T > (ch)) \
      { \
      } \
      \
      ca(uchar uch) : \
         c_number < T > (throw_cast < T > (uch)) \
      { \
      } \
      \
      ca(int16_t sh) : \
         c_number < T > (throw_cast < T > (sh)) \
      { \
      } \
      \
      ca(uint16_t uint16_t) : \
         c_number < T > (throw_cast < T > (uint16_t)) \
      { \
      } \
      \
      ca(int32_t i) : \
         c_number < T > (throw_cast < T > (i)) \
      { \
      } \
      \
      ca(uint32_t ui) : \
         c_number < T > (throw_cast < T > (ui)) \
      { \
      } \
      \
      ca(int64_t i64) : \
         c_number < T > (throw_cast < T > (i64)) \
      { \
      } \
      \
      ca(uint64_t ui64) : \
         c_number < T > (throw_cast < T > (ui64)) \
      { \
      } \
      \
      ca(float f) : \
         c_number < T > (throw_cast < T > (f)) \
      { \
      } \
      \
      ca(double d) : \
         c_number < T > (throw_cast < T > (d)) \
      { \
      } \
      \
   };

#else

#define DEFINE_C_NUMBER(e, ca, T) \
   class e ca : \
      public c_number < T > \
   { \
   public: \
      ca() \
      { \
      } \
      \
      ca(const ca & ca) : \
         c_number < T > ((const c_number < T > &) ca) \
      { \
      } \
      \
      ca(char ch) : \
         c_number < T > (throw_cast < T > (ch)) \
      { \
      } \
      \
      ca(uchar uch) : \
         c_number < T > (throw_cast < T > (uch)) \
      { \
      } \
      \
      ca(int16_t i) : \
         c_number < T > (throw_cast < T > (i)) \
      { \
      } \
      \
      ca(uint16_t ui) : \
         c_number < T > (throw_cast < T > (ui)) \
      { \
      } \
      \
      ca(int32_t i) : \
         c_number < T > (throw_cast < T > (i)) \
      { \
      } \
      \
      ca(uint32_t ui) : \
         c_number < T > (throw_cast < T > (ui)) \
      { \
      } \
      \
      ca(int64_t i) : \
         c_number < T > (throw_cast < T > (i)) \
      { \
      } \
      \
      ca(uint64_t ui) : \
         c_number < T > (throw_cast < T > (ui)) \
      { \
      } \
      \
      ca(float f) : \
         c_number < T > (throw_cast < T > (f)) \
      { \
      } \
      \
      ca(double d) : \
         c_number < T > (throw_cast < T > (d)) \
      { \
      } \
      \
   };


#endif

//#ifdef WINDOWS
DEFINE_C_NUMBER(CLASS_DECL_AXIS, os_lock_duration, uint32_t)
//#endif

//DEFINE_C_NUMBER(CLASS_DECL_AXIS, file_size        , uint64_t)
//DEFINE_C_NUMBER(CLASS_DECL_AXIS, file_position    , uint64_t)
//DEFINE_C_NUMBER(CLASS_DECL_AXIS, file_offset      ,  int64_t)


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

namespace numeric_info
{

   template < typename T > class CLASS_DECL_AXIS offset < ::c_number < T > > { public: typedef typename ::numeric_info::offset < T >::TYPE TYPE; };
   template < typename T > class CLASS_DECL_AXIS type   < ::c_number < T > > { public: typedef typename ::numeric_info::type   < T >::TYPE TYPE; };

}

