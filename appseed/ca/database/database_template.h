#pragma once

namespace database
{
   typedef CLASS_DECL_ca array < selection_item, selection_item & > selection_item_array;
   typedef CLASS_DECL_ca comparable_array < client *, client * > client_ptra;

   class CLASS_DECL_ca record :
      public var_array
   {
   };

   class CLASS_DECL_ca query_data :
      public array <record, record &>
   {
   };

   class CLASS_DECL_ca field_definition : 
      virtual public array < field_definition_item >
   {
   public:
      
   };

} // namespace database