#pragma once


typedef CLASS_DECL_c string_map < string, const string & > base_string_to_string;


class CLASS_DECL_c string_to_string :
   virtual public ::file::byte_serializable_map < attrib_map < base_string_to_string >  >
{
public:


   string_to_string(sp(base_application) papp = NULL, ::count nBlockSize = 10);
   string_to_string(const string_to_string & map);
	~string_to_string();


   string_to_string & operator = (const string_to_string & map);

};
