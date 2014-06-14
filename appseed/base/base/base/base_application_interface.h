#pragma once


namespace base
{


   class CLASS_DECL_BASE application_interface:
      virtual public ::object
   {
   public:


      application_interface();
      virtual ~application_interface();


      ::base::system *                                m_pbasesystem;
      ::base::session *                               m_pbasesession;
      ::application *                                 m_pplaneapp; // can be used only from core and upper


   };


} // namespace base
























