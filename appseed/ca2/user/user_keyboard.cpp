#include "StdAfx.h"

namespace user
{

   keyboard::keyboard(::ax::application * papp) :
      ax(papp)
   {
      m_playout = NULL;
   }


   class keyboard_layout & keyboard::layout()
   {
      return *m_playout;
   }

   void keyboard::process_escape(::xml::node * pnode, gen::property_set & set)
   {
      m_playout->process_escape(pnode, set);
   }

   bool keyboard::load_layout(const char * pszPath, bool bUser)
   {
      ::user::keyboard_layout * playout = new ::user::keyboard_layout(get_app());
      string strPath;
      if(pszPath == NULL)
      {
         strPath = get_current_system_layout();
      }
      else
      {
         strPath = pszPath;
      }
      if(initialize(playout, strPath))
      {
         TRACE("setting keyboard layout to %s (path=%s)", playout->m_strName, playout->m_strPath);
         if(playout->load(playout->m_strPath))
         {
            gen::del(m_playout);
            m_playout = playout;
            System.on_set_keyboard_layout(playout->m_strPath, bUser);
            TRACE("successfully set keyboard layout to %s (path=%s)", playout->m_strName, playout->m_strPath);
            return true;
         }
         else
         {
            gen::del(playout);
            TRACE("failed to load keyboard layout : %s (path=%s)", playout->m_strName, playout->m_strPath);
         }
      }
      else
      {
         TRACE("failed to set keyboard layout path=%s", pszPath);
      }
      return false;
   }

   string keyboard::process_key(int iCode, int iKey, int iFlags)
   {
      if(m_playout == NULL)
      {
         return (char) iCode;
      }
      return m_playout->process_key(iCode, iKey, iFlags);
   }

   string keyboard::process_char(const char * pszKey)
   {
      if(m_playout == NULL)
      {
         return pszKey;
      }
      return m_playout->process_char(pszKey);
   }

   string keyboard::process_escape(const char * pszEscape)
   {
      if(m_playout == NULL)
      {
         return pszEscape;
      }
      return m_playout->process_char(pszEscape);
   }


   string keyboard::get_current_system_layout()
   {
      keyboard_layout_ida layoutida;
      stringa straPath;
      System.dir().ls(System.dir().ca2("app/appmatter/main/_std/_std/keyboard layout"), &straPath);
      for(int i = 0; i < straPath.get_count(); i++)
      {
         keyboard_layout_id layoutid;
         if(initialize(&layoutid, straPath[i]))
         {
            layoutida.add(layoutid);
         }
      }
      layoutida.QuickSort(true);
      char szLayoutName[KL_NAMELENGTH];
      ::GetKeyboardLayoutName(szLayoutName);
      HKL hkl = ::GetKeyboardLayout(0);
      for(int i = 0; i < layoutida.get_count(); i++)
      {
         if(layoutida[i].m_hkla.contains(hkl))
         {
            return layoutida[i].m_strPath;
         }
      }
      hkl = (HKL) (((DWORD) hkl) & 0xffff);
      for(int i = 0; i < layoutida.get_count(); i++)
      {
         if(layoutida[i].m_hkla.contains(hkl))
         {
            return layoutida[i].m_strPath;
         }
      }
      string strPath;
      if(System.file().exists(System.dir().ca2("app/appmatter/main/_std/_std/keyboard layout/en_us_international.xml")))
      {
         return System.dir().ca2("app/appmatter/main/_std/_std/keyboard layout/en_us_international.xml");
      }
      return "";
   }

   bool keyboard::initialize(keyboard_layout_id * playoutid, const char * pszPath)
   {
      string str = Application.file().as_string(pszPath);
      if(str.is_empty())
         return false;
      ::xml::node node(get_app());
      if(!node.load(str))
         return false;
      playoutid->m_strPath = pszPath;
      playoutid->m_strName = node.attrs()["name"];
      stringa straHkl;
      straHkl.explode(";", node.attr("hkla"));
      for(int i = 0; i < straHkl.get_count(); i++)
      {
         string strHkl = straHkl[i];
         HKL hkl;
         strHkl.trim();
         if(gen::str::begins_eat_ci(strHkl, "0x"))
         {
            hkl = (HKL) gen::str::hex2unsigned(strHkl);
         }
         else
         {
            hkl = (HKL) atoi(strHkl);
         }
         playoutid->m_hkla.add(hkl);
      }
      if(playoutid->m_strName.is_empty())
         return false;
      return true;
   }

} // namespace user
