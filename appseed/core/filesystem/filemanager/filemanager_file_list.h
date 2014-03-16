#pragma once





namespace filemanager
{


   class document;


   class CLASS_DECL_CORE file_list :
      virtual public ::user::impact,
      virtual public ::userfs::list,
      virtual public data_interface

   {
   public:
      class create_image_list_thread :
         public thread
      {
      public:


         file_list * m_plist;


         create_image_list_thread(sp(base_application) papp);

         virtual int32_t run();


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

      class file_size
      {
      public:
         file_list * m_pview;
         string m_str;

      };

      context_menu                     m_contextmenu;
      stringa                          m_straOpenWith;
      bool                             m_bFileSize;
      bool                             m_bShow;
      uint32_t                         m_dwLastFileSize;

      


      file_list(sp(base_application) papp);



      void schedule_file_size(const char * psz);

      virtual void _017OpenContextMenuFolder(sp(::fs::item) item, ::action::context actioncontext);
      virtual void _017OpenContextMenuFile(const ::fs::item_array &itema, ::action::context actioncontext);
      virtual void _017OpenContextMenu(::action::context actioncontext);
      virtual void _017OpenFile(const ::fs::item_array & itema, ::action::context actioncontext);
      virtual void _017OpenFolder(sp(::fs::item)  item, ::action::context actioncontext);
      void StartAnimation();
      void RenameFile(int32_t iLine, string & str, ::action::context actioncontext);
      static UINT c_cdecl ThreadProcFileSize(LPVOID lpparam);

      void FileSize();

      virtual bool _001OnCmdMsg(base_cmd_msg * pcmdmsg);
      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);
      virtual bool pre_create_window(CREATESTRUCT& cs);

      bool _001OnUpdateCmdUi(cmd_ui * pcmdui);
      bool _001OnCommand(id id);

      DECL_GEN_SIGNAL(_001OnUpdateOpenWith)
      DECL_GEN_SIGNAL(_001OnEditCopy)
      DECL_GEN_SIGNAL(_001OnUpdateEditCopy)
      DECL_GEN_SIGNAL(_001OnEditPaste)
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste)
      DECL_GEN_SIGNAL(_001OnShowWindow)

      virtual id data_get_current_list_layout_id();

      virtual ~file_list();
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnTimer)

      DECL_GEN_SIGNAL(_001OnShellCommand)
      DECL_GEN_SIGNAL(_001OnFileManagerItemCommand)
      DECL_GEN_SIGNAL(_001OnFileManagerItemUpdate)

      DECL_GEN_SIGNAL(_001OnFileRename)
      DECL_GEN_SIGNAL(_001OnUpdateFileRename)

      DECL_GEN_SIGNAL(_001OnTrashThatIsNotTrash)
      DECL_GEN_SIGNAL(_001OnUpdateTrashThatIsNotTrash)

      DECL_GEN_SIGNAL(_001OnSpafy)
      DECL_GEN_SIGNAL(_001OnUpdateSpafy)
      DECL_GEN_SIGNAL(_001OnSpafy2)
      DECL_GEN_SIGNAL(_001OnUpdateSpafy2)

      virtual void _001OnClick(UINT nFlags, point point);
      virtual void _001OnRightClick(UINT nFlags, point point);

      virtual void _001OnAfterSort();

      virtual void install_message_handling(::message::dispatch * pinterface);

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

      virtual void file_size_add_request(bool bClear);


      virtual COLORREF get_background_color();
      bool add_item(const char * pszPath, const char * pszTitle);
      //virtual void schedule_file_size(const char * psz) = 0;
      // Attributes
      virtual void _017Synchronize(::action::context actioncontext);

      sp(image_list) GetActionButtonImageList(index i);



      void GetSelected(::fs::item_array & itema);

      void _001OnInitializeForm(sp(::user::control) pcontrol);
      void _001OnButtonAction(sp(::user::control) pcontrol);

      virtual void _017OpenSelected(bool bOpenFile, ::action::context actioncontext);
      virtual void _017OpenContextMenuSelected(::action::context actioncontext);
      void _017PreSynchronize(::action::context actioncontext);
      void TakeAnimationSnapshot();
      virtual void _001OnDraw(::draw2d::graphics * pdc);
      ::fs::item & GetFileManagerItem();
      DECL_GEN_SIGNAL(_001OnMainPostMessage);
      void _017UpdateList(::action::context actioncontext);
      void GetSelectedFilePath(stringa & array);
      virtual bool TwiHasTranslucency();
      void _001CreateImageList();
      bool _001CreateImageListStep();
      virtual void _001GetItemImage(::user::list_item * pitem);
      virtual void _001GetItemText(::user::list_item * pitem);
      virtual count _001GetItemCount();
      void _017Browse(const char * lpcsz, ::action::context actioncontext);
      void _017UpdateList(const char * lpcsz, ::action::context actioncontext);
      void _017UpdateZipList(const char * lpcsz, ::action::context actioncontext);

      DECL_GEN_SIGNAL(_001OnHScroll)
         DECL_GEN_SIGNAL(_001OnVScroll)


         virtual void _001InitializeFormPreData();



      virtual bool query_drop(index iDisplayDrop, index iDisplayDrag);
      virtual bool do_drop(index iDisplayDrop, index iDisplayDrag);


   };


} // namespace filemanager


