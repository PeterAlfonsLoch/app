#pragma once


template<class BASE_CLASS, class KEY, class VALUE>
class typed_pointer_map :
   public BASE_CLASS
{
public:

   typed_pointer_map(sp(::base::application) papp = NULL, ::count nBlockSize = 10) :
      element(papp),
      BASE_CLASS(papp, nBlockSize)
   {
   }

   // Lookup
   bool Lookup(typename BASE_CLASS::BASE_ARG_KEY key, VALUE& rValue) const
      { return BASE_CLASS::Lookup(key, (typename BASE_CLASS::BASE_VALUE&)rValue); }

   // Lookup and add if not there
   VALUE& operator[](typename BASE_CLASS::BASE_ARG_KEY key)
      { return (VALUE&)BASE_CLASS::operator[](key); }

   // add a new key (key, value) pair
   void set_at(KEY key, VALUE newValue)
      { BASE_CLASS::set_at(key, newValue); }

   // removing existing (key, ?) pair
   bool remove_key(KEY key)
      { return BASE_CLASS::remove_key(key); }

   // iteration
   void get_next_assoc(POSITION& rPosition, KEY& rKey, VALUE& rValue) const
      { BASE_CLASS::get_next_assoc(rPosition, (typename BASE_CLASS::BASE_KEY&)rKey,
         (typename BASE_CLASS::BASE_VALUE&)rValue); }
};

