#pragma once


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




   template < class T >
   raw_smart_pointer < T > ::raw_smart_pointer()
   {
      m_p = ::null();
   }


   template < class T >
   raw_smart_pointer < T > ::raw_smart_pointer(const raw_smart_pointer < T > & t)
   {
      m_p = ::null();
      operator = (t);
   }

   template < class T >
   raw_smart_pointer < T > ::raw_smart_pointer(raw_smart_pointer < T > && t)
   {
      
      m_p      = t.m_p;
      t.m_p    = ::null();

   }




   template < class T >
   raw_smart_pointer < T > ::raw_smart_pointer(const ::ca::null &)
   {
      m_p = ::null();
   }


   template < class T >
   raw_smart_pointer < T > ::raw_smart_pointer(T * p)
   {
      m_p = ::null();
      operator = (p);
   }

   template < class T >
   raw_smart_pointer < T > ::~raw_smart_pointer()
   {
      release();
   }

   template < class T >
   inline T * raw_smart_pointer < T > ::operator ->()
   {
      return m_p;
   }

   template < class T >
   inline T * raw_smart_pointer < T > ::operator ->() const
   {
      return m_p;
   }

   template < class T >
   inline raw_smart_pointer < T > ::operator T & ()
   {
      return *m_p;
   }

   template < class T >
   inline raw_smart_pointer < T > ::operator T & () const
   {
      return *m_p;
   }

   template < class T >
   inline raw_smart_pointer < T > ::operator T * const ()
   {
      return m_p;
   }

   template < class T >
   inline raw_smart_pointer < T > ::operator T * const () const
   {
      return m_p;
   }

   template < class T >
   inline T * raw_smart_pointer < T > ::get_()
   {
      return m_p;
   }

   template < class T >
   inline const T * raw_smart_pointer < T > ::get_() const
   {
      return m_p;
   }

   template < class T >
   inline bool raw_smart_pointer < T > ::is_null() const
   {
      return m_p == ::null();
   }

   template < class T >
   inline bool raw_smart_pointer < T > ::is_set() const
   {
      return m_p != ::null();
   }

   template < class T >
   inline raw_smart_pointer < T > & raw_smart_pointer < T > ::operator = (T * p)
   {
      if(m_p != p)
      {
         T * pOld = m_p;
         if(p != ::null())
         {
            ::ca::add_ref(p);
         }
         m_p = p;
         if(pOld != ::null())
         {
            ::ca::release(pOld);
         }
      }
      return *this;
   }

   template < class T >
   inline raw_smart_pointer < T > & raw_smart_pointer < T > ::operator = (const raw_smart_pointer < T > & t)
   {
      return operator = (t.m_p);
   }

template < class T >
   inline raw_smart_pointer < T > & raw_smart_pointer < T > ::operator = (raw_smart_pointer < T > && t)
   {
      
      if(&t != this)
      {

         m_p      = t.m_p;
         t.m_p    = ::null();

      }

      return *this;

   }

   template < class T >
   inline raw_smart_pointer < T > & raw_smart_pointer < T > ::operator = (const ::ca::null & )
   {

      if(is_set())
         release();
      
      return * this;

   }


   template < class T >
   inline T * raw_smart_pointer < T > ::detach()
   {
      T * p = m_p;
      m_p = ::null();
      return p;
   }


   template < class T >
   smart_pointer < T > ::smart_pointer(::ca::applicationsp & papp)
   {
      m_p = ::null();
      create(papp);
   }


   template < class T >
   void smart_pointer < T > ::oattrib(const sp(T) & p)
   {
      if(p.m_p == ::null())
      {
         release();
         return;
      }
      if(is_null())
         create(p->get_app());
      *m_p = *p.m_p;
   }

} // namespace ca


