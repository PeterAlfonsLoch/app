#pragma once


#define sp(TYPE) ::ca::smart_pointer < TYPE >


// ::ca::null back link to operational system oswindow.h
//
//
//
//
// operational system null/void itself to a windowing service
//
// Curitiba, inha-metro-win-ubuntu-mountain-lion-macos 4 de novembro de 2012
namespace ca
{




   class allocatorsp;


   template < class T >
   class smart_pointer
   {
   public:



      T * m_p;



      smart_pointer();
      smart_pointer(LPARAM lparam);
      smart_pointer(const smart_pointer < T > & t);
      smart_pointer(smart_pointer < T > && t);
      smart_pointer(const allocatorsp & t);
      smart_pointer(allocatorsp && t);
      smart_pointer(T * p);
      smart_pointer(void * p);
      smart_pointer(const ::ca::null &);
      template < class T2 >
      smart_pointer(T2 * p)
      {
         m_p = dynamic_cast < T * > (p);
         if(m_p != ::null()) ::ca::add_ref(p);
      }

      template < class T2 >
      smart_pointer(const T2 * p)
      {
         m_p = dynamic_cast < T * > ((T2 *) p);
         if(m_p != ::null()) ::ca::add_ref(p);
      }

      template < class T2 >
      smart_pointer(const smart_pointer < T2 > & t)
      {
         m_p = ::null();
         operator = (dynamic_cast < T * >(t.m_p));
      }
      template < class T2 >
      smart_pointer(smart_pointer < T2 > && t)
      {
         if(t.m_p != ::null())
         {
            m_p = dynamic_cast < T * >(t.m_p);
            if(m_p != ::null())
            {
               t.m_p = ::null();
            }
         }
         else
         {
            m_p = ::null();
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
      inline operator LPARAM ();
      inline operator LPARAM () const;
      //inline operator void * ();
      //inline operator void * () const;

      inline bool is_null() const;
      inline bool is_set() const;

      inline smart_pointer & operator = (T * p);
      inline smart_pointer & operator = (const smart_pointer < T > & t);
      inline smart_pointer & operator = (smart_pointer < T > && t);
      inline smart_pointer & operator = (const ::ca::null &);
      inline smart_pointer & operator = (LPARAM);
      inline smart_pointer & operator = (void *);

      template < class T2 >
      inline smart_pointer & operator = (const smart_pointer < T2 > & t)
      {
         return operator = (dynamic_cast < T * > (t.m_p));
      }

      template < class T2 >
      inline smart_pointer & operator = (smart_pointer < T2 > && t)
      {
         T * pOld = m_p;
         if(t.m_p != ::null())
         {
            m_p = dynamic_cast < T * >(t.m_p);
            if(m_p != ::null())
            {
               t.m_p = ::null();
            }
         }
         else
         {
            m_p = ::null();
         }
         if(pOld != ::null())
         {
            ::ca::release(pOld);
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
      bool operator ==(const ::ca::null &) const { return m_p == (T *) 0; }
      bool operator !=(const ::ca::null &) const { return m_p != (T *) 0; }



      void oattrib(const sp(T) & o);


      sp(T) clone() const;
      void create(allocatorsp allocer);




   };


} // namespace ca














