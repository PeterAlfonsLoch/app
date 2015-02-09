#pragma once


namespace html
{


   class CLASS_DECL_HTML application_interface :
      virtual public ::html_lite::application_interface
   {
   public:


      application_interface();
      virtual ~application_interface();


      DECL_GEN_SIGNAL(on_application_signal);


   };


} // namespace html





