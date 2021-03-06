//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   menu_base::menu_base():
      menu_base(get_app())
   {

   }


   menu_base::menu_base(::aura::application * papp):
      ::object(papp)
   {

   }


   menu_base::menu_base(::aura::application * papp, menu_base_item * pitem) :
      ::object(papp)
   {

      m_pitem = pitem;

   }


   menu_base::~menu_base()
   {

   }


   void menu_base::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::interaction::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pdispatch, this, &menu_base::_001OnShowWindow);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pdispatch, this, &menu_base::_001OnDestroy);


   }


   bool menu_base::create_menu(const stringa & straCommand, const stringa & straCommandTitle)
   {
      
      if(m_pitem.is_null())
      {
         
         m_pitem = Application.alloc(System.type_info < menu_base_item > ());
         
      }

      return m_pitem->create_menu(straCommand, straCommandTitle);

   }

   
   bool menu_base::LoadMenu(sp(::xml::node) lpnode)
   {

      if(m_pitem.is_null())
      {
         
         m_pitem = Application.alloc(System.type_info < menu_base_item > ());
         
      }
      
      return m_pitem->load_menu(lpnode);

   }


   bool menu_base::LoadXmlMenu(const char * pszMatter)
   {

      if(m_pitem.is_null())
      {
         
         m_pitem = Application.alloc(System.type_info < menu_base_item > ());
         
      }

      xml::document doc(get_app());

      string strPath = Application.dir().matter(pszMatter);

      string strXml = Application.file().as_string(strPath);

      if (!doc.load(strXml))
      {

         return false;

      }

      return LoadMenu(doc.get_root());


   }


   void menu_base::destroy_menu()
   {
      
      m_pitem.release();
      
   }
  

   bool menu_base::TrackPopupMenu(int32_t iFlags, POINT pt, ::user::interaction * oswindowParent)
   {

      return true;

   }

   void menu_base::_001OnShowWindow(signal_details * pobj)
   {

       UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::show_window, pshow, pobj);

      //if (!pshow->m_bShow)
      //{

      //   if (m_pmenubaseThis != NULL)
      //   {

      //      sp(menu_base) * pthis = m_pmenubaseThis;

      //      m_pmenubaseThis = NULL;

      //      pthis->release();

      //   }

      //}


   }

   void menu_base::_001OnDestroy(signal_details * pobj)
   {
       
       UNREFERENCED_PARAMETER(pobj);
       

   }


} // namespace user



