#include "StdAfx.h"

namespace userex
{

   pane_view::pane_view(::ax::application * papp) :
      ax(papp),
      ::userbase::view(papp)
   {
   }

   pane_view::~pane_view()
   {
   }

   bool pane_view::_001OnUpdateCmdUi(cmd_ui * pcmdui)
   {
      for(int i = 0; i < m_menua.get_size(); i++)
      {
         if(pcmdui->m_id == m_menua[i].m_id)
         {
            pcmdui->Enable(TRUE);
            return true;
         }
      }
      return _001OnUpdateCmdUi(pcmdui);
   }

   bool pane_view::_001OnCommand(id id)
   {
      for(int i = 0; i < m_menua.get_size(); i++)
      {
         if(id == m_menua[i].m_id)
         {
            // show_view where??
            return true;
         }
      }
      return ::userbase::view::_001OnCommand(id);
   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      for(int i = 0; i < m_menua.get_size(); i++)
      {
         if(pcreatordata->m_id == m_menua[i].m_id)
         {
            //create_context cc;
            //cc.m_pCurrentDoc = get_document();
            //cc.m_typeinfoNewView = ::ax::get_type_info < ::userbase::menu_list_view > ();

            ::userbase::view * pview = create_view < userbase::view > ();
            if(pview != NULL)
            {
//               ::userbase::menu_list_view * pmenuview = (::userbase::menu_list_view *) pview;
   /* xxx           xml::node node(get_app());
               node.load(Application.file().as_string(Application.dir().matter(
                  "mplite_popup_lyricview.xml")));
               pmenuview->LoadMenu(&node);*/
               pcreatordata->m_pwnd = pview;
            }
            break;
         }
      }
   }

   void pane_view::set_new_pane_info(id id, const char * pszMatter)
   {
      set_menu_info(id, pszMatter, "new_pane");
   }

   void pane_view::set_menu_info(id id, const char * pszMatter, class id idCommand)
   {
      menu * pmenu = NULL;
      for(int i = 0; i < m_menua.get_size(); i++)
      {
         if(m_menua[i].m_id == id)
         {
            pmenu = &m_menua[i];
            break;
         }
      }
      if(pmenu == NULL)
      {
         menu menu;
         menu.m_id = id;
         m_menua.add(menu);
         pmenu = &m_menua[m_menua.get_upper_bound()];
      }
      pmenu->m_strMatter = pszMatter;
      pmenu->m_id = idCommand;
   }


} // m_id userex
