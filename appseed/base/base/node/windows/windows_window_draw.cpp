//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"
//#include "windows.h"

#define DISABLE_UPDATE_BUFFER 0

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

extern bool g_bSuppressTwf;


namespace windows
{

   window_draw::window_draw(::aura::application * papp):
      ::object(papp),
      thread(papp),
      ::user::window_draw(papp)
   {

   }


   window_draw::~window_draw()
   {

   }



} // namespace windows








