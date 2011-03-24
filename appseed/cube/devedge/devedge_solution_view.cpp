#include "StdAfx.h"

namespace devedge
{
   solution_view::solution_view(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::user::tree(papp),
      m_scrollbarHorz(papp),
      m_scrollbarVert(papp),
      ex1::tree(papp)
   {
      m_pscrollbarHorz = &m_scrollbarHorz;
      m_pscrollbarVert = &m_scrollbarVert;

      m_pdata = new ex1::simple_tree_data(get_app());
      if(!m_pdata->initialize())
         throw simple_exception();
   }

   void solution_view::load()
   {
      solution_document * pdoc = dynamic_cast < solution_document * > (get_document());
      get_base_item()->delete_descendants();

      m_pitemSolution = create_item(get_base_item(), ex1::RelativeFirstChild);

      ((ex1::simple_tree_item_data *) m_pitemSolution->m_pitemdata)->m_str = System.file().name_(pdoc->get_path_name());
      ((ex1::simple_tree_item_data *) m_pitemSolution->m_pitemdata)->m_str += ", ";
      stringa straAscendants;
      System.file().get_ascendants_name(pdoc->get_path_name(), straAscendants);

      if(straAscendants.get_count() >= 4)
      {
         string str;
         straAscendants.implode(str, "/", 3, min(straAscendants.get_count(), 3));
         ((ex1::simple_tree_item_data *) m_pitemSolution->m_pitemdata)->m_str += str;
      }


      xml::node * pnodeProjects = pdoc->node_get_projects();
      if(pnodeProjects != NULL)
      {
         for(int i = 0; i < pnodeProjects->get_children_count(); i++)
         {
            xml::node * pnodeProject = pnodeProjects->child_at(i);
            if(pnodeProject->m_strName == "project")
            {
               ::ex1::tree_item * pitemProject = create_item(m_pitemSolution, ex1::RelativeLastChild);
               ((ex1::simple_tree_item_data *)pitemProject->m_pitemdata)->m_str = pnodeProject->attr("path");
               devedge::project * pproject = pdoc->m_projecta.add_new();
               pproject->load(pdoc, pnodeProject);
               ::ex1::tree_item * pitemHeaders = create_item(pitemProject, ex1::RelativeLastChild);
               ((ex1::simple_tree_item_data *)pitemHeaders->m_pitemdata)->m_str = "Header Files";
               for(int j = 0; j < pproject->m_headers.get_count(); j++)
               {
                  ::ex1::tree_item * pitemHeader = create_item(pitemHeaders, ex1::RelativeLastChild);
                  ((ex1::simple_tree_item_data *)pitemHeader->m_pitemdata)->m_str = pproject->m_headers[j].m_strName;
               }
               ::ex1::tree_item * pitemSources = create_item(pitemProject, ex1::RelativeLastChild);
               ((ex1::simple_tree_item_data *)pitemSources->m_pitemdata)->m_str = "Source Files";
               for(int j = 0; j < pproject->m_source.get_count(); j++)
               {
                  ::ex1::tree_item * pitemSource = create_item(pitemSources, ex1::RelativeLastChild);
                  ((ex1::simple_tree_item_data *)pitemSource->m_pitemdata)->m_str = pproject->m_source[j].m_strName;
               }
            }
         }
      }


   }

   void solution_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::_001InstallMessageHandling(pinterface);
      ::user::tree::_001InstallMessageHandling(pinterface);
   }

   void solution_view::_001OnOpenItem(::ex1::tree_item * pitem)
   {
      file * pfile = dynamic_cast < file * > (pitem);
      if(pfile != NULL)
      {
         ::user::interaction* puieParent = GetParentFrame()->GetParent();
         pfile->open(puieParent);
         ::userbase::split_layout * psplit = dynamic_cast < ::userbase::split_layout * > (puieParent);
         if(psplit != NULL)
         {
            psplit->get_pane_window(1)->ShowWindow(SW_HIDE);
            psplit->SetPane(1, pfile->m_pdocument->get_edit_view()->GetParentFrame(), false);
            psplit->layout();
         }

      }
   }   
} // namespace devedge