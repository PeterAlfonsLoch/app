#include "framework.h"


string_to_string_map::string_to_string_map(int_ptr nBlockSize) :
   base_string_to_string_map(nBlockSize)
{

}


string_to_string_map::string_to_string_map(const string_to_string_map & map) :
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
