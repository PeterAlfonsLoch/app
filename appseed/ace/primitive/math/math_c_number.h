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
      return ::numeric_info< T >::maximum();
   }

   inline static T min_value()
   {
      return ::numeric_info< T >::minimum();
   }

   inline static T allset_value()
   {
      return ::numeric_info< T >::allset();
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











#define DEFINE_UNIT(e, ca, T) \
   class e ca : \
      public c_number < T > \
   { \
   public: \
      ca() \
      { \
      } \
      \
      ca(const T & ca) : \
         c_number < T > ((const c_number < T > &) ca) \
      { \
      } \
      \
   };


//#ifdef WINDOWS
DEFINE_UNIT(CLASS_DECL_AURA,lock_duration,uint32_t)
DEFINE_UNIT(CLASS_DECL_AURA,tick_duration,uint32_t)
//#endif

//DEFINE_C_NUMBER(CLASS_DECL_AURA, file_size_t        , uint64_t)
//DEFINE_C_NUMBER(CLASS_DECL_AURA, file_position_t    , uint64_t)
//DEFINE_C_NUMBER(CLASS_DECL_AURA, file_offset_t      ,  int64_t)


/*namespace numeric_info
{


   template <>
   inline file_size_t get_maximum_value < file_size_t > ()
   {
      return static_cast < file_size_t > (0xffffffffffffffff);
   }

   template <>
   inline file_size_t get_minimum_value < file_size_t > ()
   {
      return static_cast < uint64_t > (0);
   }

   template <>
   inline file_size_t get_allset_value < file_size_t > ()
   {
      return static_cast < file_size_t > (0xffffffffffffffff);
   }

   template <>
   inline file_size_t get_null_value < file_size_t > ()
   {
      return 0;
   }

   template <>
   inline file_size_t get_unitary_value < file_size_t >()
   {
      return 1;
   }


} // namespace numeric_info



*/

namespace numeric_info_internal
{

   template < typename T >
   class CLASS_DECL_AURA numeric_info < ::c_number < T > > :
   public numeric_info < T >
   {
   public:


   };

}


template < typename T > 
inline ::file::istream &  operator >>(::file::istream & istream, c_number < T > & t)
{
   
   return istream >> t.m_number;

}

template < typename T > 
inline ::file::ostream &  operator <<(::file::ostream & ostream, const c_number < T > & t)
{
   
   return ostream << t.m_number;

}
