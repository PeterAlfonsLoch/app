#pragma once


namespace user
{


   class CLASS_DECL_CORE core :
      virtual public ::aura::departament
   {
   public:


      core(::aura::application * papp);
      virtual ~core();


      virtual bool initialize();


   };

}