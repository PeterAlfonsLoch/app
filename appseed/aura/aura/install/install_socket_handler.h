#pragma once


namespace install
{


   class CLASS_DECL_AURA socket_handler :
      virtual public ::netserver::socket_handler
   {
   public:

      
      socket_handler(::aura::application * papp);


   };


} // namespace install



