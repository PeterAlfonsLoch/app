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

      inline smart_pointer & operator = (T * p);
      inline smart_pointer & operator = (const smart_pointer < T > & t);
      inline smart_pointer & operator = (uint_ptr dw);
      inline smart_pointer & operator = (int32_t i);

      inline smart_pointer & operator() (T * p);


      void oattrib(const T * p);


      T * clone() const;
      void create(::ca::application * papp);


      void destroy();
      inline T * detach();


   };


   template < class T >
   smart_pointer < T > ::smart_pointer()
   {
      m_p = NULL;
   }


   template < class T >
   smart_pointer < T > ::smart_pointer(const smart_pointer < T > & t) :
      ca(&t != NULL ? t.get_app() : NULL)
   {
      m_p = NULL;
      operator = (t);
   }

   template < class T >
   smart_pointer < T > ::smart_pointer(const T & t) :
      ca(&t != NULL ? t.get_app() : NULL)
   {
      m_p = NULL;
      operator = (System.factory().clone(&t));
   }

   template < class T >
   smart_pointer < T > ::smart_pointer(const ::ca::null &)
   {
      m_p = NULL;
   }


   template < class T >
   smart_pointer < T > ::smart_pointer(T * p) :
      ca(p != NULL ? p->get_app() : NULL)
   {
      m_p = NULL;
      operator = (p);
   }

   template < class T >
   smart_pointer < T > ::smart_pointer(::ca::application * papp)
   {
      if(get_app() == NULL)
         set_app(papp);
      m_p = NULL;
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
            ::ca::add_ref(p);
         }
         m_p = p;
         if(pOld != NULL)
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
   inline smart_pointer < T > & smart_pointer < T > ::operator = (uint_ptr dw)
   {
      return operator = ((T *) dw);
   }

   template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator = (int32_t i)
   {

      if(i == 0)
      {

         return operator = ((T *) NULL);

      }
      else
      {

         throw simple_exception(get_app(), "cannot assign directly from non-null integer");

      }

   }

   template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator () (T * p)
   {
      if(p != m_p)
      {
         ::ca::release(m_p);
         m_p = p;
      }
      return *this;
   }

   template < class T >
   inline T * smart_pointer < T > ::detach()
   {
      T * p = m_p;
      m_p = NULL;
      return p;
   }

   template < class T >
   void smart_pointer < T > ::oattrib(const T * p)
   {
      if(p == NULL)
      {
         operator = ((T *) NULL);
         return;
      }
      if(is_null())
         create(p->get_app());
      *m_p = *p;
   }


} // namespace ca



#define sp(TYPE) ::ca::smart_pointer < TYPE >










