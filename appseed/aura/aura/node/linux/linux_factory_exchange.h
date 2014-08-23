#pragma once


namespace linux
{

   class CLASS_DECL_LINUX factory_exchange :
      virtual public ::object
   {
   public:
      factory_exchange(sp(::aura::application) papp);
      virtual ~factory_exchange();
   };


} // namespace linux

