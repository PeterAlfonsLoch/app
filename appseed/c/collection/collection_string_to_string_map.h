#pragma once


typedef CLASS_DECL_c string_map < string, const string & > base_string_to_string_map;


class CLASS_DECL_c string_to_string_map :
   virtual public ::file::byte_serializable_map < attrib_map < base_string_to_string_map >  >
{
public:


   string_to_string_map(sp(base_application) papp = NULL, ::count nBlockSize = 10);
   string_to_string_map(const string_to_string_map & map);
	~string_to_string_map();


   string_to_string_map & operator = (const string_to_string_map & map);

};
