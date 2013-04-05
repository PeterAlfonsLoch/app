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

   template < class T >
   class smart_pointer;

   
   class ca;


   template < class T >
   class raw_smart_pointer
   {
   public:


      T * m_p;



      raw_smart_pointer();
      raw_smart_pointer(int32_t i) { m_p = (T *) (uint_ptr) i; }
      raw_smart_pointer(uint32_t ui) { m_p = (T *) (uint_ptr) ui; }
      raw_smart_pointer(int64_t i) { m_p = (T *) (uint_ptr) i; }
      raw_smart_pointer(uint64_t ui) { m_p = (T *) (uint_ptr) ui; }
      raw_smart_pointer(const raw_smart_pointer < T > & t);
      raw_smart_pointer(raw_smart_pointer < T > && t);
      raw_smart_pointer(T * p);
      raw_smart_pointer(const ::ca::null &);
      template < class T2 >
      raw_smart_pointer(T2 * p)
      {
         m_p = dynamic_cast < T * > (p);
         if(m_p != ::null()) ::ca::add_ref(p);
      }

      template < class T2 >
      raw_smart_pointer(const T2 * p)
      {
         m_p = dynamic_cast < T * > ((T2 *) p);
         if(m_p != ::null()) ::ca::add_ref(p);
      }

      template < class T2 >
      raw_smart_pointer(const raw_smart_pointer < T2 > & t)
      {
         m_p = ::null();
         operator = (dynamic_cast < T * >(t.m_p));
      }
      template < class T2 >
      raw_smart_pointer(raw_smart_pointer < T2 > && t)
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
      template < class T2 >
      raw_smart_pointer(const smart_pointer < T2 > & t)
      {
         m_p = ::null();
         operator = (dynamic_cast < T * >(t.m_p));
      }
      template < class T2 >
      raw_smart_pointer(smart_pointer < T2 > && t)
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
      ~raw_smart_pointer();


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

      inline raw_smart_pointer & operator = (int32_t i) { return operator = ((T *) (uint_ptr) i); }
      inline raw_smart_pointer & operator = (uint32_t ui) { return operator = ((T *) (uint_ptr) ui); }
      inline raw_smart_pointer & operator = (int64_t i) { return operator = ((T *) (uint_ptr) i); }
      inline raw_smart_pointer & operator = (uint64_t ui) { return operator = ((T *) (uint_ptr) ui); }

      inline raw_smart_pointer & operator = (T * p);
      inline raw_smart_pointer & operator = (const raw_smart_pointer < T > & t);
      inline raw_smart_pointer & operator = (raw_smart_pointer < T > && t);
      inline raw_smart_pointer & operator = (const ::ca::null &);

      template < class T2 >
      inline raw_smart_pointer & operator = (const raw_smart_pointer < T2 > & t)
      {
         return operator = (dynamic_cast < T * > (t.m_p));
      }

      template < class T2 >
      inline raw_smart_pointer & operator = (raw_smart_pointer < T2 > && t)
      {
         T * pOld = m_p;
         m_papp = t.m_papp;
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


   };


   class application;


   class CLASS_DECL_ca applicationsp :
      public raw_smart_pointer < application >
   {
   public:
      applicationsp() : raw_smart_pointer < application >() {}
      applicationsp(int32_t i) { m_p = (application *) (uint_ptr) i; }
      applicationsp(uint32_t ui) { m_p = (application *) (uint_ptr) ui; }
      applicationsp(int64_t i) { m_p = (application *) (uint_ptr) i; }
      applicationsp(uint64_t ui) { m_p = (application *) (uint_ptr) ui; }
      applicationsp(const raw_smart_pointer < application > & t) : raw_smart_pointer < application >(t) {}
      applicationsp(raw_smart_pointer < application > && t) : raw_smart_pointer < application >(t) {}
      applicationsp(application * p) : raw_smart_pointer < application >(p) {}
      applicationsp(const ::ca::null &) : raw_smart_pointer < application >(::null()) {}
      template < class T2 >
      applicationsp(const raw_smart_pointer < T2 > & t)
      {
         m_p = ::null();
         operator = (dynamic_cast < application * >(t.m_p));
      }
      template < class T2 >
      applicationsp(raw_smart_pointer < T2 > && t)
      {
         if(t.m_p != ::null())
         {
            m_p = dynamic_cast < application * >(t.m_p);
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
      template < class T2 >
      applicationsp(const smart_pointer < T2 > & t)
      {
         m_p = ::null();
         operator = (dynamic_cast < application * >(t.m_p));
      }
      template < class T2 >
      applicationsp(smart_pointer < T2 > && t)
      {
         if(t.m_p != ::null())
         {
            m_p = dynamic_cast < application * >(t.m_p);
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
   };
      


   template < class T >
   class smart_pointer :
      public raw_smart_pointer <T >
   {
   public:



      smart_pointer() : raw_smart_pointer < T>() {}
      smart_pointer(int32_t i) { m_p = (T *) (uint_ptr) i; }
      smart_pointer(uint32_t ui) { m_p = (T *) (uint_ptr) ui; }
      smart_pointer(int64_t i) { m_p = (T *) (uint_ptr) i; }
      smart_pointer(uint64_t ui) { m_p = (T *) (uint_ptr) ui; }
      smart_pointer(const raw_smart_pointer < T > & t) : raw_smart_pointer < T >(t) {}
      smart_pointer(raw_smart_pointer < T > && t) : raw_smart_pointer < T >(t) {}
      smart_pointer(T * p) : raw_smart_pointer < T >(p) {}
      smart_pointer(const ::ca::null &) : raw_smart_pointer < T >(::null()) {}
      smart_pointer(::ca::applicationsp & papp);
//      smart_pointer(const ::ca::null &);
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

      /*
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

      inline smart_pointer & operator = (T * p);*/
//      inline smart_pointer & operator = (const T & t);
      /*inline smart_pointer & operator = (const smart_pointer < T > & t);
      inline smart_pointer & operator = (smart_pointer < T > && t);
      inline smart_pointer & operator = (const ::ca::null &);

      template < class T2 >
      inline smart_pointer & operator = (const smart_pointer < T2 > & t)
      {
         return operator = (dynamic_cast < T * > (t.m_p));
      }

      template < class T2 >
      inline smart_pointer & operator = (smart_pointer < T2 > && t)
      {
         T * pOld = m_p;
         m_papp = t.m_papp;
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
      }*/

      void oattrib(const sp(T) & o);


      sp(T) clone() const;
      void create(::ca::applicationsp papp);


      //void destroy();
      //inline T * detach();

   };




} // namespace ca














