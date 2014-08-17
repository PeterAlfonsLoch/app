#pragma once


namespace fs
{


   class CLASS_DECL_BASE fs :
      virtual public ::base::departament
   {
   public:




      fs(::base::application * papp);
      virtual ~fs();

      bool initialize();


   };


} // namespace fs


