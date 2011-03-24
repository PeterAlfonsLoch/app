#pragma once

#define FILE_MANAGER_ID_FILE_NAME 1

class FileManagerInterface;
class ::fs::item;

namespace filemanager
{

   enum EFolder
   {
      FolderMyComputer,
   };

   class CLASS_DECL_ca SimpleFolderTreeInterface :
      virtual public ::fs::tree,
      virtual public FileManagerViewInterface
   {
   public:
      
      
      enum e_message
      {
         MessageMainPost,
      };
      enum EMessageMainPost
      {
         MessageMainPostCreateImageListItemRedraw,
      };

      enum ETimer
      {
         TimerDelayedListUpdate = 100,
         TimerCreateImageList
      };


      critical_section      m_csBrowse;
      bool                  m_bCreateImageList;
      bool                  m_bCreateImageListRedraw;
      int                  m_iAnimate;
      bool                 m_bTimer123;
      stringa              m_straUpdatePtrFilter;
      stringa              m_straMissingUpdate;
      bool                 m_bDelayedListUpdate;
      ::collection::map < EFolder, EFolder, IShellFolder *, IShellFolder *> m_mapFolder;
      ex1::tree_item *     m_pdataitemCreateImageListStep;
      string               m_strPath;


      SimpleFolderTreeInterface(::ca::application * papp);
      virtual ~SimpleFolderTreeInterface();


      virtual void _001InsertColumns();
      //virtual void _001CreateImageList(CColumn & column);
      virtual void _001UpdateImageList(ex1::tree_item * pitem);

      DECL_GEN_VSIGNAL(_001OnTimer)
   

      int   m_iDefaultImage;
      int   m_iDefaultImageSelected;
      virtual void _017Synchronize();
      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   

      void _StartCreateImageList();
      void _StopCreateImageList();
      void _CreateImageListStep();

      // user::tree
      virtual void _001OnOpenItem(::ex1::tree_item * pitem);
      virtual void _001OnItemExpand(::ex1::tree_item * pitem);
      virtual void _001OnItemCollapse(::ex1::tree_item * pitem);


      virtual void _017OpenFolder(::fs::item & item);
      
      virtual COLORREF get_background_color();

      int MapToCSIDL(EFolder efolder);
      IShellFolder * _001GetFolder(EFolder efolder);
      void _017PreSynchronize();
      void TakeAnimationSnapshot();
      virtual void StartAnimation();
      virtual void _001OnNcDraw(::ca::graphics * pdc);
      DECL_GEN_SIGNAL(_001OnMainPostMessage)
      void GetSelectedFilePath(stringa & stra);
      virtual bool _001IsTranslucent();

      void _017Browse(const char * lpcsz, bool bForceUpdate = false);
      void _017UpdateList();
      void _017UpdateList(const char * lpcsz, ex1::tree_item * pitemParent, int iLevel);
      void _017UpdateZipList(const char * lpcsz, ex1::tree_item * pitemParent, int iLevel);
      void _017EnsureVisible(const char * lpcsz);
      
      ex1::tree_item * find_item(const char * lpcsz);



   protected:
      void _StartDelayedListUpdate(void);
      void _StopDelayedListUpdate(void);
      void _DelayedListUpdate(void);
   };


} // namespace filemanager

