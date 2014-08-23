#include "framework.h"


string_to_string::string_to_string(sp(::axis::application) papp, int_ptr nBlockSize) :
   element(papp),
   base_string_to_string(papp,  nBlockSize)
{

}


string_to_string::string_to_string(const string_to_string & map) :
   element(map.get_app()),
   base_string_to_string(dynamic_cast < const base_string_to_string & > (map))
{

}


string_to_string::~string_to_string()
{
}



string_to_string & string_to_string::operator = (const string_to_string & map)
{

   if(this != &map)
   {

      base_string_to_string::m_nBlockSize = map.base_string_to_string::m_nBlockSize;
      attrib_map < base_string_to_string >::operator = (map);

   }

   return *this;

}
