#include "StdAfx.h"

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
               data_get("gcom::backview::CurrentBackgroundImagePath", ::ca::system::idEmpty, strCurrentImagePath);
               return m_spfilesetBackgroundImage->get_next_file(strCurrentImagePath);
            }
            return "";
         }

         void interaction::BackViewSetCurrentBackgroundImagePath(const char * psz)
         {
            data_set("gcom::backview::CurrentBackgroundImagePath", ::ca::system::idEmpty, psz);
         }

         int interaction::BackViewGetBackgroundUpdateMillis()
         {
            return m_iBackgroundUpdateMillis;
         }

      } // namespace user

   } //namespace backview

}  //namespace gcom







