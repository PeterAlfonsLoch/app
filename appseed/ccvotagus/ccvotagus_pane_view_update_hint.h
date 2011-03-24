#pragma once


enum EPaneView
{
   PaneViewNone,
   PaneViewContextMenu,
   PaneViewDevEdge,
   PaneViewHtmlEdit,
   PaneViewHtml,
   PaneViewFileManager,
   PaneViewPlaylist,
   PaneViewMediaLibrary,
   PaneViewAudioControl,
   PaneViewOptions,
};


class CLASS_DECL_CA2_PAINTAPPLICATION pane_view_update_hint :
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
   DECLARE_DYNAMIC(pane_view_update_hint)
public:
	void SetType(EType etype);
	bool IsTypeOf(EType etype);

	pane_view_update_hint();
	virtual ~pane_view_update_hint();

   EPaneView m_eview;
protected:
   EType m_etype;

};
