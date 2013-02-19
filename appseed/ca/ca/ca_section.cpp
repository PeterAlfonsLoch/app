#include "framework.h"


namespace ca
{


   section::section()
   {
   }

   section::~section()
   {
   }

   // designed to be in constructors, so should
   // not contain advanced initialization as the
   // papp application pointer may be incompletely
   // initialized specially its virtual functions.
   void section::construct(::ca::application * papp)
   {

      set_app(papp);

   }


   bool section::initialize()
   {

      return true;

   }


   bool section::initialize1()
   {

      return true;

   }


   bool section::initialize2()
   {

      return true;

   }


   bool section::initialize3()
   {

      return true;

   }


   bool section::initialize_instance()
   {

      return true;

   }


   bool section::finalize()
   {

      return true;

   }


   int32_t section::exit_instance()
   {

      return 0;

   }


} // namespace ca




