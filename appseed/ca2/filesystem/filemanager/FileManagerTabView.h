#pragma once

namespace filemanager
{

   class SimpleFileListView;
   class SimpleFolderListView;

}

class CLASS_DECL_ca2 FileManagerTabView :
   virtual public ::userex::pane_tab_view,
   virtual public FileManagerViewInterface
{
public:
   FileManagerTabView(sp(::application) papp);

   virtual void on_create_view(::user::view_creator_data * pcreatordata);
   virtual void install_message_handling(::ca2::message::dispatch * pinterface);
   void FileManagerBrowse(const char * lpcwstr);


   DECL_GEN_SIGNAL(_001OnCreate)
   virtual void on_update(sp(::user::view) pSender, LPARAM lHint, object* pHint);
   virtual ~FileManagerTabView();
#ifdef DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};


