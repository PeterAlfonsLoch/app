#include "framework.h"


CLASS_DECL_BASE void draw_ca2(::draw2d::graphics * pdc, int x, int y, int z, COLORREF crBk, COLORREF cr);
CLASS_DECL_BASE void draw_ca2_with_border(::draw2d::graphics * pdc, int x, int y, int z, int b, COLORREF crBk, COLORREF cr, COLORREF crOut);
CLASS_DECL_BASE void draw_ca2_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crBorderOut, COLORREF crIn);
CLASS_DECL_BASE void draw_ca2_with_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crBorderOut, COLORREF crIn);


namespace fontopus
{


   login::login(sp(::base::application) papp, int left, int top) :
      element(papp),
      m_labelUser(papp),
      m_editUser(papp),
      m_labelPassword(papp),
      m_password(papp),
      m_tap(papp)
   {

      m_bSelfLayout = false;

      m_picon95 = NULL;

#if defined(WINDOWS)

      {

         HICON hicon95 = (HICON) ::LoadImage(::GetModuleHandle(NULL),MAKEINTRESOURCE(95),IMAGE_ICON,95,95,LR_VGACOLOR);

         if(hicon95 != NULL)
         {

            m_picon95 = new ::visual::icon(hicon95);

         }

      }

#endif
      m_bCred = false;


   }


   void login::install_message_handling(::message::dispatch * pdispatch)
   {

      ::simple_ui::interaction::install_message_handling(pdispatch);

      IGUI_CREATE(login);

   }


   void login::defer_translate(::simple_ui::style * pstyle)
   {

      xxdebug_box("defer_translate", "login", 0);

      string strFontopusServer = Session.fontopus()->get_fontopus_server("account.ca2.cc");

      string strForm = pstyle->defer_get("http://" + strFontopusServer + "/login_form");

      if (strForm.is_empty())
         return;

      ::xml::document doc(get_app());

      if (!doc.load(strForm))

         return;
      ::xml::node & node = *doc.get_root();

      string str;

      str = node.attr("email");

      if (str.has_char())
         m_labelUser.SetWindowText(str);

      str = node.attr("senha");

      if (str.has_char())
         m_labelPassword.SetWindowText(str);

      str = node.attr("abrir");

      if (str.has_char())
         m_tap.SetWindowText(str);

   }


   login::~login()
   {
   }


   void login::initialize()
   {

   }






   void login::layout()
   {


      int stdw = 884;
      int stdh = 184 + 23 + 184;

      int h;
      int w;

      rect rectClient;

      GetClientRect(rectClient);

      if (m_bSelfLayout)
      {
         

         double dwh = (double)stdw / (double)stdh;

         int availw = (int) (rectClient.width() * (1.0 - 0.14));
         int availh = (int) (rectClient.height() * (1.0 - 0.14));

         double davailwh;

         if (availh == 0.0)
         {
            davailwh = 1.0;
         }
         else
         {
            davailwh = (double)availw / (double)availh;
         }


         if (davailwh > dwh) // remaining width
         {

            h = (int) min(stdh, availh);
            w = (int) min(stdw, h  * dwh);

         }
         else // remaining height
         {

            w = (int) min(stdw, availw);
            h = (int) min(stdh, w / dwh);

         }

         rectClient.left = (rectClient.width() - w) / 2;
         rectClient.top = (rectClient.height() - h) / 3;
         rectClient.right = rectClient.left + w;
         rectClient.bottom = rectClient.top + h;

         SetPlacement(rectClient);

      }
      else
      {
         
         GetClientRect(rectClient);

      }

      
      w = (int)(rectClient.width());

      h = (int)(rectClient.height());
      
      m_dRateX = (double)w / (double)stdw;

      m_dRateY = (double)h / (double)stdh;
      
      double rx = m_dRateX;

      double ry = m_dRateY;

      int32_t x1 = (int) (49 * rx);
      int32_t w2 = (int) ((rectClient.width() - 49 * 2 * rx));
      int32_t h1 = (int) (23 * ry);
      int32_t pad = (int) (5 * ry);

      int32_t y = (int) ((49 + 86) * ry);
      m_labelUser.RepositionWindow(x1,y,w2,h1);
      y += h1 + pad;
      m_editUser.RepositionWindow(x1,y,w2, h1);
      y += h1 + pad;
      m_labelPassword.RepositionWindow(x1,y,w2, h1);
      y += h1 + pad;
      m_password.RepositionWindow(x1,y,w2,h1);
      y += h1 + pad;
      y += pad + h1 + pad;
      m_tap.RepositionWindow(x1,y,w2,h1 * 3);;


   }



   void login::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      simple_ui_draw_frame_window_rect(pgraphics);

      COLORREF crOut, crIn, crBorderOut, crBorderIn, cr, crBk;

      //       if (is_hover() || m_bDown || m_bMouseMove)
      /*       {

      #if CA2_PLATFORM_VERSION == CA2_BASIS

      crOut = ARGB(184 + 49, 255, 230, 255);

      crIn = ARGB(255, 255, 84 + 49, 255);

      crBorderOut = ARGB(184, 150, 100, 150);

      crBorderIn = ARGB(184, 255, 240, 255);

      #else

      crOut = ARGB(184 + 49, 230, 255, 225);

      crIn = ARGB(255, 84 + 49, 255, 77 + 49);

      crBorderOut = ARGB(184, 100, 150, 100);

      crBorderIn = ARGB(184, 240, 255, 235);

      #endif

      }
      else*/
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         /*crOut = ARGB(184, 255, 210, 255);

         crIn = ARGB(255, 255, 184 + 49, 255);

         crBorderOut = ARGB(184, 90, 20, 90);

         crBorderIn = ARGB(184, 255, 240, 255);*/

         crOut = ARGB(255, 255, 210, 255);

         crIn = ARGB(255, 255, 184 + 49, 255);

         crBorderOut = ARGB(255, 90, 20, 90);

         crBorderIn = ARGB(255, 255, 240, 255);

#else

         crOut = ARGB(184, 210, 255, 205);

         crIn = ARGB(255, 84 + 49, 255, 77 + 49);

         crBorderOut = ARGB(184, 20, 90, 20);

         crBorderIn = ARGB(184, 240, 255, 235);

#endif

      }


#if CA2_PLATFORM_VERSION == CA2_BASIS

      //cr = ARGB(223, 84, 49, 77);
      cr = ARGB(255, 84, 49, 77);

#else

      //cr = ARGB(223, 49, 84, 23);
      cr = ARGB(255, 49, 84, 23);

#endif

      crBk = ARGB(
         (argb_get_a_value(crOut) + argb_get_a_value(crIn)) / 2,
         (argb_get_r_value(crOut) + argb_get_r_value(crIn)) / 2,
         (argb_get_g_value(crOut) + argb_get_g_value(crIn)) / 2,
         (argb_get_b_value(crOut) + argb_get_b_value(crIn)) / 2);

      double rx = m_dRateX;

      double ry = m_dRateY;

      if (m_bCred && m_strCred.has_char())
      {
         float fHeight = 18.0;

         ::draw2d::font_sp f(allocer());

         /*f->create_pixel_font("Geneva", (int32_t)height(rectClient) * 0.7);

         float fMargin = (height(rectClient) * ((1.0f - 0.7f) / 2.0f));*/

         f->create_point_font("Geneva", fHeight * 1.0);


         pgraphics->SelectObject(f);

         pgraphics->set_text_color(crBorderOut);
         pgraphics->TextOut((int)(49 * rx), (int)(49 * ry), m_strCred);
      }
      else if (m_picon95)
      {

         draw_ca2_border2(pgraphics, (int)(49 * rx), (int)(49 * ry) - 11, (int)((91 + 2 + 2) * ry), 1, 1, crBk, cr, crBorderOut, crBorderIn);

         pgraphics->DrawIcon((int)(49 * rx) + 2, (int)(49 * ry) + 2 - 11, m_picon95, (int)((91 + 2 + 2) * ry), (int)((91 + 2 + 2) * ry), 0, NULL, 0);

      }
      else
      {

         draw_ca2_with_border2(pgraphics, (int)(49 * rx), (int)(49 * ry) - 11, (int)((91 + 2 + 2) * ry), 1, 1, crBk, cr, crBorderOut, crBorderIn);

      }


   }


   bool login::on_action(const char * pszId)
   {

      if (!strcmp(pszId, "submit"))
      {

         GetTopLevelParent()->EndModalLoop("ok");

         return true;

      }
      else if (!strcmp(pszId, "escape"))
      {

         GetTopLevelParent()->EndModalLoop("cancel");

         return true;

      }

      return false;


   }



   void login::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      if(pcreate->previous())
         return;

      if(!m_labelUser.create(this,"label_user")
         || !m_editUser.create(this, "edit_user")
         || !m_labelPassword.create(this, "label_password")
         || !m_password.create(this, "password")
         || !m_tap.create(this, "submit"))
      {
         pcreate->set_lresult(-1);
         pcreate->m_bRet = true;
         return;
      }
      

      m_labelUser.SetWindowText("e-mail:");
      m_labelPassword.SetWindowText("password:");
      m_tap.SetWindowText("open");

      int stdw = 884;
      int stdh = 177 + 23 + 184 + 49;

      RepositionWindow(0,0,stdw,stdh);

      m_editUser.keyboard_set_focus();
      
   }


} // namespace fontopus




