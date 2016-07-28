#include "framework.h" // from ""axis/user/user.h"
#include "linux.h"



class keep_event_reset
{
public:


   event * m_pevent;


   keep_event_reset(event * pevent)
   {
      m_pevent = pevent;
      pevent->ResetEvent();
   }
   ~keep_event_reset()
   {
      m_pevent->SetEvent();
   }


};


namespace linux
{


   window_draw::window_draw(::aura::application *  papp) :
      ::object(papp),
      ::thread(papp),
      ::user::window_draw(papp)
   {

   }


   window_draw::~window_draw()
   {

   }


} // namespace linux




