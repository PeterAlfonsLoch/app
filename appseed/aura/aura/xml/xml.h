#pragma once


#include "xml_enum.h"


#include "pugixml.hpp"
//#include "xml_xmlite.h"

#include "xml_entity.h"
#include "xml_disp_option.h"
#include "xml_parse_info.h"
#include "xml_attr.h"
//#include "xml_node.h"
#include "xml_document.h"
#include "xml_exportable.h"
#include "xml_importable.h"
#include "xml_tree_schema.h"
#include "xml_var_exchange.h"
#include "xml_tree_base.h"
#include "xml_output_tree.h"
#include "xml_input_tree.h"
#include "xml_property_exchange.h"
#include "xml_base_array.h"


#include "xml_edit.h"
#include "xml_data.h"


#include "xml_departament.h"



inline ::file::output_stream & operator << (::file::output_stream & os,const ::xml::node & node)
{

   node.print(os);

   return os;

}

inline ::file::input_stream & operator >> (::file::input_stream & is,::xml::node & node)
{

   string str;
   is >> str;
   node.append_buffer(str,str.get_length());

   return is;

}

inline ::file::output_stream & operator << (::file::output_stream & os,const ::xml::document & doc)
{

   doc.print(os);

   return os;

}

inline ::file::input_stream & operator >> (::file::input_stream & is,::xml::document & doc)
{

   string str;
   is >> str;
   doc.load(str);

   return is;

}
