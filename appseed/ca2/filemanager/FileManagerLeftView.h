#pragma once

namespace filemanager
{
   class SimpleFileListView;
   class SimpleFolderListView;
}


class CLASS_DECL_ca2 FileManagerLeftView :
   virtual public ::userbase::split_view,
   virtual public FileManagerViewInterface
{
public:
   FileManagerLeftView(::ca::application * papp);

   void CreateViews();
   
   void FileManagerBrowse(const char * lpcwstr);


   virtual void on_update(::view * pSender, LPARAM lHint, ::gen::object* pHint);
   virtual ~FileManagerLeftView();
#ifdef DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};

