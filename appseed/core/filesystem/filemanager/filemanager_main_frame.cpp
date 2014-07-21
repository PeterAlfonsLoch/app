#include "framework.h"


namespace filemanager
{



   main_frame::main_frame(sp(::base::application) papp) :
      element(papp),
      simple_frame_window(papp),
      m_menubar(papp),
      m_toolbar(papp)
   {
   }

   main_frame::~main_frame()
   {
   }



   void main_frame::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);


   }


   bool main_frame::CreateBars()
   {
      
      sp(document) pdoc = (GetActiveDocument());

      ASSERT(pdoc != NULL);
      ASSERT(base_class < document >::bases(pdoc));

      string strToolBar;

      if (pdoc->get_filemanager_data()->is_saving())
      {
         strToolBar = pdoc->get_filemanager_data()->m_pschema->m_strToolBarSave;
      }
      else
      {
         strToolBar = pdoc->get_filemanager_data()->m_pschema->m_strToolBar;
      }

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


      string str = session().file().as_string(session().dir().matter(strToolBar));

      if (!m_toolbar.CreateEx(this) ||
         !m_toolbar.LoadXmlToolBar(session().file().as_string(session().dir().matter(strToolBar))))
      {
         TRACE0("Failed to create toolbar\n");
         return false;      // fail to create
      }

      return true;

   }





} // namespace filemanager



