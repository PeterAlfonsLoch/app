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
   smart_pointer < T > ::smart_pointer()
   {
      m_p = ::null();
   }


   template < class T >
   smart_pointer < T > ::smart_pointer(const smart_pointer < T > & t)
   {
      m_p = ::null();
      operator = (t);
   }

   template < class T >
   smart_pointer < T > ::smart_pointer(smart_pointer < T > && t)
   {
      
      m_p      = t.m_p;
      t.m_p    = ::null();

   }




   template < class T >
   smart_pointer < T > ::smart_pointer(const ::ca::null &)
   {
      m_p = ::null();
   }


   template < class T >
   smart_pointer < T > ::smart_pointer(T * p)
   {
      m_p = p;
      ::ca::add_ref(m_p);
   }

   template < class T >
   smart_pointer < T > ::smart_pointer(LPARAM lparam)
   {
      m_p = (T *) lparam;
      ::ca::add_ref(m_p);
   }

   template < class T >
   smart_pointer < T > ::smart_pointer(void * p)
   {
      m_p = (T *) p;
      ::ca::add_ref(m_p);
   }
   

   template < class T >
   smart_pointer < T > ::smart_pointer(const allocer & a)
   {
      m_p = ::null();
      create(a);
   }

   template < class T >
   smart_pointer < T > ::smart_pointer(allocer && a)
   {
      m_p = ::null();
      create(a);
   }

   template < class T >
   smart_pointer < T > ::~smart_pointer()
   {
      release();
   }

   template < class T >
   inline T * smart_pointer < T > ::operator ->()
   {
      return m_p;
   }

   template < class T >
   inline T * smart_pointer < T > ::operator ->() const
   {
      return m_p;
   }

   template < class T >
   inline smart_pointer < T > ::operator T & ()
   {
      return *m_p;
   }

   template < class T >
   inline smart_pointer < T > ::operator T & () const
   {
      return *m_p;
   }

   template < class T >
   inline smart_pointer < T > ::operator T * const ()
   {
      return m_p;
   }

   template < class T >
   inline smart_pointer < T > ::operator T * const () const
   {
      return m_p;
   }

   template < class T >
   inline smart_pointer < T > ::operator LPARAM ()
   {
      ::ca::add_ref(m_p);
      return (LPARAM) m_p;
   }

   template < class T >
   inline smart_pointer < T > ::operator LPARAM () const
   {
      ::ca::add_ref(((smart_pointer *) this)->m_p);
      return (LPARAM) m_p;
   }

/*   template < class T >
   inline smart_pointer < T > ::operator void * ()
   {
      ::ca::add_ref(m_p);
      return (void *) m_p;
   }

   template < class T >
   inline smart_pointer < T > ::operator void * () const
   {
      ::ca::add_ref(((smart_pointer *) this)->m_p);
      return (void *) m_p;
   }
*/

   template < class T >
   inline T * smart_pointer < T > ::get_()
   {
      return m_p;
   }

   template < class T >
   inline const T * smart_pointer < T > ::get_() const
   {
      return m_p;
   }

   template < class T >
   inline bool smart_pointer < T > ::is_null() const
   {
      return m_p == ::null();
   }

   template < class T >
   inline bool smart_pointer < T > ::is_set() const
   {
      return m_p != ::null();
   }

   template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator = (T * p)
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
   inline smart_pointer < T > & smart_pointer < T > ::operator = (const smart_pointer < T > & t)
   {
      return operator = (t.m_p);
   }

template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator = (smart_pointer < T > && t)
   {
      
      if(&t != this)
      {

         m_p      = t.m_p;
         t.m_p    = ::null();

      }

      return *this;

   }

   template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator = (const ::ca::null & )
   {

      if(is_set())
         release();
      
      return * this;

   }

   template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator = (LPARAM lparam)
   {

      release();

      m_p = (T *) lparam;
      
      return * this;

   }

   template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator = (void * p)
   {

      release();

      m_p = (T *) p;
      
      return * this;

   }

   template < class T >
   inline T * smart_pointer < T > ::detach()
   {
      T * p = m_p;
      m_p = ::null();
      return p;
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


template < class T1, class T2 >
bool operator ==(const ::ca::smart_pointer < T1 > & t1, const ::ca::smart_pointer < T2 > & t2)
{
   T1 * pt1 = dynamic_cast < T1 * > (t2.m_p);
   if(pt1 != NULL)
   {
      return pt1 == t1.m_p;
   }
   T2 * pt2 = dynamic_cast < T2 * > (t1.m_p);
   if(pt2 != NULL)
   {
      return pt2 == t2.m_p;
   }
   return false;
}

template < class T1, class T2 >
bool operator !=(const ::ca::smart_pointer < T1 > & t1, const ::ca::smart_pointer < T2 > & t2)
{ 
   return !operator == (t1, t2);
}

//template < class T >
//bool operator ==(const T * p, const ::ca::smart_pointer < T > & sp) { return p == sp.m_p; }
//template < class T >
//bool operator !=(const T * p, const ::ca::smart_pointer < T > & sp) { return p != sp.m_p; }
template < class T >
bool operator ==(LPARAM l, const ::ca::smart_pointer < T > & sp) { return ((T *) l) == sp.m_p; }
template < class T >
bool operator !=(LPARAM l, const ::ca::smart_pointer < T > & sp) { return ((T *) l) == sp.m_p; }
/*template < class T >
bool operator ==(void * p, const ::ca::smart_pointer < T > & sp) { return ((T *) p) == sp.m_p; }
template < class T >
bool operator !=(void * p, const ::ca::smart_pointer < T > & sp) { return ((T *) p) == sp.m_p; }*/
template < class T >
bool operator ==(const ::ca::null &, const ::ca::smart_pointer < T > & sp) { return ((T *) 0) == sp.m_p; }
template < class T >
bool operator !=(const ::ca::null &, const ::ca::smart_pointer < T > & sp) { return ((T *) 0) == sp.m_p; }
