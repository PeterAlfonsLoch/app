#pragma once


namespace filemanager
{

   class CLASS_DECL_CORE item_action
   {
   public:
      item_action();
      virtual ~item_action();

      virtual bool file_manager_open_file(
         ::filemanager::list_data * pdata, 
         ::fs::item_array & itema);

   };



} // namespace filemanager