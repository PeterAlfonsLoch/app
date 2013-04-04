#pragma once


typedef CLASS_DECL_ca string_map < string, const string & > base_string_to_string_map;


class CLASS_DECL_ca string_to_string_map :
   virtual public ::ca::byte_serializable_map < attrib_map < base_string_to_string_map >  >
{
public:


   string_to_string_map(int_ptr nBlockSize = 10);
   string_to_string_map(const string_to_string_map & map);
	~string_to_string_map();


   string_to_string_map & operator = (const string_to_string_map & map);

};
