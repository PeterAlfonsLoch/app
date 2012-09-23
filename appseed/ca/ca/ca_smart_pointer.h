#pragma once


namespace ca
{


   class CLASS_DECL_ca null
   {
   public:


      null() {}


   };


   template < class T >
   class smart_pointer :
      virtual public ::radix::object
   {
   public:


      T * m_p;


      smart_pointer();
      smart_pointer(const smart_pointer < T > & t);
      smart_pointer(T * p);
      smart_pointer(::ca::application * papp);
      smart_pointer(const ::ca::null &);
      virtual ~smart_pointer();


      inline T * operator ->();
      inline const T * operator ->() const ;
      inline operator T & ();
      inline operator const T & () const ;
      inline operator T * & ();
      inline operator T * const & () const;
      inline T * get_();
      inline const T * get_() const;

      inline bool is_null() const;
      inline bool is_set() const;

      inline smart_pointer & operator = (T * p);
      inline smart_pointer & operator = (const smart_pointer < T > & t);
      inline smart_pointer & operator = (dword_ptr dw);
      inline smart_pointer & operator = (int i);

      inline smart_pointer & operator() (T * p);


      void oattrib(T * p);


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
      gen::release(m_p);
   }

   template < class T >
   inline T * smart_pointer < T > ::operator ->()
   {
      return m_p;
   }

   template < class T >
   inline const T * smart_pointer < T > ::operator ->() const
   {
      return m_p;
   }

   template < class T >
   inline smart_pointer < T > ::operator T & ()
   {
      return *m_p;
   }

   template < class T >
   inline smart_pointer < T > ::operator const T & () const
   {
      return *m_p;
   }

   template < class T >
   inline smart_pointer < T > ::operator T * & ()
   {
      return m_p;
   }

   template < class T >
   inline smart_pointer < T > ::operator T * const & () const
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
         if(m_p != NULL)
         {
            gen::release(m_p);
         }
         m_p = p;
         if(m_p != NULL)
         {
            gen::add_ref(m_p);
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
   inline smart_pointer < T > & smart_pointer < T > ::operator = (dword_ptr dw)
   {
      return operator = ((T *) dw);
   }

   template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator = (int i)
   {

      if(i == 0)
      {

         return operator = ((T *) NULL);

      }
      else
      {

         throw simple_exception("cannot assign directly from non-null integer");

      }

   }

   template < class T >
   inline smart_pointer < T > & smart_pointer < T > ::operator () (T * p)
   {
      if(p != m_p)
      {
         gen::release(m_p);
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
   void smart_pointer < T > ::oattrib(T * p)
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

   template < class T >
   class smart_pointer_array :
      virtual public base_array < ::ca::smart_pointer < T > >
   {
   public:


      template < class DERIVED >
      DERIVED * get(index iStart = 0)
      {

         DERIVED * pderived = NULL;

         for(index i = iStart; i < this->get_count(); i++)
         {

            try
            {

               pderived = dynamic_cast < DERIVED * > (this->element_at(i).m_p);

            }
            catch(...)
            {

            }

            if(pderived != NULL)
               return pderived;

         }

         return NULL;

      }


   };


} // namespace ca





#define sp(TYPE) ::ca::smart_pointer < TYPE >
#define spa(TYPE) ::ca::smart_pointer_array < TYPE >
