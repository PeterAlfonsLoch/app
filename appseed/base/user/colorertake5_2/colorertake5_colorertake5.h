#pragma once


namespace colorertake5
{


   class CLASS_DECL_BASE colorertake5 :
      virtual public ::axis::departament
   {
   public:


      colorertake5(::axis::application * papp);
      virtual ~colorertake5();


      virtual bool initialize();


   };


} // namespace colorertake5



