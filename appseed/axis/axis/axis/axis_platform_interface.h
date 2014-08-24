#pragma once


namespace axis
{


   class CLASS_DECL_AURA platform_interface:
      virtual public ::aura::application_interface
   {
   public:


      platform_interface();
      virtual ~platform_interface();


      virtual ::visual::cursor * get_cursor();

      virtual ::visual::cursor * get_default_cursor();


   };


} // namespace axis
















