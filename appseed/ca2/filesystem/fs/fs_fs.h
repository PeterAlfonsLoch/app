#pragma once


namespace fs
{


   class CLASS_DECL_ca2 fs :
      virtual public ::ca::section
   {
   public:




      fs(::ca::application * papp);
      virtual ~fs();

      bool initialize();


   };


} // namespace fs


