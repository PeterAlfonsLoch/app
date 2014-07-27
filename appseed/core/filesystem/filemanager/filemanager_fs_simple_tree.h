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
            virtual public element
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

         class CLASS_DECL_CORE tree :
            virtual public ::data::tree
         {
         public:

            int32_t                                m_iIconFolderNormal;
            int32_t                                m_iIconFolderSelected;
            int32_t                                m_iIconArtistNormal;
            int32_t                                m_iIconArtistSelected;
            sp(::filemanager::fs::simple::view)    m_pserver;
            FolderArray                            m_foldera; 
            int64_t                                m_iParentFolder;
            //sp(::data::simple_tree_data)           m_spdataFs;


            tree(sp(::base::application) papp);
            virtual ~tree();


            void _001OnItemExpand(::data::tree_item * pitem, ::action::context actioncontext);


            void parse(const char * lpszSource);

            sp(::data::tree_item) FindTreeItem(int64_t iFolder);
            index _001GetItemImage(sp(::data::tree_item) pitem, bool bSelected);


         #ifdef DEBUG
            virtual void assert_valid() const;
            virtual void dump(dump_context & dumpcontext) const;
         #endif

         };

      } // namespace simple


   } // namespace fs


} // namespace filemanager

