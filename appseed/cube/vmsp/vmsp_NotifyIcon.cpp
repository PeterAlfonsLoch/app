#include "StdAfx.h"
#include "notify_icon.h"

namespace vmsp
{

   notify_icon::notify_icon(::ca::application * papp) :
      ca(papp)
   {
      m_pnotifyicon = new userbase::notify_icon(papp);
   }

   notify_icon::~notify_icon()
   {
      if(m_pnotifyicon != NULL)
      {
         delete m_pnotifyicon;
         m_pnotifyicon = NULL;
      }
   }

   void notify_icon::Start()
   {
      m_pnotifyicon->create(0, this, (HICON) ::LoadImage(
            NULL, 
            System.dir_matter("mplite/mainframe/icon.ico"), 
            IMAGE_ICON,
            16, 16,
            LR_LOADFROMFILE));
   }

   void notify_icon::OnNotifyIconContextMenu(UINT uiNotifyIcon)
   {
   }

   notify_icon * notify_icon::AppGetNotifyIcon(::ca::application * papp)
   {
      return (dynamic_cast < vmsp::application * >(papp))->GetNotifyIcon();
   }


   void notify_icon::AddHiddenWindow(::ca::window * pwnd)
   {
      m_wndptraHidden.add(pwnd);
   }

   void notify_icon::OnNotifyIconLButtonDblClk(UINT uiNotifyIcon)
   {
      while(m_wndptraHidden.get_size() > 0)
      {
         m_wndptraHidden.element_at(0)->ShowWindow(SW_SHOW);
         m_wndptraHidden.remove_at(0);
      }
   }

} // namespace vmsp

