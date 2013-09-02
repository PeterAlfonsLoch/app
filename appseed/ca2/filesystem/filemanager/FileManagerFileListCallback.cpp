#include "framework.h"

FileManagerFileListCallback::FileManagerFileListCallback()
{
   m_pimagelistSubItemHover   = NULL;
   m_pimagelistItemHover      = NULL;
   m_pimagelistNormal         = NULL;

}

FileManagerFileListCallback::~FileManagerFileListCallback()
{

}

bool FileManagerFileListCallback::initialize()
{
   sp(::application) papp = get_app();
   m_pimagelistSubItemHover   = new image_list(papp);
   m_pimagelistItemHover      = new image_list(papp);
   m_pimagelistNormal         = new image_list(papp);

   ::draw2d::graphics_sp spgraphics(allocer());
   spgraphics->CreateCompatibleDC(NULL);

   m_pimagelistSubItemHover->create(16, 16, 0,  10, 10);

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


int32_t FileManagerFileListCallback::GetActionButtonCount()
{
   return 0;
}

void FileManagerFileListCallback::InitializeActionButton(id id, sp(BaseButtonControl) pbutton)
{
   switch(id)
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

void FileManagerFileListCallback::OnButtonAction(id i, sp(::fs::item)  item)
{
   UNREFERENCED_PARAMETER(i);
   UNREFERENCED_PARAMETER(item);
}



bool FileManagerFileListCallback::GetMenuItemCallback(id iId)
{
   UNREFERENCED_PARAMETER(iId);
   return false;
}

void FileManagerFileListCallback::OnMenuItemAction(id iId, const ::fs::item_array & itema)
{
   UNREFERENCED_PARAMETER(iId);
   UNREFERENCED_PARAMETER(itema);
}

void FileManagerFileListCallback::GetMenuItemUpdate(id iId, const ::fs::item_array & itema, cmd_ui * pcmdui)
{
   UNREFERENCED_PARAMETER(iId);
   UNREFERENCED_PARAMETER(itema);
   UNREFERENCED_PARAMETER(pcmdui);
}

sp(image_list) FileManagerFileListCallback::GetActionButtonImageList(id i)
{
   UNREFERENCED_PARAMETER(i);
   //if(i == 0)
   {
      //return System.user()->shellimageset().GetImageList16();
   }
   return NULL;
}

