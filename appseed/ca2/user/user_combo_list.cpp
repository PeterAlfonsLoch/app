#include "framework.h"


namespace user
{


   combo_list::combo_list()
   {

   }

   combo_list::~combo_list()
   {
   }


   void combo_list::install_message_handling(::gen::message::dispatch * pdispatch)
   {

      ::user::control::install_message_handling(pdispatch);

   }


   void combo_list::_001OnDraw(::ca::graphics * pdc)
   {

      count c = m_pcombo->_001GetListCount();
      
      string strItem;

      rect rectClient;

      GetClientRect(rectClient);

      ::ca::brush_sp br(get_app());

      br->CreateSolidBrush(ARGB(84, 255, 255, 255));

      pdc->SelectObject(br);

      pdc->FillRectangle(rectClient);

      rect rectItem;

      rectItem = rectClient;

      rectItem.bottom = rectClient.top + _001GetItemHeight();

      for(index i = 0; i < c; i++)
      {
         rectItem.top = rectItem.bottom;
         rectItem.bottom = rectItem.top + _001GetItemHeight();
         m_pcombo->_001GetListText(i, strItem);
         pdc->draw_text(strItem, rectItem, 0);
      }

   }

   void combo_list::query_full_size(LPSIZE lpsize) const
   {
      
      lpsize->cx = 0;
      lpsize->cy = _001GetItemHeight() * (m_pcombo->_001GetListCount() + 2);

   }

   int combo_list::_001GetItemHeight() const
   {
      
      return 18;

   }


   const char * combo_list::GetIconWndClass(DWORD dwDefaultStyle, const char * pszMatter)
   {

   #ifdef WINDOWS

      HICON hIcon = (HICON) ::LoadImage(
         NULL,
         Application.dir().matter(pszMatter, "icon.ico"), IMAGE_ICON,
         16, 16,
         LR_LOADFROMFILE);

      if(hIcon != NULL)
      {
         CREATESTRUCT cs;
         memset(&cs, 0, sizeof(CREATESTRUCT));
         cs.style = dwDefaultStyle;
         pre_create_window(cs);
            // will fill lpszClassName with default WNDCLASS name
            // ignore instance handle from pre_create_window.

         WNDCLASS wndcls;
         if (cs.lpszClass != NULL &&
            GetClassInfo(System.m_hInstance, cs.lpszClass, &wndcls) &&
            wndcls.hIcon != hIcon)
         {
            // register a very similar WNDCLASS
            return System.RegisterWndClass(wndcls.style,
               wndcls.hCursor, wndcls.hbrBackground, hIcon);
         }
      }
   #else

      throw not_implemented_exception();

   #endif
      return NULL;        // just use the default
   }


} // namespace user



