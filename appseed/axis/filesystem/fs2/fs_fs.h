#pragma once


namespace fs
{


   class CLASS_DECL_AXIS fs :
      virtual public ::axis::departament
   {
   public:




      fs(::axis::application * papp);
      virtual ~fs();

      bool initialize();


   };


} // namespace fs


