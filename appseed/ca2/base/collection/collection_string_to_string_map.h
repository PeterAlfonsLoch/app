#pragma once


typedef CLASS_DECL_ca2 string_map < string, const string & > base_string_to_string_map;


class CLASS_DECL_ca2 string_to_string_map :
   virtual public ::ca2::byte_serializable_map < attrib_map < base_string_to_string_map >  >
{
public:


   string_to_string_map(::ca2::application * papp = NULL, ::count nBlockSize = 10);
   string_to_string_map(const string_to_string_map & map);
	~string_to_string_map();


   string_to_string_map & operator = (const string_to_string_map & map);

};
