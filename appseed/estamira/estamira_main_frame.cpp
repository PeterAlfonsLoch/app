#include "framework.h"


namespace estamira
{


   main_frame::main_frame(::aura::application * papp) :
      ::object(papp),
      simple_frame_window(papp)
   {

      //      m_dataid = "::core::tictactoe::main_frame";

      WfiEnableFullScreen();

      m_bWindowFrame = !Application.command()->m_varTopicQuery.has_property("client_only");

   }


   main_frame::~main_frame()
   {

   }


   void main_frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void main_frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }




   sp(::user::wndfrm::frame::frame) main_frame::create_frame_schema()
   {

      sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm().get_frame_schema(NULL, "001");
      pschema->set_style("StyleLightBlue");
      //pschema->m_typeinfoControlBoxButton = System.type_info < MetaButton > ();
      return pschema;

      /*      main_frame::FrameSchemaHardCoded005 * pschema = new main_frame::FrameSchemaHardCoded005(get_app());
      pschema->m_typeinfoControlBoxButton = System.type_info < MetaButton > ();
      pschema->SetStyle(main_frame::FrameSchemaHardCoded005::StyleTranslucidWarmGray);
      return pschema;*/
   }


   bool main_frame::get_translucency(::user::ETranslucency & etranslucency)
   {

      etranslucency = ::user::TranslucencyPresent;

      return true;


   }

   bool main_frame::on_create_bars()
   {

      return true;

   }


   bool main_frame::has_pending_graphical_update()
   {

      return IsWindowVisible();

   }

} // namespace estamira





