#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE file_list_callback :
      virtual public ::object
   {
   public:

      sp(image_list)           m_pimagelistSubItemHover;
      sp(image_list)           m_pimagelistItemHover;
      sp(image_list)           m_pimagelistNormal;

      file_list_callback();
      virtual ~file_list_callback();

      virtual bool initialize();

      virtual int32_t GetActionButtonCount();
      virtual sp(image_list) GetActionButtonImageList(id i);
      virtual void InitializeActionButton(id i, sp(BaseButtonControl) pbutton);
      virtual void OnButtonAction(id i, sp(::fs::item)  item);

      virtual bool GetMenuItemCallback(id iId);
      virtual void OnMenuItemAction(id iId, const ::fs::item_array & itema);
      virtual void GetMenuItemUpdate(id iId, const ::fs::item_array & itema, cmd_ui * pcmdui);

   };


} // namespace filemanager