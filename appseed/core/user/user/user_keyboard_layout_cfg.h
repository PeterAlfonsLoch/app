#pragma once


namespace user
{


   class CLASS_DECL_CORE keyboard_layout_cfg :
      virtual public ::object
   {
   public:



      keyboard_layout_cfg(sp(::axis::application) papp);
      virtual ~keyboard_layout_cfg();

      bool CreateViews();

      void on_show();

   };


} // namespace user


