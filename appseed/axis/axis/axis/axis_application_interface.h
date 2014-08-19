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


      ::axis::system *                                m_paxissystem;
      ::axis::session *                               m_paxissession;
      ::base::application *                           m_pbasesapp; // can be used only from base and upper
      ::base::system *                                m_pbasesystem; // can be used only from base and upper
      ::base::session *                               m_pbasesession; // can be used only from base and upper
      ::core::application *                           m_pcoreapp; // can be used only from core and upper
      ::core::system *                                m_pcoresystem; // can be used only from core and upper
      ::core::platform *                              m_pcoreplatform; // can be used only from core and upper


      application_interface();
      virtual ~application_interface();




   };


} // namespace axis
























