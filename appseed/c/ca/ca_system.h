#pragma once


class CLASS_DECL_c system :
   virtual public application
{
public:


   stridsp(type)                                m_typemap;
   spa(service_base)                            m_serviceptra;
   sp(factory)                                  m_pfactory;
   url_departament                              m_urldepartament;



   system::system(sp(::application) papp);



   virtual bool initialize_instance();



   class factory                    & factory();
   inline url_departament           & url()     { return m_urldepartament; }


   using application::alloc;
   virtual sp(element) alloc(sp(::application) papp, sp(type) info);
   virtual sp(element) alloc(sp(::application) papp, const class id & idType);

   virtual sp(element) on_alloc(sp(::application) papp, sp(type) info);
   virtual sp(element) clone();
   virtual sp(element) clone(sp(element) pobj);
   template < typename T >
   inline T * cast_clone(T * pt)
   {
      return dynamic_cast < T * > (clone(dynamic_cast < sp(element) > (pt)));
   }

   template < class T >
   sp(type) type_info()
   {
      return get_type_info(typeid(T));
   }

   virtual sp(::type) get_type_info(const ::std_type_info & info);
   sp(::type) get_type_info(const class id & idType)
   {
      return m_typemap[idType];
   }


   virtual void discard_to_factory(sp(element) pca);


   static ::exception::engine & eengine();


   virtual UINT os_post_to_all_threads(UINT uiMessage, WPARAM wparam, lparam lparam);


};


template < class T >
void smart_pointer < T >::create(const allocatorsp & allocer)
{
   static class id idType = CaSys(allocer).type_info < T > ()->m_id;
   if(m_p != NULL)
      ::ca::release(m_p);
   sp(element) pca = CaSys(allocer).alloc(allocer->m_papp, idType);
   if(pca.is_set())
   {
      m_p = dynamic_cast < T * >(pca.m_p);
      if(m_p != NULL)
      {
         ::ca::add_ref(m_p);
      }
   }
}

template < class T >
sp(T) smart_pointer <T>::clone() const
{
   if(m_p == NULL)
      return NULL;
   if(m_p->get_app() == NULL)
      return NULL;
   return CaSys(m_p).clone(m_p);
}




template < size_t _Bits >
inline ::file::byte_output_stream & operator << (::file::byte_output_stream & _Ostr, const bitset<_Bits>& _Right)
{
   // insert bitset as a string
   return (_Ostr << _Right.template to_string());
}

// TEMPLATE operator>>
template < size_t _Bits >
inline ::file::byte_input_stream & operator >>( ::file::byte_input_stream &  _Istr, bitset<_Bits>& _Right)
{
   // extract bitset as a string
   string _Str;

   _Istr >> _Str;

   _Right = bitset<_Bits>(_Str);	// convert string and store

   return (_Istr);

}



#pragma once

#undef new

   inline void * object::operator new(size_t nSize)
   {
      void * p = ::operator new(nSize);
      /*try
      {
      if(::ca2::get_thread_state() != NULL)
      {
      ::ca2::get_thread_state()->m_heapitema.add_item(p, nSize);
      }
      }
      catch(...)
      {
      }*/
      return p;
   }


#ifdef DEBUG

   inline void * object::operator new(size_t nSize, const char * lpszFileName, int32_t nLine)
   {
      void * p = ::operator new(nSize, ___CLIENT_BLOCK, lpszFileName, nLine);
      /*try
      {
      if(::ca2::get_thread_state() != NULL)
      {
      ::ca2::get_thread_state()->m_heapitema.add_item(p, nSize);
      }
      }
      catch(...)
      {
      }*/
      return p;
   }

#endif


#define new DEBUG_NEW


