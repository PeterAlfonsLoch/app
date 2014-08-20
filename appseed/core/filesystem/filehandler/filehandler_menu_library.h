#pragma once


namespace filehandler
{


   class CLASS_DECL_CORE menu_library :
      virtual public library
   {
   public:


      menu_library(sp(::axis::application) papp);
      virtual ~menu_library();


   };


} // namespace filehandler


