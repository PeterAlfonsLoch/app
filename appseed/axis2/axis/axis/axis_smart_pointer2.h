#pragma once


// ::ca::null_class back link to operational system oswindow.h
//
//
//
//
// operational system NULL/void itself to a windowing service
//
// Curitiba, inha-metro-win-ubuntu-mountain-lion-macos 4 de novembro de 2012
   template < class T >
   smart_pointer < T > ::smart_pointer()
   {
      m_p = NULL;
   }


   template < class T >
   smart_pointer < T > ::smart_pointer(const smart_pointer < T > & t)
   {
      m_p = NULL;
      operator = (t);
   }

#ifdef MOVE_SEMANTICS
   template < class T >
   smart_pointer < T > ::smart_pointer(smart_pointer < T > && t)
   {

      m_p      = t.m_p;
      t.m_p    = NULL;

   }
#endif

   template < class T >
   inline smart_pointer < T > ::smart_pointer(T * p)
   {
      m_p = p;
      ::add_ref(m_p);
   }

   template < class T >
   inline smart_pointer < T > ::smart_pointer(const lparam & lparam)
   {
      m_p = (T *) lparam.m_lparam;
   }

   template < class T >
   smart_pointer < T > ::smart_pointer(const allocatorsp & a)
   {
      m_p = NULL;
      alloc(a);
   }

#ifdef MOVE_SEMANTICS
   template < class T >
   smart_pointer < T > ::smart_pointer(allocatorsp && a)
   {
      m_p = NULL;
      alloc(a);
   }
#endif

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
   inline T & smart_pointer < T > ::operator * ()
   {
      return *m_p;
   }

   template < class T >
   inline T & smart_pointer < T > ::operator * () const
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
   inline smart_pointer < T > ::operator lparam ()
   {
      ::add_ref(m_p);
      return lparam(m_p);
   }

   template < class T >
   inline smart_pointer < T > ::operator lparam () const
   {
      ::add_ref(((smart_pointer *) this)->m_p);
      return lparam(m_p);
   }

/*   template < class T >
   inline smart_pointer < T > ::operator void * ()
   {
      ::c::add_ref(m_p);
      return (void *) m_p;
   }

   template < class T >
   inline smart_pointer < T > ::operator void * () const
   {
      ::c::add_ref(((smart_pointer *) this)->m_p);
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
      return m_p == NULL;
   }

   template < class T >
   inline bool smart_pointer < T > ::is_set() const
   {
      return m_p != NULL;
   }

   template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator = (T * p)
   {
      if(m_p != p)
      {
         T * pOld = m_p;
         if(p != NULL)
         {
            ::add_ref(p);
         }
         m_p = p;
         if(pOld != NULL)
         {
            ::release(pOld);
         }
      }
      return *this;
   }

   template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator = (const smart_pointer < T > & t)
   {
      return operator = (t.m_p);
   }

#ifdef MOVE_SEMANTICS
   template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator = (smart_pointer < T > && t)
   {

      if(&t != this)
      {

         m_p      = t.m_p;
         t.m_p    = NULL;

      }

      return *this;

   }
#endif

   template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator = (const lparam & lparam)
   {

      release();

      m_p = (T *) lparam;

      return * this;

   }

   template < class T >
   inline T * smart_pointer < T > ::detach()
   {
      T * p = m_p;
      m_p = NULL;
      return p;
   }


   template < class T >
   void smart_pointer < T > ::oattrib(const sp(T) & p)
   {
      if(p.m_p == NULL)
      {
         release();
         return;
      }
      if(is_null())
         alloc(p->allocer());
      *m_p = *p.m_p;
   }


    // cut and paste with very good capabilities of RealVNC for MacOS in OVH.fr/eu/pt cloud from Windows client.
    // slashes with ABNT 2 keyboard and even c cedilha working with RealVNC
    template < class T >
    void smart_pointer <T>::release()
    {

        ::release(m_p);

    }

   template < class T1, class T2 >
   bool operator ==(const T1  * t1, const smart_pointer < T2 > & t2)
   {
      T1 * pt1 = dynamic_cast < T1 * > (t2.m_p);
      if(pt1 != NULL)
      {
         return pt1 == t1;
      }
      T2 * pt2 = dynamic_cast < T2 * > ((T1 *) t1);
      if(pt2 != NULL)
      {
         return pt2 == t2.m_p;
      }
      return false;
   }

   template < class T1, class T2 >
   bool operator ==(const smart_pointer < T1 > & t1, const T2 * t2)
   {
      T1 * pt1 = dynamic_cast < T1 * > ((T2 *) t2);
      if(pt1 != NULL)
      {
         return pt1 == t1.m_p;
      }
      T2 * pt2 = dynamic_cast < T2 * > (t1.m_p);
      if(pt2 != NULL)
      {
         return pt2 == t2;
      }
      return false;
   }


template < class T1, class T2 >
bool operator ==(const smart_pointer < T1 > & t1, const smart_pointer < T2 > & t2)
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
bool operator ==(T1 * t1, const smart_pointer < T2 > & t2)
{
   return operator == ((const T1 *) t1, t2);
}


template < class T1, class T2 >
bool operator ==(const smart_pointer < T1 > & t1, T2 * t2)
{
   return operator == (t1,  (const T2 *) t2);
}


template < class T1, class T2 >
bool operator !=(const T1 * t1, const smart_pointer < T2 > & t2)
{
   return !operator == (t1, t2);
}


template < class T1, class T2 >
bool operator !=(const smart_pointer < T1 > & t1, const T2 * t2)
{
   return !operator == (t1, t2);
}

template < class T1, class T2 >
bool operator !=(T1 * t1, const smart_pointer < T2 > & t2)
{
   return !operator == ((const T1 *) t1, t2);
}


template < class T1, class T2 >
bool operator !=(const smart_pointer < T1 > & t1, T2 * t2)
{
   return !operator == (t1, (const T2 *) t2);
}


template < class T1, class T2 >
bool operator !=(const smart_pointer < T1 > & t1, const smart_pointer < T2 > & t2)
{
   return !operator == (t1, t2);
}

//template < class T >
//bool operator ==(const T * p, const smart_pointer < T > & sp) { return p == sp.m_p; }
//template < class T >
//bool operator !=(const T * p, const smart_pointer < T > & sp) { return p != sp.m_p; }
template < class T >
bool operator ==(LPARAM l, const smart_pointer < T > & sp) { return ((T *) l) == sp.m_p; }
template < class T >
bool operator !=(LPARAM l, const smart_pointer < T > & sp) { return ((T *) l) == sp.m_p; }
/*template < class T >
bool operator ==(void * p, const smart_pointer < T > & sp) { return ((T *) p) == sp.m_p; }
template < class T >
bool operator !=(void * p, const smart_pointer < T > & sp) { return ((T *) p) == sp.m_p; }*/
#if !defined(ANDROID) && !defined(SOLARIS) && !defined(APPLE_OS)
template < class T >
inline bool operator ==(int i, const smart_pointer < T > & sp) { return ((T *) i) == sp.m_p; }
template < class T >
inline bool operator !=(int i, const smart_pointer < T > & sp) { return ((T *) i) == sp.m_p; }
#endif


