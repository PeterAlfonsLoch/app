#pragma once


namespace aura
{


   class CLASS_DECL_AURA session_interface:
      virtual public ::aura::application_interface
   {
   public:


      ::aura::platform_interface *     m_pplatformcomposite;


      session_interface();
      virtual ~session_interface();





   };


} // namespace aura
















