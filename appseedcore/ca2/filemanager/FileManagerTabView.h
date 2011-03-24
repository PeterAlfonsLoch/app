#pragma once

namespace filemanager
{

   class SimpleFileListView;
   class SimpleFolderListView;

}

class CLASS_DECL_ca FileManagerTabView :
   virtual public ::userex::pane_tab_view,
   virtual public FileManagerViewInterface
{
public:
   FileManagerTabView(::ca::application * papp);

   virtual void on_create_view(view_data * pviewdata);
   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   void FileManagerBrowse(const char * lpcwstr);


   DECL_GEN_SIGNAL(_001OnCreate)
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   virtual ~FileManagerTabView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};


