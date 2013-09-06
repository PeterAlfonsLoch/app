#pragma once


namespace userfs
{


   class CLASS_DECL_ca2 userfs :
      virtual public ::departament
   {
   public:


      userfs(application * papp);
      virtual ~userfs();

      bool initialize();


   };



} // namespace userfs



