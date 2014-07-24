#pragma once

namespace nature
{

   enum EPaneView
   {
      PaneViewNone,
      PaneViewIdioma,
      PaneViewDevEdge,
      PaneViewHtmlEdit,
      PaneViewHtml,
      PaneViewFileManager,
      PaneViewAudioControl,
      PaneViewOptions,
      PaneViewAppearance,
      PaneViewKeyboardLayout,
   };


   class CLASS_DECL_CORE pane_view_update_hint :
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
      
   public:
      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);

      pane_view_update_hint();
      virtual ~pane_view_update_hint();

      nature::EPaneView m_eview;
   protected:
      e_type m_etype;

   };

} // namespace nature