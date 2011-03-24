#pragma once


namespace loginstartup
{

enum EPaneView
{
   PaneViewNone,
   PaneViewContextMenu,
   PaneViewWinActionArea,
   PaneViewFileManager,
   PaneViewThreeActionLaunch,
   PaneViewConfiguration,
};


class CLASS_DECL_CA2_LOGINSTARTUPAPPLICATION pane_view_update_hint :
   public base_object  
{
public:
   enum etype
   {
      TypeGetView,
      TypeSetView,
      TypeOnShowKaraoke,
      TypeOnShowView,
   };
   // DECLARE_DYNAMIC(pane_view_update_hint)
public:
	void set_type(etype etype);
	bool is_type_of(etype etype);

	pane_view_update_hint();
	virtual ~pane_view_update_hint();

   EPaneView m_eview;
protected:
   etype m_etype;

};

} // namespace loginstartup
