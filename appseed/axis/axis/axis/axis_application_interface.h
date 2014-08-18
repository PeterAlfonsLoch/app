#pragma once


namespace axis
{


   class CLASS_DECL_AXIS application_interface:
      virtual public ::thread,
      virtual public ::axis::live_object,
      virtual public command_target_interface,
      virtual public request_interface,
      virtual public int_scalar_source
   {
   public:


      ::axis::system *                                m_pbasesystem;
      ::axis::session *                               m_pbasesession;
      ::core::application *                           m_pcoreapp; // can be used only from core and upper
      ::core::system *                                m_pcoresystem; // can be used only from core and upper
      ::core::platform *                              m_pcoreplatform; // can be used only from core and upper


      application_interface();
      virtual ~application_interface();




   };


} // namespace axis
























