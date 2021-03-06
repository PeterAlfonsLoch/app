﻿//#include "framework.h"


namespace calculator
{


   view::view(::aura::application * papp) :
      ::object(papp),
      ::user::interaction(papp)
   {

   }


   view::~view()
   {

   }


   void view::install_message_handling(::message::dispatch * pinterface)
   {

      ::user::impact::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);

      //   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &view::_001OnTabClick);
      IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &view::_001OnWavePlayerEvent);
      //connect_command(ID_FILE_PRINT, ::user::impact::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, ::user::impact::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, ::user::impact::OnFilePrintPreview)
      //  IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
      //   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);


   }

#ifdef DEBUG
   void view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // view message handlers

   // vmpLightView.cpp : implementation of the view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // view


   bool view::pre_create_window(::user::create_struct& cs)
   {

      cs.style &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);

   }


   void view::_001OnInitialUpdate()
   {
      ::user::impact::_001OnInitialUpdate();


   }

   void view::on_update(::user::impact * pSender, LPARAM lHint, ::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }

   sp(::user::interaction) view::BackViewGetWnd()
   {
      return this;
   }
   void view::_001OnDestroy(signal_details * pobj)
   {
      ::user::impact::_001OnDestroy(pobj);

   }



   void view::_001OnSize(signal_details * pobj)
   {
      
      UNREFERENCED_PARAMETER(pobj);

   }

   void view::_001OnPaint(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void view:: _001OnDraw(::draw2d::graphics * pgraphics)
   {
      
      UNREFERENCED_PARAMETER(pgraphics);

   }


   void view::_001OnCreate(signal_details * pobj)
   {
      if(pobj->previous())
         return;


   }
   void view::_001OnContextMenu(signal_details * pobj)
   {
//      SCAST_PTR(::message::context_menu, pcontextmenu, pobj);
//         point point = pcontextmenu->GetPoint();

   }


   void view::_001OnTabClick(int32_t iTab)
   {
      if(iTab == 1)
      {
         System.simple_message_box(NULL, "Playlist");
      }
   }

   void view::_001OnWavePlayerEvent(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::message::base, pbase, pobj);
   }

   void view::_001OnUpdateViewEncoding(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::message::update_cmd_ui, pupdatecmdui, pobj);
   }
   void view::_001OnViewEncoding(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::message::command, pcommand, pobj);
   }



   void view::_001OnSetCursor(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pmouse->m_ecursor = ::visual::cursor_arrow;

   }


   ::user::document * view::get_document()
   {

      return  (::user::impact::get_document());

   }


} // namespace calculator








