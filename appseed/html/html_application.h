#pragma once


namespace html
{


   class CLASS_DECL_HTML application :
      virtual public ::html_lite::application
   {
   public:


      application();
      virtual ~application();


      DECL_GEN_SIGNAL(on_application_signal);


   };


} // namespace html





