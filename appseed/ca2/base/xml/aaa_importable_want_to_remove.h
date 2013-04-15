#pragma once

namespace xml
{

   class input_tree;

   class CLASS_DECL_ca2 importable
   {
   public:


      importable();


      virtual void xml_import(input_tree & xmlif) = 0;


   };


} // namespace xml
