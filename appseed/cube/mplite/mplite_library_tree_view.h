#pragma once

namespace mplite
{
   namespace library
   {

      class view;

      enum EFolderType
      {
         FolderTypeNormal,
         FolderTypeArtist,
      };
      class Folder
      {
      public:
         id m_id;
         string m_strTitle;
         EFolderType m_etype;
         int m_iImage;
         int m_iImageSelected;
      };

      class FolderArray :
         public array_ptr_alloc < Folder, Folder & >
      {
      public:
         int FindAbsolute(const char * lpszId);
      };

      class CLASS_DECL_CA2_CUBE tree_view :
         virtual public ::userbase::view,
         virtual public ::user::tree
      {
      public:
         simple_scroll_bar         m_scrollbarVert;
         simple_scroll_bar         m_scrollbarHorz;

         int                                             m_iIconFolderNormal;
         int                                             m_iIconFolderSelected;
         int                                             m_iIconArtistNormal;
         int                                             m_iIconArtistSelected;
         ::mplite::library::view *            m_pserver;
         FolderArray                            m_foldera; 


         tree_view(::ca::application * papp);

         virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);



         void _001OnItemExpand(::ex1::tree_item *pitem);


         void Parse(const char * lpszParentId, const char * lpszSource);

         ::ex1::tree_item * FindTreeItem(const char * lpszId);
         index _001GetItemImage(::ex1::tree_item * pitem, bool bSelected);


         virtual ~tree_view();
      #ifdef _DEBUG
         virtual void assert_valid() const;
         virtual void dump(dump_context & dumpcontext) const;
      #endif

         DECL_GEN_SIGNAL(_001OnCreate)

      };
   } // namespace library
} // namespace mplite
