#pragma once

namespace filemanager
{


class CLASS_DECL_ca SimpleFolderListInterface :
   virtual public ::user::list,
   virtual public FileManagerViewInterface
{
public:
   
   enum EMode
   {
      ModeNormal, // a bit ridiculous that folder list
      ModeConfigurationItem,
   };

   SimpleFolderListInterface(::ca::application * papp);
   virtual ~SimpleFolderListInterface();

public:
   class Folder
   {
   public:
      string      m_strPath;
      string      m_wstrName;
      int          m_iImage;
   };
   class FolderArray :
      protected base_array < Folder, Folder & >
   {

   public:
      void AddFolder(Folder & folder);
      int GetFolderCount();
      void clear(LPITEMIDLIST lpiidlPreserve1, LPITEMIDLIST lpiidlPreserve2);
      Folder & GetFolder(int i);
   };

   virtual void _017Synchronize();
   
   FolderArray         m_foldera; 
   ::collection::map < HICON, HICON, int, int > m_iconmap;
   
   ::fs::item & GetFileManagerItem();

   virtual index _001GetItemImage(index iItem, index iSubItem, index iListItem);
   void _017UpdateList(const char * lpcszParent);
   virtual void _001CreateImageList(Column & column);
   void _017UpdateList();
   void _017Browse(const char * lpcsz);
   void _017Browse(const wchar_t * lpcsz);
   virtual bool _001GetItemText(string &str, index iItem, index iSubItem, index iListItem);
   virtual count _001GetItemCount();
   virtual void _001InsertColumns();

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   virtual COLORREF get_background_color();

};

} // namespace filemanager
