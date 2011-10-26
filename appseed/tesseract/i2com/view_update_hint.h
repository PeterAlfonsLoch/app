#pragma once

namespace i2com
{

enum EPaneView
{
   PaneViewNone,
   PaneViewContact,
   PaneViewCommunication,
   PaneViewHtmlEdit,
   PaneViewHtml,
   PaneViewFileManager,
   PaneViewPlaylist,
   PaneViewMediaLibrary,
   PaneViewAudioControl,
   PaneViewOptions,
};




class CLASS_DECL_CA2_TESSERACT view_update_hint :
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

   view_update_hint();
   virtual ~view_update_hint();

   i2com::EPaneView m_eview;
protected:
   e_type m_etype;

};


} // namespace i2com