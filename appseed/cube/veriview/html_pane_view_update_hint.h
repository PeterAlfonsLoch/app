#pragma once

namespace html
{

enum EPaneView
{
   PaneViewNone,
   PaneViewContextMenu,
   PaneViewSourceEdit,
   PaneViewHtmlEdit,
   PaneViewHtml,
   PaneViewFileManager,
   PaneViewPlaylist,
   PaneViewMediaLibrary,
   PaneViewAudioControl,
   PaneViewOptions,
};

} // namespace html

class CLASS_DECL_CA2_VERIVIEW html_pane_view_update_hint :
   public base_object  
{
public:
   enum EType
   {
      TypeGetView,
      TypeSetView,
      TypeOnShowKaraoke,
      TypeOnShowView,
      TypeOpenDocument,
   };
   // DECLARE_DYNAMIC(html_pane_view_update_hint)
public:
	void SetType(EType etype);
	bool IsTypeOf(EType etype);

	html_pane_view_update_hint();
	virtual ~html_pane_view_update_hint();

   int   m_iId;
protected:
   EType m_etype;

};
