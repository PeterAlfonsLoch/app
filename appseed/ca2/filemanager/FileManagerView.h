#pragma once

namespace filemanager
{
   class SimpleFileListView;
   class SimpleFolderListView;
   class SimplePreview;
   class SimpleFilePropertiesForm;
}



class CLASS_DECL_ca FileManagerAView :
   virtual public ::userbase::split_view,
   virtual public FileManagerViewInterface
{
public:
   FileManagerAView(::ax::application * papp);

   void CreateViews();
   
   void FileManagerBrowse(const char * lpcwstr);

   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   virtual ~FileManagerAView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif
};



class CLASS_DECL_ca FileManagerView :
   virtual public ::userbase::split_view,
   virtual public FileManagerViewInterface
{
public:
   FileManagerView(::ax::application * papp);
   
   filemanager::SimpleFileListView *         m_pfilelist;
   filemanager::SimplePreview *              m_ppreview;
   filemanager::SimpleFilePropertiesForm *   m_ppropform;
   ::fs::item_array                      m_itema;

   void CreateViews();
   
   void FileManagerBrowse(const char * lpcwstr);

   bool _001OnCommand(id id);

   virtual void OpenSelectionProperties();

   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

   virtual ~FileManagerView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};


