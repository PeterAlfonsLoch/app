#pragma once


namespace linux
{


   namespace axis
   {


      class CLASS_DECL_AXIS factory_exchange :
         virtual public ::object
      {
      public:

         factory_exchange(sp(::aura::application) papp);
         virtual ~factory_exchange();

      };


   } // namespace axis

} // namespace linux







