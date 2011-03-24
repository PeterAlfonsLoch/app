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


class CLASS_DECL_CA2_DEVEDGE PaneViewUpdateHint :
   public base_object  
{
public:
   enum EType
   {
      TypeGetView,
      TypeSetView,
      TypeOnShowKaraoke,
      TypeOnBeforeShowView,
      TypeOnShowView,
   };
   // DECLARE_DYNAMIC(PaneViewUpdateHint)
public:
	void SetType(EType etype);
	bool IsTypeOf(EType etype);

	PaneViewUpdateHint();
	virtual ~PaneViewUpdateHint();

   EPaneView m_eview;
protected:
   EType m_etype;

};
