#pragma once


namespace sockets
{


   class CLASS_DECL_ca application :
      virtual public ::colorertake5::application
#ifdef BSD_STYLE_SOCKETS
      , virtual public ::ca::interface_application < ::bsd::sockets::application_interface >
#endif
   {
   public:


   };


} // namespace sockets



