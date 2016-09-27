//#include "framework.h"

/*
namespace visual
{


   visual::visual(::draw2d::dib * pdib)
   {
      m_pdc = pgraphics;
   }


   visual::~visual()
   {
   }


   void visual::Polygon(const point_array & pointa)
   {
      m_pdc->Polygon(pointa.get_data(), (int32_t) pointa.get_size());
   }


} // visual


//#include "framework.h"

*/


namespace visual
{


   visual::visual(::aura::application * papp) :
      ::object(papp),
      ::aura::department(papp)
   {

      m_pimaging = NULL;
      m_pfontcentral = NULL;
      m_pvisualapi = new ::visual::api(papp);

   }


   visual::~visual()
   {

      ::aura::del(m_pimaging);
      ::aura::del(m_pvisualapi);
      ::aura::del(m_pfontcentral);

   }


   void visual::construct(::aura::application * papp)
   {

      ::aura::department::construct(papp);



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

      if (!::aura::department::initialize1())
         return false;

      if (m_pfontcentral == NULL)
      {

         m_pfontcentral = new class font_central(get_app());

         if (m_pfontcentral == NULL)
            return false;

         if (!m_pfontcentral->Initialize())
            return false;

      }

      if (m_pimaging == NULL)
      {

         m_pimaging = new class imaging(get_app());

         if (m_pimaging == NULL)
            throw memory_exception(get_app());

      }

      return true;

   }


   bool visual::process_initialize()
   {

      if (!::aura::department::process_initialize())
         return false;

      if (!m_pvisualapi->open())
         return false;

      return true;

   }


   bool visual::initialize()
   {

      if (!::aura::department::initialize())
         return false;

      //if(Application.dir().is(System.dir().commonappdata("")))
      {

         __begin_thread(get_app(), &visual::thread_proc_parallel_initialize, this, ::multithreading::priority_highest);

      }

      return true;

   }

   uint32_t c_cdecl visual::thread_proc_parallel_initialize(void * pparamThis)
   {

      visual * pvisual = (visual *)pparamThis;

      pvisual->set_cursor_set_from_matter("cursor/antialiased-classic");

      return 0;

   }


   bool visual::finalize()
   {

      bool bOk = true;

      try
      {

         if (m_pvisualapi != NULL)
         {

            bOk = m_pvisualapi->close();

         }

      }
      catch (...)
      {

         bOk = false;

      }

      try
      {

         if (m_pfontcentral != NULL)
         {

            m_pfontcentral->Finalize();

         }

      }
      catch (...)
      {


      }

      ::aura::del(m_pvisualapi);

      ::aura::del(m_pfontcentral);

      ::aura::del(m_pimaging);

      for (auto & p : m_cursormap)
      {

         delete p.m_element2;

      }

      m_cursormap.remove_all();

      return bOk;

   }


   class font_central & visual::font_central()
   {
      return *m_pfontcentral;
   }

   cursor * visual::set_cursor_file(e_cursor ecursor, const ::file::path & psz, bool bFromCache)
   {

      cursor * pcursor = get_cursor(ecursor);

      if (System.visual().imaging().load_from_file(pcursor, psz, bFromCache))
      {

         return pcursor;

      }
      else
      {

         return NULL;

      }

   }


   cursor * visual::get_cursor(e_cursor ecursor)
   {

      cursor * pcursor = NULL;

      if (m_cursormap.Lookup(ecursor, pcursor))
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



   ::count visual::set_cursor_set_from_matter(const ::file::path & pszMatter)
   {

      // "arrow.png" is a troll/bait for getting the right path of the cursor file, then the directory where found

      return set_cursor_set_from_dir(Application.dir().matter(pszMatter / "arrow.png").folder(), true);

   }


   ::count visual::set_cursor_set_from_dir(const ::file::path & pszDir, bool bFromCache)
   {
      ::count count = 0;
      if (set_cursor_file(::visual::cursor_arrow, pszDir / "arrow.png", bFromCache))
      {
         count++;
      }
      else
      {
         return 0;
      }
      if (set_cursor_file(::visual::cursor_hand, pszDir / "hand.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_hand, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_text_select, pszDir / "text_select.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_text_select, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_top_left, pszDir / "size_top_left.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_top_left, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_top, pszDir / "size_top.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_top, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_top_right, pszDir / "size_top_right.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_top_right, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_right, pszDir / "size_right.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_right, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_bottom_right, pszDir / "size_bottom_right.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_bottom_right, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_bottom, pszDir / "size_bottom.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_bottom, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_bottom_left, pszDir / "size_bottom_left.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_bottom_left, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_left, pszDir / "size_left.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_left, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_vertical, pszDir / "size_vertical.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_vertical, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_horizontal, pszDir / "size_horizontal.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_horizontal, pszDir / "arrow.png", bFromCache);
      }

      return count;
   }

   // should not call axis class implementation because visual::visual is inside a n-furcation of user::visual
   int32_t visual::exit_instance()
   {

      int32_t iExitCode = 0;

      try
      {

         iExitCode = ::aura::department::exit_instance();

      }
      catch (...)
      {

         ::simple_message_box(NULL, "except", "except", MB_OK);
         iExitCode = -1;

      }

      return iExitCode;

   }

   bool visual::embossed_text_out(
      ::draw2d::graphics * pgraphics,
      LPCRECT lpcrect,
      string strText,
      ::visual::fastblur & dib2,
      ::draw2d::font * pfont,
      int iDrawTextFlags,
      COLORREF crText,
      COLORREF crGlow,
      int iSpreadRadius,
      int iBlurRadius,
      int iBlur,
      bool bUpdate)

   {

      if (strText.is_empty())
      {

         return false;

      }


      int iR = MAX(iSpreadRadius, iBlurRadius, iBlur);

      ::rect rectText = *lpcrect;

      rectText.left -= iR;
      rectText.top -= iR;
      rectText.right += iR;
      rectText.bottom += iR;

      if (bUpdate || dib2.is_null() || dib2->area() <= 0)
      {

         int iEffectiveSpreadRadius = iSpreadRadius;

         int iEffectiveBlurRadius = iBlurRadius;

         if (dib2.is_null())
         {

            dib2.alloc(allocer());

         }

         class size size = rectText.size();

         dib2.initialize(size, iEffectiveBlurRadius);

         dib2->Fill(0, 0, 0, 0);

         class rect rectCache;

         rectCache.left = iR + (iR >= 2 ? 1 : 0);
         rectCache.top = iR + 1;
         rectCache.right = rectCache.left + (int32_t)width(lpcrect);
         rectCache.bottom = rectCache.top + (int32_t)height(lpcrect);

         ::draw2d::dib_sp dib(allocer());

         dib->create(size.cx, size.cy);
         dib->Fill(0, 0, 0, 0);

         ::draw2d::brush_sp brushText(allocer());

         brushText->create_solid(ARGB(255, 255, 255, 255));
         dib->get_graphics()->SelectObject(brushText);

         dib->get_graphics()->SelectObject(pfont);
         dib->get_graphics()->_DrawText(strText, rectCache, iDrawTextFlags);

         System.visual().imaging().channel_spread_set_color(dib2->get_graphics(), null_point(), size, dib->get_graphics(), null_point(), ::visual::rgba::channel_alpha, iEffectiveSpreadRadius, ARGB(255, 255, 255, 255));
         
         for (index i = 0; i < iBlur; i++)
         {

            dib2.blur();

         }

         dib2->set_rgb(crGlow);

         dib2->mult_alpha();

      }

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
      pgraphics->BitBlt(rectText, dib2->get_graphics(), point(1, 1));

      ::draw2d::brush_sp brushText(allocer());
      brushText->create_solid(crText);
      pgraphics->SelectObject(brushText);
      pgraphics->SelectObject(pfont);
      pgraphics->_DrawText(strText, *lpcrect, iDrawTextFlags);

      return true;

   }


} // namespace visual
