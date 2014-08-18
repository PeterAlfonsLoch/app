#pragma once


template<class AXIS_CLASS, class KEY, class VALUE>
class typed_pointer_map :
   public AXIS_CLASS
{
public:

   typed_pointer_map(sp(::base::application) papp = NULL, ::count nBlockSize = 10) :
      element(papp),
      AXIS_CLASS(papp, nBlockSize)
   {
   }

   // Lookup
   bool Lookup(typename AXIS_CLASS::AXIS_ARG_KEY key, VALUE& rValue) const
      { return AXIS_CLASS::Lookup(key, (typename AXIS_CLASS::AXIS_VALUE&)rValue); }

   // Lookup and add if not there
   VALUE& operator[](typename AXIS_CLASS::AXIS_ARG_KEY key)
      { return (VALUE&)AXIS_CLASS::operator[](key); }

   // add a new key (key, value) pair
   void set_at(KEY key, VALUE newValue)
      { AXIS_CLASS::set_at(key, newValue); }

   // removing existing (key, ?) pair
   bool remove_key(KEY key)
      { return AXIS_CLASS::remove_key(key); }

   // iteration
   void get_next_assoc(POSITION& rPosition, KEY& rKey, VALUE& rValue) const
      { AXIS_CLASS::get_next_assoc(rPosition, (typename AXIS_CLASS::AXIS_KEY&)rKey,
         (typename AXIS_CLASS::AXIS_VALUE&)rValue); }
};

