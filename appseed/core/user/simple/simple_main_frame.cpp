//#include "framework.h"


simple_main_frame::simple_main_frame(::aura::application * papp) :
   object(papp),
   simple_frame_window(papp)
{

   m_bAutoWindowFrame   = false;
   m_bWindowFrame       = true;
   m_bPlacing           = false;

}

simple_main_frame::~simple_main_frame()
{
}

#ifdef DEBUG
void simple_main_frame::assert_valid() const
{
   simple_frame_window::assert_valid();
}

void simple_main_frame::dump(dump_context & dumpcontext) const
{
   simple_frame_window::dump(dumpcontext);
}
#endif //DEBUG

void simple_main_frame::install_message_handling(::message::dispatch * pinterface)
{
   simple_frame_window::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&simple_main_frame::_001OnCreate);
}

void simple_main_frame::_001OnCreate(signal_details * pobj)
{

   //      SCAST_PTR(::message::create, pcreate, pobj);

   m_bWindowFrame = !Application.directrix()->m_varTopicQuery.has_property("client_only");

   if(pobj->previous())
      return;

   //if(!m_bPlacing)
   //{
   //   keep < bool > keepPlacing(&m_bPlacing, true, false, true);
   //   Session.place(this);
   //}

}
