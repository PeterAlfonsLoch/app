﻿#include "StdAfx.h"


namespace fs
{


   list::list(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      m_headerctrl(papp),
      list_interface(papp),
      user::list(papp),
      user::form(papp),
      ::ca2::user::form(papp),
      user::form_list(papp),
      userbase::form_list(papp)
   {

      m_headerctrl.m_dataid = "veiev::list::header_ctrl";

      string str;
      str = "<veiev>\n";
      str += "<head>\n";
      str += "</head>\n";
      str += "<body>\n";
      // tag fixer tabjs!!
      str += "<span>Curitiba, 04 de veiev de 2008</span>\n";
      str += unitext("<h1>Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!</h1>");
      str += "<h2>Assinado Camilo Sasuke Tsumanuma.</h2>\n";
      str += "<span>htmlapp dedicado ao Carlos Gustavo Cecyn Lundgren!!</span>";
      str += "<br />";
      str += unitext("<span>Voc・conhece o ca2?</span>");
      str += "<br />";
      str += "<span>Se positivo, entre com seu nome abaixo e clique em enviar!</span>";
      str += "<br />";
      str += "<input type=\"text\" />";
      str += "</body>\n";
      str += "</veiev>\n";

      m_etranslucency = TranslucencyPresent;

   }

   list::~list()
   {
   }

   void list::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::fs::list_interface::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &list::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &list::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &list::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_CANCELMODE, pinterface, this, &list::_001OnCancelMode);
   }

   void list::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
      _001UpdateColumns();
      _001OnUpdateItemCount();
   }


   void list::_001OnTimer(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   void list::_001OnClick(UINT uiFlags, point point)
   {
      UNREFERENCED_PARAMETER(uiFlags);
      UNREFERENCED_PARAMETER(point);
      Range range;
      _001GetSelection(range);
      if(range.get_item_count() > 0)
      {
         list_data * pdata = get_fs_list_data();
         ItemRange & itemrange = range.ItemAt(0);
         index iLItem = itemrange.GetLBound();
         index iUItem = itemrange.GetUBound();
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
         get_document()->request(varFile, varQuery);
      }
   }


#ifdef _DEBUG
   void list::assert_valid() const
   {
      ::fs::list_interface::assert_valid();
   }

   void list::dump(dump_context & dumpcontext) const
   {
      ::fs::list_interface::dump(dumpcontext);
   }
#endif //_DEBUG

   void list::on_update(::view * pSender, LPARAM lHint, ::radix::object * phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
      /*if(phint != NULL)
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

   void list::_001OnLButtonDblClk(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
/*         index iItem;
      list_data * pdata = get_fs_list_data();
      if(_001HitTest_(pmouse->m_pt, iItem))
      {
         ::fs::item item;
         item.m_strPath         = pdata->m_foldera.GetFolder(iItem).m_strPath;
         GetFileManager()->get_filemanager_data()->OnFileManagerOpenFolder(item);
      }*/
   }

   void list::_001OnCancelMode(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   // trans   ::userbase::view::OnCancelMode();

      // TODO: add your message handler code here

   }

   BOOL list::pre_create_window(CREATESTRUCT& cs)
   {

      cs.style |= WS_CLIPCHILDREN;

      return ::fs::list_interface::pre_create_window(cs);
   }

} // namespace fs

