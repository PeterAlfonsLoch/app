#pragma once


class FileManagerInterface;


namespace fs
{


   class item;


} // namespace fs


namespace filemanager
{


   class SimpleFileListInterface :
      virtual public ::userfs::list,
      virtual public FileManagerViewInterface
   {
   public:


      class create_image_list_thread :
         public ::core::thread
      {
      public:


         SimpleFileListInterface * m_plist;


         create_image_list_thread(sp(base_application) papp);

         virtual int32_t run();


      };


      enum EArrange
      {
         ArrangeByName,
      };
      enum e_message
      {
         MessageMainPost = WM_USER + 23,
      };
      enum EMessageMainPost
      {
         MessageMainPostCreateImageListItemStepSetRedraw,
         MessageMainPostCreateImageListItemRedraw,
      };
      virtual void _001InsertColumns();
      /*class Item
      {
      public:
         index            m_iCsidl;
         string         m_strPath;
         string         m_strName;
         string        m_strExtra;
         index            m_iImage;
         index            m_iIndex;
         index            m_iArrange;
         flags < filemanager::e_flag > m_flags;

         Item();

         static index CompareArrangeByName(Item & pitema, Item & itemb);
         index CompareArrangeByName(const Item & item) const;
         index GetIndex() const;
         bool IsFolder() const;
      };*/


      /*class ItemArray :
         protected class_sort_array < ItemArray, Item, Item & >
      {

      public:


         ItemArray(sp(base_application) papp);


         void add_item(Item & item);
         ::count get_item_count();
         void clear(LPITEMIDLIST lpiidlPreserve1, LPITEMIDLIST lpiidlPreserve2);
         Item & get_item(index i);
         void SetItemAt(index i, Item & item);
         void SetItemCount(::count iCount);
         index find_item_by_path(const char * pszPath);

         void SoftSwap(index i1, index i2);

         void Arrange(EArrange earrange);
      };*/

      index                     m_iNameSubItem;
      index                     m_iNameSubItemText;
      index                     m_iSelectionSubItem;
      index                     m_iSizeSubItem;
      bool                    m_bPendingSize;
      uint32_t                   m_dwLastFileSizeGet;

      map < icon_key, const icon_key &, icon, icon & > m_iconmap;

      mutex            m_mutex;
#ifdef WINDOWSEX
      IShellFolder *   m_pshellfolder;
#endif
      bool               m_bCreateImageList;
      bool               m_bCreateImageListRedraw;
      index               m_iAnimate;
      ::user::buffer   m_gdibuffer;
      create_image_list_thread * m_pcreateimagelistthread;

      int64_t          m_iCreateImageListStep;

      string                  m_strPath;

      uint32_t             m_dwLastRedraw;
      bool              m_bRestartCreateImageList;

      bool              m_bStatic;

   /*   class icon_key
      {
      public:
         icon_key();
         string      m_strPath;
         index         m_iIcon;
         string      m_strExtension;

         operator uint32_t () const
         {
            return m_iIcon;
         }
         bool operator == (const icon_key & key) const;
      };



      class icon
      {
      public:
         icon();
         HICON         m_hicon;
         index         m_iImage;
      };*/

      SimpleFileListInterface(sp(base_application) papp);
      virtual ~SimpleFileListInterface();
      virtual void file_size_add_request(bool bClear);


      virtual COLORREF get_background_color();
      bool add_item(const char * pszPath, const char * pszTitle);
      //virtual void schedule_file_size(const char * psz) = 0;
   // Attributes
      virtual void _017Synchronize();
      virtual void install_message_handling(message::dispatch * pinterface);

      sp(image_list) GetActionButtonImageList(index i);



      void GetSelected(::fs::item_array & itema);

      void _001OnInitializeForm(sp(::user::control) pcontrol);
      void _001OnButtonAction(sp(::user::control) pcontrol);

      virtual void _017OpenFile(const ::fs::item_array & itema);
      virtual void _017OpenFolder(sp(::fs::item)  item);
      virtual void _017OpenSelected(bool bOpenFile);
      virtual void _017OpenContextMenuSelected();
      virtual void _017OpenContextMenuFolder(sp(::fs::item) item);
      virtual void _017OpenContextMenuFile(const ::fs::item_array &itema);
      virtual void _017OpenContextMenu();
      void _017PreSynchronize();
      void TakeAnimationSnapshot();
      virtual void StartAnimation();
      virtual void _001OnDraw(::draw2d::graphics * pdc);
      ::fs::item & GetFileManagerItem();
      DECL_GEN_SIGNAL(_001OnMainPostMessage)
      void _017UpdateList();
      void GetSelectedFilePath(stringa & array);
      virtual bool TwiHasTranslucency();
      void _001CreateImageList();
      bool _001CreateImageListStep();
      virtual void _001GetItemImage(::user::list_item * pitem);
      virtual void _001GetItemText(::user::list_item * pitem);
      virtual count _001GetItemCount();
      void _017Browse(const char * lpcsz);
      void _017UpdateList(const char * lpcsz);
      void _017UpdateZipList(const char * lpcsz);

      DECL_GEN_SIGNAL(_001OnHScroll)
      DECL_GEN_SIGNAL(_001OnVScroll)
      DECL_GEN_SIGNAL(_001OnFileRename)
      DECL_GEN_SIGNAL(_001OnUpdateFileRename)
      DECL_GEN_SIGNAL(_001OnShowWindow)


      virtual void _001InitializeFormPreData();



      virtual bool query_drop(index iDisplayDrop, index iDisplayDrag);
      virtual bool do_drop(index iDisplayDrop, index iDisplayDrag);


   };


} // namespace filemanager


