#pragma once

/*

#define new DEBUG_NEW


#ifdef DEBUG
#define TEMPLATE_TYPE_NEW new(__FILE__ + string(" - ") + typeid(TYPE).name(), __LINE__)
#else
#define TEMPLATE_TYPE_NEW new
#endif


class index_array;


#undef new


#define new TEMPLATE_TYPE_NEW


#ifndef __max
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#define ARRAY_MOVE_SEMANTICS(A) \
      \
   A(A && a) :  \
   element(a.) \
   { \
    \
   m_nGrowBy      = a.m_nGrowBy; \
   m_pData        = a.m_pData; \
   m_nSize        = a.m_nSize; \
   m_nMaxSize     = a.m_nMaxSize; \
   \
   a.m_pData      = NULL; \
   \
   } \
   \
   inline A & A::operator = (A && a)      \
   {                                      \
                                          \
      if(&a != this)                      \
      { \
         destroy(); \
         \
         m_nGrowBy      = a.m_nGrowBy; \
         m_pData        = a.m_pData; \
         m_nSize        = a.m_nSize; \
         m_nMaxSize     = a.m_nMaxSize; \
         \
         a.m_pData      = NULL(); \
         \
      } \
      \
   return *this; \
   \
   } 




// raw array is a special array and should be used with care
// it uses operations like memmove and memcopy to move objects and does not
// call constructors and destructors for the elements
// it is faster than the more generic arrays and is proper for use
// with strict structs and primitive data types

template < typename C >
class const_class_size
{
public:

   sp(C)          m_p;
   ::count        m_c;

   const_class_size(const C * p) : m_p(p), m_c(-1) {}

   const_class_size(const C * p, ::count ca) : m_p(NULL), m_c(ca) {}

   const_class_size(const const_class_size & size) : m_p(size.m_p), m_c(size.m_c) {}

   operator ::count () const
   {
      if(m_c >= 0)
      {
         return m_c;
      }
      else
      {
         return m_p->get_size();
      }

   }


};


template < typename C >
class class_size
{
public:

   sp(C)          m_p;
   ::count        m_c;

   class_size(C * p) : m_p(p), m_c(-1) {}

   class_size(C * p, ::count ca) : m_p(NULL), m_c(ca) {}

   class_size(const class_size & size) : m_p(size.m_p), m_c(size.m_c) {}

   operator ::count () const
   {
      if(m_c >= 0)
      {
         return m_c;
      }
      else
      {
         return m_p->get_size();
      }

   }

   class class_size & operator ++()
   {

      m_p->set_size(m_p->get_size() + 1);

      return *this;

   }

   class class_size & operator --()
   {

      m_p->set_size(m_p->get_size() - 1);

      return *this;

   }


   class class_size operator ++(int)
   {

      class_size size(m_p, m_p->get_size());

      m_p->set_size(m_p->get_size() + 1);

      return size;

   }

   class class_size operator --(int)
   {

      class_size size(m_p, m_p->get_size());

      m_p->set_size(m_p->get_size() - 1);

      return size;

   }



   class class_size & operator +=(::count ca)
   {

      m_p->set_size(m_p->get_size() + ca);

      return *this;

   }

   class class_size & operator -=(::count ca)
   {

      m_p->set_size(m_p->get_size() - ca);

      return *this;

   }

};


*/



