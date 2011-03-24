#include "StdAfx.h"

namespace userbase
{

   menu_item::menu_item(::ca::application * papp) :
      ca(papp),
      m_button(papp)
   {
      m_pitema = new menu_item_ptra(this);
      m_iLevel       = 0;
      m_bPopup       = false;
   }

   menu_item::~menu_item()
   {
   }

   void menu_item::add_item(menu_item * pitem)
   {
      m_pitema->add(pitem);
   }

   /*bool menu_item::LoadMenuA(UINT uiId)
   {
      HINSTANCE hinstance = AfxFindResourceHandle(MAKEINTRESOURCE(uiId), RT_MENU);
      if(hinstance == NULL)
         return false;
      HMENU hmenu = ::LoadMenu(hinstance, MAKEINTRESOURCE(uiId));
      if(hmenu == NULL)
         return false;
      return LoadMenu(hmenu);
   }

   bool menu_item::LoadMenu(HMENU hmenu)
   {
      m_iSeparatorCount = 0;
      m_iFullHeightItemCount = 0;
      return LoadMenu(this, hmenu, m_iLevel);
   }*/

   bool menu_item::load_menu(xml::node * lpnode)
   {
      m_iSeparatorCount = 0;
      m_iFullHeightItemCount = 0;
      return load_menu(lpnode, m_iLevel);
   }

   /*bool menu_item::LoadMenu(menu_item * pitem, HMENU hmenu, int iLevel)
   {
      int iItemCount = ::GetMenuItemCount(hmenu);
      MENUITEMINFO mii;
      for(int i = 0; i < iItemCount; i++)
      {
         menu_item * pitemNew = new menu_item(pitem->get_app());
         memset(&mii, 0, sizeof(mii));
         mii.cbSize = sizeof(mii);
         mii.fMask = MIIM_SUBMENU | MIIM_TYPE | MIIM_ID;
         ::GetMenuItemInfo(hmenu, i, TRUE, &mii);
         pitemNew->m_bPopup = false;
         if(mii.hSubMenu != NULL)
         {
            pitemNew->m_id.Empty();
            pitemNew->m_bPopup = true;
            pitemNew->m_iLevel = iLevel + 1;
            pitemNew->LoadMenu(mii.hSubMenu);

         }
         if(mii.fType & MFT_SEPARATOR)
         {
            pitemNew->m_id = "separator";
            pitem->m_iSeparatorCount++;
         }
         else
         {
            HINSTANCE hinst = AfxFindResourceHandle(MAKEINTRESOURCE(mii.wID), RT_MENU);
            if(hinst != NULL)
            {
               HMENU hmenuInline = ::LoadMenu(hinst, MAKEINTRESOURCE(mii.wID));
               if(hmenuInline != NULL)
               {
                  LoadMenu(pitem, hmenuInline, iLevel);
                  continue;
               }
            }
            pitem->m_iFullHeightItemCount++;
            pitemNew->m_id = mii.wID;
            pitemNew->m_iLevel = iLevel;
            if(mii.fType & MFT_STRING)
            {
               pitemNew->m_button._001SetButtonText(mii.dwTypeData);
            }
            else
            {
               int iLen = ::GetMenuString(hmenu, i, NULL, 0, MF_BYPOSITION);
               string str;
               ::GetMenuString(hmenu, i, str.GetBufferSetLength(iLen + 1), iLen + 1, MF_BYPOSITION);
               str.ReleaseBuffer();
               pitemNew->m_button._001SetButtonText(str);
            }
         }
         pitem->add_item(pitemNew);
      }
      
      return true;
   }*/

   bool menu_item::load_menu(xml::node * lpnode, int iLevel)
   {
      //CommandIdSpace idspace;

      xml::node node(get_app());

//      gen::application * papp = dynamic_cast < gen::application * > (pbergedgeapp);
         
      int iItemCount = lpnode->get_children_count();
      for(int i = 0; i < iItemCount; i++)
      {
         xml::node * pnodeChild = lpnode->child_at(i);
         
         menu_item * pitemNewChild = new menu_item(get_app());
         
         pitemNewChild->m_bPopup = pnodeChild->get_children_count() > 0 && pnodeChild->m_strName == "menubar";

         if(pitemNewChild->m_bPopup)
         {
            pitemNewChild->m_iLevel = iLevel + 1;
            pitemNewChild->load_menu(pnodeChild);
         }
         if(pnodeChild->m_strName == "separator")
         {
            pitemNewChild->m_id = "separator";
            m_iSeparatorCount++;
         }
         else
         {
   /* xxx submenu expansion  how?         HINSTANCE hinst = AfxFindResourceHandle(MAKEINTRESOURCE(mii.wID), RT_MENU);
            if(hinst != NULL)
            {
               HMENU hmenuInline = ::LoadMenu(hinst, MAKEINTRESOURCE(mii.wID));
               if(hmenuInline != NULL)
               {
                  LoadMenu(pitem, hmenuInline, iLevel);
                  continue;
               }
            }*/
            
            
            m_iFullHeightItemCount++;
            pitemNewChild->m_id = pnodeChild->attr("id");
            pitemNewChild->m_iLevel = iLevel;
            if(pitemNewChild->m_bPopup)
            {
               pitemNewChild->m_button._001SetButtonText(pnodeChild->attr("title"));
            }
            else
            {
               pitemNewChild->m_button._001SetButtonText(pnodeChild->m_strValue);
            }
         }
         add_item(pitemNewChild);
      }
      
      return true;
   }

   /*void menu_item::AddRef()
   {
      m_iRefCount++;
   }

   void menu_item::Release()
   {
      m_iRefCount--;
      if(m_iRefCount == 0)
         delete this;
   }*/

   bool menu_item::IsPopup(void)
   {
      return m_pitema != NULL;
   }

   menu_item_ptra::menu_item_ptra(menu_item * pitemContainer)
   {
      m_pitemContainer = pitemContainer;
   }

   menu_item_ptra::~menu_item_ptra()
   {
   }


   /*void menu_item_ptra::set_at(int iIndex, menu_item & item)
   {
      menu_item * pitem = new menu_item(item);
      pitem->AddRef();
      base_array < menu_item *, menu_item * >::set_at(iIndex, pitem);
   }
   */

   menu_item * menu_item::find(id id)
   {
      if(m_pitema == NULL)
         return NULL;
      return m_pitema->find(id);
   }

   void menu_item::OnAddRef()
   {
   }

   void menu_item::OnRelease()
   {
   }

   menu_item * menu_item_ptra::find(id id)
   {
      menu_item * pitemFind;
      for(int i = 0; i < get_size(); i++)
      {
         menu_item * pitem = ptr_at(i);
         if(pitem->m_id  == id)
            return pitem;
         pitemFind = pitem->find(id);
         if(pitemFind != NULL)
            return pitemFind;
      }
      return NULL;
   }

} // namespace userbase