#pragma once


class ::fs::item;

namespace mplite
{

   class filelist_callback :
      public FileManagerFileListCallback,
      virtual public ::radix::object
   {
   public:
      filelist_callback(::ca::application * papp);
      virtual ~filelist_callback();

      image_list            m_imagelistSubItemHover;
      image_list            m_imagelistItemHover;
      image_list            m_imagelistNormal;


      virtual int GetActionButtonCount();
      virtual void InitializeActionButton(id i, BaseButtonControl * pbutton);
      virtual void OnButtonAction(id i, ::fs::item & item);

      virtual void OnMenuItemAction(id iId, ::fs::item_array & itema);
      virtual bool GetMenuItemCallback(id iId);
      virtual void GetMenuItemUpdate(id iId, ::fs::item_array & itema, cmd_ui * pcmdui);

   };

} // namespace mplite
