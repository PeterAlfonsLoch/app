#pragma once


namespace md5
{

   enum e_pane_view
   {
      pane_view_none,
      PaneViewContextMenu,
      PaneViewDevEdge,
      PaneViewHtmlEdit,
      PaneViewHtml,
      PaneViewFileManager,
      PaneViewPlaylist,
      PaneViewMediaLibrary,
      PaneViewAudioControl,
      PaneViewOptions,
      PaneViewAlarmTest,
   };


   class CLASS_DECL_CA2_MD5 pane_view_update_hint :
      public base_object  
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


} // namespace md5