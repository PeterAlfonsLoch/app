#include "framework.h"


namespace user
{


   control_event::control_event()
   {
      
      // Set default return for system event to true for some events because they should end processing of system originated events by default,
      // so the system originated event (like WM_LBUTTONDOWN) is not propagated to the ascendants for
      // the translated control event (like ::user::event_button_down) unless
      // a custom processing of the event returns differently and deem the event processed.
      // This allows to use many controls and process their message shallowly (by default) for certain expected behaviour,
      // without the need of any other extra code.

      m_bRet         = true;

      m_bProcessed   = false;

      m_pobj         = NULL;

   }


   control_event::~control_event()
   {

   }


} // namespace user




