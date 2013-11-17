#pragma once


namespace fs
{


   class CLASS_DECL_CORE fs :
      virtual public ::base_departament
   {
   public:




      fs(base_application * papp);
      virtual ~fs();

      bool initialize();


   };


} // namespace fs


