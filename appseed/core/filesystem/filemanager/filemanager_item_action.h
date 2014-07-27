#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE item_action
   {
   public:
   
      
      item_action();
      virtual ~item_action();

      virtual bool open_file(::filemanager::data * pdata, ::fs::item_array & itema);

   };



} // namespace filemanager