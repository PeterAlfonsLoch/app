#pragma once


#define sp(TYPE) ::c::smart_pointer < TYPE >


namespace ca
{


      class allocatorsp;


} // namespace ca


// ::ca::null_class back link to operational system oswindow.h
//
//
//
//
// operational system NULL/void itself to a windowing service
//
// Curitiba, inha-metro-win-ubuntu-mountain-lion-macos 4 de novembro de 2012
namespace c
{




   template < class T >
   class smart_pointer
   {
   public:



      T * m_p;



      smart_pointer();
      smart_pointer(int32_t i);
      smart_pointer(int64_t i);
      smart_pointer(lparam lparam);
      smart_pointer(const smart_pointer < T > & t);
      smart_pointer(smart_pointer < T > && t);
      smart_pointer(const ::ca::allocatorsp & t);
      smart_pointer(::ca::allocatorsp && t);
      smart_pointer(T * p);
      smart_pointer(void * p);
      template < class T2 >
      smart_pointer(T2 * p)
      {
         m_p = dynamic_cast < T * > (p);
         if(m_p != NULL) ::c::add_ref(p);
      }

      template < class T2 >
      smart_pointer(const T2 * p)
      {
         m_p = dynamic_cast < T * > ((T2 *) p);
         if(m_p != NULL) ::c::add_ref(p);
      }

      template < class T2 >
      smart_pointer(const smart_pointer < T2 > & t)
      {
         m_p = NULL;
         operator = (dynamic_cast < T * >(t.m_p));
      }
      template < class T2 >
      smart_pointer(smart_pointer < T2 > && t)
      {
         if(t.m_p != NULL)
         {
            m_p = dynamic_cast < T * >(t.m_p);
            if(m_p != NULL)
            {
               t.m_p = NULL;
            }
         }
         else
         {
            m_p = NULL;
         }
      }
      ~smart_pointer();


      inline T * operator ->();
      inline T * operator ->() const ;
      inline operator T & ();
      inline operator T & () const ;
      inline operator T * const ();
      inline operator T * const () const;
      inline T * get_();
      inline const T * get_() const;
      inline operator lparam ();
      inline operator lparam () const;
      //inline operator void * ();
      //inline operator void * () const;

      inline bool is_null() const;
      inline bool is_set() const;

      inline smart_pointer & operator = (T * p);
      inline smart_pointer & operator = (const smart_pointer < T > & t);
      inline smart_pointer & operator = (smart_pointer < T > && t);
      inline smart_pointer & operator = (lparam);
      inline smart_pointer & operator = (void *);
      inline smart_pointer & operator = (int32_t i);
      inline smart_pointer & operator = (int64_t i);

      template < class T2 >
      inline smart_pointer & operator = (const smart_pointer < T2 > & t)
      {
         return operator = (dynamic_cast < T * > (t.m_p));
      }

      template < class T2 >
      inline smart_pointer & operator = (smart_pointer < T2 > && t)
      {
         T * pOld = m_p;
         if(t.m_p != NULL)
         {
            m_p = dynamic_cast < T * >(t.m_p);
            if(m_p != NULL)
            {
               t.m_p = NULL;
            }
         }
         else
         {
            m_p = NULL;
         }
         if(pOld != NULL)
         {
            ::c::release(pOld);
         }
         return *this;
      }

      void release();
      inline T * detach();


      template < class T2 >
      inline T2 * cast()
      {
         return dynamic_cast < T2 * > (m_p);
      }

      template < class T2 >
      inline T2 * cast() const
      {
         return dynamic_cast < T2 * > (m_p);
      }


//      bool operator ==(const smart_pointer & p) const { return m_p == p.m_p; }
//      bool operator !=(const smart_pointer & p) const { return m_p != p.m_p; }
//      bool operator ==(const T * p) const { return m_p == p; }
//      bool operator !=(const T * p) const { return m_p != p; }
      bool operator ==(LPARAM l) const { return m_p == (T *) l; }
      bool operator !=(LPARAM l) const { return m_p != (T *) l; }
      //bool operator ==(void * p) const { return m_p == (T *) p; }
      //bool operator !=(void * p) const { return m_p != (T *) p; }



      void oattrib(const sp(T) & o);


      sp(T) clone() const;
      void create(const ::ca::allocatorsp & allocer);




   };


} // namespace c














