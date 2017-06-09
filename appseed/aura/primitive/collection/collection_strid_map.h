#pragma once


template < class VALUE, class ARG_VALUE = const VALUE &  >
using strid_map = id_map < VALUE,ARG_VALUE > ;

template < class T >
class CLASS_DECL_AURA string_to_pointer :
   virtual public string_to_ptr
{
public:

   class pair
   {
   public:
      const string first;
      T * second;
   };

   bool lookup(string key, T * & rValue) const
   {
      return string_to_ptr::lookup(key, rValue);
   }
   const pair *find_first(string key) const
   {
      return reinterpret_cast < const string_to_pointer::pair * > (string_to_ptr::find_first(key));
   }
   pair *find_first(string key)
   {
      return reinterpret_cast < string_to_pointer::pair * > (string_to_ptr::find_first(key));
   }


   T ** pget(string key)
   {
      return (T**) string_to_ptr::pget(key);
   }
   T * get(string key)
   {
      T ** p = (T **) string_to_ptr::pget(key);
      if(p == NULL)
         return NULL;
      else
         return (T*) *p;
   }

   // Operations
   // lookup and add if not there
   T * & operator[](string key)
   {
      return (T * &) string_to_ptr::operator[](key);
   }


   pair * PGetFirstAssoc()
   {
      return (pair *) string_to_ptr::PGetFirstAssoc();
   }

   pair * PGetNextAssoc(pair * & rPpair)
   {
      return (pair *) string_to_ptr::PGetNextAssoc((string_to_ptr::pair * &) rPpair);
   }

};



#define stridsp(ca) strid_map < sp(ca) >

