#pragma once

namespace filemanager
{
   class SimpleFileListView;
   class SimpleFolderListView;
}


class CLASS_DECL_ca2 FileManagerLeftView :
   virtual public ::user::split_view,
   virtual public FileManagerViewInterface
{
public:
   FileManagerLeftView(sp(base_application) papp);

   void CreateViews();
   
   void FileManagerBrowse(const char * lpcwstr);


   virtual void on_update(sp(::user::view) pSender, LPARAM lHint, object* pHint);
   virtual ~FileManagerLeftView();
#ifdef DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};

