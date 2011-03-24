#pragma once

class folder_selection_list_view;

namespace mplite
{

   enum EOptionsFolders
   {
      OptionsFoldersSong,
      OptionsFoldersImage,
      OptionsFoldersAutoRecord,
   };

   class CLASS_DECL_CA2_CUBE OptionsFoldersView :
      public ::userex::pane_tab_view
   {
   public:
      OptionsFoldersView(::ca::application * papp);
      virtual ~OptionsFoldersView();

      virtual void on_create_view(view_data * pviewdata);

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnEditAdd)
      DECL_GEN_SIGNAL(_001OnEditRemove)

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   };


} // namespace mplite