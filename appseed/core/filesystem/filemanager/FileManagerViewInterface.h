#pragma once

namespace filemanager
{

   class document;

} // namespace filemanager

class CLASS_DECL_ca2 FileManagerViewInterface
{
public:
   FileManagerViewInterface();
   virtual ~FileManagerViewInterface();
   
   sp(FileManagerInterface) m_pfilemanagerinterface;

   ::fs::item & GetFileManagerItem();

   virtual sp(FileManagerInterface) GetFileManager();
   virtual sp(::filemanager::document) GetFileManagerDoc();

   void on_update(sp(::user::view) pSender, LPARAM lHint, object* pHint);
};