//#include "framework.h"


namespace user
{


   tooltip::tooltip(::aura::application * papp):
      ::object(papp),
      m_font(allocer())
   {

      m_font->create_point_font(FONT_SANS_EX,12.0);

      m_bError = false;

   }

   tooltip::~tooltip()
   {
   }


#ifdef DEBUG


   void tooltip::assert_valid() const
   {
      ::user::interaction::assert_valid();
   }

   void tooltip::dump(dump_context & dumpcontext) const
   {
      ::user::interaction::dump(dumpcontext);
   }


#endif //DEBUG
   void tooltip::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::interaction::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&tooltip::_001OnCreate);
      //

   }


   void tooltip::_001OnCreate(signal_details * pobj)
   {

      pobj->previous();

      if(pobj->m_bRet)
         return;

   }



   void tooltip::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);


   }

   bool tooltip::get_translucency(::user::ETranslucency  & etranslucency)
   {

      etranslucency = ::user::TranslucencyPresent;

      return true;

   }


   void tooltip::_001OnDraw(::draw2d::graphics * pdc)
   {

      pdc->SelectClipRgn(NULL);

      rect rectClient;

      GetClientRect(rectClient);

      ::draw2d::path_sp path(allocer());

      path->add_move(rectClient.left, rectClient.bottom);

      ::rect rectBody;

      rectBody = rectClient;

      rectBody.left += 16;
      rectBody.bottom -= 16;

      path->add_line(rectBody.left, rectBody.top + rectBody.height()/2);
      path->add_line(rectBody.left,rectBody.top);
      path->add_line(rectBody.right,rectBody.top);
      path->add_line(rectBody.right,rectBody.bottom);
      path->add_line(rectBody.left + rectBody.height() / 2,rectBody.bottom);
      path->end_figure(true);

      ::draw2d::brush_sp b(allocer());

      b->create_solid(ARGB(184,255,255,123));

      pdc->SelectObject(b);

      pdc->fill_path(path);

      ::draw2d::pen_sp p(allocer());

      pdc->SelectObject(p);

      p->create_solid(1.0, ARGB(184,123,123,255));

      pdc->draw_path(path);

      pdc->set_text_color(ARGB(255,123,123,255));

      //::rect rect;

      //rectText.left = 0;

      //rectText.top = 0;

      //rectText.right = m_size.cx;

      //rectText.bottom = m_size.cy;

      pdc->SelectFont(m_font);

      rectBody.offset(4,0);

      pdc->draw_text(m_str,rectBody,DT_VCENTER);

   }

   size tooltip::CalcSize()
   {

      stringa stra;

      stra.add_lines(m_str);

      ::size size(0,0);

      ::size sizeLine;

      ::draw2d::graphics_sp g(allocer());

      g->CreateCompatibleDC(NULL);

      g->selectFont(m_font);

      for(auto strLine : stra)
      {

         sizeLine = g->GetTextExtent(strLine);

         size.cx = MAX(size.cx,sizeLine.cx);

         size.cy += sizeLine.cy;

      }

      size.cx += 16 + 16;
      size.cy += 16 + 16;


      m_size = size;

      return size;

   }


   ::user::interaction::e_type tooltip::get_window_type()
   {

      return type_frame;

   }


} // namespace veritile



