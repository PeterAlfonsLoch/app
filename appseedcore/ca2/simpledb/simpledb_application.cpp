#include "StdAfx.h"
#include "mysql/mysql.h"

//#include "gen/command_line.h"


namespace simpledb
{


   application::application()
   {
      m_pserver = NULL;
   }



   bool application::InitializeDataCentral()
   {

      m_pserver = new db_server(this);


      /* initialize client library */
      if (mysql_library_init (0, NULL, NULL))
      {
         TRACE("mysql_library_init() failed\n");
         return false;
      }

      m_pserver->add_client(this);

      if(!m_pserver->initialize())
      {
         simple_message_box(NULL, "Could not initialize simpledb.", MB_OK);
         return false;
      }

      return true;
   }

   void application::on_set_locale(const char * lpcsz, bool bUser)
   {
      if(bUser)
      {
         data_set("locale", lpcsz);
      }
      ::user::application::on_set_locale(lpcsz, bUser);
   }

   void application::on_set_style(const char * lpcsz, bool bUser)
   {
      if(bUser)
      {
         data_set("style", lpcsz);
      }
      ::user::application::on_set_style(lpcsz, bUser);
   }

   void application::on_set_keyboard_layout(const char * pszPath, bool bUser)
   {
      if(bUser)
      {
         data_set("keyboard_layout", pszPath);
      }
      ::user::application::on_set_keyboard_layout(pszPath, bUser);
   }

   bool application::FinalizeDataCentral()
   {
      if(is_system())
      {
         
         m_pserver->finalize();
         delete m_pserver;
         m_pserver = NULL;

         mysql_library_end();
      }

      return true;
   }


   bool application::initialize()
   {

      if(!user::application::initialize())
         return false;

//      if(&AppUser(this) == NULL)
  //       return false;

      if(!InitializeDataCentral())  
      {
         simple_message_box(NULL, "Could not initialize data central"); 
         return false; 
      }
      ::database::client::initialize(this);

      string str;
      // if system locale has changed (compared to last recorded one by ca2)
      // use the system locale
      if(data_get("system_locale", str))
      {
         if(str.has_char())
         {
            if(str != get_locale())
            {
               try
               {
                  data_set("system_locale", get_locale());
                  data_set("locale", get_locale());
               }
               catch(...)
               {
               }
            }
         }
      }
      else
      {
         data_set("system_locale", get_locale());
      }
      if(data_get("locale", str))
      {
         if(str.has_char())
         {
            set_locale(str, false);
         }
      }
      // if system style has changed (compared to last recorded one by ca2)
      // use the system style
      if(data_get("system_style", str))
      {
         if(str.has_char())
         {
            if(str != get_style())
            {
               try
               {
                  data_set("system_style", get_style());
                  data_set("style", get_style());
               }
               catch(...)
               {
               }
            }
         }
      }
      else
      {
         data_set("system_style", get_style());
      }
      if(data_get("style", str))
      {
         if(str.has_char())
         {
            set_style(str, false);
         }
      }
      if(data_get("keyboard_layout", str))
      {
         if(str.has_char())
         {
            set_keyboard_layout(str, false);
         }
      }
      else if(&keyboard().layout() != NULL)
      {
         data_set("keyboard_layout", keyboard().layout().m_strPath);
      }

      data_pulse_change("ca2_fontopus_votagus", "savings", NULL);

      return true;
   }

   bool application::finalize()
   {

      try
      {
         user::application::finalize();
      }
      catch(...)
      {
      }

      try
      {
         FinalizeDataCentral();
      }
      catch(...)
      {
      }


      return true;


   }

   ::database::server * application::get_data_server()
   {
      return m_pserver;
   }

   db_server & application::db()
   {
      return *m_pserver;
   }

} // namespace application