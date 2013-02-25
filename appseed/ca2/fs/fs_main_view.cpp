#include "framework.h"


namespace fs
{


   main_view::main_view(::ca::application * papp) :
      ca(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      place_holder_container(papp)
   {
   }

   void main_view::install_message_handling(::ca::message::dispatch * pinterface)
   {
      ::userbase::split_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &main_view::_001OnCreate);
   }

   void main_view::_001OnCreate(::ca::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;

//      application * papp = dynamic_cast < application * > (get_app());
      //papp->m_pmainview = this;
      SetPaneCount(2);
      SetSplitOrientation(orientation_vertical);
      set_position_rate(0, 0.2);
      ::ca::create_context_sp cc(get_app());

//      cc->m_usercreatecontext.m_pCurrentDoc = get_document();
  //    cc->m_usercreatecontext.m_typeinfoNewView = System.type_info < tree > ();
      ::user::interaction* pwnd = create_view(System.type_info < tree > (), get_document(), this, 100);
      SetPane(0, pwnd, false);
//      tree * ptree = dynamic_cast < tree * > (pwnd);


//      cc->m_usercreatecontext.m_pCurrentDoc = get_document();
  //    cc->m_usercreatecontext.m_typeinfoNewView = System.type_info < list > ();
      pwnd = create_view(System.type_info < list > (), get_document(), this, 101);
//      list * plist = dynamic_cast < list * > (pwnd);
      SetPane(1, pwnd, false);
      layout();
      SetTimer(123, 1000, NULL);


   }

   void main_view::_001OnTimer(::ca::signal_object * pobj)
   {

      SCAST_PTR(::ca::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == 123)
      {
//         Application.TimerStep();
      }

   }

   document * main_view::get_document()
   {
      return dynamic_cast < document * > (::userbase::split_view::get_document());
   }


} // namespace fs


