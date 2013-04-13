#include "framework.h"

/*
namespace visual
{


   visual::visual(::ca::graphics * pdc)
   {
      m_pdc = pdc;
   }


   visual::~visual()
   {
   }


   void visual::Polygon(const point_array & pointa)
   {
      m_pdc->Polygon(pointa.get_data(), (int32_t) pointa.get_size());
   }


} // visual


#include "framework.h"

*/


namespace visual
{


   visual::visual()
   {
      m_pimaging        = ::null();
      m_pfontcentral    = ::null();
      m_pvisualapi      = ::null();
   }

   visual::~visual()
   {
      if(m_pimaging != ::null())
      {
         delete m_pimaging;
      }

      if(m_pvisualapi != ::null())
      {
         delete m_pvisualapi;
      }

   }


   void visual::construct(sp(::ca::application) papp)
   {

      ::ca::section::construct(papp);

      m_pvisualapi               = new ::visual::api(papp);

   }

   api & visual::api()
   {

      return *m_pvisualapi;

   }

   imaging & visual::imaging()
   {

      return *m_pimaging;

   }


   bool visual::initialize1()
   {

      if(!::ca::section::initialize1())
         return false;

      m_pfontcentral = new class font_central(get_app());

      if(m_pfontcentral == ::null())
         return false;

      if(!m_pfontcentral->Initialize())
         return false;

      m_pimaging = new class imaging(get_app());

      if(m_pimaging == ::null())
         throw memory_exception(get_app());
      
      return true;

   }


   bool visual::process_initialize()
   {

      if(!::ca::section::process_initialize())
         return false;

      if(!m_pvisualapi->open())
         return false;

      return true;

   }


   bool visual::initialize()
   {

      if(!::ca::section::initialize())
         return false;

      __begin_thread(get_app(), &visual::thread_proc_parallel_initialize, this, ::ca::thread_priority_highest);

      

      return true;

   }

   uint32_t c_cdecl visual::thread_proc_parallel_initialize(void * pparamThis)
   {
      
      visual * pvisual = (visual *) pparamThis;

      pvisual->set_cursor_set_from_matter("cursor/antialiased-classic");

      return 0;

   }


   bool visual::finalize()
   {

      bool bOk = true;

      try
      {

         bOk = m_pvisualapi->close();

      }
      catch(...)
      {

         bOk = false;

      }

      return bOk;
      
   }


   class font_central & visual::font_central()
   {
      return *m_pfontcentral;
   }

   cursor * visual::set_cursor_file(e_cursor ecursor, const char * psz)
   {
      cursor * pcursor = get_cursor(ecursor);
      if(pcursor->load_from_file(psz))
      {
         return pcursor;
      }
      else
      {
         return ::null();
      }
   }

   cursor * visual::set_cursor_matter(e_cursor ecursor, const char * pszMatter)
   {
      cursor * pcursor = get_cursor(ecursor);
      if(pcursor->load_from_matter(pszMatter))
      {
         return pcursor;
      }
      else
      {
         return ::null();
      }
   }


   cursor * visual::get_cursor(e_cursor ecursor)
   {

      cursor * pcursor = ::null();

      if(m_cursormap.Lookup(ecursor, pcursor))
      {

         return pcursor;

      }
      else
      {

         pcursor = new cursor(get_app());

         pcursor->m_ecursor = ecursor;

         m_cursormap.set_at(ecursor, pcursor);

         return pcursor;

      }

   }



   ::count visual::set_cursor_set_from_matter(const char * pszMatter)
   {
      return set_cursor_set_from_dir(
         System.dir().name(
            Application.dir().matter(
               System.dir().path(pszMatter, "arrow.png"))));
   }

   ::count visual::set_cursor_set_from_dir(const char * pszDir)
   {
      ::count count = 0;
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
      if(set_cursor_file(::visual::cursor_size_vertical, System.dir().path(pszDir, "size_vertical.png")))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_vertical, System.dir().path(pszDir, "arrow.png"));
      }
      if(set_cursor_file(::visual::cursor_size_horizontal, System.dir().path(pszDir, "size_horizontal.png")))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_horizontal, System.dir().path(pszDir, "arrow.png"));
      }

      return count;
   }

   // should not call base class implementation because visual::visual is inside a n-furcation of user::visual
   int32_t visual::exit_instance()
   {

      int32_t iExitCode = 0;
      
      try
      {

         iExitCode = ::ca::section::exit_instance();

      }
      catch(...)
      {
         
         iExitCode = -1;

      }

      return iExitCode;

   }


} // namespace visual