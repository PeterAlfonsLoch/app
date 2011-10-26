#include "StdAfx.h"
#include "view.h"
#include <Psapi.h>

namespace querydb
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::user::form(papp),
      ::user::list(papp),
      ::user::form_list(papp),
      ::userbase::form_list(papp),
      simple_list_view(papp)
   {
      LOGFONT lf;
      memset(&lf, 0, sizeof(lf));

      m_etranslucency      = TranslucencyPresent;

      strcpy(lf.lfFaceName, "Verdana");
      lf.lfHeight = 13;
      m_font->CreateFontIndirect(&lf);

      lf.lfHeight = 15;
      lf.lfWeight = 900;

   }

   view::~view()
   {
   }

   void view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::install_message_handling(pinterface);

	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);

   }

#ifdef _DEBUG
   void view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
	   ::userbase::view::dump(dumpcontext);
   }
#endif //_DEBUG

   BOOL view::PreCreateWindow(CREATESTRUCT& cs)
   {
      cs.lpszClass = Application.RegisterWndClass(
		   CS_DBLCLKS |
		   CS_OWNDC,
		   0, 0, 0);
      cs.style &= ~WS_EX_CLIENTEDGE;
	   return ::userbase::view::PreCreateWindow(cs);
   }

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(phint);
      if(lHint == 5432108)
      {
         SetTimer(5432108, 100, NULL);
      }
      else if(lHint == 1234)
      {
         string strQuery;
         strQuery = get_document()->m_strQuery;
         _001UpdateColumns();
         _001OnUpdateItemCount();
      }
   	
   }


   void view::_001InsertColumns()
   {
      
      ::user::list_column column;

      database::result_set * pset = get_document()->m_var["::database::result_set"].ca2 < database::result_set > ();
      if(pset == NULL)
      {
         column.m_uiText = "query";
         column.m_iWidth = 500;
         column.m_iSubItem = 0;

         _001AddColumn(column);
      }
      else
      {
         int iCount = pset->records.get_count();
         if(iCount == 0)
         {
            column.m_uiText = "info";
            column.m_iWidth = 500;
            column.m_iSubItem = 0;

            _001AddColumn(column);
         }
         else
         {
            iCount = pset->records[0].get_count();
            for(int i = 0; i < iCount; i++)
            {
               column.m_uiText = "col" + gen::str::itoa(i);
               column.m_iWidth = 100;
               column.m_iSubItem = i;

               _001AddColumn(column);
            }
         }
      }

   }


   count view::_001GetItemCount()
   {
      database::result_set * pset = get_document()->m_var["::database::result_set"].ca2 < database::result_set > ();
      if(pset == NULL)
         return 1;
      else
         return max(1, pset->records.get_count());
   }

   
   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;

   }

   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }


   void view::_001GetItemText(::user::list_item * pitem)
   {
      simple_list_view::_001GetItemText(pitem);
      if(pitem->m_bOk)
         return;
      database::result_set * pset = get_document()->m_var["::database::result_set"].ca2 < database::result_set > ();
      if(pset == NULL)
      {
         if(pitem->m_iItem == 0 && pitem->m_iSubItem == 0)
         {
            pitem->m_strText = get_document()->m_strQuery;
            pitem->m_bOk = true;
            return;
         }
      }
      else
      {
         int iCount = pset->records.get_count();
         if(iCount == 0)
         {
            if(pitem->m_iItem == 0 && pitem->m_iSubItem == 0)
            {
               pitem->m_strText = "empty result returned";
               pitem->m_bOk = true;
               return;
            }
         }
         else
         {
            if(pitem->m_iItem >= 0 && pitem->m_iItem < pset->records.get_count())
            {
               if(pitem->m_iSubItem >= 0 && pitem->m_iSubItem < pset->records[pitem->m_iItem].get_count())
               {
                  pitem->m_strText = pset->records[pitem->m_iItem][pitem->m_iSubItem].get_string();
                  pitem->m_bOk = true;
                  return;
               }
            }
         }
      }
      pitem->m_bOk = false;
   }


} // namespace querydb