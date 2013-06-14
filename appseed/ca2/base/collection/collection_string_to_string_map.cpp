#include "framework.h"


string_to_string_map::string_to_string_map(::ca2::application * papp, int_ptr nBlockSize) :
   ::ca2::ca2(papp),
   base_string_to_string_map(papp,  nBlockSize)
{

}


string_to_string_map::string_to_string_map(const string_to_string_map & map) :
   ::ca2::ca2(map.get_app()),
   base_string_to_string_map(dynamic_cast < const base_string_to_string_map & > (map))
{

}


string_to_string_map::~string_to_string_map()
{
}



string_to_string_map & string_to_string_map::operator = (const string_to_string_map & map)
{

   if(this != &map)
   {

      base_string_to_string_map::m_nBlockSize = map.base_string_to_string_map::m_nBlockSize;
      attrib_map < base_string_to_string_map >::operator = (map);

   }

   return *this;

}
