#pragma once


namespace linux
{


   namespace aura
   {


      class CLASS_DECL_AURA factory_exchange :
         virtual public ::object
      {
      public:


         factory_exchange(sp(::aura::application) papp);
         virtual ~factory_exchange();


      };


   } // namespace aura


} // namespace linux

