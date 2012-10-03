#include "framework.h"

namespace visual
{

   application::application()
   {
      m_pimaging        = NULL;
      m_pfontcentral    = NULL;
      m_ecursorDefault  = cursor_arrow;
      m_ecursor         = cursor_default;
   }

   application::~application()
   {
      if(m_pimaging != NULL)
      {
         delete m_pimaging;
      }
   }

   imaging & application::imaging()
   {
      return *m_pimaging;
   }

   bool application::initialize1()
   {

      if(!::userpresence::application::initialize1())
         return false;

      m_pfontcentral = new class font_central(this);
      if(m_pfontcentral == NULL)
         return false;

      if(!m_pfontcentral->Initialize())
         return false;

      m_pimaging = new class imaging(this);
      if(m_pimaging == NULL)
         throw memory_exception(this);

      set_cursor_set_from_matter("cursor/antialiased-classic");
      
      return true;

   }

   bool application::initialize()
   {

      if(!::userpresence::application::initialize())
         return false;

      return true;

   }

   class font_central & application::font_central()
   {
      return *m_pfontcentral;
   }

   cursor * application::set_cursor_file(e_cursor ecursor, const char * psz)
   {
      cursor * pcursor = get_cursor(ecursor);
      if(pcursor->load_from_file(psz))
      {
         return pcursor;
      }
      else
      {
         return NULL;
      }
   }

   cursor * application::set_cursor_matter(e_cursor ecursor, const char * pszMatter)
   {
      cursor * pcursor = get_cursor(ecursor);
      if(pcursor->load_from_matter(pszMatter))
      {
         return pcursor;
      }
      else
      {
         return NULL;
      }
   }

   cursor * application::get_cursor(e_cursor ecursor)
   {
      cursor * pcursor = NULL;
      if(m_cursormap.Lookup(ecursor, pcursor))
      {
         return pcursor;
      }
      else
      {
         pcursor = new cursor(this);
         pcursor->m_ecursor = ecursor;
         m_cursormap.set_at(ecursor, pcursor);
         return pcursor;
      }
   }

   cursor * application::get_cursor()
   {
      if(m_ecursor == cursor_none)
         return NULL;
      else if(m_ecursor == cursor_default)
         return get_cursor(m_ecursorDefault);
      else
         return get_cursor(m_ecursor);
   }

   void application::set_cursor(e_cursor ecursor)
   {
      m_ecursor = ecursor;
      try
      {
         if(m_psession != NULL)
         {
            m_psession->m_ecursor = ecursor;
         }
      }
      catch(...)
      {
      }
   }

   cursor * application::get_default_cursor()
   {
      return get_cursor(m_ecursorDefault);
   }

   void application::set_default_cursor(e_cursor ecursor)
   {
      if(ecursor == cursor_default)
      {
         m_ecursorDefault = cursor_arrow;
      }
      else
      {
         m_ecursorDefault = ecursor;
      }
   }

   count application::set_cursor_set_from_matter(const char * pszMatter)
   {
      return set_cursor_set_from_dir(
         System.dir().name(
            Application.dir().matter(
               System.dir().path(pszMatter, "arrow.png"))));
   }

   count application::set_cursor_set_from_dir(const char * pszDir)
   {
      count count = 0;
      if(set_cursor_file(::visual::cursor_arrow, System.dir().path(pszDir, "arrow.png")))
      {
         count++;
      }
      else
      {
         return 0;
      }
      if(set_cursor_file(::visual::cursor_hand, System.dir().path(pszDir, "hand.png")))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_hand, System.dir().path(pszDir, "arrow.png"));
      }
      if(set_cursor_file(::visual::cursor_text_select, System.dir().path(pszDir, "text_select.png")))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_text_select, System.dir().path(pszDir, "arrow.png"));
      }
      if(set_cursor_file(::visual::cursor_size_top_left, System.dir().path(pszDir, "size_top_left.png")))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_top_left, System.dir().path(pszDir, "arrow.png"));
      }
      if(set_cursor_file(::visual::cursor_size_top, System.dir().path(pszDir, "size_top.png")))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_top, System.dir().path(pszDir, "arrow.png"));
      }
      if(set_cursor_file(::visual::cursor_size_top_right, System.dir().path(pszDir, "size_top_right.png")))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_top_right, System.dir().path(pszDir, "arrow.png"));
      }
      if(set_cursor_file(::visual::cursor_size_right, System.dir().path(pszDir, "size_right.png")))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_right, System.dir().path(pszDir, "arrow.png"));
      }
      if(set_cursor_file(::visual::cursor_size_bottom_right, System.dir().path(pszDir, "size_bottom_right.png")))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_bottom_right, System.dir().path(pszDir, "arrow.png"));
      }
      if(set_cursor_file(::visual::cursor_size_bottom, System.dir().path(pszDir, "size_bottom.png")))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_bottom, System.dir().path(pszDir, "arrow.png"));
      }
      if(set_cursor_file(::visual::cursor_size_bottom_left, System.dir().path(pszDir, "size_bottom_left.png")))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_bottom_left, System.dir().path(pszDir, "arrow.png"));
      }
      if(set_cursor_file(::visual::cursor_size_left, System.dir().path(pszDir, "size_left.png")))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_left, System.dir().path(pszDir, "arrow.png"));
      }

      return count;
   }

   // should not call base class implementation because visual::application is inside a n-furcation of user::application
   int application::exit_instance()
   {

      int iExitCode = 0;
      
      try
      {

         iExitCode = ::userpresence::application::exit_instance();

      }
      catch(...)
      {
         
         iExitCode = -1;

      }

      return iExitCode;

   }


} // namespace visual