#pragma once

namespace mplite
{

   class MediaLibraryDoc;

   class CLASS_DECL_CA2_CUBE MediaLibraryListView :
      public simple_list_view
   {
   public:

      enum EFieldIndex
      {
         FieldIndexNone = -1,
         FieldIndexId = 0,
         FieldIndexTitle,
         FieldIndexArtist,
         FieldIndexFileName,
         FieldIndexFilePath,
      };

      enum ESubItem
      {
         SubItemId,
         SubItemTitle,
         SubItemArtist,
         SubItemFileName,
         SubItemFilePath,
      };

      MediaLibraryListView(::ca::application * papp);

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      ::user::list_cache        m_cache;
      bool                 m_bKickActive;

      class BuildHelper
      {
      public:
         BuildHelper();
         int      m_iTopIndex;
         int      m_iDisplayItemCount;
         int      m_iStep;
         bool     m_bActive;
      };

      BuildHelper          m_buildhelper;

      static UINT AFX_CDECL ThreadProcFillTask(LPVOID lpParameter);

      class FillTask
      {
      public:
         //FillTask(MAlbumView * pview, const wchar_t * lpcsz);
   //      MediaLibraryListView *      m_pview;
         string             m_wstrFile;
         UINT              m_uiTimer;

      };


      void KickBuild(int iItem = -1);
      
      void PostFillTask(string & wstrFile, UINT uiTimer);

      virtual void _001OnSort();
      bool GetSongPath(string & str, int iItem);
      MediaLibraryDoc * get_document();

      virtual index _001GetItemImage(index iItem, index iSubItem, index iListItem);
      virtual void _001InsertColumns();
      virtual bool _001GetItemText(string &str, index iItem, index iSubItem, index iListItem);
      virtual count _001GetItemCount();
      virtual bool _001SearchGetItemText(string &str, index iItem, index iSubItem, index iListItem);

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      virtual ~MediaLibraryListView();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnLButtonDblClk)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnAlbumExecutePlay)
      DECL_GEN_SIGNAL(_001OnUpdateAlbumExecutePlay)
      DECL_GEN_SIGNAL(_001OnExecutePrevious)
      DECL_GEN_SIGNAL(_001OnUpdateExecutePrevious)
      DECL_GEN_SIGNAL(_001OnExecuteNext)
      DECL_GEN_SIGNAL(_001OnUpdateExecuteNext)
      DECL_GEN_SIGNAL(_001OnFillTaskResponse)

   };

} // namespace mplite