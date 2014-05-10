#include "framework.h"


namespace filemanager
{



   frame::frame(sp(::base::application) papp) :
      element(papp),
      simple_frame_window(papp),
      m_toolbar(papp),
      m_menubar(papp)
   {
   }

   frame::~frame()
   {
   }


   // BEGIN_MESSAGE_MAP( frame, simple_frame_window)
   //{{__MSG_MAP( frame)
   // xxx   
   //}}__MSG_MAP
   // END_MESSAGE_MAP()

   /////////////////////////////////////////////////////////////////////////////
   //  frame message handlers

   void  frame::_001OnCreate(signal_details * pobj)
   {

      pobj->previous();


   }

   bool  frame::DestroyBars()
   {

      m_toolbar.DestroyWindow();
      m_toolbar.RemoveAllTools();

      return true;
   }


   bool  frame::CreateBars()
   {
      sp(document) pdoc = (GetActiveDocument());

      ASSERT(pdoc != NULL);
      ASSERT(base_class <  document > ::bases(pdoc));

      DestroyBars();

      // CBaseRelation < UINT, UINT, UINT, UINT > * prel;
      //   BaseMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
      //m_menuhook.Initialize(
      // BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      //BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      //NULL,
      //System.visual().font_central().GetMenuFont());

      //m_menuhook.Install(this);

      //UINT uiMenuBar = pdoc->get_filemanager_data()->m_pschema->m_uiMenuBar;

      //  SetMenu(NULL);

      /*    if (!m_menubar.CreateEx(this))
         {
         TRACE0("Failed to create toolbar\n");
         return false;      // fail to create
         }*/
      /*
         if(!m_menubar.Initialize(
         BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
         BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListHueLight(),
         NULL,
         System.visual().font_central().GetMenuFont()) ||
         VMS_FAILED(m_menubar.LoadMenuBar(uiMenuBar)))
         {
         TRACE0("Failed to create toolbar\n");
         return false;      // fail to create
         }
         */
      string strToolBar = pdoc->get_filemanager_data()->m_pschema->m_strToolBar;


      if (strToolBar.is_empty())
      {
         if (pdoc->get_filemanager_data()->is_saving())
         {
            strToolBar = pdoc->get_filemanager_data()->m_strToolBarSave;
         }
         else
         {
            strToolBar = pdoc->get_filemanager_data()->m_strToolBar;
         }
      }

      if (!m_toolbar.CreateEx(this) ||
         !m_toolbar.LoadXmlToolBar(Application.file().as_string(Application.dir().matter(strToolBar))))
      {
         TRACE0("Failed to create toolbar\n");
         return false;      // fail to create
      }



      return true;
   }


   void  frame::install_message_handling(::message::dispatch * pinterface)
   {
      simple_frame_window::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_SETTEXT, pinterface, this, &frame::_001OnSetText);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate);
   }


   void  frame::_001OnSetText(signal_details * pobj)
   {
      //   SCAST_PTR(::message::base, pbase, pobj)

      pobj->previous();

      string str;

      ::filemanager::tab_view * ptabview = GetTypedParent < ::filemanager::tab_view >();
      if (ptabview != NULL)
      {
         GetWindowText(str);
         ptabview->SetTitleById(m_idTab, str);
      }

   }



} // namespace filemanager




