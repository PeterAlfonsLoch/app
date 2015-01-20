#include "framework.h"
#include <math.h>


namespace turboc
{


   frame::frame(::aura::application * papp) :
      element(papp),
      simple_frame_window(papp)
   {

      m_dataid = "::core::turboc::frame";

      WfiEnableFullScreen();

      m_bWindowFrame = !Application.command()->m_varTopicQuery["client_only"].is_set();

   }


   frame::~frame()
   {

   }


   void frame::assert_valid() const
   {

	   simple_frame_window::assert_valid();

   }


   void frame::dump(dump_context & dumpcontext) const
   {

	   simple_frame_window::dump(dumpcontext);

   }


   sp(::user::wndfrm::frame::frame) frame::create_frame_schema()
   {

      //sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm().get_frame_schema("wndfrm_core", "001");

      sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm().get_frame_schema("wndfrm_core","013");

      pschema->set_style("LightBlue");

      pschema->m_typeinfoControlBoxButton = System.type_info < MetaButton > ();

      return pschema;

   }


   bool frame::get_translucency(::user::ETranslucency & etranslucency)
   {

      etranslucency = ::user::TranslucencyPresent;

      return true;

   }


} // namespace turboc







