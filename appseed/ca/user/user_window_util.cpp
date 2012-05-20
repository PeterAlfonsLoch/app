#include "framework.h"

namespace user
{

   void HWNDArray::SortByZOrder()
   {
      WndUtil::SortByZOrder(*this);
   }

   // This function sort the ::ca::window base_array
   // by ascending z order.

   // This implementation relays in the fact
   // that all windows are siblings
   void HWNDArray::SortSiblingsByZOrder()
   {
      HWND hwndSwap;
      for(int i = 0; i < this->get_size(); i++)
      {
         for(int j = i + 1; j < this->get_size(); j++)
         {
            if(WndUtil::GetZOrder(this->element_at(i)) > WndUtil::GetZOrder(this->element_at(j)))
            {
               hwndSwap = this->element_at(i);
               this->element_at(i) = this->element_at(j);
               this->element_at(j) = hwndSwap;
            }
         }
      }

   }
   void HWNDArray::top_windows_by_z_order()
   {
      int iOrder = 0;
      HWND hwndOrder = ::GetDesktopWindow();
      hwndOrder = ::GetWindow(hwndOrder, GW_CHILD);
      while(hwndOrder != NULL
         && ::IsWindow(hwndOrder))
      {
         add(hwndOrder);
         hwndOrder = ::GetWindow(hwndOrder, GW_HWNDNEXT);
         iOrder++;
      }
   }


   WndUtil::WndUtil()
   {

   }

   WndUtil::~WndUtil()
   {

   }

   // This function sort the ::ca::window base_array
   // by ascending z order.

   // This implementation relays in the fact
   // that all windows are siblings,
   // have a permanent ::ca::window associated object
   // and that all ::ca::window base_array pointers
   // are pointers to permanent objects.
   /*void WndUtil::SortByZOrder(Carray < ::ca::window *, ::ca::window * > & wndpa)
   {
   if(wndpa.get_size() <= 0)
   return;

   Carray < ::ca::window *, ::ca::window * > wndpa2;

   ::ca::window * pwnd = wndpa[0];

   ::ca::window * pwndChild = pwnd->GetWindow(GW_HWNDFIRST);

   while(pwndChild != NULL
   && ::IsWindow(pwndChild->GetSafeHwnd()))
   {
   pwnd = ::ca::window::FromHandlePermanent(pwndChild->GetSafeHwnd());
   if(pwnd == NULL)
   {
   CTransparentWndInterface * ptwi = NULL;
   CTransparentWndInterface::CGetProperty getp;
   getp.m_eproperty = CTransparentWndInterface::PropertyInterface;
   pwndChild->SendMessage(CTransparentWndInterface::MessageGetProperty, 0, (LPARAM) &getp);
   ptwi = getp.m_pinterface;
   if(ptwi != NULL)
   {
   pwnd = ptwi->TwiGetWnd();
   if(pwnd != NULL)
   {
   wndpa2.add(pwnd);
   }
   }

   }
   else
   {
   wndpa2.add(pwnd);
   }
   pwndChild = pwndChild->GetWindow(GW_HWNDNEXT);
   }

   Carray < ::ca::window *, ::ca::window * > wndpa3;
   Carray < ::ca::window *, ::ca::window * > wndpa4;

   for(int i = 0; i < wndpa2.get_size(); i++)
   {
   if(wndpa.find_first(wndpa2[i]) >= 0)
   {
   wndpa3.add(wndpa2[i]);
   }
   }

   for(i = 0; i < wndpa.get_size(); i++)
   {
   if(wndpa3.find_first(wndpa[i]) < 0)
   {
   wndpa3.add(wndpa[i]);
   }
   }

   wndpa.copy(wndpa3);

   }*/

   // This function sort the ::ca::window base_array
   // by ascending z order.

   // This implementation relays in the fact
   // that all windows are siblings,
   // have a permanent ::ca::window associated object
   // and that all ::ca::window base_array pointers
   // are pointers to permanent objects.
   /*void WndUtil::SortByZOrder(Carray < HWND, HWND > & hwnda)
   {
   if(hwnda.get_size() <= 0)
   return;

   Carray < HWND, HWND > hwnda2;

   HWND hwnd = hwnda[0];

   HWND hwndChild = ::GetWindow(hwnd, GW_HWNDFIRST);

   while(hwndChild != NULL
   && ::IsWindow(hwndChild))
   {
   hwnda2.add(hwndChild);
   hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
   }

   Carray < HWND, HWND > hwnda3;
   Carray < HWND, HWND > hwnda4;

   for(int i = 0; i < hwnda2.get_size(); i++)
   {
   if(hwnda.find_first(hwnda2[i]) >= 0)
   {
   hwnda3.add(hwnda2[i]);
   }
   }

   for(i = 0; i < hwnda.get_size(); i++)
   {
   if(hwnda3.find_first(hwnda[i]) < 0)
   {
   hwnda3.add(hwnda[i]);
   }
   }

   hwnda.copy(hwnda3);

   }*/


   /*void WndUtil::EnumChildren(HWND hwnd, Carray < HWND, HWND > & hwnda)
   {
   if(!::IsWindow(hwnd))
   return;
   HWND hwndChild = ::GetTopWindow(hwnd);
   while(hwndChild != NULL)
   {
   hwnda.add(hwndChild);
   hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
   }
   }

   void WndUtil::ExcludeChildren(HWND hwnd, HRGN hrgn, POINT ptOffset)
   {


   Carray < HWND, HWND > hwnda;

   EnumChildren(hwnd, hwnda);

   for(int i = 0; i < hwnda.get_size(); i++)
   {
   HWND hwndChild = hwnda[i];
   rect rectChild;
   ::GetClientRect(hwndChild, rectChild);
   ::ClientToScreen(hwndChild, &rectChild.top_left());
   ::ClientToScreen(hwndChild, &rectChild.bottom_right());
   ::ScreenToClient(hwnd, &rectChild.top_left());
   ::ScreenToClient(hwnd, &rectChild.bottom_right());
   rectChild.offset(ptOffset);
   HRGN hrgnChild = ::CreateRectRgnIndirect(rectChild);
   ::CombineRgn(hrgn, hrgn, hrgnChild, RGN_DIFF);
   ::DeleteObject(hrgnChild);
   }




   }*/

   /*HRGN WndUtil::GetAClipRgn(HWND hwnd, POINT ptOffset, bool bExludeChildren)
   {
   rect rectWnd;
   ::GetClientRect(hwnd, rectWnd);
   rectWnd.offset(ptOffset);
   HRGN hrgn = ::CreateRectRgnIndirect(rectWnd);

   if(bExludeChildren)
   {
   ExcludeChildren(hwnd, hrgn, ptOffset);
   }

   return hrgn;
   }*/




   void HwndTree::EnumDescendants()
   {
      HWND hwnd = m_hwnd;
      if(!::IsWindow(hwnd))
         return;

      HWND hwndChild = ::GetTopWindow(hwnd);

      while(hwndChild != NULL)
      {
         m_hwndtreea.add_new();
         HwndTree & hwndtreeChild = m_hwndtreea.last_element();
         hwndtreeChild.m_hwnd = hwndChild;
         hwndtreeChild.m_dwUser = 0;
         hwndtreeChild.m_pvoidUser = NULL;
         hwndtreeChild.EnumDescendants();
         hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
      }
   }

   void HwndTree::Array::EnumDescendants()
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         this->element_at(i).EnumDescendants();
      }
   }

   HwndTree::HwndTree()
   {
      m_hwnd = NULL;
   }
   HwndTree::HwndTree(const HwndTree & tree)
   {
      operator =(tree);
   }


   HwndTree & HwndTree::operator = (const HwndTree & tree)
   {
      m_hwnd = tree.m_hwnd;
      m_hwndtreea.copy(tree.m_hwndtreea);
      return * this;
   }

   int HwndTree::CompareHwnd(HwndTree &tree1, HwndTree &tree2)
   {
      return (int) (tree1.m_hwnd - tree2.m_hwnd);
   }

   int_ptr HwndTree::Array::find(HWND hwnd)
   {
      HwndTree tree;
      tree.m_hwnd = hwnd;
      return array_ptr_alloc < HwndTree, const HwndTree & >::find_first(tree, HwndTree::CompareHwnd);
   }


   bool HwndTree::Array::remove(HWND hwnd)
   {
      if(hwnd == NULL)
         return true;
      int i;
      for(i = 0; i < this->get_size();)
      {
         HwndTree & tree = this->element_at(i);
         if(tree.m_hwnd == hwnd)
         {
            remove_at(i);
            return true;
         }
         else
         {
            i++;
         }
      }
      for(i = 0; i < this->get_size(); i++)
      {
         HwndTree & tree = this->element_at(i);
         if(tree.m_hwndtreea.remove(hwnd))
         {
            return true;
         }
      }
      return false;
   }

   HwndTree::Array &
      HwndTree::Array::
      operator = (HWNDArray & hwnda)
   {
      remove_all();
      HwndTree hwndtree;
      for(int i = 0; i < hwnda.get_size(); i++)
      {
         hwndtree.m_hwnd = hwnda[i];
         add(hwndtree);
      }
      return * this;
   }



   // This function get all child windows of
   // the ::ca::window pointed by pwnd and add it
   // to the ::ca::window base_array wndpa. The top
   // windows come first in the enumeration.

   /*void WndUtil::EnumChildren(::ca::window * pwnd, LPWndArray & wndpa)
   {
   if(!::IsWindow(pwnd->GetSafeHwnd()))
   return;
   ::ca::window * pwndChild = pwnd->GetTopWindow();
   while(pwndChild != NULL)
   {
   wndpa.add(pwndChild);
   pwndChild = pwndChild->GetWindow(GW_HWNDNEXT);
   }
   }*/

   // This function get all child windows of
   // the ::ca::window pointed by pwnd and add it
   // to the ::ca::window base_array wndpa. The top
   // windows come first in the enumeration.

   void WndUtil::EnumChildren(HWND hwnd, HWNDArray & hwnda)
   {
      if(!::IsWindow(hwnd))
         return;
      HWND hwndChild = ::GetTopWindow(hwnd);
      while(hwndChild != NULL)
      {
         hwnda.add(hwndChild);
         hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
      }
   }


   // This function sort the ::ca::window base_array
   // by ascending z order.

   // This implementation relays in the fact
   // that all windows are siblings,
   // have a permanent ::ca::window associated object
   // and that all ::ca::window base_array pointers
   // are pointers to permanent objects.
   /*void WndUtil::SortByZOrder(LPWndArray & wndpa)
   {
   if(wndpa.get_size() <= 0)
   return;

   LPWndArray wndpa2;

   ::ca::window * pwnd = wndpa[0];

   ::ca::window * pwndChild = pwnd->GetWindow(GW_HWNDFIRST);

   while(pwndChild != NULL)
   {
   pwnd = ::ca::window::FromHandlePermanent(pwndChild->GetSafeHwnd());
   if(pwnd == NULL)
   {
   wndpa2.add(pwnd);
   }
   pwndChild = pwndChild->GetWindow(GW_HWNDNEXT);
   }

   LPWndArray wndpa3;
   LPWndArray wndpa4;

   int i;
   for( i = 0; i < wndpa2.get_size(); i++)
   {
   if(wndpa.find_first(wndpa2[i]) >= 0)
   {
   wndpa3.add(wndpa2[i]);
   }
   }

   for(i = 0; i < wndpa.get_size(); i++)
   {
   if(wndpa3.find_first(wndpa[i]) < 0)
   {
   wndpa3.add(wndpa[i]);
   }
   }

   wndpa.copy(wndpa3);

   }*/

   /*void WndUtil::ExcludeChild(LPWndArray & wndpa)
   {

   for(int i = 0; i < wndpa.get_size();)
   {
   if(wndpa[i]->GetParent() != NULL)
   {
   wndpa.remove_at(i);
   }
   else
   {
   i++;
   }
   }

   }
   */



   void WndUtil::ContraintPosToParent(HWND hwnd)
   {
      rect rectMajor;
      HWND hwndParent = ::GetParent(hwnd);
      if(hwndParent == NULL)
      {
         rectMajor.left = 0;
         rectMajor.top = 0;
         rectMajor.right = GetSystemMetrics(SM_CXSCREEN);
         rectMajor.bottom = GetSystemMetrics(SM_CYSCREEN);
      }
      else
      {
         ::GetClientRect(hwndParent, rectMajor);
      }

      rect rect;
      ::GetClientRect(hwnd, rect);
      ::ClientToScreen(hwnd, &rect.top_left());
      ::ClientToScreen(hwnd, &rect.bottom_right());
      if(hwndParent != NULL)
      {
         ::ScreenToClient(hwndParent, &rect.top_left());
         ::ScreenToClient(hwndParent, &rect.bottom_right());
      }

      bool bModified = false;

      if(rect.left > rectMajor.right)
      {
         rect.offset(- rect.width() - (rect.left - rectMajor.right), 0);
         bModified = true;
      }
      if(rect.right < rectMajor.left)
      {
         rect.offset(rect.width() + (rectMajor.left - rect.right), 0);
         bModified = true;
      }
      if(rect.top > rectMajor.bottom)
      {
         rect.offset(0, - rect.height() - (rect.top - rectMajor.bottom));
         bModified = true;
      }
      if(rect.bottom < rectMajor.top)
      {
         rect.offset(0, rect.height() + (rectMajor.top - rect.bottom));
         bModified = true;
      }

      if(bModified)
      {
         ::SetWindowPos(
            hwnd,
            HWND_TOP,
            rect.left,
            rect.top,
            rect.width(),
            rect.height(),
            0);
      }

   }

   /*void WndUtil::SendMessageToDescendants(HWND hWnd, UINT message,
   WPARAM wParam, LPARAM lParam, bool bDeep, bool bOnlyPerm)
   {
   // walk through HWNDs to avoid creating temporary ::ca::window objects
   // unless we need to call this function recursively
   for (HWND hWndChild = ::GetTopWindow(hWnd); hWndChild != NULL;
   hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
   {
   // if bOnlyPerm is TRUE, don't send to non-permanent windows
   if (bOnlyPerm)
   {
   ::ca::window* pWnd = ::ca::window::FromHandlePermanent(hWndChild);
   if (pWnd != NULL)
   {
   // call ::ca::window proc directly since it is a C++ ::ca::window
   __call_window_procedure(pWnd, pWnd->m_hWnd, message, wParam, lParam);
   }
   }
   else
   {
   // send message with Windows SendMessage API
   ::SendMessage(hWndChild, message, wParam, lParam);
   }
   if (bDeep && ::GetTopWindow(hWndChild) != NULL)
   {
   // send to child windows after parent
   SendMessageToDescendants(hWndChild, message, wParam, lParam,
   bDeep, bOnlyPerm);
   }
   }
   }*/


   void WndUtil::SendMessageToDescendants(HWND hWnd, UINT message,
      WPARAM wParam, LPARAM lParam, bool bDeep)
   {
      // walk through HWNDs to avoid creating temporary ::ca::window objects
      // unless we need to call this function recursively
      for (HWND hWndChild = ::GetTopWindow(hWnd); hWndChild != NULL;
         hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
      {
         // send message with Windows SendMessage API
         try
         {
            ::SendMessage(hWndChild, message, wParam, lParam);
         }
         catch(...)
         {
         }
         if (bDeep && ::GetTopWindow(hWndChild) != NULL)
         {
            // send to child windows after parent
            try
            {
               SendMessageToDescendants(hWndChild, message, wParam, lParam,
                  bDeep);
            }
            catch(...)
            {
            }
         }
      }
   }

   // This function sort the ::ca::window base_array
   // by ascending z order.

   // This implementation relays in the fact
   // that all windows are siblings
   void WndUtil::SortByZOrder(HWNDArray & hwnda)
   {
      if(hwnda.get_size() <= 0)
         return;

      int_array ia1;
      int_array ia2;
      HWND hwndSwap;

      for(int i = 0; i < hwnda.get_size(); i++)
      {
         for(int j = i + 1; j < hwnda.get_size(); j++)
         {
            try
            {
               GetZOrder(hwnda[i], ia1);
               GetZOrder(hwnda[j], ia2);
               if(ia1.Cmp(ia2) > 0)
               {
                  hwndSwap = hwnda[i];
                  hwnda[i] = hwnda[j];
                  hwnda[j] = hwndSwap;
               }
            }
            catch(...)
            {
            }
         }
      }

   }

   int WndUtil::GetZOrder(HWND hwnd)
   {
      int iOrder = 0;
      HWND hwndOrder = NULL;
      try
      {
         hwndOrder = ::GetWindow(hwnd, GW_HWNDFIRST);
      }
      catch(...)
      {
         return 0x7fffffff;
      }
      while(hwndOrder != NULL && ::IsWindow(hwndOrder))
      {
         if(hwnd == hwndOrder)
            return iOrder;
         hwndOrder = ::GetWindow(hwndOrder, GW_HWNDNEXT);
         iOrder++;
      }
      return 0x7fffffff;
   }


   void WndUtil::GetZOrder(HWND hwnd, int_array & ia)
   {
      int iOrder;
      ia.remove_all();
      while(true)
      {
         if(hwnd == NULL || !::IsWindow(hwnd))
            break;
         iOrder = GetZOrder(hwnd);
         if(iOrder == 0x7fffffff)
            break;
         ia.insert_at(0, iOrder);
         hwnd = ::GetParent(hwnd);
      }
   }

   /*void WndUtil::EnumChildren(HWND hwnd, HWNDArray & hwnda)
   {
   if(!::IsWindow(hwnd))
   return;
   HWND hwndChild = ::GetTopWindow(hwnd);
   while(hwndChild != NULL)
   {
   hwnda.add(hwndChild);
   hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
   }
   }*/

   void WndUtil::ExcludeChildren(HWND hwnd, HRGN hrgn, POINT ptOffset)
   {


      HWNDArray hwnda;

      EnumChildren(hwnd, hwnda);

      for(int i = 0; i < hwnda.get_size(); i++)
      {
         HWND hwndChild = hwnda[i];
         rect rectChild;
         ::GetClientRect(hwndChild, rectChild);
         ::ClientToScreen(hwndChild, &rectChild.top_left());
         ::ClientToScreen(hwndChild, &rectChild.bottom_right());
         ::ScreenToClient(hwnd, &rectChild.top_left());
         ::ScreenToClient(hwnd, &rectChild.bottom_right());
         rectChild.offset(ptOffset);
         HRGN hrgnChild = ::CreateRectRgnIndirect(rectChild);
         ::CombineRgn(hrgn, hrgn, hrgnChild, RGN_DIFF);
         ::DeleteObject(hrgnChild);
      }




   }

   HRGN WndUtil::GetAClipRgn(HWND hwnd, POINT ptOffset, bool bExludeChildren)
   {
      rect rectWnd;
      ::GetClientRect(hwnd, rectWnd);
      rectWnd.offset(ptOffset);
      HRGN hrgn = ::CreateRectRgnIndirect(rectWnd);

      if(bExludeChildren)
      {
         ExcludeChildren(hwnd, hrgn, ptOffset);
      }

      return hrgn;
   }

   bool WndUtil::IsAscendant(HWND hwndAscendant, HWND hwndDescendant)
   {
      while(true)
      {
         hwndDescendant = ::GetParent(hwndDescendant);
         if(hwndDescendant == NULL)
            return false;
         if(hwndDescendant == hwndAscendant)
            return true;
      }
   }

   ::user::interaction * LPWndArray::find_first(::ca::type_info info)
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         if(typeid(*this->element_at(i)).raw_name() == info.raw_name())
         {
            return this->element_at(i);
         }
      }
      return NULL;
   }

   ::user::interaction * LPWndArray::find_first(HWND hwnd)
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         if(this->element_at(i)->get_safe_handle() == hwnd)
         {
            return this->element_at(i);
         }
      }
      return NULL;
   }

   void LPWndArray::get_wnda(HWNDArray & hwnda)
   {
      hwnda.remove_all();
      for(int i = 0; i < this->get_size(); i++)
      {
         hwnda.add(this->element_at(i)->_get_handle());
      }
   }

   void LPWndArray::send_message(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         try
         {
            this->element_at(i)->SendMessageA(uiMessage, wparam, lparam);
         }
         catch(...)
         {
         }
      }
   }

   void LPWndArray::send_message_to_descendants(UINT uiMessage, WPARAM wparam, LPARAM lparam, bool bRecursive)
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         try
         {
            this->element_at(i)->SendMessageToDescendants(uiMessage, wparam, lparam, bRecursive);
         }
         catch(...)
         {
         }
      }
   }

} // namespace user
