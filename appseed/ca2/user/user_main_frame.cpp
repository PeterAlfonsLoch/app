#include "framework.h"


namespace user
{


   main_frame::main_frame(sp(::application) papp) :
      element(papp),
      simple_frame_window(papp)
   {
      m_bPlacing = false;
   }

   main_frame::~main_frame()
   {
   }



#ifdef DEBUG
   void main_frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void main_frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }
#endif //DEBUG

   void main_frame::install_message_handling(::ca2::message::dispatch * pinterface)
   {
      simple_frame_window::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE,         pinterface, this, &main_frame::_001OnCreate);
   }

   void main_frame::_001OnCreate(signal_details * pobj)
   {

//      SCAST_PTR(::ca2::message::create, pcreate, pobj)
      
      m_bWindowFrame = !Application.directrix()->m_varTopicQuery["client_only"].is_set();

      if(pobj->previous())
         return;

      //if(!m_bPlacing)
      //{
      //   keeper < bool > keepPlacing(&m_bPlacing, true, false, true);
      //   Session.place(this);
      //}

   }


} // namespace user



