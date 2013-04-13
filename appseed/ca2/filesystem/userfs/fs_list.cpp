#include "framework.h"


namespace fs
{


   list::list(sp(::ca::application) papp) :
      ca(papp),
      ::user::scroll_view(papp),
      m_headerctrl(papp),
      list_interface(papp),
      user::list(papp),
      user::form(papp),
      ::ca::user::form(papp),
      ::user::view(papp),
      user::form_list(papp),
      user::form_list(papp)
   {

      m_headerctrl.m_dataid = "veiev::list::header_ctrl";


      m_etranslucency = TranslucencyPresent;

   }

   list::~list()
   {
   }

   void list::install_message_handling(::ca::message::dispatch * pinterface)
   {
      ::fs::list_interface::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &list::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &list::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &list::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_CANCELMODE, pinterface, this, &list::_001OnCancelMode);
   }

   void list::_001OnCreate(::ca::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
      _001UpdateColumns();
      _001OnUpdateItemCount();
   }


   void list::_001OnTimer(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   void list::_001OnClick(UINT uiFlags, point point)
   {
      UNREFERENCED_PARAMETER(uiFlags);
      UNREFERENCED_PARAMETER(point);
      range range;
      _001GetSelection(range);
      if(range.get_item_count() > 0)
      {
         list_data * pdata = get_fs_list_data();
         item_range & itemrange = range.ItemAt(0);
         index iLItem = itemrange.get_lower_bound();
         index iUItem = itemrange.get_upper_bound();
         if(iUItem < iLItem)
         {
            iUItem = pdata->m_itema.get_upper_bound();
         }
         if(iLItem < 0)
            return;
         if(iLItem >= pdata->m_itema.get_size())
            return;
         if(iUItem >= pdata->m_itema.get_size())
            iUItem = pdata->m_itema.get_upper_bound();
         var varFile;
         var varQuery;
         if(iUItem == iLItem)
         {
            varFile = get_fs_list_data()->m_itema.get_item(iLItem).m_strPath;
         }
         else
         {
            stringa stra;
            for(index iItem = iLItem; iItem < iLItem; iItem++)
            {
               stra.add(pdata->m_itema.get_item(iItem).m_strPath);
            }
            varFile = stra;
         }
         get_document()->request_file_query(varFile, varQuery);
      }
   }


#ifdef DEBUG
   void list::assert_valid() const
   {
      ::fs::list_interface::assert_valid();
   }

   void list::dump(dump_context & dumpcontext) const
   {
      ::fs::list_interface::dump(dumpcontext);
   }
#endif //DEBUG

   void list::on_update(sp(::view) pSender, LPARAM lHint, ::ca::object * phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
      /*if(phint != ::null())
      {
         if(base < FileManagerViewUpdateHint > :: bases(phint))
         {
            FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
            if(puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
            {
               string str;
               str.Format("list(%s)", GetFileManager()->get_filemanager_data()->m_strDISection);
               m_dataid = str;
               if(GetFileManager()->get_filemanager_data()->m_bPassBk)
               {
                  ::user::list::m_bBackgroundBypass = true;
               }
               else if(GetFileManager()->get_filemanager_data()->m_bTransparentBackground)
               {
                  ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
               }
               _001UpdateColumns();
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeSynchronize))
            {
               _017Synchronize();
            }
         }
      }*/
   }

   void list::_001OnLButtonDblClk(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::ca::message::mouse, pmouse, pobj)
/*         index iItem;
      list_data * pdata = get_fs_list_data();
      if(_001HitTest_(pmouse->m_pt, iItem))
      {
         ::fs::item item;
         item.m_strPath         = pdata->m_foldera.GetFolder(iItem).m_strPath;
         GetFileManager()->get_filemanager_data()->OnFileManagerOpenFolder(item);
      }*/
   }

   void list::_001OnCancelMode(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   // trans   ::user::view::OnCancelMode();

      // TODO: add your message handler code here

   }

   bool list::pre_create_window(CREATESTRUCT& cs)
   {

      cs.style |= WS_CLIPCHILDREN;

      return ::fs::list_interface::pre_create_window(cs);
   }

} // namespace fs

