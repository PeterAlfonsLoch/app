#include "framework.h"


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {


         tree::tree(sp(::base::application) papp) :
            element(papp),
            ::data::data(papp),
            ::data::tree(papp),
            ::user::tree_data(papp)
         {

            m_iIconFolderNormal     = m_pimagelist->add_matter_icon("mplite/vmskarlib_folder_normal.ico");
            m_iIconFolderSelected   = m_pimagelist->add_matter_icon("mplite/vmskarlib_folder_selected.ico");
            m_iIconArtistNormal     = m_pimagelist->add_matter_icon("mplite/vmskarlib_artist_normal.ico");
            m_iIconArtistSelected   = m_pimagelist->add_matter_icon("mplite/vmskarlib_artist_selected.ico");

         }

         tree::~tree()
         {
         }




         #ifdef DEBUG
         void tree::assert_valid() const
         {
            ::data::tree::assert_valid();
         }

         void tree::dump(dump_context & dumpcontext) const
         {
            ::data::tree::dump(dumpcontext);
         }
         #endif //DEBUG


         void tree::parse(const char * lpszSource)
         {
            string str;
            xml::document doc(get_app());
            if(doc.load(lpszSource))
            {
               str  = doc.get_xml();
            }
            else
            {
               System.simple_message_box(NULL, "error"); // simple parsing error check
               return;
            }

            m_iParentFolder = doc.get_root()->attr("id");

            sp(::data::tree_item) pdataitemParent;
            sp(::data::tree_item) pdataitemChild;

            pdataitemParent = FindTreeItem(m_iParentFolder);
            if(pdataitemParent == NULL)
            {
               pdataitemParent = get_base_item();
            }

            xml::node::array childs(get_app());

            string wstrType;
            Folder folder;
            // method 3: Selected Childs with GetChilds()
            // Result: Person, Person, Person
            index iNode = 0;
            sp(::xml::node) pnodeFolder = doc.get_root()->get_child("folder");


   //         xml::node::array childs(get_app());

   //         string wstrType;
            // method 3: Selected Childs with GetChilds()
            // Result: Person, Person, Person
   //         index iNode = 0;
            for(int32_t i = 0 ; i < pnodeFolder->get_children_count(); i++)
            {
               sp(::xml::node) pnodeItem = pnodeFolder->child_at(i);
               folder.m_iFolder = pnodeItem->attr("id");
               folder.m_strName = pnodeItem->attr("name");

   /*            if(wstrType == "normal")
               {
                  folder.m_etype = FolderTypeNormal;
               }
               else if(wstrType == "artist")
               {
                  folder.m_etype = FolderTypeArtist;
               }
               else
               {
                  // unknown folder type
                  ASSERT(FALSE);
               }*/

               switch(folder.m_etype)
               {
               case FolderTypeNormal:
                  folder.m_iImage = m_iIconFolderNormal;
                  folder.m_iImageSelected = m_iIconFolderSelected;
                  break;
               case FolderTypeArtist:
                  folder.m_iImage = m_iIconArtistNormal;
                  folder.m_iImageSelected = m_iIconArtistSelected;
                  break;
               default:
                  // unknown folder type
                  break;
               }

               index iNewItem = m_foldera.FindAbsolute(folder.m_iFolder);
               if(iNewItem == -1)
               {
                  iNewItem = m_foldera.get_size();
                  m_foldera.add_new();
               }
               m_foldera.at(iNewItem) = folder;

               pdataitemChild = pdataitemParent->get_child_by_user_data(iNewItem);

               if(pdataitemChild == NULL)
               {
                  pdataitemChild = insert_item(new ::data::simple_item(this), ::data::RelativeLastChild, pdataitemParent);
               }

               if(pdataitemChild->m_pitem == NULL)
               {
                  pdataitemChild->m_pitem = new ::data::simple_item(this);
               }

               pdataitemChild->m_pitem.cast < ::data::simple_item >()->m_str = folder.m_strName;
               pdataitemChild->m_dwUser = iNewItem;

         //      else
            //    {
               //     ptraRemove.remove_first(pdataitemChild);
               //}


               m_foldera.add(new Folder(folder));
               iNode++;
            }

         }


         sp(::data::tree_item) tree::FindTreeItem(int64_t iFolder)
         {
            int32_t iUser;

            if(iFolder < 0)
               return NULL;

            iUser = m_foldera.FindAbsolute(iFolder);
            if(iUser >= 0)
            {
               return get_base_item()->find_next_by_user_data(iUser);
            }
            else
               return NULL;
         }

         int32_t FolderArray::FindAbsolute(int64_t iFolder)
         {
            for(int32_t i = 0; i < this->get_size(); i++)
            {
               if(this->element_at(i)->m_iFolder == iFolder)
                  return i;
            }
            return -1;
         }


         index tree::_001GetItemImage(
            sp(::data::tree_item) pitem,
            bool bSelected
            )
         {
            if(bSelected)
            {
               return m_foldera.element_at(pitem->m_dwUser)->m_iImageSelected;
            }
            else
            {
               return m_foldera.element_at(pitem->m_dwUser)->m_iImage;
            }
         }

         void tree::_001OnItemExpand(::data::tree_item * pitem, ::action::context actioncontext)
         {

            m_pserver->open_folder(m_foldera[pitem->m_dwUser].m_iFolder);

         }


      } // namespace simple


   } // namespace library


} // namespace mplite



