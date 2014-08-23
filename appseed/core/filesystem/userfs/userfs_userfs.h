#pragma once


namespace userfs
{


   class CLASS_DECL_CORE userfs :
      virtual public ::aura::departament
   {
   public:


      userfs(sp(::axis::application) papp);
      virtual ~userfs();

      bool initialize();


   };



} // namespace userfs



