#include "StdAfx.h"
#include "mplite_library_tree_view.h"
#include "mplite_library_view.h"

namespace mplite
{

   namespace library
   {

      tree_view::tree_view(::ca::application * papp) :
         ca(papp),
         ::ca::data_container(papp),
         ::userbase::view(papp),
         ::user::scroll_view(papp),
         ::user::tree(papp),
         m_scrollbarVert(papp),
         m_scrollbarHorz(papp),
         ex1::tree(papp)
      {

         m_pscrollbarVert  = &m_scrollbarVert;
         m_pscrollbarHorz  = &m_scrollbarHorz;

         m_etranslucency = TranslucencyPresent;


         m_pdata = new ex1::simple_tree_data(get_app());
         if(!m_pdata->initialize())
            throw simple_exception();
      }

      tree_view::~tree_view()
      {
      }




      #ifdef _DEBUG
      void tree_view::assert_valid() const
      {
         ::userbase::view::assert_valid();
      }

      void tree_view::dump(dump_context & dumpcontext) const
      {
         ::userbase::view::dump(dumpcontext);
      }
      #endif //_DEBUG


      void tree_view::Parse(const char * lpszParentId, const char * lpszSource)
      {
         string str;
         xml::node xml(get_app());
         if(xml.load(lpszSource))
         {
            str  = xml.get_xml();
         }
         else
         {
            System.simple_message_box(NULL, "error"); // simple parsing error check
            return;
         }

         ::ex1::tree_item * pdataitemParent;
         ::ex1::tree_item * pdataitemChild;

         pdataitemParent = FindTreeItem(lpszParentId);
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
         xml::node * pnode;
         while((pnode = xml.get_child("folder", iNode)) != NULL)
         {
            wstrType = pnode->get_child_value("type");
            folder.m_id = pnode->get_child_value("id");
            folder.m_strTitle = pnode->get_child_value("title");

            if(wstrType == "normal")
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
            }

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

            int iNewItem = m_foldera.FindAbsolute(folder.m_id);
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

            ((ex1::simple_tree_item_data *) pdataitemChild->m_pitemdata)->m_str = folder.m_strTitle;
            pdataitemChild->m_dwUser = iNewItem;

      //      else
         //    {
            //     ptraRemove.remove_first(pdataitemChild);
            //}

            
            m_foldera.add(folder);
            iNode++;
         }

         _001SelectItem(FindTreeItem(lpszParentId));
         layout();
      }


      ::ex1::tree_item * tree_view::FindTreeItem(
         const char * lpszId)
      {
         int iUser;

         if(lpszId == NULL)
            return NULL;

         iUser = m_foldera.FindAbsolute(lpszId);
         if(iUser >= 0)
         {
            return get_base_item()->find_next_by_user_data(iUser);
         }
         else
            return NULL;
      }

      int FolderArray::FindAbsolute(const char * lpszId)
      {
         for(int i = 0; i < get_size(); i++)
         {
            if(element_at(i).m_id == lpszId)
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
         m_pserver->Request(m_foldera[pitem->m_dwUser].m_id);
      }

      void tree_view::_001InstallMessageHandling(::user::win::message::dispatch * pdispatch)
      {
         ::userbase::view::_001InstallMessageHandling(pdispatch);
         ::user::tree::_001InstallMessageHandling(pdispatch);
         InstallBuffering(this);
      }


      void tree_view::_001OnCreate(gen::signal_object * pobj)
      {
         pobj->previous();
         m_iIconFolderNormal = m_pimagelist->add_matter_icon("mplite/vmskarlib_folder_normal.ico");

         m_iIconFolderSelected = m_pimagelist->add_matter_icon("mplite/vmskarlib_folder_selected.ico");

         m_iIconArtistNormal = m_pimagelist->add_matter_icon("mplite/vmskarlib_artist_normal.ico");

         m_iIconArtistSelected = m_pimagelist->add_matter_icon("mplite/vmskarlib_artist_selected.ico");

      }

   } // namespace library

} // namespace mplite