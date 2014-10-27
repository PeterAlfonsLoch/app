#pragma once


namespace aura
{


   class CLASS_DECL_AURA platform_interface:
      virtual public ::aura::application_interface
   {
   public:


      platform_interface();
      virtual ~platform_interface();


      virtual ::visual::cursor * get_cursor();

      virtual ::visual::cursor * get_default_cursor();

      virtual sp(::aura::application) start_application(const char * pszType,const char * pszAppId,sp(::create_context) pcreatecontext);


   };


} // namespace aura
















