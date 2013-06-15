#pragma once


namespace ca
{


   template < class T >
   void smart_pointer <T>::create(const ::ca2::allocatorsp & allocer)
   {
      static class id idType = Sys(allocer->m_papp).type_info < T > ()->m_id;
      if(m_p != NULL)
         ::ca::release(m_p);
      sp(::ca2::ca2) pca = Sys(allocer->m_papp).alloc(allocer->m_papp, idType);
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
      return Sys(m_p->m_papp).clone(m_p);
   }



} // namespace ca




   template < size_t _Bits >
   inline ::ca2::byte_output_stream & operator << (::ca2::byte_output_stream & _Ostr, const bitset<_Bits>& _Right)
   {
      // insert bitset as a string
	   return (_Ostr << _Right.template to_string());
   }

		// TEMPLATE operator>>
   template < size_t _Bits >
	inline ::ca2::byte_input_stream & operator >>( ::ca2::byte_input_stream &  _Istr, bitset<_Bits>& _Right)
	{
      // extract bitset as a string
   	string _Str;

      _Istr >> _Str;

   	_Right = bitset<_Bits>(_Str);	// convert string and store

      return (_Istr);

	}
