#include "StdAfx.h"
#include "window_frame/FrameSchema.h"

namespace gcom
{
   namespace backview
   {
      namespace user
      {
         interaction::interaction(::ca::application * papp) :
            ca(papp),
            Interface(papp)
         {
            m_dwTimerStep = 0;
            m_colorBackground.set_rgb(RGB(63, 150, 106));
         }

         interaction::~interaction()
         {
         }


         void interaction::BackViewGetClientRect(LPRECT lprect)
         {
            GetClientRect(lprect);
         }

         void interaction::BackViewClientToScreen(LPRECT lprect)
         {
            ClientToScreen(lprect);
         }

         void interaction::BackViewUpdateScreen(rect_array & recta, UINT uiRedraw)
         {
            UNREFERENCED_PARAMETER(recta);
            UNREFERENCED_PARAMETER(uiRedraw);
            _001RedrawWindow();
         }

         void interaction::BackViewUpdateScreen()
         {
            _001RedrawWindow();
         }

         void interaction::BackViewUpdateScreen(LPCRECT lpcrect, UINT uiRedraw)
         {
            UNREFERENCED_PARAMETER(lpcrect);
            UNREFERENCED_PARAMETER(uiRedraw);
            _001RedrawWindow();
         }

         void interaction::BackViewPostMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam)
         {
            PostMessage(uiMessage, wparam, lparam);
         }

         void interaction::BackViewGetData(InterfaceData & data)
         {
            if(data.is_signalized(InterfaceDataNextImagePath))
            {
               data.m_wstrNextImagePath = BackViewGetNextBackgroundImagePath();
            }
            if(data.is_signalized(InterfaceDataEnhancedMetaFile))
            {
               data.m_henhmetafile = NULL;
            }
         }

         void interaction::BackViewSetData(InterfaceData & data)
         {
            if(data.is_signalized(InterfaceDataCurrentImagePath))
            {
               BackViewSetCurrentBackgroundImagePath(data.m_wstrCurrentImagePath);
            }
         }

         string interaction::BackViewGetNextBackgroundImagePath()
         {
            if(m_spfilesetBackgroundImage.is_set())
            {
               string strCurrentImagePath;
               data_get("gcom::backview::CurrentBackgroundImagePath", ::radix::system::idEmpty, strCurrentImagePath);
               return m_spfilesetBackgroundImage->get_next_file(strCurrentImagePath);
            }
            return "";
         }

         void interaction::BackViewSetCurrentBackgroundImagePath(const char * psz)
         {
            data_set("gcom::backview::CurrentBackgroundImagePath", ::radix::system::idEmpty, psz);
         }

         int interaction::BackViewGetBackgroundUpdateMillis()
         {
            return m_iBackgroundUpdateMillis;
         }

         COLORREF interaction::GetBackgroundColor()
         {
            return m_colorBackground.get_rgb();

         }

         void interaction::initialize_user_interaction()
         {
            ::simple_frame_window * pframe = GetTypedParent < ::simple_frame_window > ();
            if(pframe != NULL && pframe->m_workset.m_pframeschema != NULL)
            {
               color c;
               c.set_rgb(pframe->m_workset.m_pframeschema->get_border_main_body_color());
               color::hls hls;
               hls.m_dH = 1.0;
               hls.m_dL = 0.5;
               hls.m_dS = 0.5;
               c.hls_mult(hls);
               m_colorBackground.set_rgb(c.get_rgb());
            }
         }



      } // namespace user

   } //namespace backview

}  //namespace gcom







