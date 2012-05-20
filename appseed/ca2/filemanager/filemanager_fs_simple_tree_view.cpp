#include "framework.h"


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {


         tree_view::tree_view(::ca::application * papp) :
            ca(papp),
            ::userbase::view(papp),
            ::user::scroll_view(papp),
            ::user::tree(papp)
         {

            m_etranslucency = TranslucencyPresent;


            ::ca::data_container::m_spdata = new ex1::simple_tree_data(get_app());
            if(!::ca::data_container::m_spdata->initialize_data())
               throw simple_exception();
         }

         tree_view::~tree_view()
         {
         }




         #ifdef DEBUG
         void tree_view::assert_valid() const
         {
            ::userbase::view::assert_valid();
         }

         void tree_view::dump(dump_context & dumpcontext) const
         {
            ::userbase::view::dump(dumpcontext);
         }
         #endif //DEBUG


         void tree_view::parse(const char * lpszSource)
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

            ::ex1::tree_item * pdataitemParent;
            ::ex1::tree_item * pdataitemChild;

            pdataitemParent = FindTreeItem(m_iParentFolder);
            if(pdataitemParent == NULL)
            {
               pdataitemParent = get_base_item();
            }

            xml::node::base_array childs(get_app());

            string wstrType;
            Folder folder;
            // method 3: Selected Childs with GetChilds()
            // Result: Person, Person, Person
            index iNode = 0;
            xml::node * pnodeFolder = doc.get_root()->get_child("folder");


   //         xml::node::base_array childs(get_app());

   //         string wstrType;
            // method 3: Selected Childs with GetChilds()
            // Result: Person, Person, Person
   //         index iNode = 0;
            for(int i = 0 ; i < pnodeFolder->get_children_count(); i++)
            {
               xml::node * pnodeItem = pnodeFolder->child_at(i);
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
               m_foldera.element_at(iNewItem) = folder;

               pdataitemChild = pdataitemParent->get_child_by_user_data(iNewItem);

               if(pdataitemChild == NULL)
               {
                  pdataitemChild = create_item(pdataitemParent, ex1::RelativeLastChild);
               }

               if(pdataitemChild->m_pitemdata == NULL)
               {
                  pdataitemChild->m_pitemdata = new ex1::simple_tree_item_data();
               }

               ((ex1::simple_tree_item_data *) pdataitemChild->m_pitemdata)->m_str = folder.m_strName;
               pdataitemChild->m_dwUser = iNewItem;

         //      else
            //    {
               //     ptraRemove.remove_first(pdataitemChild);
               //}


               m_foldera.add(folder);
               iNode++;
            }

            _001SelectItem(FindTreeItem(m_iParentFolder));
            layout();
         }


         ::ex1::tree_item * tree_view::FindTreeItem(__int64 iFolder)
         {
            int iUser;

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

         int FolderArray::FindAbsolute(__int64 iFolder)
         {
            for(int i = 0; i < this->get_size(); i++)
            {
               if(this->element_at(i).m_iFolder == iFolder)
                  return i;
            }
            return -1;
         }


         index tree_view::_001GetItemImage(
            ::ex1::tree_item * pitem,
            bool bSelected
            )
         {
            if(bSelected)
            {
               return m_foldera.element_at(pitem->m_dwUser).m_iImageSelected;
            }
            else
            {
               return m_foldera.element_at(pitem->m_dwUser).m_iImage;
            }
         }

         void tree_view::_001OnItemExpand(::ex1::tree_item *pitem)
         {
            m_pserver->open_folder(m_foldera[pitem->m_dwUser].m_iFolder);
         }

         void tree_view::install_message_handling(::gen::message::dispatch * pdispatch)
         {
            ::userbase::view::install_message_handling(pdispatch);
            ::user::tree::install_message_handling(pdispatch);
         }


         void tree_view::_001OnCreate(gen::signal_object * pobj)
         {
            pobj->previous();
            m_iIconFolderNormal = m_pimagelist->add_matter_icon("mplite/vmskarlib_folder_normal.ico");

            m_iIconFolderSelected = m_pimagelist->add_matter_icon("mplite/vmskarlib_folder_selected.ico");

            m_iIconArtistNormal = m_pimagelist->add_matter_icon("mplite/vmskarlib_artist_normal.ico");

            m_iIconArtistSelected = m_pimagelist->add_matter_icon("mplite/vmskarlib_artist_selected.ico");

         }


      } // namespace simple


   } // namespace library


} // namespace mplite



