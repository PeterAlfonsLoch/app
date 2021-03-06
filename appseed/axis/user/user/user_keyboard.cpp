//#include "framework.h" 


#if defined(LINUX) || defined(SOLARIS)
//#include "base/base/os/x11/x11_keyboard.h"
string x11_keyboard_get_current_group_symbol();
#elif defined(MACOS)
string keyboard_input_source();
#endif





namespace user
{

   keyboard::keyboard(::aura::application * papp) :
      ::object(papp)
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
      System.set_enum_name(key_semicolon2, "key_semicolon2");
      System.set_enum_name(key_comma, "key_comma");
      System.set_enum_name(key_dot, "key_dot");
      System.set_enum_name(key_shift, "key_shift");
      System.set_enum_name(key_lshift, "key_lshift");
      System.set_enum_name(key_rshift, "key_rshift");
      System.set_enum_name(key_control, "key_control");
      System.set_enum_name(key_lcontrol, "key_lcontrol");
      System.set_enum_name(key_rcontrol, "key_rcontrol");
      System.set_enum_name(key_alt, "key_alt");
      System.set_enum_name(key_lalt, "key_lalt");
      System.set_enum_name(key_ralt, "key_ralt");
      System.set_enum_name(key_command, "key_command");
      System.set_enum_name(key_lcommand, "key_lcommand");
      System.set_enum_name(key_rcommand, "key_rcommand");
      System.set_enum_name(key_lbutton, "key_lbutton");
      System.set_enum_name(key_mbutton, "key_mbutton");
      System.set_enum_name(key_rbutton, "key_rbutton");
      System.set_enum_name(key_back, "key_back");
      System.set_enum_name(key_delete, "key_delete");
      System.set_enum_name(key_space, "key_space");
      System.set_enum_name(key_right, "key_right");
      System.set_enum_name(key_down, "key_down");
      System.set_enum_name(key_left, "key_left");
      System.set_enum_name(key_up, "key_up");
      System.set_enum_name(key_prior, "key_prior");
      System.set_enum_name(key_next, "key_next");
      System.set_enum_name(key_return, "key_return");
      System.set_enum_name(key_home, "key_home");
      System.set_enum_name(key_end, "key_end");
      System.set_enum_name(key_tab, "key_tab");
      System.set_enum_name(key_capslock, "key_capslock");
      System.set_enum_name(key_hyphen, "key_hyphen");
      System.set_enum_name(key_semicolon3, "key_semicolon3");
      System.set_enum_name(key_slash2, "key_slash2");
      System.set_enum_name(key_backslash2, "key_backslash2");
      System.set_enum_name(key_closebracket2, "key_closebracket2");
      System.set_enum_name(key_openbracket2, "key_openbracket2");
      System.set_enum_name(key_til2, "key_til2");
      System.set_enum_name(key_acute2, "key_acute2");
      System.set_enum_name(key_equal, "key_equal");
      System.set_enum_name(key_escape,"key_escape");
      System.set_enum_name(key_apostrophe2,"key_apostrophe2");
      System.set_enum_name(key_numpad_0, "key_numpad_0");
      System.set_enum_name(key_numpad_1, "key_numpad_1");
      System.set_enum_name(key_numpad_2, "key_numpad_2");
      System.set_enum_name(key_numpad_3, "key_numpad_3");
      System.set_enum_name(key_numpad_4, "key_numpad_4");
      System.set_enum_name(key_numpad_5, "key_numpad_5");
      System.set_enum_name(key_numpad_6, "key_numpad_6");
      System.set_enum_name(key_numpad_7, "key_numpad_7");
      System.set_enum_name(key_numpad_8, "key_numpad_8");
      System.set_enum_name(key_numpad_9, "key_numpad_9");
      System.set_enum_name(key_print_screen,"key_print_screen");

   }


   bool keyboard::initialize()
   {

      string strPath;
#ifdef MACOS
      strPath = Application.dir().matter("keyboard/windows/default.xml");

#elif defined( LINUX)
      strPath = Application.dir().matter("keyboard/linux/default.xml");
#elif defined(APPLEOS)
      strPath = Application.dir().matter("keyboard/macos/default.xml");
#elif defined(ANDROID)
      //strPath = Application.dir().matter("keyboard/android/default.xml");
      strPath = Application.dir().matter("keyboard/windows/default.xml");
#else
#ifndef METROWIN
      WCHAR wsz[KL_NAMELENGTH];

      WORD w;

      if(GetKeyboardLayoutNameW(wsz))
      {

         if(wcslen(wsz) == 8)
         {

            index i = 0;

            for(; i < 8; i++)
            {
               if(!::str::ch::is_digit(wsz[i]) && !(wsz[i] >= 'A' && wsz[i] <= 'F') && !(wsz[i] >= 'a' && wsz[i] <= 'f'))
                  break;
            }

            if(i == 8)
            {
               string str(wstring(wsz,4)); // first four digits

               w = (WORD) ::hex::to_int64(str);

            }

         }
         else
         {

            HKL hkl = GetKeyboardLayout(::GetCurrentThreadId());

            w = HIWORD(hkl);

            w &= 0x0fff;

         }

      }

      string str = ::str::from(w);

      strPath = Application.dir().matter("keyboard/windows/" + str + ".xml");

      if(Application.file().exists(strPath))
      {

         if(load_os_layout(strPath))
            return true;

      }

#endif

      strPath = Application.dir().matter("keyboard/windows/default.xml");

#endif

      if(!Application.file().exists(strPath))
      {

         if(is_debugger_attached())
         {

            Application.simple_message_box(NULL,"keyboard default.xml doesn't exist?!?!?!?!");

         }

         return false;

      }

      if(!load_os_layout(strPath))
         return false;

      return true;

   }



   bool keyboard::load_os_layout(const ::file::path & pszPath)
   {

      int32_t iCode;

      int32_t iScan;

      ::user::e_key ekey;

      sp(type) typeinfoKey = System.type_info < ::user::e_key > ();

      string str = Application.file().as_string(pszPath);


      output_debug_string(pszPath);

      output_debug_string(str);

      if(str.is_empty())
      {
         TRACE0("unable to load os keyboard on_layout");
         if(is_debugger_attached())
         {

            Application.simple_message_box(NULL,"keyboard default.xml is empty?!?!?!?!");

         }
         return false;
      }

      ::xml::document doc(get_app());

      if(!doc.load(str))
      {
         TRACE0("unable to load os keyboard on_layout");
         if(is_debugger_attached())
         {

            Application.simple_message_box(NULL,"keyboard default.xml syntax is incorrect?!?!?!?!");

         }
         return false;
      }

      for(int32_t i = 0; i < doc.get_root()->get_children_count(); i++)
      {

         sp(::xml::node) pnode = doc.get_root()->child_at(i);

         if(pnode->get_name().compare_ci("item") == 0)
         {

            string strCode    = pnode->attr("code");

            string strScan    = pnode->attr("scan");

            string strExt    = pnode->attr("ext");

            string strValue   = pnode->attr("value");

            ekey     = System.enum_from_name < ::user::e_key >(typeinfoKey,strValue);

            if(strCode.has_char())
            {

               iCode    = atoi(strCode);

               m_mapKey.set_at(iCode,ekey);

            }

            if(strScan.has_char())
            {

               iScan    = atoi(strScan);

               if(strExt == "1")
               {

                  m_mapExt.set_at(iScan,ekey);

               }
               else
               {

                  m_mapScan.set_at(iScan,ekey);

               }

            }



         }

      }

      if((m_mapKey.get_count() + m_mapExt.get_count() + m_mapScan.get_count()) <= 0)
      {

         if(is_debugger_attached())
         {

            Application.simple_message_box(NULL,"keyboard default.xml has no keyboard entries?!?!?!?!");

         }

      }

      return true;

   }


   class keyboard_layout & keyboard::on_layout()
   {
      return *m_playout;
   }

   void keyboard::process_escape(sp(::xml::node) pnode, property_set & set)
   {
      m_playout->process_escape(pnode, set);
   }

   bool keyboard::load_layout(const char * pszPath, ::action::context actioncontext)
   {
      sp(::user::keyboard_layout) playout = canew(::user::keyboard_layout(get_app()));
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
         TRACE("setting keyboard on_layout to %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
         if(playout->load(playout->m_strPath))
         {
            m_playout = playout;
// xxx            Application.simpledb().on_set_keyboard_layout(playout->m_strPath, actioncontext);
            TRACE("successfully set keyboard on_layout to %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
            return true;
         }
         else
         {
            playout->release();
            TRACE("failed to load keyboard on_layout : %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
         }
      }
      else
      {
         TRACE("failed to set keyboard on_layout path=%s", pszPath);
      }
      return false;
   }

   string keyboard::process_key(key * pkey)
   {

      if(m_playout == NULL)
      {

         return string((char)(pkey->m_nChar & 0xff),1);

      }

      pkey->m_iCode = (int)(pkey->m_ekey);

      if(Session.is_key_pressed(::user::key_shift))
      {
         pkey->m_iCode |= 0x80000000;
      }
      if(Session.is_key_pressed(::user::key_ralt))
      {
         pkey->m_iCode |= 0x40000000;
      }

      return m_playout->process_key(pkey);

   }

   string keyboard::process_key(::user::e_key ekey)
   {

      if(m_playout == NULL)
      {

         return string((char) ekey, 1);

      }

      int iCode = (int) (ekey);

      if(Session.is_key_pressed(::user::key_shift))
      {
         iCode |= 0x80000000;
      }
      if(Session.is_key_pressed(::user::key_ralt))
      {
         iCode |= 0x40000000;
      }

      return m_playout->process_key(iCode);

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
      ::file::patha patha;
      Application.dir().matter_ls_file("keyboard layout", patha);
      for(int32_t i = 0; i < patha.get_count(); i++)
      {
         keyboard_layout_id layoutid;
         if(initialize(&layoutid, patha[i]))
         {
            layoutida.add(layoutid);
         }
      }
      ::sort::quick_sort(layoutida, true);

#ifdef WINDOWSEX


      string strOverride = file_as_string_dup(::dir::system() / "config\\system\\keyboard_layout.txt");

      if(strOverride.has_char())
      {

         string strTest;

         string strPath = Application.dir().matter("keyboard layout/" + strOverride + ".xml");

         strTest = file_as_string_dup(strPath);

         if(strTest.has_char())
         {

            return strPath;

         }

      }

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
      hkl = (HKL) (((uint_ptr) hkl) & 0xffff);
      for(int32_t i = 0; i < layoutida.get_count(); i++)
      {
         if(layoutida[i].m_hkla.contains(hkl))
         {
            return layoutida[i].m_strPath;
         }
      }

#elif defined(LINUX) || defined(SOLARIS)

   string strSymbol = x11_keyboard_get_current_group_symbol();

   for(int32_t i = 0; i < layoutida.get_count(); i++)
   {
      if(layoutida[i].m_countrycode.contains_ci(strSymbol))
      {
         return layoutida[i].m_strPath;
      }
   }

#elif defined(MACOS)

      string strSymbol = keyboard_input_source();

      for(int32_t i = 0; i < layoutida.get_count(); i++)
      {
         if(layoutida[i].m_keylayout.has_char() && strSymbol.contains(layoutida[i].m_keylayout))
         {
            return layoutida[i].m_strPath;
         }
      }

#else

      {

         string strPath = Application.dir().matter("keyboard layout/br_abnt2.xml");

         if(Application.file().exists(strPath))
         {

            return strPath;

         }

         return strPath;

      }

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

      playoutid->m_countrycode = doc.get_root()->attrs()["cc"];

      playoutid->m_keylayout = doc.get_root()->attrs()["kl"];

      stringa straHkl;

      straHkl.explode(";", doc.get_root()->attr("hkla"));

#ifdef WINDOWS

      for(int32_t i = 0; i < straHkl.get_count(); i++)
      {
         string strHkl = straHkl[i];
         HKL hkl;
         strHkl.trim();
         if(::str::begins_eat_ci(strHkl, "0x"))
         {
            hkl = (HKL) ::hex::to_uint_ptr(strHkl);
         }
         else
         {
            hkl = (HKL) atouiptr_dup(strHkl);
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

   void keyboard::translate_os_key_message(key * pkey)
   {

#if defined(WINDOWSEX) || defined(MACOS)

      if(pkey->m_bExt)
      {

         pkey->m_ekey = m_mapExt[(int32_t)pkey->m_nScanCode];

         if(pkey->m_ekey != ::user::key_none)
            return;

      }

      pkey->m_ekey = m_mapScan[(int32_t)pkey->m_nScanCode];

      if(pkey->m_ekey != ::user::key_none)
         return;

#endif

      if(pkey->m_ekey == ::user::key_none)
      {

         pkey->m_ekey = m_mapKey[(int32_t) pkey->m_nChar];

      }

   }


} // namespace user


