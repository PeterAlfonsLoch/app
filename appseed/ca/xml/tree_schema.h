#pragma once

namespace xml
{


class CLASS_DECL_ca tree_schema  
{
public:
   tree_schema();
   virtual ~tree_schema();

   string get_node_name(int iNameIndex);
   void set_node_name(int iNameIndex, const char * lpcszNodeName);

protected:
   stringa m_stra;

};

} // namespace xml