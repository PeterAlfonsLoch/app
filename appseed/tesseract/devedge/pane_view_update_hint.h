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
   PaneViewSolution,
};


class CLASS_DECL_CA2_TESSERACT PaneViewUpdateHint :
   public ::radix::object  
{
public:
   enum e_type
   {
      TypeGetView,
      TypeSetView,
      TypeOnShowKaraoke,
      TypeOnBeforeShowView,
      TypeOnShowView,
   };
   
public:
   void set_type(e_type e_type);
   bool is_type_of(e_type e_type);

   PaneViewUpdateHint();
   virtual ~PaneViewUpdateHint();

   EPaneView m_eview;
protected:
   e_type m_etype;

};
