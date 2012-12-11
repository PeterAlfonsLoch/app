#pragma once


#include "ContextMenu.h"


#include "SimpleFileListInterface.h"


namespace filemanager
{


   class document;


   class CLASS_DECL_ca2 SimpleFileListView :
      virtual public ::userbase::view,
      virtual public filemanager::SimpleFileListInterface
   {
   public:

      class file_size
      {
      public:
         SimpleFileListView * m_pview;
         string m_str;

      };

      ContextMenu                      m_contextmenu;
      stringa                          m_straOpenWith;
      bool                             m_bFileSize;
      bool                             m_bShow;
      DWORD                            m_dwLastFileSize;



      SimpleFileListView(::ca::application * papp);



      void schedule_file_size(const char * psz);

      virtual void _017OpenContextMenuFolder(const ::fs::item &item);
      virtual void _017OpenContextMenuFile(const ::fs::item_array &itema);
      virtual void _017OpenContextMenu();
      virtual void _017OpenFile(const ::fs::item_array & itema);
      virtual void _017OpenFolder(const ::fs::item & item);
      void StartAnimation();
      void RenameFile(int iLine, string & str);
      static UINT c_cdecl ThreadProcFileSize(LPVOID lpparam);

      void FileSize();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
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

      virtual ~SimpleFileListView();
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

      virtual void install_message_handling(::gen::message::dispatch * pinterface);


   };


} // namespace filemanager


