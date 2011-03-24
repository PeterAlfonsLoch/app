#pragma once


namespace alarm
{

   enum e_pane_view
   {
      pane_view_none,
      PaneViewContextMenu,
      PaneViewDevEdge,
      PaneViewHtmlEdit,
      PaneViewHtml,
      PaneViewFileManager,
      PaneViewByWeekday,
      PaneViewPlaylist,
      PaneViewMediaLibrary,
      PaneViewAudioControl,
      PaneViewOptions,
      PaneViewAlarmTest,
   };


   class CLASS_DECL_CA2_ALARM pane_view_update_hint :
      public ::radix::object  
   {
   public:


      enum EType
      {
         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,
      };

      e_pane_view m_eview;
      EType m_etype;


      void SetType(EType etype);
	   bool IsTypeOf(EType etype);

	   pane_view_update_hint();
	   virtual ~pane_view_update_hint();


   };


} // namespace alarm