#pragma once


namespace fs
{


   class CLASS_DECL_ca2 fs :
      virtual public ::ca2::section
   {
   public:




      fs(::ca2::application * papp);
      virtual ~fs();

      bool initialize();


   };


} // namespace fs


