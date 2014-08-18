#pragma once


template < class VALUE, class ARG_VALUE = const VALUE &, class HASH = ::comparison::strid_hash, class EQUALS = ::comparison::strid_equals  >
class strid_map :
   virtual public attrib_map < map < id, const id &, VALUE, ARG_VALUE, HASH, EQUALS > >
{
public:

   strid_map(sp(::base::application) papp = NULL, ::count nBlockSize = 256);
   strid_map(const strid_map & map);


   strid_map & operator = (const strid_map & map);


};


template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
strid_map < VALUE, ARG_VALUE, HASH, EQUALS >::strid_map(sp(::base::application) papp, ::count nBlockSize) :
   element(papp),
   map < id, const id &, VALUE, ARG_VALUE, HASH, EQUALS > (papp, nBlockSize)
{
}


template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
strid_map < VALUE, ARG_VALUE, HASH, EQUALS >::strid_map(const strid_map & map) :
   element(map.get_app()),
   attrib_map < ::map < id, const id &, VALUE, ARG_VALUE, HASH, EQUALS > > (map)
{
}

template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
strid_map < VALUE, ARG_VALUE, HASH, EQUALS > & strid_map < VALUE, ARG_VALUE, HASH, EQUALS >::operator = (const strid_map & map)
{

   if(this != &map)
   {
      this->attrib_map < ::map < id, const id &, VALUE, ARG_VALUE, HASH, EQUALS > >::operator = (map);
   }

   return *this;

}


template < class T >
class CLASS_DECL_AXIS string_to_pointer :
   virtual public string_to_ptr
{
public:

   class pair
   {
   public:
      const string m_element1;
      T * m_element2;
   };

   bool Lookup(string key, T * & rValue) const
   {
      return string_to_ptr::Lookup(key, rValue);
   }
   const pair *PLookup(string key) const
   {
      return reinterpret_cast < const string_to_pointer::pair * > (string_to_ptr::PLookup(key));
   }
   pair *PLookup(string key)
   {
      return reinterpret_cast < string_to_pointer::pair * > (string_to_ptr::PLookup(key));
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
   // Lookup and add if not there
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

