#pragma once

class image_list;

namespace mplite
{

   class MediaLibraryDoc;

   namespace library
   {

      enum EItemType
      {
         ItemTypeFolder,
         ItemTypeArtist,
         ItemTypeSong,
      };
      class Item
      {
      public:
         string  m_id;
         string  m_strTitle;
         string  m_strFileName;
         int      m_iId;
         EItemType m_etype;
         int m_iImage;

         bool IsFolder();
      };

      class ItemArray :
         public array_ptr_alloc < Item, Item & >
      {
      public:
         int FindAbsolute(const char * lpszId);
      };


      class view;

      class CLASS_DECL_CA2_CUBE list_view :
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

         list_view(::ca::application * papp);
         ::mplite::library::view * m_pserver;

         void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
       
         ::user::list_cache        m_cache;
         bool                 m_bKickActive;

         ItemArray         m_itema; 

         image_list *          m_pil;


         int m_iIconFolder;
         int m_iIconArtist;
         int m_iIconSong;

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
      //      list_view *      m_pview;
            string             m_strFile;
            UINT              m_uiTimer;

         };


         void Parse(const char * lpszSource);
         void KickBuild(int iItem = -1);
         
         void PostFillTask(string & strFile, UINT uiTimer);

         virtual void _001OnSort();
         bool GetSongPath(string & str, int iItem);
         MediaLibraryDoc * get_document();

         virtual index _001GetItemImage(index iItem, index iSubItem, index iListItem);
         virtual void _001InsertColumns();
         virtual bool _001GetItemText(string &str, index iItem, index iSubItem, index iListItem);
         virtual count _001GetItemCount();
         virtual bool _001SearchGetItemText(string &str, index iItem, index iSubItem, index iListItem);

         virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

         virtual void _001OnClick(UINT nFlags, point point);

         virtual ~list_view();
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
         DECL_GEN_SIGNAL(_001OnEraseBkgnd)
         DECL_GEN_SIGNAL(_001OnFillTaskResponse)

      };

   } // namespace library

} // namespace mplite