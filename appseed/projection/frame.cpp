#include "StdAfx.h"
#include <math.h>
#include "window_frame/FrameSchemaHardCoded002.h"
#include "window_frame/FrameSchemaHardCoded005.h"

namespace projection
{

   frame::frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp)
   {
      m_dataid = "ca2::projection::frame";

      WfiEnableFullScreen();

      m_etranslucency = TranslucencyTotal;

      m_bCustomFrame = !Application.command().m_varTopicQuery["client_only"].is_set();
   }

   frame::~frame()
   {
   }

#ifdef _DEBUG
   void frame::assert_valid() const
   {
	   simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
	   simple_frame_window::dump(dumpcontext);
   }
#endif //_DEBUG



   window_frame::FrameSchema * frame::create_frame_schema()
   {
      window_frame::FrameSchemaHardCoded005 * pschema = new window_frame::FrameSchemaHardCoded005(get_app());
      pschema->m_typeinfoControlBoxButton = ::ca::get_type_info < MetaButton > ();
      pschema->SetStyle(window_frame::FrameSchemaHardCoded005::StyleTranslucidWarmGray);
      return pschema;
   }

} // namespace projection
