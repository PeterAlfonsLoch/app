#include "framework.h"


namespace ca2
{


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



      bool application::initialize1()
      {

         if(!::cubebase::application::initialize1())
            return false;

         return true;

      }


      bool application::initialize()
      {


         if(is_cube())
         {
            System.factory().cloneable_small < int_biunique > ();
            System.factory().creatable_small < ::user::edit_plain_text > ();
            System.factory().cloneable_small < XfplayerViewLine > ();
            System.factory().creatable_small < ::user::place_holder > ();
            System.factory().creatable_small < ::user::place_holder_container > ();
         }

         if(!::cubebase::application::initialize())
            return false;

         return true;
      }

      int application::exit_instance()
      {
         if(is_cube())
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


      void application::SendMessageToWindows(UINT message, WPARAM wparam, LPARAM lparam)
      {
         ::user::interaction_ptr_array wnda = frames();
         for(int i = 0; i < wnda.get_size(); i++)
         {
            ::user::interaction * pwnd = wnda.element_at(i);
            if(pwnd != NULL && pwnd->IsWindow())
            {
               pwnd->send_message(message, wparam, lparam);
               pwnd->SendMessageToDescendants(message, wparam, lparam);
            }
         }
      }


      int application::GetVisibleFrameCountExcept(::user::interaction * pwndExcept)
      {
         ::user::interaction_ptr_array wnda = frames();
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
         ::user::interaction_ptr_array wnda = frames();
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
         ::user::interaction_ptr_array wnda = frames();
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

      string application::message_box(const char * pszMatter, gen::property_set & propertyset)
      {

         class ::ca8::message_box box(this);

         box.show(pszMatter, propertyset);

         return box.m_strResponse;

      }



   } // namespace user


} // namespace ca2