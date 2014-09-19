#include "framework.h" // from "axis/user/user.h"

#if defined(LINUX) || defined(SOLARIS)
#include "axis/axis/os/x11/x11_keyboard.h"
#elif defined(APPLEOS)
string keyboard_input_source();
#endif


namespace user
{

   keyboard::keyboard(sp(::aura::application) papp) :
      element(papp)
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
      System.set_enum_name(key_command, "key_alt");
      System.set_enum_name(key_lcommand, "key_lalt");
      System.set_enum_name(key_rcommand, "key_ralt");
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

   }


   bool keyboard::initialize()
   {

         string strPath;

#ifdef LINUX
      strPath = Application.dir_matter("keyboard/linux/default.xml");
#elif defined(APPLEOS)
      strPath = Application.dir_matter("keyboard/macos/default.xml");
#else
      strPath = Application.dir_matter("keyboard/windows/default.xml");
#endif

      if(!Application.file_exists(strPath))
         return false;

      if(!load_os_layout(strPath))
         return false;

      return true;

   }



   bool keyboard::load_os_layout(const char * pszPath)
   {

      int32_t iCode;

      ::user::e_key ekey;

      sp(type) typeinfoKey = System.type_info < ::user::e_key > ();

      string str = Application.file_as_string(pszPath);

      if(str.is_empty())
      {
         TRACE0("unable to load os keyboard layout");
         return false;
      }

      ::xml::document doc(get_app());

      if(!doc.load(str))
      {
         TRACE0("unable to load os keyboard layout");
         return false;
      }

      for(int32_t i = 0; i < doc.get_root()->get_children_count(); i++)
      {

         sp(::xml::node) pnode = doc.get_root()->child_at(i);

         if(pnode->get_name().CompareNoCase("item") == 0)
         {

            string strCode    = pnode->attr("code");

            string strValue   = pnode->attr("value");

            iCode    = atoi(strCode);

            ekey     = System.enum_from_name < ::user::e_key > (typeinfoKey, strValue);

            m_mapKey.set_at(iCode, ekey);

         }

      }

      return true;

   }


   class keyboard_layout & keyboard::layout()
   {
      return *m_playout;
   }

   void keyboard::process_escape(sp(::xml::node) pnode, property_set & set)
   {
      m_playout->process_escape(pnode, set);
   }

   bool keyboard::load_layout(const char * pszPath, ::action::context actioncontext)
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
         TRACE("setting keyboard layout to %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
         if(playout->load(playout->m_strPath))
         {
            m_playout = playout;
// xxx            System.simpledb().on_set_keyboard_layout(playout->m_strPath, actioncontext);
            TRACE("successfully set keyboard layout to %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
            return true;
         }
         else
         {
            playout->release();
            TRACE("failed to load keyboard layout : %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
         }
      }
      else
      {
         TRACE("failed to set keyboard layout path=%s", pszPath);
      }
      return false;
   }

   string keyboard::process_key(::user::e_key ekey)
   {

      if(m_playout == NULL)
      {

         return (char) ekey;

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
      stringa straPath;
      Application.dir_matter_ls_file("keyboard layout", straPath);
      for(int32_t i = 0; i < straPath.get_count(); i++)
      {
         keyboard_layout_id layoutid;
         if(initialize(&layoutid, straPath[i]))
         {
            layoutida.add(layoutid);
         }
      }
      layoutida.quick_sort(true);

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

#elif defined(LINUX) || defined(SOLARIS)

   string strSymbol = x11_keyboard_get_current_group_symbol();

   for(int32_t i = 0; i < layoutida.get_count(); i++)
   {
      if(layoutida[i].m_countrycode.contains_ci(strSymbol))
      {
         return layoutida[i].m_strPath;
      }
   }
   
#elif defined(APPLEOS)

      string strSymbol = keyboard_input_source();
      
      for(int32_t i = 0; i < layoutida.get_count(); i++)
      {
         if(layoutida[i].m_keylayout.has_char() && strSymbol.contains(layoutida[i].m_keylayout))
         {
            return layoutida[i].m_strPath;
         }
      }

#else

      TRACE("not implemented exception");

#endif

      string strPath = Application.dir_matter("keyboard layout/en_us_international.xml");

      if(Application.file_exists(strPath))
      {

         return strPath;

      }

      return "";

   }


   bool keyboard::initialize(keyboard_layout_id * playoutid, const char * pszPath)
   {

      if(!Application.file_exists(pszPath))
         return false;

      string str = Application.file_as_string(pszPath);

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
            hkl = (HKL) ::hex::to_uint(strHkl);
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

   void keyboard::translate_os_key_message(::message::key * pkey)
   {

#ifdef WINDOWSEX

      if(pkey->m_uiMessage == WM_KEYDOWN ||
         pkey->m_uiMessage == WM_KEYUP)
      {

         switch(pkey->m_nChar)
         {
         case 'a':
         case 'A':
            pkey->m_ekey = ::user::key_a;
            break;
         case 'b':
         case 'B':
            pkey->m_ekey = ::user::key_b;
            break;
         case 'c':
         case 'C':
            pkey->m_ekey = ::user::key_c;
            break;
         case 'd':
         case 'D':
            pkey->m_ekey = ::user::key_d;
            break;
         case 'e':
         case 'E':
            pkey->m_ekey = ::user::key_e;
            break;
         case 'f':
         case 'F':
            pkey->m_ekey = ::user::key_f;
            break;
         case 'g':
         case 'G':
            pkey->m_ekey = ::user::key_g;
            break;
         case 'h':
         case 'H':
            pkey->m_ekey = ::user::key_h;
            break;
         case 'i':
         case 'I':
            pkey->m_ekey = ::user::key_i;
            break;
         case 'j':
         case 'J':
            pkey->m_ekey = ::user::key_j;
            break;
         case 'k':
         case 'K':
            pkey->m_ekey = ::user::key_k;
            break;
         case 'l':
         case 'L':
            pkey->m_ekey = ::user::key_l;
            break;
         case 'm':
         case 'M':
            pkey->m_ekey = ::user::key_m;
            break;
         case 'n':
         case 'N':
            pkey->m_ekey = ::user::key_n;
            break;
         case 'o':
         case 'O':
            pkey->m_ekey = ::user::key_o;
            break;
         case 'p':
         case 'P':
            pkey->m_ekey = ::user::key_p;
            break;
         case 'q':
         case 'Q':
            pkey->m_ekey = ::user::key_q;
            break;
         case 'r':
         case 'R':
            pkey->m_ekey = ::user::key_r;
            break;
         case 's':
         case 'S':
            pkey->m_ekey = ::user::key_s;
            break;
         case 't':
         case 'T':
            pkey->m_ekey = ::user::key_t;
            break;
         case 'u':
         case 'U':
            pkey->m_ekey = ::user::key_u;
            break;
         case 'v':
         case 'V':
            pkey->m_ekey = ::user::key_v;
            break;
         case 'w':
         case 'W':
            pkey->m_ekey = ::user::key_w;
            break;
         case 'x':
         case 'X':
            pkey->m_ekey = ::user::key_x;
            break;
         case 'y':
         case 'Y':
            pkey->m_ekey = ::user::key_y;
            break;
         case 'z':
         case 'Z':
            pkey->m_ekey = ::user::key_z;
            break;
         case '0':
            pkey->m_ekey = ::user::key_0;
            break;
         case '1':
            pkey->m_ekey = ::user::key_1;
            break;
         case '2':
            pkey->m_ekey = ::user::key_2;
            break;
         case '3':
            pkey->m_ekey = ::user::key_3;
            break;
         case '4':
            pkey->m_ekey = ::user::key_4;
            break;
         case '5':
            pkey->m_ekey = ::user::key_5;
            break;
         case '6':
            pkey->m_ekey = ::user::key_6;
            break;
         case '7':
            pkey->m_ekey = ::user::key_7;
            break;
         case '8':
            pkey->m_ekey = ::user::key_8;
            break;
         case '9':
            pkey->m_ekey = ::user::key_9;
            break;
         case VK_SHIFT:
            pkey->m_ekey = ::user::key_shift;
            break;
         case VK_MENU:
            pkey->m_ekey = ::user::key_alt;
            break;
         case VK_CONTROL:
            pkey->m_ekey = ::user::key_control;
            break;
         case VK_DELETE:
            pkey->m_ekey = ::user::key_delete;
            break;
         case VK_BACK:
            pkey->m_ekey = ::user::key_back;
            break;
         case VK_UP:
            pkey->m_ekey = ::user::key_up;
            break;
         case VK_DOWN:
            pkey->m_ekey = ::user::key_down;
            break;
         case VK_RIGHT:
            pkey->m_ekey = ::user::key_right;
            break;
         case VK_LEFT:
            pkey->m_ekey = ::user::key_left;
            break;
         case VK_OEM_PERIOD:
            pkey->m_ekey = ::user::key_dot;
            break;
         case VK_OEM_COMMA:
            pkey->m_ekey = ::user::key_comma;
            break;
         case VK_OEM_MINUS:
            pkey->m_ekey = ::user::key_hyphen;
            break;
         case VK_RETURN:
            pkey->m_ekey = ::user::key_return;
            break;
         case VK_TAB:
            pkey->m_ekey = ::user::key_tab;
            break;
         case VK_SPACE:
            pkey->m_ekey = ::user::key_space;
            break;
         default:
            pkey->m_ekey = m_mapKey[(int32_t)pkey->m_nChar];
            break;
         }

         return;

      }

#endif

      pkey->m_ekey = m_mapKey[(int32_t) pkey->m_nChar];

   }


} // namespace user


