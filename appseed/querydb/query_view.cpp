#include "StdAfx.h"
#include "query_view.h"
#include "html/html_view.h"
#include "html/html_document.h"

namespace querydb
{

   query_view::query_view(::ca::application * papp) :
      ca(papp),
      ::userbase::split_layout(papp),
         ::userbase::view(papp),
      ::userbase::split_view(papp),
      ::userex::split_view(papp),
      place_holder_container(papp)
   {
      m_pdocStartMenu = NULL;
      m_etranslucency      = TranslucencyPresent;


   }

   query_view::~query_view()
   {
   }




   #ifdef _DEBUG
   void query_view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void query_view::dump(dump_context & dumpcontext) const
   {
	   ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // query_view message handlers

   void query_view::_001OnCreate(gen::signal_object * pobj) 
   {
//      SCAST_PTR(::user::win::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

        SetPaneCount(2);

      SetSplitOrientation(orientation_horizontal);
  
      set_position_rate(0, 0.2);

      SetPane(0, ::user::view_creator::create("query_edit_view")->m_pwnd, false, "query_edit_view");
      SetPane(1, ::user::view_creator::create("list_view")->m_pwnd, false, "list_view");

   }

   void query_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      ::userbase::split_view::on_update(pSender, lHint, pHint);

   }


   BOOL query_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;	

	   return ::userbase::view::PreCreateWindow(cs);
   }


   void query_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
//      filemanager::application * pfilemanagerapp = dynamic_cast < filemanager::application * > (get_app());
      if(pcreatordata->m_id == "query_edit_view")
      {
         pcreatordata->m_pdoc = get_document();
         pcreatordata->m_pwnd = create_view(::ca::get_type_info < query_edit_view > ());
      }
      else if(pcreatordata->m_id == "list_view")
      {
         pcreatordata->m_pdoc = get_document();
         pcreatordata->m_pwnd = create_view(::ca::get_type_info < querydb::view > ());
      }


   }

   void query_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userex::split_view::install_message_handling(pinterface);
	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &query_view::_001OnCreate);
   }


   void query_view::OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         int i = (int) ::ShellExecuteW(
            GetTopLevelParent()->_get_handle(), 
            NULL, 
            gen::international::utf8_to_unicode("\"" + itema[0].m_strPath + "\""),
            NULL,
            gen::international::utf8_to_unicode("\"" + System.dir().name(itema[0].m_strPath) + "\""),
            SW_SHOWNORMAL);
         string str;
         str.Format("%d", i);
         //Application.simple_message_box(str);
         if(i == ERROR_FILE_NOT_FOUND)
         {
         }
      }
      GetParentFrame()->ShowWindow(SW_HIDE);
   }



   void query_view::on_show()
   {
      if(m_pdocStartMenu != NULL)
      {
         string strDir = Application.dir().userappdata("querydb\\menu");
         m_pdocStartMenu->FileManagerBrowse(strDir);
      }
   }

} // namespace querydb