#pragma once



class CLASS_DECL_AXIS root
{
public:


   int64_t                       m_countReference;
   bool                          m_bHeap;
   ::base::application *         m_pbaseapp;



   root();
   root(sp(::base::application) papp);
   virtual ~root();


   virtual void delete_this();



   inline int64_t get_ref_count()
   {
      return m_countReference;
   }

   inline bool is_heap()
   {
      return m_bHeap;
   }


   virtual int64_t add_ref();
   virtual int64_t dec_ref();
   virtual int64_t release();

   inline ::base::session     & session();
   inline ::core::platform    & platform();

};

template < class T >
T * dereference_no_delete(T * p) { p->m_bHeap = true; p->m_countReference--; return p; }




template < class c_derived >
inline int64_t add_ref(c_derived * pca)
{
   if(pca == NULL)
      return -1;
   return pca->add_ref();
}

template < class c_derived >
inline int64_t release(c_derived * & pca)
{
   if(pca == NULL)
      return -1;
   c_derived * p = pca;
   pca = NULL;
   int64_t count = p->release();
   return count;
}

template < class c_derived >
inline int64_t ref_count(c_derived * pca)
{
   if(pca == NULL)
      return -1;
   return pca->get_ref_count();
}


template < class TYPE >
bool is_null(TYPE * p)
{
   return (((int_ptr) p) < sizeof(TYPE));
}

template < class TYPE >
bool is_null(TYPE & t)
{
   return (((int_ptr)&t) < sizeof(TYPE));
}


template <class t>
inline void delptr(t *& p)
{
   if(p != NULL)
   {
      delete p;
      p = NULL;
   }
}




#define canew(x) dereference_no_delete(new x)



