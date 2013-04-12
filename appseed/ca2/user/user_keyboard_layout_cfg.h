#pragma once


namespace user
{


   class CLASS_DECL_ca2 keyboard_layout_cfg :
      virtual public ::ca::object
   {
   public:



      keyboard_layout_cfg(sp(::ca::application) papp);
      virtual ~keyboard_layout_cfg();

      bool CreateViews();

      void on_show();

   };


} // namespace user


