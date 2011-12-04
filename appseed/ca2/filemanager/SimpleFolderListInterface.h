#pragma once

namespace filemanager
{


class CLASS_DECL_ca2 SimpleFolderListInterface :
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

   virtual void _001GetItemImage(::user::list_item * pitem);
   void _017UpdateList(const char * lpcszParent);
   virtual void _001CreateImageList(::user::list_column * column);
   void _017UpdateList();
   void _017Browse(const char * lpcsz);
   void _017Browse(const wchar_t * lpcsz);
   virtual void _001GetItemText(::user::list_item * pitem);
   virtual count _001GetItemCount();
   virtual void _001InsertColumns();

   virtual void install_message_handling(::gen::message::dispatch * pinterface);

   virtual COLORREF get_background_color();

};

} // namespace filemanager
