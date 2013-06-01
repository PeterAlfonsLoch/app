#include "framework.h"
#include "FileManagerViewUpdateHint.h"
#include "SimpleFolderListView.h"


namespace filemanager
{


   SimpleFolderListView::SimpleFolderListView(sp(::ca::application) papp) :
      ca(papp),
      m_headerctrl(papp),
      
      ::user::scroll_view(papp),
      ::user::list(papp),
      SimpleFolderListInterface(papp)
   {

      m_pheaderctrl     = &m_headerctrl;

      m_pheaderctrl->SetBaseListCtrlInterface(this);

   }


   SimpleFolderListView::~SimpleFolderListView()
   {

   }


   void SimpleFolderListView::install_message_handling(::ca::message::dispatch * pinterface)
   {
      ::user::view::install_message_handling(pinterface);
      SimpleFolderListInterface::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &SimpleFolderListView::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_CANCELMODE, pinterface, this, &SimpleFolderListView::_001OnCancelMode);
   }


   // BEGIN_MESSAGE_MAP(SimpleFolderListView, ::user::view)
   //{{__MSG_MAP(SimpleFolderListView)
   /*
   ON_WM_LBUTTONDBLCLK()
   ON_WM_CANCELMODE()
   */
   //}}__MSG_MAP
   // END_MESSAGE_MAP()

   /////////////////////////////////////////////////////////////////////////////
   // SimpleFolderListView drawing

   void SimpleFolderListView::OnDraw(::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      //sp(::user::document) pDoc = get_document();
      // TODO: add draw code here
   }

   /////////////////////////////////////////////////////////////////////////////
   // SimpleFolderListView diagnostics

#ifdef DEBUG
   void SimpleFolderListView::assert_valid() const
   {
      ::user::view::assert_valid();
   }

   void SimpleFolderListView::dump(dump_context & dumpcontext) const
   {
      ::user::view::dump(dumpcontext);
   }
#endif //DEBUG

   void SimpleFolderListView::on_update(sp(::user::view) pSender, LPARAM lHint, ::ca::object * phint) 
   {
      FileManagerViewInterface::on_update(pSender, lHint, phint);  
      if(phint != NULL)
      {
         if(base < FileManagerViewUpdateHint > :: bases(phint))
         {
            FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
            if(puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
            {
               string str;
               str.Format("SimpleFolderListView(%s)", GetFileManager()->get_filemanager_data()->m_strDISection);
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
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeSynchronizePath))
            {
               _017Synchronize();
            }
         }
      }
   }

   void SimpleFolderListView::_001OnLButtonDblClk(::ca::signal_object * pobj) 
   {
      SCAST_PTR(::ca::message::mouse, pmouse, pobj)
         index iItem;
      if(_001HitTest_(pmouse->m_pt, iItem))
      {
         GetFileManager()->get_filemanager_data()->OnFileManagerOpenFolder(new::fs::item(m_foldera.GetFolder(iItem).m_strPath));
      }
   }

   void SimpleFolderListView::_001OnCancelMode(::ca::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      // trans   ::user::view::OnCancelMode();

      // TODO: add your message handler code here

   }

   bool SimpleFolderListView::pre_create_window(CREATESTRUCT& cs) 
   {

      cs.style |= WS_CLIPCHILDREN;

      return ::user::view::pre_create_window(cs);
   }


} // namespace filemanager








