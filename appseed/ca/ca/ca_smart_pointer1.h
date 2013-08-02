#pragma once


#define sp(TYPE) ::ca::smart_pointer < TYPE >


namespace ca2
{


      class allocatorsp;


} // namespace ca2


// ::ca::null_class back link to operational system oswindow.h
//
//
//
//
// operational system NULL/void itself to a windowing service
//
// Curitiba, inha-metro-win-ubuntu-mountain-lion-macos 4 de novembro de 2012
namespace ca
{




   template < class T >
   class smart_pointer
   {
   public:



      T * m_p;



      smart_pointer();
      smart_pointer(int32_t i);
      smart_pointer(int64_t i);
#ifdef MACOS
#ifdef OS64BIT
      smart_pointer(long l);
#endif
#endif
      smart_pointer(lparam lparam);
      smart_pointer(const smart_pointer < T > & t);
#ifdef MOVE_SEMANTICS
      smart_pointer(smart_pointer < T > && t);
#endif
      smart_pointer(const ::ca2::allocatorsp & t);
#ifdef MOVE_SEMANTICS
      smart_pointer(::ca2::allocatorsp && t);
#endif
      smart_pointer(T * p);
      smart_pointer(void * p);
      template < class T2 >
      smart_pointer(T2 * p)
      {
         m_p = dynamic_cast < T * > (p);
         if(m_p != NULL) ::ca::add_ref(p);
      }

      template < class T2 >
      smart_pointer(const T2 * p)
      {
         m_p = dynamic_cast < T * > ((T2 *) p);
         if(m_p != NULL) ::ca::add_ref(p);
      }

      template < class T2 >
      smart_pointer(const smart_pointer < T2 > & t)
      {
         m_p = NULL;
         operator = (dynamic_cast < T * >(t.m_p));
      }


#ifdef MOVE_SEMANTICS
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
#endif

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
#ifdef MOVE_SEMANTICS
      inline smart_pointer & operator = (smart_pointer < T > && t);
#endif
      inline smart_pointer & operator = (lparam);
      inline smart_pointer & operator = (void *);
      inline smart_pointer & operator = (int32_t i);
      inline smart_pointer & operator = (int64_t i);
#ifdef MACOS
#ifdef OS64BIT
      inline smart_pointer & operator = (long l);
#endif
#endif
      

      template < class T2 >
      inline smart_pointer & operator = (const smart_pointer < T2 > & t)
      {
         return operator = (dynamic_cast < T * > (t.m_p));
      }

#ifdef MOVE_SEMANTICS
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
            ::ca::release(pOld);
         }
         return *this;
      }
#endif

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
      void copy(T * po) { return oattrib(po); }


      sp(T) clone() const;
      void create(const ::ca2::allocatorsp & allocer);




   };


} // namespace ca














