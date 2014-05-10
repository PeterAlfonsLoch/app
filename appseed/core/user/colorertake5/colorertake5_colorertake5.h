#pragma once


namespace colorertake5
{


   class CLASS_DECL_CORE colorertake5 :
      virtual public ::base_departament
   {
   public:


      colorertake5(::base::application * papp);
      virtual ~colorertake5();


      virtual bool initialize();


   };


} // namespace colorertake5



