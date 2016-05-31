#pragma once


template < typename POINTER,class ARRAY_TYPE = comparable_array < POINTER,POINTER,comparable_eq_array < POINTER,POINTER,raw_array < POINTER,POINTER,::allocator::zero < POINTER > > > >  >
class raw_ref_array:
   public ARRAY_TYPE
{
public:



   inline raw_ref_array() {}
   inline raw_ref_array(::ace::application * papp):object(papp) {   }
   inline raw_ref_array(const raw_ref_array & a) { this->operator = (a); }
   inline raw_ref_array(raw_ref_array && a) { this->operator = (a); }


   inline raw_ref_array & operator = (const raw_ref_array & a) { this->ARRAY_TYPE::operator = (a); return *this; }
   inline raw_ref_array & operator = (raw_ref_array && a){ this->ARRAY_TYPE::operator = (a); return *this; }


   index add(POINTER newElement)  { return ARRAY_TYPE::add(newElement); }
   index add(const raw_ref_array & src) { return ARRAY_TYPE::add(src); }


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



template < class TYPE,class ARRAY_TYPE = raw_ref_array < TYPE * > >
class ref_array:
   public ARRAY_TYPE
{
public:


   //DECLARE_AND_IMPLEMENT_DEFAULT_CONSTRUCTION_AND_ASSIGNMENT(ref_array, ARRAY_TYPE)
   //inline ref_array() {}
   //inline ref_array(const ref_array & a) { this->operator = (a); }
   //inline ref_array(ref_array && a) { this->operator = (a); }


   //inline ref_array & operator = (const ref_array & a) { this->ARRAY_TYPE::operator = (a); return *this; }
   //inline ref_array & operator = (ref_array && a){ this->ARRAY_TYPE::operator = (a); return *this; }


   inline TYPE & operator()(index i) { return *this->element_at(i); }
   inline const TYPE & operator()(index i) const { return *this->element_at(i); }

   template < class T >
   T * typed_ptr_at(index i)
   {

      return dynamic_cast <T *> (this->element_at(i));

   }


};













class CLASS_DECL_AURA const_char_ptra:
   public ref_array < const char >
{
};






typedef raw_ref_array < void * > void_ptra;



template < class TYPE, class ARRAY_TYPE = ref_array < TYPE > >
class ptr_array :
   public ARRAY_TYPE
{
public:


   //DECLARE_AND_IMPLEMENT_DEFAULT_CONSTRUCTION_AND_ASSIGNMENT(ref_array, ARRAY_TYPE)
   //inline ref_array() {}
   //inline ref_array(const ref_array & a) { this->operator = (a); }
   //inline ref_array(ref_array && a) { this->operator = (a); }



   virtual ~ptr_array()
   {

      this->remove_all();

   }

   void remove_all()
   {

      index i;

      while((i = this->get_upper_bound()) >= 0)
      {

         try
         {

            this->remove_at(i);

         }
         catch (...)
         {

         }

      }

   }


   ::count remove(TYPE * p)
   {

      ::count cRemoved = 0;

      index iFind = 0;

      while ((iFind = find_first(p, iFind)) >= 0)
      {

         cRemoved++;

         this->remove_at(iFind);

      }

      if (cRemoved > 0)
      {

         try
         {

            delete p;

         }
         catch (...)
         {

         }

      }

      return cRemoved;

   }


   index find_first(TYPE * p, index iFind = 0)
   {

      for (; iFind < this->get_size(); iFind++)
      {

         if (this->element_at(iFind) == p)
         {

            return iFind;

         }

      }

      return -1;

   }


   bool contains(TYPE * p, index iFind = 0)
   {

      return this->find_first(p, iFind) >= 0;

   }


   void remove_at(index i)
   {

      TYPE * p = this->element_at(i);

      ARRAY_TYPE::remove_at(i);

      try
      {

         delete p;

      }
      catch (...)
      {

      }

   }


   //inline ref_array & operator = (const ref_array & a) { this->ARRAY_TYPE::operator = (a); return *this; }
   //inline ref_array & operator = (ref_array && a){ this->ARRAY_TYPE::operator = (a); return *this; }


   inline TYPE & operator()(index i) { return *this->element_at(i); }
   inline const TYPE & operator()(index i) const { return *this->element_at(i); }



};

