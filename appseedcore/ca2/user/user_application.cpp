#include "StdAfx.h"

namespace user
{

   application::application()
   {

      //gen::application * papp = dynamic_cast <gen::application *>(System.GetThread()->m_pAppThread);
      //gen::connect(papp->m_signalAppLanguageChange, this, &application::VmsGuiiOnAppLanguage);

      m_pkeyboard = NULL;
      m_pwindowmap = NULL;

   }

   application::~application()
   {
   }


   void application::SendMessageToWindows(UINT message, WPARAM wparam, LPARAM lparam)
   {
      user::LPWndArray wnda = frames();
      for(int i = 0; i < wnda.get_size(); i++)
      {
         ::user::interaction * pwnd = wnda.element_at(i);
         if(pwnd != NULL && pwnd->IsWindow())
         {
            pwnd->SendMessage(message, wparam, lparam);
            pwnd->SendMessageToDescendants(message, wparam, lparam);
         }
      }
   }


   int application::GetVisibleFrameCountExcept(::user::interaction * pwndExcept)
   {
      user::LPWndArray wnda = frames();
      int iCount = 0;
      for(int i = 0; i < wnda.get_size(); i++)
      {
           ::user::interaction * pwnd = wnda.element_at(i);
           if(pwnd != NULL &&
               pwnd != pwndExcept &&
               pwnd->IsWindowVisible())
           {
               iCount++;
           }
       }
       return iCount;
   }

   int application::GetVisibleTopLevelFrameCountExcept(::user::interaction * pwndExcept)
   {
      user::LPWndArray wnda = frames();
      int iCount = 0;
      for(int i = 0; i < wnda.get_size(); i++)
      {
         ::user::interaction * pwnd = wnda.element_at(i);
         if(pwnd != NULL &&
            pwnd != pwndExcept &&
            pwnd->IsWindow() &&
            pwnd->IsWindowVisible() &&
            !(pwnd->GetStyle() & WS_CHILD))
         {
            iCount++;
         }
      }
      return iCount;
   }

   int application::GetVisibleFrameCount()
   {
      user::LPWndArray wnda = frames();
      int iCount = 0;
      for(int i = 0; i < wnda.get_size(); i++)
      {
         ::user::interaction * pwnd = wnda.element_at(i);
         if(pwnd != NULL
            && pwnd->IsWindow()
            && pwnd->IsWindowVisible())
         {
            iCount++;
         }
      }
      return iCount;
   }

   void application::VmsGuiiOnAppLanguage(gen::signal_object * pobject)
   {
      SendMessageToWindows(gen::application::APPM_LANGUAGE, 0, (LPARAM) pobject);
   }

   bool application::initialize()
   {
      if(is_system())
      {
         m_pwindowmap = new class window_map();
      }
      else
      {
         m_pwindowmap = System.m_pwindowmap;
      }

      m_pkeyboard = new ::user::keyboard(this);


      if(is_system())
      {
         System.factory().cloneable_small < int_biunique > ();
         System.factory().cloneable_small < ::user::edit_plain_text > ();
         System.factory().cloneable_small < XfplayerViewLine > ();
         System.factory().creatable_small < place_holder > ();
         System.factory().creatable_small < place_holder_container > ();
      }

      if(!::ca4::application::initialize())
         return false;

      if(!database::application::initialize())
         return false;

      if(!visual::application::initialize())
         return false;

      return true;
   }

   int application::exit_instance()
   {
      if(is_system())
      {
         if(m_pwindowmap != NULL)
         {
            delete m_pwindowmap;
            m_pwindowmap = NULL;
         }
      }
      try
      {
         ::visual::application::exit_instance();
      }
      catch(...)
      {
      }
      try
      {
         ::database::application::exit_instance();
      }
      catch(...)
      {
      }
      try
      {
         ::ca4::application::exit_instance();
      }
      catch(...)
      {
      }
      return 0;
   }


   ca::type_info application::controltype_to_typeinfo(user::control::e_type e_type)
   {
      switch(e_type)
      {
      case user::control::type_button:
         return ::ca::get_type_info < ::user::button > ();
      case user::control::type_edit_plain_text:
         return ::ca::get_type_info < ::user::edit_plain_text > ();
      }
      return ::ca::type_info();
   }

   ::user::keyboard & application::keyboard()
   {
      if(this != &System)
      {
         application * papp = dynamic_cast < application * > (&System);
         return papp->keyboard();
      }
      return *m_pkeyboard;
   }


   bool application::set_keyboard_layout(const char * pszPath, bool bUser)
   {
      on_set_keyboard_layout(pszPath, bUser);
      return true;
   }

   void application::on_set_keyboard_layout(const char * pszPath, bool bUser)
   {
      UNREFERENCED_PARAMETER(pszPath);
      UNREFERENCED_PARAMETER(bUser);
   }

   class window_map & application::window_map()
   {
      return *m_pwindowmap;
   }

} // namespace user
