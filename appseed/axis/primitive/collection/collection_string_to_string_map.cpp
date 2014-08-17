#include "framework.h"


string_to_string::string_to_string(sp(::base::application) papp, int_ptr nBlockSize) :
   element(papp),
   axis_string_to_string(papp,  nBlockSize)
{

}


string_to_string::string_to_string(const string_to_string & map) :
   element(map.get_app()),
   axis_string_to_string(dynamic_cast < const axis_string_to_string & > (map))
{

}


string_to_string::~string_to_string()
{
}



string_to_string & string_to_string::operator = (const string_to_string & map)
{

   if(this != &map)
   {

      axis_string_to_string::m_nBlockSize = map.axis_string_to_string::m_nBlockSize;
      attrib_map < axis_string_to_string >::operator = (map);

   }

   return *this;

}
