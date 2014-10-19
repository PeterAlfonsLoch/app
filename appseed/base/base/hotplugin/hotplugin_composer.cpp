#include "framework.h"


namespace hotplugin
{


   composer::composer()
   {

      m_bFocus                   = false;

      m_bActive                  = false;

      m_bActivationStateSent     = false;

      m_bSendActivationState     = false;

      m_bInit                 = true; // default implemenation assume initialized on construction, derivations may change it

      m_estatus               = status_start_system;
      m_bSystemOk             = false;
      m_bTryInitHost          = false;
      m_bHostOk               = false;
      m_bTryInitWindow        = false;
      m_bWindowOk             = false;
      m_bOk                   = false;
      m_bResponsive           = true;
      m_bWrite                = false;

      m_bRectSent             = false;

   }
   
   
   composer::~composer()
   {

   }



   ::hotplugin::host * composer::create_host(sp(::base::system) psystem)
   {

      return NULL;

   }


   void composer::hotplugin_composer_on_timer()
   {

      if(m_estatus == status_start_system)
      {

         if(m_bSystemOk)
         {

            m_estatus = status_start_host;

         }
         else
         {

            if(::hotplugin::get_base_system() == NULL)
            {

               ::hotplugin::start_base_system();

            }
            else
            {


               if(::hotplugin::get_base_system()->m_bReady)
               {

                  if(::hotplugin::get_base_system()->m_iReturnCode != 0)
                  {

                     string str;
                     
                     str.Format("::hotplugin::g_pbasesystem initialization error %d",::hotplugin::get_base_system()->m_iReturnCode);

                     ::OutputDebugString(str);

                  }
                  else
                  {

                     m_bSystemOk = true;

                  }

               }

            }


         }


      }
      else if(m_estatus == status_start_host)
      {

         if(m_bHostOk)
         {

            m_estatus = status_init_host;

         }
         else if(m_bInit)
         {

            if(m_pbasehost == NULL)
            {

               m_pbasehost = create_host(::hotplugin::get_base_system());

               m_pbasehost->m_pbasecomposer = this;

               m_pbasehost->hotplugin_host_begin();

            }
            else
            {

               if(m_pbasehost->m_bReady)
               {

                  if(m_pbasehost->m_iReturnCode != 0)
                  {

                     string str;

                     str.Format("::hotplugin::composer::m_pbasehost initialization error %d",::hotplugin::get_base_system()->m_iReturnCode);

                     ::OutputDebugString(str);

                  }
                  else
                  {

                     m_bHostOk = true;

                  }

               }

            }

         }

      }
      else if(m_estatus == status_init_host)
      {

         if(m_bHostInit)
         {

            m_estatus = status_start_window;

         }
         else
         {

            m_bTryInitHost = true;

            if(!m_pbasehost->hotplugin_host_is_initialized())
            {

               if(m_pbasehost->hotplugin_host_initialize())
               {

                  m_bHostInit = true;

               }

            }

         }

      }
      else if(m_estatus == status_start_window)
      {

         if(m_bWindowOk)
         {

            m_estatus = status_ok;

         }
         else if(!m_bTryInitWindow)
         {

            m_bTryInitWindow = true;

            if(on_composer_init_window())
            {
               
               m_bWindowOk = true;

            }

         }

      }
      else if(m_estatus == status_ok)
      {

         if(!m_bOk)
         {

            m_bOk = true;

         }
      }


      if(m_pbasehost != NULL && m_pbasehost->hotplugin_host_is_initialized())
      {

         if(m_bWrite)
         {

            m_bWrite = false;

            m_pbasehost->hotplugin_host_on_write(); // at least m_strPluginUrl is ready

         }

      }


      if(m_bOpenUrl)
      {

         m_bOpenUrl = false;

         if(!_open_link(m_strOpenUrl, m_strOpenTarget))
         {

            m_bOpenUrl = true;

         }

      }

   }


   bool composer::on_composer_init_window()
   {

      return true;

   }


   bool composer::open_link(const string & strLink,const string & pszTarget)
   {

      m_strOpenUrl = strLink;

      m_strOpenTarget = pszTarget;

      m_bOpenUrl = true;

      return true;

   }


   bool composer::_open_link(const string & strLink,const string & pszTarget)
   {

      return true;

   }


   // if composer on paint returns (returns true), it has painted something meaningful : no other painting is needed or even desired (finally when system, and host are ok, 
   // if host returns in a fashion-timed way the response for bitmap, it draw this bitmap, and not the default waiting [hall] screen painted by this composer).

#ifdef WINDOWS

   bool composer::windows_on_paint(HDC hdc)
   {

      if((!m_bOk || !m_bResponsive) || m_pbasehost == NULL || !m_pbasehost->hotplugin_host_is_initialized() || m_strEntryHallText.has_char())
      {

         ::rect rect = m_rect;

         POINT pt;

         //::SetViewportOrgEx(hdc, rect.left, rect.top, &pt);

         ::hotplugin::entry_hall_windows_on_paint(hdc,m_rect,m_strEntryHallText);

         return true;

      }
      /*else 
      {

         m_pbasehost->m_bOnPaint = true;

         ::draw2d::graphics_sp g(m_pbasehost->allocer());

         g->Attach((HDC)hdc);

         ::rect rect;

         m_pbasehost->GetWindowRect(rect);

         m_pbasehost->on_paint(g,rect);

         g->Detach();

         m_pbasehost->m_bOnPaint = false;

      }*/
      
      return false;


   }

#endif

   void composer::deferred_prodevian_redraw()
   {

      if(m_pbasehost != NULL && m_pbasehost->hotplugin_host_is_initialized())
      {

         m_pbasehost->deferred_prodevian_redraw();

      }

   }

   
   bool composer::is_active()
   {

      return true;

   }


} // namespace hotplugin






