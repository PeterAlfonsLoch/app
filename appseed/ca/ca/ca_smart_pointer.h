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
   class smart_pointer :
      virtual public ::ca::object
   {
   public:


      T * m_p;



      smart_pointer();
      smart_pointer(int32_t i) { m_p = (T *) (uint_ptr) i; }
      smart_pointer(uint32_t ui) { m_p = (T *) (uint_ptr) ui; }
      smart_pointer(int64_t i) { m_p = (T *) (uint_ptr) i; }
      smart_pointer(uint64_t ui) { m_p = (T *) (uint_ptr) ui; }
      smart_pointer(const smart_pointer < T > & t);
      smart_pointer(T * p);
      smart_pointer(const T & t);
      smart_pointer(::ca::application * papp);
      smart_pointer(const ::ca::null &);
      virtual ~smart_pointer();


      inline T * operator ->();
      inline T * operator ->() const ;
      inline operator T & ();
      inline operator T & () const ;
      inline operator T * const ();
      inline operator T * const () const;
      inline T * get_();
      inline const T * get_() const;

      inline bool is_null() const;
      inline bool is_set() const;

      inline smart_pointer & operator = (int32_t i) { return operator = ((T *) (uint_ptr) i); }
      inline smart_pointer & operator = (uint32_t ui) { return operator = ((T *) (uint_ptr) ui); }
      inline smart_pointer & operator = (int64_t i) { return operator = ((T *) (uint_ptr) i); }
      inline smart_pointer & operator = (uint64_t ui) { return operator = ((T *) (uint_ptr) ui); }

      inline smart_pointer & operator = (T * p);
      inline smart_pointer & operator = (const smart_pointer < T > & t);
      inline smart_pointer & operator = (const ::ca::null &);

      void oattrib(const T * p);


      T * clone() const;
      void create(::ca::application * papp);


      void destroy();
      inline T * detach();


   };


   template < class T >
   smart_pointer < T > ::smart_pointer()
   {
      m_p = ::null();
   }


   template < class T >
   smart_pointer < T > ::smart_pointer(const smart_pointer < T > & t) :
      ca(t.get_app())
   {
      m_p = ::null();
      operator = (t);
   }

   template < class T >
   smart_pointer < T > ::smart_pointer(const T & t) :
      ca(&t != ::null() ? t.get_app() : ::null())
   {
      m_p = ::null();
      operator = (System.factory().clone(&t));
   }

   template < class T >
   smart_pointer < T > ::smart_pointer(const ::ca::null &)
   {
      m_p = ::null();
   }


   template < class T >
   smart_pointer < T > ::smart_pointer(T * p) :
      ca(p != ::null() ? p->get_app() : ::null())
   {
      m_p = ::null();
      operator = (p);
   }

   template < class T >
   smart_pointer < T > ::smart_pointer(::ca::application * papp)
   {
      if(get_app() == ::null())
         set_app(papp);
      m_p = ::null();
      create(papp);
   }

   template < class T >
   smart_pointer < T > ::~smart_pointer()
   {
      ::ca::release(m_p);
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
   inline smart_pointer < T > & smart_pointer < T > ::operator = (const ::ca::null & )
   {

      if(is_set())
         release();
      
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
   void smart_pointer < T > ::oattrib(const T * p)
   {
      if(p == ::null())
      {
         operator = ((T *) ::null());
         return;
      }
      if(is_null())
         create(p->get_app());
      *m_p = *p;
   }


} // namespace ca



#define sp(TYPE) ::ca::smart_pointer < TYPE >










