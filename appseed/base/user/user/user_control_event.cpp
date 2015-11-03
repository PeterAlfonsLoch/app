//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


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

      m_bOk          = true;

      m_pobj         = NULL;

      m_puie         = NULL;

      m_ptab         = NULL;

   }


   control_event::~control_event()
   {

   }


   impact * control_event::get_view()
   {

      return dynamic_cast <::user::impact *> (m_puie);

   }

   document * control_event::get_document()
   {

      impact * pimpact = get_view();

      if(pimpact == NULL)
         return NULL;

      return pimpact->get_document();

   }

   impact_system * control_event::get_impact_system()
   {

      document * pdocument = get_document();

      if(pdocument == NULL)
         return NULL;

      return pdocument->get_document_template();

   }

   string control_event::get_impact_matter()
   {

      impact_system * psystem = get_impact_system();

      if(psystem == NULL)
         return "";

      return psystem->m_strMatter;

   }

} // namespace user




