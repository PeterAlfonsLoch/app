#pragma once


template < typename POINTER,class ARRAY_TYPE = comparable_raw_array < POINTER >  >
class raw_ptr_array:
   public ARRAY_TYPE
{
public:



   inline raw_ptr_array() {}
   inline raw_ptr_array(::aura::application * papp):element(papp) {   }
   inline raw_ptr_array(const raw_ptr_array & a) { this->operator = (a); }
   inline raw_ptr_array(raw_ptr_array && a) { this->operator = (a); }


   inline raw_ptr_array & operator = (const raw_ptr_array & a) { this->ARRAY_TYPE::operator = (a); return *this; }
   inline raw_ptr_array & operator = (raw_ptr_array && a){ this->ARRAY_TYPE::operator = (a); return *this; }


   index add(POINTER newElement)  { return ARRAY_TYPE::add(newElement); }
   index add(const raw_ptr_array & src) { return ARRAY_TYPE::add(src); }


   inline POINTER & element_at(index i) { return (POINTER &)ARRAY_TYPE::element_at(i); }
   inline POINTER element_at(index i) const { return (POINTER)ARRAY_TYPE::element_at(i); }

   inline POINTER & element_at_grow(index i){ return (POINTER &)ARRAY_TYPE::element_at_grow(i);  }


   inline POINTER & operator[](index i) { return element_at(i); }
   inline POINTER operator[](index i) const { return element_at(i); }

   inline POINTER & first(index i = 0) { return (POINTER &)ARRAY_TYPE::first(i); }
   inline POINTER first(index i = 0) const { return (POINTER)ARRAY_TYPE::first(i); }

   inline POINTER & last(index i = -1) { return (POINTER &)ARRAY_TYPE::last(i); }
   inline POINTER last(index i = 0) const { return (POINTER)ARRAY_TYPE::last(i); }

   inline POINTER* get_data() { return (POINTER*)ARRAY_TYPE::get_data(); }
   inline POINTER* get_data() const { return (POINTER*)ARRAY_TYPE::get_data(); }


};



template < class TYPE,class ARRAY_TYPE = raw_ptr_array < TYPE * > >
class ptr_array:
   public ARRAY_TYPE
{
public:


   //DECLARE_AND_IMPLEMENT_DEFAULT_CONSTRUCTION_AND_ASSIGNMENT(ptr_array, ARRAY_TYPE)
   //inline ptr_array() {}
   //inline ptr_array(const ptr_array & a) { this->operator = (a); }
   //inline ptr_array(ptr_array && a) { this->operator = (a); }


   //inline ptr_array & operator = (const ptr_array & a) { this->ARRAY_TYPE::operator = (a); return *this; }
   //inline ptr_array & operator = (ptr_array && a){ this->ARRAY_TYPE::operator = (a); return *this; }


   inline TYPE & operator()(index i) { return *element_at(i); }
   inline const TYPE & operator()(index i) const { return *element_at(i); }

};













class CLASS_DECL_AURA const_char_ptra:
   public ptr_array < const char >
{
};






typedef raw_ptr_array < void * > void_ptra;