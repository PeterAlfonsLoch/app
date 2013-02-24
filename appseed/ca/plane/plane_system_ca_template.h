#pragma once


namespace ca
{
 

   template < class T >
   void smart_pointer <T>::create(::ca::application * papp)
   {
      if(get_app() == NULL)
         set_app(papp);
      if(get_app() == NULL)
         return;
      static class id idType = Sys(papp).type_info < T > ().m_id;
      if(m_p != NULL)
         ca::release(m_p);
      m_p = dynamic_cast < T * > (Sys(papp).alloc(papp, idType));
   }

   template < class T >
   T * smart_pointer <T>::clone() const   
   {
      if(m_p == NULL)
         return NULL;
      if(m_p->get_app() == NULL)
         return NULL;
      return dynamic_cast < T * > (Sys(m_p->m_papp).clone(m_p));
   }

   template < class T >
   void smart_pointer <T>::destroy()
   {
      if(m_p != NULL)
      {
         m_p->delete_this();
         m_p = NULL;
      }
   }


} // namespace ca




   template < size_t _Bits >
   inline ::ca::byte_output_stream & operator << (::ca::byte_output_stream & _Ostr, const bitset<_Bits>& _Right)
   {	
      // insert bitset as a string
	   return (_Ostr << _Right.template to_string());
   }

		// TEMPLATE operator>>
   template < size_t _Bits >
	inline ::ca::byte_input_stream & operator >>( ::ca::byte_input_stream &  _Istr, bitset<_Bits>& _Right)
	{	
      // extract bitset as a string
   	string _Str;
	
      _Istr >> _Str;

   	_Right = bitset<_Bits>(_Str);	// convert string and store
	   
      return (_Istr);

	}
