#pragma once


namespace userfs
{


   class CLASS_DECL_CORE userfs :
      virtual public ::base_departament
   {
   public:


      userfs(::base::application * papp);
      virtual ~userfs();

      bool initialize();


   };



} // namespace userfs



