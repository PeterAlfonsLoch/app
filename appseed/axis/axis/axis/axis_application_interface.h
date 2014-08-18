#pragma once


namespace base
{


   class CLASS_DECL_BASE application_interface:
      virtual public ::thread,
      virtual public ::base::live_object,
      virtual public command_target_interface,
      virtual public request_interface,
      virtual public int_scalar_source
   {
   public:


      ::base::system *                                m_pbasesystem;
      ::base::session *                               m_pbasesession;
      ::core::application *                           m_pcoreapp; // can be used only from core and upper
      ::core::system *                                m_pcoresystem; // can be used only from core and upper
      ::core::platform *                              m_pcoreplatform; // can be used only from core and upper


      application_interface();
      virtual ~application_interface();




   };


} // namespace base
























