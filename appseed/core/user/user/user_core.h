#pragma once


namespace user
{


   class CLASS_DECL_CORE core :
      virtual public ::axis::departament
   {
   public:


      core(sp(::axis::application) papp);
      virtual ~core();


      virtual bool initialize();


   };

}