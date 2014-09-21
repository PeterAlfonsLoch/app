#include "framework.h"


namespace filemanager
{


   file_list_callback::file_list_callback()
   {
      m_pimagelistSubItemHover = NULL;
      m_pimagelistItemHover = NULL;
      m_pimagelistNormal = NULL;

   }

   file_list_callback::~file_list_callback()
   {

   }

   bool file_list_callback::initialize()
   {
      sp(::aura::application) papp = get_app();
      m_pimagelistSubItemHover = new image_list(papp);
      m_pimagelistItemHover = new image_list(papp);
      m_pimagelistNormal = new image_list(papp);

      ::draw2d::graphics_sp spgraphics(allocer());
      spgraphics->CreateCompatibleDC(NULL);

      m_pimagelistSubItemHover->create(16, 16, 0, 10, 10);

      m_pimagelistSubItemHover->add_matter("filemanager/execute_16.png");

      System.visual().imaging().CreateHueImageList(
         spgraphics,
         m_pimagelistNormal,
         m_pimagelistSubItemHover,
         RGB(220, 220, 215),
         0.50);

      System.visual().imaging().Createcolor_blend_ImageList(
         m_pimagelistItemHover,
         m_pimagelistSubItemHover,
         RGB(220, 220, 215),
         127);
      return true;
   }


   int32_t file_list_callback::GetActionButtonCount()
   {
      return 0;
   }

   void file_list_callback::InitializeActionButton(id id, sp(BaseButtonControl) pbutton)
   {
      switch (id)
      {
      case 0: // ExecuteButton
      {
                 pbutton->m_pimagelistNormal = m_pimagelistSubItemHover;
                 pbutton->m_iImageNormal = 0;
                 pbutton->m_pimagelistItemHover = m_pimagelistSubItemHover;
                 pbutton->m_iImageItemHover = 0;
                 pbutton->m_pimagelistSubItemHover = m_pimagelistSubItemHover;
                 pbutton->m_iImageSubItemHover = 0;
      }
         break;
      }
   }

   void file_list_callback::OnButtonAction(id i, sp(::fs::item)  item)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(item);
   }



   bool file_list_callback::GetMenuItemCallback(id iId)
   {
      UNREFERENCED_PARAMETER(iId);
      return false;
   }

   void file_list_callback::OnMenuItemAction(id iId, const ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(iId);
      UNREFERENCED_PARAMETER(itema);
   }

   void file_list_callback::GetMenuItemUpdate(id iId, const ::fs::item_array & itema, cmd_ui * pcmdui)
   {
      UNREFERENCED_PARAMETER(iId);
      UNREFERENCED_PARAMETER(itema);
      UNREFERENCED_PARAMETER(pcmdui);
   }

   sp(image_list) file_list_callback::GetActionButtonImageList(id i)
   {
      UNREFERENCED_PARAMETER(i);
      //if(i == 0)
      {
         //return Platform.userex()->shellimageset().GetImageList16();
      }
      return NULL;
   }



} // namespace filemanager



