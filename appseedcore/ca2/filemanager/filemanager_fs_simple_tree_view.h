#pragma once


namespace filemanager
{
   
   namespace fs
   {

      namespace simple
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
            __int64        m_iFolder;
            string         m_strName;
            EFolderType    m_etype;
            int            m_iImage;
            int            m_iImageSelected;
         };

         class FolderArray :
            public array_ptr_alloc < Folder, Folder & >
         {
         public:
            int FindAbsolute(__int64 iFolder);
         };

         class CLASS_DECL_ca tree_view :
            virtual public ::userbase::view,
            virtual public ::user::tree
         {
         public:
            simple_scroll_bar                m_scrollbarVert;
            simple_scroll_bar                m_scrollbarHorz;

            int                              m_iIconFolderNormal;
            int                              m_iIconFolderSelected;
            int                              m_iIconArtistNormal;
            int                              m_iIconArtistSelected;
            ::filemanager::fs::simple::view *   m_pserver;
            FolderArray                         m_foldera; 
            __int64                             m_iParentFolder;


            tree_view(::ca::application * papp);

            virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);



            void _001OnItemExpand(::ex1::tree_item *pitem);


            void parse(const char * lpszSource);

            ::ex1::tree_item * FindTreeItem(__int64 iFolder);
            index _001GetItemImage(::ex1::tree_item * pitem, bool bSelected);


            virtual ~tree_view();
         #ifdef _DEBUG
            virtual void assert_valid() const;
            virtual void dump(dump_context & dumpcontext) const;
         #endif

            DECL_GEN_SIGNAL(_001OnCreate)

         };

      } // namespace simple


   } // namespace fs


} // namespace filemanager

