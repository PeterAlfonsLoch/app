#include "framework.h"

namespace user
{

   keyboard::keyboard(::ca::application * papp) :
      ca(papp)
   {


     System.set_enum_name(key_0, "key_0");
     System.set_enum_name(key_1, "key_1");
     System.set_enum_name(key_2, "key_2");
     System.set_enum_name(key_3, "key_3");
     System.set_enum_name(key_4, "key_4");
     System.set_enum_name(key_5, "key_5");
     System.set_enum_name(key_6, "key_6");
     System.set_enum_name(key_7, "key_7");
     System.set_enum_name(key_8, "key_8");
     System.set_enum_name(key_9, "key_9");
     System.set_enum_name(key_a, "key_a");
     System.set_enum_name(key_b, "key_b");
     System.set_enum_name(key_c, "key_c");
     System.set_enum_name(key_d, "key_d");
     System.set_enum_name(key_e, "key_e");
     System.set_enum_name(key_f, "key_f");
     System.set_enum_name(key_g, "key_g");
     System.set_enum_name(key_h, "key_h");
     System.set_enum_name(key_i, "key_i");
     System.set_enum_name(key_j, "key_j");
     System.set_enum_name(key_k, "key_k");
     System.set_enum_name(key_l, "key_l");
     System.set_enum_name(key_m, "key_m");
     System.set_enum_name(key_n, "key_n");
     System.set_enum_name(key_o, "key_o");
     System.set_enum_name(key_p, "key_p");
     System.set_enum_name(key_q, "key_q");
     System.set_enum_name(key_r, "key_r");
     System.set_enum_name(key_s, "key_s");
     System.set_enum_name(key_t, "key_t");
     System.set_enum_name(key_u, "key_u");
     System.set_enum_name(key_v, "key_v");
     System.set_enum_name(key_w, "key_w");
     System.set_enum_name(key_x, "key_x");
     System.set_enum_name(key_y, "key_y");
     System.set_enum_name(key_z, "key_z");
     System.set_enum_name(key_semicolon, "key_semicolon");
     System.set_enum_name(key_comma, "key_comma");
     System.set_enum_name(key_dot, "key_dot");
     System.set_enum_name(key_shift, "key_shift");
     System.set_enum_name(key_control, "key_control");
     System.set_enum_name(key_alt, "key_alt");
     System.set_enum_name(key_lbutton, "key_lbutton");
     System.set_enum_name(key_mbutton, "key_mbutton");
     System.set_enum_name(key_rbutton, "key_rbutton");


      m_playout = NULL;

      string strPath;

#ifdef LINUX
      strPath = Application.dir().matter("keyboard/linux/default.xml");
#elif defined(MACOS)
      strPath = Application.dir().matter("keyboard/macos/default.xml");
#else
      strPath = Application.dir().matter("keyboard/windows/default.xml");
#endif

      if(Application.file().exists(strPath))
      {

         load_os_layout(strPath);

      }

   }


   void keyboard::load_os_layout(const char * pszPath)
   {
      
      int32_t iCode;

      ::user::e_key ekey;

      ::ca::type_info typeinfoKey = System.type_info < ::user::e_key > ();

      string str = Application.file().as_string(pszPath);

      if(str.is_empty())
         throw "unable to load os keyboard layout";

      ::xml::document doc(get_app());

      if(!doc.load(str))
         throw "unable to load os keyboard layout";

      for(int32_t i = 0; i < doc.get_root()->get_children_count(); i++)
      {

         ::xml::node * pnode = doc.get_root()->child_at(i);

         if(pnode->get_name().CompareNoCase("item") == 0)
         {

            string strCode    = pnode->attr("code");

            string strValue   = pnode->attr("value");

            iCode    = atoi(strCode);

            ekey     = System.enum_from_name < ::user::e_key > (typeinfoKey, strValue);

            m_mapKey.set_at(iCode, ekey);

         }

      }

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
#ifdef LINUX
      Application.dir().matter_ls_file("keyboard layout/linux", straPath);
#else
      Application.dir().matter_ls_file("keyboard layout", straPath);
#endif
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

#ifdef LINUX
      string strPath = Application.dir().matter("keyboard layout/linux/br_abnt2.xml");
#else
      string strPath = Application.dir().matter("keyboard layout/en_us_international.xml");
#endif

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

   void keyboard::translate_os_key_message(::ca::message::key * pkey)
   {
      
      pkey->m_ekey = m_mapKey[pkey->m_nFlags];

   }


} // namespace user


