#pragma once


namespace filemanager
{

   class CLASS_DECL_ca2 item_action
   {
   public:
      item_action();
      virtual ~item_action();

      virtual bool file_manager_open_file(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

   };



} // namespace filemanager