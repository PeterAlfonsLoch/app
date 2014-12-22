#pragma once


namespace fs
{


   class CLASS_DECL_BASE fs :
      virtual public ::aura::departament
   {
   public:




      fs(::aura::application * papp);
      virtual ~fs();

      bool initialize();


   };


} // namespace fs


