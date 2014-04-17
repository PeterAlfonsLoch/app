#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE main_frame :
   public simple_frame_window
   {
   public:


      simple_menu_bar           m_menubar;
      simple_toolbar           m_toolbar;
      //   SimpleReBar             m_rebar;


      main_frame(sp(base_application) papp);
      virtual ~main_frame();

      bool CreateBars();

      DECL_GEN_SIGNAL(_001OnCreate);

   };



} // namespace filemanager



