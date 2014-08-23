#pragma once


namespace colorertake5
{


   class CLASS_DECL_AURA colorertake5 :
      virtual public ::aura::departament
   {
   public:


      colorertake5(::aura::application * papp);
      virtual ~colorertake5();


      virtual bool initialize();


   };


} // namespace colorertake5



