#pragma once


namespace xml
{


   class CLASS_DECL_BASE tree_schema :
      virtual public ::object
   {
   public:
   

      stringa m_stra;
      
      
      tree_schema();
      virtual ~tree_schema();

      string get_node_name(int32_t iNameIndex);
      void set_node_name(int32_t iNameIndex, const char * lpcszNodeName);


   };
   

} // namespace xml



