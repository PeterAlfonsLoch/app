#pragma once


namespace user
{


   class CLASS_DECL_CORE core :
      virtual public ::base_departament
   {
   public:


      core(sp(::base::application) papp);
      virtual ~core();


      virtual bool initialize();


   };

}