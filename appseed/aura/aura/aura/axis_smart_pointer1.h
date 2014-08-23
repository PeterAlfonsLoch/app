#pragma once


template < class root_derived >
inline int64_t add_ref(root_derived * pca);

template < class root_derived >
inline int64_t release(root_derived * & pca);

// ::ca::null_class back link to operational system oswindow.h
//
//
//
//
// operational system NULL/void itself to a windowing service
//
// Curitiba, inha-metro-win-ubuntu-mountain-lion-macos 4 de novembro de 2012
template < class T >
class smart_pointer
{
public:



   T * m_p;



   smart_pointer();
   smart_pointer(const lparam & lparam);
   smart_pointer(const smart_pointer < T > & t);
#ifdef MOVE_SEMANTICS
   smart_pointer(smart_pointer < T > && t);
#endif
   smart_pointer(const allocatorsp & t);
#ifdef MOVE_SEMANTICS
   smart_pointer(allocatorsp && t);
#endif
   template < class T2 >
   smart_pointer(T2 * p)
   {
      m_p = dynamic_cast < T * > (p);
      if(m_p != NULL) ::add_ref(p);
   }
   smart_pointer(T * p);

   template < class T2 >
   smart_pointer(const T2 * p)
   {
      m_p = dynamic_cast < T * > ((T2 *) p);
      if(m_p != NULL) ::add_ref(p);
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
   inline T & operator *();
   inline T & operator *() const ;
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

   inline smart_pointer & operator = (const smart_pointer < T > & t);
#ifdef MOVE_SEMANTICS
   inline smart_pointer & operator = (smart_pointer < T > && t);
#endif
   inline smart_pointer & operator = (const lparam & lparam);

   template < class T2 >
   inline smart_pointer & operator = (T2 * p)
   {
      return operator = (dynamic_cast < T * > (p));
   }


   inline smart_pointer & operator = (T * p);

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
         ::release(pOld);
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
   template < typename T2 >
   inline bool operator ==(const T2 * p) const { return m_p == p; }
   template < typename T2 >
   inline bool operator !=(const T2 * p) const { return m_p != p; }
   inline bool operator ==(const T * p) const { return m_p == p; }
   inline bool operator !=(const T * p) const { return m_p != p; }
   //bool operator ==(void * p) const { return m_p == (T *) p; }
   //bool operator !=(void * p) const { return m_p != (T *) p; }



   void oattrib(const sp(T) & o);
   void copy(T * po) { return oattrib(po); }


   sp(T) clone() const;
   void alloc(const allocatorsp & allocer);




};


