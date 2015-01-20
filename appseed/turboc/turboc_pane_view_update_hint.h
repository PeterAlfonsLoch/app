#pragma once


namespace turboc
{


   enum EPaneView
   {
      PaneViewNone,
      PaneViewHelloMultiverse,
      PaneViewHelloMultiverseSwitcher,
      PaneViewFileManager,
   };


   class CLASS_DECL_TURBOC pane_view_update_hint :
      public object  
   {
   public:


      enum e_type
      {

         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,

      };

      EPaneView m_eview;
      e_type m_etype;


      pane_view_update_hint();
      virtual ~pane_view_update_hint();
      
      
      void set_type(e_type e_type);

      bool is_type_of(e_type e_type);


   };


} // namespace turboc















