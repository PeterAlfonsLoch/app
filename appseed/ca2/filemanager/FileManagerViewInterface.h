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
   
   FileManagerInterface * m_pfilemanagerinterface;

   ::fs::item & GetFileManagerItem();

   virtual FileManagerInterface * GetFileManager();
   virtual ::filemanager::document * GetFileManagerDoc();

   void on_update(::view * pSender, LPARAM lHint, ::gen::object* pHint);
};