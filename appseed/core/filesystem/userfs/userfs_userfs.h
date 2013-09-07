#pragma once


namespace userfs
{


   class CLASS_DECL_ca2 userfs :
      virtual public ::base_departament
   {
   public:


      userfs(base_application * papp);
      virtual ~userfs();

      bool initialize();


   };



} // namespace userfs



