#include "framework.h"


CLASS_DECL_BASE void draw_ca2(::draw2d::graphics * pdc, int x, int y, int z, COLORREF crBk, COLORREF cr);
CLASS_DECL_BASE void draw_ca2_with_border(::draw2d::graphics * pdc, int x, int y, int z, int b, COLORREF crBk, COLORREF cr, COLORREF crOut);
CLASS_DECL_BASE void draw_ca2_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crBorderOut, COLORREF crIn);
CLASS_DECL_BASE void draw_ca2_with_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crBorderOut, COLORREF crIn);


namespace fontopus
{


   simple_ui::simple_ui(sp(::base::application) papp) :
      element(papp),
      ::simple_ui::style(papp),
      m_login(papp, 0, 0)
   {

      m_eschema = schema_normal;
      m_login.m_pstyle = this;
      m_bLButtonDown = false;
      m_bFontopusSimpleUiLayout = false;
   }


   simple_ui::~simple_ui()
   {

   }

   void simple_ui::install_message_handling(::message::dispatch * pdispatch)
   {

      ::simple_ui::interaction::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&simple_ui::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CHAR,pdispatch,this,&simple_ui::_001OnChar);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,pdispatch,this,&simple_ui::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,pdispatch,this,&simple_ui::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,pdispatch,this,&simple_ui::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOVE,pdispatch,this,&simple_ui::_001OnMove);
      IGUI_WIN_MSG_LINK(WM_SIZE,pdispatch,this,&simple_ui::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_TIMER,pdispatch,this,&simple_ui::_001OnTimer);

   }

   
   void simple_ui::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      if(pcreate->previous())
         return;

      if(!m_login.create(this,"pane_first"))
      {

         pcreate->set_lresult(-1);

         pcreate->m_bRet = true;

         return;

      }

   }


   void simple_ui::_001OnChar(signal_details * pobj)
   {

      SCAST_PTR(::message::key, pkey, pobj)

      if(pkey->m_ekey == ::user::key_return)
      {

         m_login.on_action("submit");

         pobj->m_bRet = true;

      }

   }


   //void simple_ui::GetWindowRect(LPRECT lprect)
   //{

   //   *lprect = m_rect;

   //}


   void simple_ui::_001OnTimer(::signal_details * pobj)
   {

      SCAST_PTR(::message::timer,ptimer,pobj);

      if(ptimer->m_nIDEvent == 1984)
      {

         try
         {

            string strUsername;
            string strPassword;

            ::fontopus::get_cred(get_app(),strUsername,strPassword,"ca2");

            if(strUsername.has_char() && strPassword.has_char())
            {
               KillTimer(1984);

               m_login.on_action("submit");



            }

         }
         catch(...)
         {

         }

      }

   }



   string simple_ui::do_fontopus(LPCRECT lprect)
   {

      ::user::interaction * puiParent = session().oprop("plugin_parent").cast < ::user::interaction >();

      if(!CreateEx(0, NULL, NULL, 0, null_rect(), puiParent, "fontopus"))
         return "";

      ::rect rectDesktop;

      if(puiParent != NULL)
      {

         puiParent->GetWindowRect(rectDesktop);

      }
      else if (lprect == NULL)
      {

         session().get_main_monitor(rectDesktop);

      }
      else
      {

         rectDesktop = *lprect;

      }

      SetWindowText( "fontopus Auth Windows");

      m_login.m_editUser.SetFocus();

      rect rectFontopus;

      rect rectLogin;

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

      if(puiParent != NULL)
         puiParent->ScreenToClient(rectFontopus);


      m_login.defer_translate(this);


      m_login.layout();

      SetWindowPos(ZORDER_TOP, rectFontopus, SWP_SHOWWINDOW);

      m_login.ShowWindow(SW_NORMAL);
      
      SetForegroundWindow();

      ShowWindow(SW_NORMAL);

      BringWindowToTop();

      SetTimer(1984,284,NULL);

      id idResult = RunModalLoop();

      return idResult;

   }


   string simple_ui::get_cred(LPCRECT lprect, string & strUsername, string & strPassword, string strToken, string strTitle)
   {

      if(strTitle == "ca2")
      {

         m_login.m_bCred = false;

         m_login.m_strCred = "";

      }
      else
      {

         m_login.m_bCred = true;

         m_login.m_strCred = strTitle;

      }

      id idResult = do_fontopus(lprect);

      if(idResult == "ok")
      {

         m_login.m_editUser.GetWindowText(strUsername);

         m_login.m_password.GetWindowText(strPassword);

         return "ok";

      }
      else
      {

         return "fail";

      }

   }


   void simple_ui::layout()
   {

      if(!m_bFontopusSimpleUiLayout)
      {

         keep < bool > keepLayout(&m_bFontopusSimpleUiLayout,true,false,true);

         rect rectClient1;

         GetClientRect(rectClient1);

         bool bParentChange = false;

         if(GetParent() != NULL)
         {

            ::rect rectParent;

            GetParent()->GetWindowRect(rectParent);

            if(rectParent != m_rectParent)
            {

               bParentChange = true;

            }

         }


         if(rectClient1.area() < 100 * 100 || bParentChange)
         {

            ::rect rectDesktop;

            if(GetParent() != NULL)
            {

               GetParent()->GetWindowRect(rectDesktop);

            }
            else
            {

               session().get_main_monitor(rectDesktop);

            }

            rect rectFontopus;

            rect rectLogin;

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


            if(GetParent() != NULL)
               GetParent()->ScreenToClient(rectFontopus);


            SetWindowPos(ZORDER_TOP,rectFontopus,SWP_SHOWWINDOW);

         }

      }


      rect rectClient;

      GetClientRect(rectClient);

      m_login.SetPlacement(rectClient);

      m_login.layout();

   }


   void simple_ui::_001OnLButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if (pobj->previous())
         return;
      
      GetWindow()->show_keyboard(false);

      m_bLButtonDown = true;
      m_bDrag = false;

      m_ptLButtonDownPos = pmouse->m_pt;
      ::GetCursorPos(&m_ptLButtonDown);
      SetCapture();

      pmouse->m_bRet = true;

   }


   void simple_ui::_001OnLButtonUp(signal_details * pobj)
   {

      m_bLButtonDown = false;

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if(pmouse->previous())
         return;

      ReleaseCapture();

      m_bDrag = false;

      pobj->m_bRet = true;

   }


   void simple_ui::_001OnMouseMove(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if (m_bLButtonDown)
      {
         if (!m_bDrag)
         {
            m_bDrag = true;
            POINT ptNow = pmouse->m_pt;
            point pt;
            pt.x = ptNow.x - m_ptLButtonDown.x + m_ptLButtonDownPos.x;
            pt.y = ptNow.y - m_ptLButtonDown.y + m_ptLButtonDownPos.y;
            MoveWindow(pt);
            m_bDrag = false;
         }
         pobj->m_bRet = true;

      }
      else
      {
         if(pobj->previous())
            return;

         pobj->m_bRet = true;
      }

   }



   string CLASS_DECL_BASE get_cred(::base::application * papp, LPCRECT lprect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive)
   {

      ::fontopus::simple_ui ui(papp);

      string str = get_cred(papp, strUsername, strPassword, strToken);

      if (str == "ok")
         return "ok";

      if(!bInteractive)
         return "failed";

      ui.m_login.m_editUser.SetWindowText(strUsername);

      ui.m_login.m_password.SetWindowText(strPassword);

      string strResult = ui.get_cred(lprect, strUsername, strPassword, strToken, strTitle);

      ui.DestroyWindow();

      return strResult;

   }

   string CLASS_DECL_BASE get_cred(::base::application * papp, string & strUsername, string & strPassword, string strToken)
   {

      string str;
      crypto_file_get(::dir::userappdata("cred/" + strToken + "_a.data"), strUsername, "");
      crypto_file_get(::dir::userappdata("cred/" + strToken + "_b.data"), strPassword, strToken);
      crypto_file_get(::dir::userappdata("cred/" + strToken + "_c.data"), str, strToken);

      return str;

   }

   void set_cred(::base::application * papp, string strToken, const char * pszUsername, const char * pszPassword)
   {

      string strUsername(pszUsername);
      string strPassword(pszPassword);
      string strUsernamePrevious;
      string strPasswordPrevious;

      get_cred(papp, strUsernamePrevious, strPasswordPrevious, strToken);

      if ((strUsername.has_char() && strPassword.has_char())
         && (strUsernamePrevious != strUsername || strPasswordPrevious != strPassword))
      {
         dir::mk(::dir::userappdata("cred"));
         crypto_file_set(::dir::userappdata("cred/" + strToken + "_a.data"), strUsername, "");
         crypto_file_set(::dir::userappdata("cred/" + strToken + "_b.data"), strPassword, strToken);
      }

   }


   void set_cred_ok(::base::application * papp,string strToken,bool bOk)
   {

      if(bOk)
      {

         crypto_file_set(::dir::userappdata("cred/" + strToken + "_c.data"),"ok",strToken);

      }
      else
      {
         crypto_file_set(::dir::userappdata("cred/" + strToken + "_c.data"),"failed",strToken);

      }

   }


} // namespace fontopus


CLASS_DECL_BASE void draw_ca2_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crOut, COLORREF crIn)
{


   rect r(x + bIn + bOut, y + bIn + bOut, x + bIn + bOut + z, y + bIn + bOut + z);

   ::draw2d::pen_sp p(pdc->allocer());

   p->create_solid(1.0, crIn);

   for (int i = 0; i < bIn; i++)
   {

      r.inflate(1, 1);

      pdc->DrawRect(r, p);

   }

   p->create_solid(1.0, crOut);

   for (int i = 0; i < bOut; i++)
   {

      r.inflate(1, 1);

      pdc->DrawRect(r, p);

   }


}

CLASS_DECL_BASE void draw_ca2_with_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crOut, COLORREF crIn)
{

   draw_ca2(pdc, x + bIn + bOut, y + bIn + bOut, z, crBk, cr);

   draw_ca2_border2(pdc, x, y, z, bOut, bIn, crBk, cr, crOut, crIn);

}


CLASS_DECL_BASE void draw_ca2_with_border(::draw2d::graphics * pdc, int x, int y, int z, int b, COLORREF crBk, COLORREF cr, COLORREF crBorder)
{

   draw_ca2(pdc, x + b, y + b, z, crBk, cr);

   int w = z / 19;

   if (w < 1)
      w = 1;

   z = w * 19;

   rect r(x + b, y + b, x + b + z, y + b + z);

   ::draw2d::pen_sp p(pdc->allocer());

   p->create_solid(1.0, crBorder);

   for(int i = 0; i < b; i++)
   {

      r.inflate(1, 1);

      pdc->DrawRect(r, p);

   }



}


CLASS_DECL_BASE void draw_ca2(::draw2d::graphics * pdc, int x, int y, int z, COLORREF crBk, COLORREF cr)
{

   ::draw2d::brush_sp b(pdc->allocer());

   // black rectangle

   int w = z / 19;

   if (w < 1)
      w = 1;

   z = w * 19;

   b->create_solid(crBk);

   rect r(x, y, x + z, y + z);

   pdc->FillRect(r, b);








   // bottom line

   b->create_solid(cr);

   r.top += w * 13;
   r.bottom -= w;









   // c

   r.left += w;
   r.right = r.left + w * 5;

   rect c = r;

   // c vertical

   c.right = c.left + w;

   pdc->FillRect(c, b);

   c = r;

   c.bottom = c.top + w;

   pdc->FillRect(c, b);

   c = r;

   c.top = c.bottom - w;

   pdc->FillRect(c, b);








   // a

   r.left += w * 6;
   r.right = r.left + w * 5;

   c = r;

   c.bottom = c.top + w;

   pdc->FillRect(c, b);

   c = r;

   c.top = c.bottom - w;

   pdc->FillRect(c, b);

   c = r;

   c.right = c.left + w * 2;
   c.top += w * 2;
   c.bottom = c.top + w;

   pdc->FillRect(c, b);

   c = r;

   c.left += w * 5 / 2;
   c.right = c.left + w;
   c.top += w * 2;
   c.bottom = c.top + w;

   pdc->FillRect(c, b);

   c = r;

   c.left = c.right - w;

   pdc->FillRect(c, b);

   c = r;

   c.right = c.left + w;
   c.top += w * 2;

   pdc->FillRect(c, b);





   // 2

   r.left += w * 6;
   r.right = r.left + w * 5;

   c = r;

   c.bottom = c.top + w;

   pdc->FillRect(c, b);

   c = r;

   c.top = c.bottom - w;

   pdc->FillRect(c, b);

   c = r;

   c.top += w * 2;
   c.bottom = c.top + w;

   pdc->FillRect(c, b);

   c = r;

   c.right = c.left + w;
   c.top += w * 2;

   pdc->FillRect(c, b);

   c = r;

   c.left = c.right - w;
   c.bottom -= w * 2;

   pdc->FillRect(c, b);

}

