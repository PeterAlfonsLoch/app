#pragma once


namespace base
{


   class CLASS_DECL_BASE system:
      virtual public ::axis::system,
      virtual public :: base ::application
   {
   public:

      system(::aura::application * papp);
      virtual ~system();



      virtual ::aura::session * on_create_session();
   };


} // namespace base



template < size_t _Bits >
inline ::file::ostream & operator << (::file::ostream & _Ostr,const bitset<_Bits>& _Right)
{
   // insert bitset as a string
   return (_Ostr << _Right.template to_string());
}

// TEMPLATE operator>>
template < size_t _Bits >
inline ::file::istream & operator >>(::file::istream &  _Istr,bitset<_Bits>& _Right)
{
   // extract bitset as a string
   string _Str;

   _Istr >> _Str;

   _Right = bitset<_Bits>(_Str);	// convert string and store

   return (_Istr);

}




void CLASS_DECL_BASE __start_system(::base::system * psystem);




