#include "framework.h"


#define SIZEX 584
#define SIZEY 384


namespace simple_ui
{


   message_box::message_box(sp(::base::application) papp) :
      element(papp)
   {

      m_uiFlags      = 0;
      m_iResult      = 0;

   }


   message_box::~message_box()
   {

   }


   int32_t message_box::show(const char * pszMessage, uint32_t uiFlags)
   {

      m_uiFlags = uiFlags;

      if(!CreateEx(WS_EX_LAYERED, NULL, NULL, 0, null_rect(), NULL, "fontopus"))
         throw simple_exception(get_app(), "not excepted! Failing Message box!!");

      m_ptapOk = new ::simple_ui::tap(get_app());

      m_ptapOk->create(this, "ok");

      m_ptapOk->SetWindowText("OK");

      ::rect rectDesktop;

      stringa stra;

      stra.add("\r");

      stra.add("\n");

      stra.add("\r\n");

      m_stra.add_smallest_tokens(pszMessage, stra);

      session().get_main_monitor(rectDesktop);

      SetWindowText( "fontopus Auth Windows");

      rect rectFontopus;

      int stdw = 800;

      int stdh = 184 + 23 + 184;

      int w = stdw;

      int h = stdh;

      if(w > rectDesktop.width())
      {

         w = rectDesktop.width();

      }

      if(h > rectDesktop.height())
      {

         h = rectDesktop.height();

      }

      rectFontopus.left = rectDesktop.left + (width(rectDesktop) - w) / 2;

      rectFontopus.top = rectDesktop.top + (height(rectDesktop) - h) / 3;

      rectFontopus.right = rectFontopus.left + w;

      rectFontopus.bottom = rectFontopus.top + h;

      SetWindowPos(ZORDER_TOP, rectFontopus, SWP_SHOWWINDOW);

      SetForegroundWindow();

      BringWindowToTop();

      BringToTop(SW_NORMAL);

      RunModalLoop();

      return m_iResult;

   }


   void message_box::_001OnDraw(::draw2d::graphics * pdc)
   {

      rect rectClient;

      GetClientRect(rectClient);

      pdc->FillSolidRect(rectClient, ARGB(255, 0xcc, 0xcc, 0xc5));

      sp(::draw2d::font) font(allocer());

      font->create_point_font("Arial", 12);

      pdc->selectFont(font);

      ::draw2d::text_metric tm;

      pdc->get_text_metrics(&tm);

      int iHeight = tm.tmHeight;

      int y = 10;

      for(int i = 0; i < m_stra.get_size(); i++)
      {

         pdc->TextOut(10, y, m_stra[i]);

         y+= iHeight;

      }


   }


   void message_box::layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if(m_ptapOk.is_set())
      {

         m_ptapOk->SetWindowPos(ZORDER_TOP, rectClient.left + 10, rectClient.bottom - 94, 200, 84, SWP_SHOWWINDOW);

      }

   }


   bool message_box::on_action(const char * pszId)
   {

      if(stricmp_dup(pszId, "ok") == 0)
      {

         m_iResult = IDOK;

         EndModalLoop(IDOK);

         return true;

      }
      else if(stricmp_dup(pszId, "yes") == 0)
      {

         m_iResult = IDYES;

         EndModalLoop(IDOK);

         return true;

      }
      else if(stricmp_dup(pszId, "no") == 0)
      {

         m_iResult = IDNO;

         EndModalLoop(IDOK);

         return true;

      }
      else if(stricmp_dup(pszId, "cancel") == 0)
      {

         m_iResult = IDCANCEL;

         EndModalLoop(IDOK);

         return true;

      }

      return false;

   }


} // namespace simple_ui


int32_t simple_ui_message_box(oswindow interaction_impl, const char * lpText,const char * lpCaption, uint32_t uiFlags)
{

   if(::get_thread_app() == NULL || ::get_thread_app()->m_pbasesession == NULL)
   {

      return MessageBox(interaction_impl,lpText,lpCaption,uiFlags);

   }

   sp(::simple_ui::message_box) pmessagebox = canew(::simple_ui::message_box(::get_thread_app()));

   int32_t iResult = pmessagebox->show(lpText, uiFlags);

   //pmessagebox->DestroyWindow();

   return iResult;

}


extern "C"
CLASS_DECL_BASE int32_t simple_message_box(oswindow interaction_impl,const char * lpText,const char * lpCaption,uint32_t uiFlags)
{

   return simple_ui_message_box(interaction_impl,lpText,lpCaption,uiFlags);

}
