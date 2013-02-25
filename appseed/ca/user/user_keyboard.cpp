#include "framework.h"

namespace user
{

   keyboard::keyboard(::ca::application * papp) :
      ca(papp)
   {
      m_playout = NULL;
   }


   class keyboard_layout & keyboard::layout()
   {
      return *m_playout;
   }

   void keyboard::process_escape(::xml::node * pnode, ::ca::property_set & set)
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
            ::ca::del(m_playout);
            m_playout = playout;
            System.simpledb().on_set_keyboard_layout(playout->m_strPath, bUser);
            TRACE("successfully set keyboard layout to %s (path=%s)", playout->m_strName, playout->m_strPath);
            return true;
         }
         else
         {
            ::ca::del(playout);
            TRACE("failed to load keyboard layout : %s (path=%s)", playout->m_strName, playout->m_strPath);
         }
      }
      else
      {
         TRACE("failed to set keyboard layout path=%s", pszPath);
      }
      return false;
   }

   string keyboard::process_key(int32_t iCode, int32_t iKey, int32_t iFlags)
   {
      if(m_playout == NULL)
      {
         if(iCode == 0 && iKey != 0)
            return (char) iKey;
         else
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
      Application.dir().matter_ls_file("keyboard layout", straPath);
      for(int32_t i = 0; i < straPath.get_count(); i++)
      {
         keyboard_layout_id layoutid;
         if(initialize(&layoutid, straPath[i]))
         {
            layoutida.add(layoutid);
         }
      }
      layoutida.QuickSort(true);

#ifdef WINDOWSEX

      char szLayoutName[KL_NAMELENGTH];

      ::GetKeyboardLayoutName(szLayoutName);

      HKL hkl = ::GetKeyboardLayout(0);

      for(int32_t i = 0; i < layoutida.get_count(); i++)
      {
         if(layoutida[i].m_hkla.contains(hkl))
         {
            return layoutida[i].m_strPath;
         }
      }
      hkl = (HKL) (((uint32_t) hkl) & 0xffff);
      for(int32_t i = 0; i < layoutida.get_count(); i++)
      {
         if(layoutida[i].m_hkla.contains(hkl))
         {
            return layoutida[i].m_strPath;
         }
      }

#else

      TRACE("not implemented exception");

#endif

      string strPath = Application.dir().matter("keyboard layout/en_us_international.xml");

      if(Application.file().exists(strPath))
      {

         return strPath;

      }

      return "";

   }


   bool keyboard::initialize(keyboard_layout_id * playoutid, const char * pszPath)
   {

      if(!Application.file().exists(pszPath))
         return false;

      string str = Application.file().as_string(pszPath);

      if(str.is_empty())
         return false;

      ::xml::document doc(get_app());

      if(!doc.load(str))
         return false;

      playoutid->m_strPath = pszPath;

      playoutid->m_strName = doc.get_root()->attrs()["name"];

      stringa straHkl;

      straHkl.explode(";", doc.get_root()->attr("hkla"));

#ifdef WINDOWS

      for(int32_t i = 0; i < straHkl.get_count(); i++)
      {
         string strHkl = straHkl[i];
         HKL hkl;
         strHkl.trim();
         if(::ca::str::begins_eat_ci(strHkl, "0x"))
         {
            hkl = (HKL) ::ca::hex::to_uint(strHkl);
         }
         else
         {
            hkl = (HKL) atoi(strHkl);
         }
         playoutid->m_hkla.add(hkl);
      }

#else

      //throw todo(get_app());

#endif

      if(playoutid->m_strName.is_empty())
         return false;

      return true;

   }

} // namespace user
