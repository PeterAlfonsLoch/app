#pragma once


namespace userfs
{


   class CLASS_DECL_ca2 userfs :
      virtual public ::ca::section
   {
   public:


      userfs(::ca::application * papp);
      virtual ~userfs();

      bool initialize();


   };



} // namespace userfs



