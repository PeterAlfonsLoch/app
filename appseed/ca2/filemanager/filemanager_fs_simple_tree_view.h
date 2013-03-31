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
         class Folder :
            virtual public ::ca::ca
         {
         public:
            int64_t        m_iFolder;
            string         m_strName;
            EFolderType    m_etype;
            int32_t            m_iImage;
            int32_t            m_iImageSelected;
         };

         class FolderArray :
            public spa(Folder)
         {
         public:
            int32_t FindAbsolute(int64_t iFolder);
         };

         class CLASS_DECL_ca2 tree_view :
            virtual public ::userbase::view,
            virtual public ::user::tree
         {
         public:

            int32_t                              m_iIconFolderNormal;
            int32_t                              m_iIconFolderSelected;
            int32_t                              m_iIconArtistNormal;
            int32_t                              m_iIconArtistSelected;
            ::filemanager::fs::simple::view *   m_pserver;
            FolderArray                         m_foldera; 
            int64_t                             m_iParentFolder;


            tree_view(::ca::application * papp);

            virtual void install_message_handling(::ca::message::dispatch * pdispatch);



            void _001OnItemExpand(::ca::tree_item *pitem);


            void parse(const char * lpszSource);

            ::ca::tree_item * FindTreeItem(int64_t iFolder);
            index _001GetItemImage(::ca::tree_item * pitem, bool bSelected);


            virtual ~tree_view();
         #ifdef DEBUG
            virtual void assert_valid() const;
            virtual void dump(dump_context & dumpcontext) const;
         #endif

            DECL_GEN_SIGNAL(_001OnCreate)

         };

      } // namespace simple


   } // namespace fs


} // namespace filemanager

