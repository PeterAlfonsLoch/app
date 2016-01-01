#include "framework.h"
#include <math.h>


namespace user
{


   font_list::font_list()
   {
      font_list_common_construct();

   }


   font_list::font_list(::aura::application * papp):
      object(papp),
      ::user::interaction(papp)
    {

       font_list_common_construct();

   }


   void font_list::font_list_common_construct()
   {

      m_rectMargin = rect(5,5,5,5);
      m_iSel                     = -1;

   }


   font_list::~font_list()
   {

   }


   void font_list::install_message_handling(::message::dispatch * pdispatch)
   {

      ::database::user::interaction::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&font_list::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,pdispatch,this,&font_list::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,pdispatch,this,&font_list::_001OnMouseMove);

   }


   void font_list::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      data_get("sel", m_iSel);

      //update();


   }

   void font_list::_001OnLButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      index iSel = hit_test(pt);

      if(iSel != m_iSel)
      {

         m_iSel = iSel;
         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::event_after_change_cur_sel;
         ev.m_actioncontext = ::action::source_user;

         BaseOnControlEvent(&ev);


         data_set("sel",m_iSel);



      }

   }

   void font_list::_001OnMouseMove(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      m_iHover = hit_test(pt);


   }


   void font_list::on_update(::user::impact * pSender,LPARAM lHint,object* phint)
   {

      if(lHint == 0)
      {

      }
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }


   void font_list::_001OnDraw(::draw2d::graphics * pdc)
   {


      rect rectClient;

      GetClientRect(rectClient);

      pdc->FillSolidRect(rectClient,ARGB(123,255,255,255));

      if(m_strText != m_strTextLayout)
      {

         m_strTextLayout = m_strText;

         layout();

      }


      string strText = m_strTextLayout;

      for(int i = 0; i < m_fonta.get_count(); i++)
      {

         if(m_strText.is_empty())
         {

            strText = m_straName[i];

         }
         rect & r = m_recta[i];

         if(i == m_iSel)
         {
            pdc->FillSolidRect(r,ARGB(184,84,84,84));

            if(i == m_iHover)
            {

               pdc->set_text_color(ARGB(255,223,255,223));

            }
            else
            {

               pdc->set_text_color(ARGB(255,223,223,223));

            }

         }
         else if(i == m_iHover)
         {
            pdc->FillSolidRect(r,ARGB(255,0,0,0));
            pdc->set_text_color(ARGB(255,255,255,255));
         }
         else
         {
            pdc->set_text_color(ARGB(255,84,84,84));
         }


         pdc->SelectFont(m_fonta[i]);

         pdc->TextOut(r.left + m_rectMargin.left,r.top + m_rectMargin.top,strText);



      }




   }




   void font_list::layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.area() <= 0)
         return;

      update();

   }

#ifdef WINDOWSEX

   BOOL CALLBACK EnumFamCallBack(LPLOGFONT lplf,LPNEWTEXTMETRIC lpntm,DWORD FontType,LPVOID p);

#endif

   void font_list::update()
   {

      single_lock sl(m_pmutex);

      sl.lock();

      m_fonta.remove_all();
      m_straFontEnum.remove_all();
      m_straNameEnum.remove_all();

      sl.unlock();

      ::draw2d::font_sp f;

      rect rectClient;

      GetClientRect(rectClient);

      ::draw2d::graphics_sp g(allocer());

      g->CreateCompatibleDC(NULL);

      g->enum_fonts(m_straFontEnum, m_straNameEnum);

      ::draw2d::graphics * pdc = g;

      string strText = m_strTextLayout;

      size s;

      rect r;

      int x = 0;

      int y = 0;

      int h = 0;

      sl.lock();
      m_straFont.remove_all();
      m_straName.remove_all();
      m_fonta.remove_all();
      m_recta.remove_all();

      for(int i = 0; i < m_straFontEnum.get_count(); i++)
      {
         f.alloc(allocer());
         m_straFont.set_at_grow(i, m_straFontEnum[i]);
         m_straName.set_at_grow(i, m_straNameEnum[i]);
         f->create_pixel_font(m_straFont[i],18);
         m_fonta.set_at_grow(i, f);
         if(m_strTextLayout.is_empty())
         {

            strText = m_straName[i];

         }

         pdc->SelectFont(m_fonta[i]);

         s = pdc->GetTextExtent(strText);

         s.cx += m_rectMargin.left + m_rectMargin.right;
         s.cy += m_rectMargin.top + m_rectMargin.bottom;

         x+= s.cx / 2;

         if(x >= rectClient.width())
         {
            x = 0;
            y += h;
            h = 0;
         }

         //pdc->TextOut(x + m_rectMargin.left,y + m_rectMargin.top,strText);

         r.left = x ;
         r.top = y ;
         r.right = r.left + s.cx;
         r.bottom = r.top + s.cy;

         x+= s.cx / 2 + 2;

         h = MAX(h,s.cy);

         m_recta.set_at_grow(i,r);

         sl.unlock();
         sl.lock();
      }



   }


   string      font_list::get_cur_sel_face_name()
   {

      int iSel = get_cur_sel();

      if(iSel < 0)
         return "";


      return m_straFont[iSel];


   }

   int         font_list::get_cur_sel()
   {
      if(m_iSel < 0)
         return -1;
      if(m_iSel >= m_straFont.get_count())
         return -1;
      return m_iSel;
   }

   int font_list::hit_test(point pt)
   {

      return m_recta.pred_find_first([=](auto & r) {return r.contains(pt);});

   }

   bool font_list::set_sel_by_name(string str)
   {

      int iSel =  m_straFont.find_first_ci(str);

      if(iSel < 0)
         return false;


      m_iSel = iSel;

      return true;



   }
} // namespace user

















