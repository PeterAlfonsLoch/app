#include "StdAfx.h"
#include "ToolsOptionsSongDirectoriesListView.h"


CToolsOptionsSongDirectoriesListView::CToolsOptionsSongDirectoriesListView(::ca::application * papp) :
   ca(papp),
   ::user::form(papp),
      ::userbase::view(papp),

   ::user::scroll_view(papp),
   ::user::list(papp),
   ::user::form_list(papp),
   ::userbase::form_list(papp),
   simple_list_view(papp)
{
   m_dataid = "ToolsOptionsSongDirectoriesListView";
}

CToolsOptionsSongDirectoriesListView::~CToolsOptionsSongDirectoriesListView()
{
}


 // BEGIN_MESSAGE_MAP(CToolsOptionsSongDirectoriesListView, simple_list_view)
   //{{AFX_MSG_MAP(CToolsOptionsSongDirectoriesListView)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsSongDirectoriesListView drawing

void CToolsOptionsSongDirectoriesListView::OnDraw(::ca::graphics * pgraphics)
{
   ::userbase::document* pDoc = get_document();
   // TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsSongDirectoriesListView diagnostics

#ifdef _DEBUG
void CToolsOptionsSongDirectoriesListView::assert_valid() const
{
   simple_list_view::assert_valid();
}

void CToolsOptionsSongDirectoriesListView::dump(dump_context & dumpcontext) const
{
   simple_list_view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsSongDirectoriesListView message handlers


bool CToolsOptionsSongDirectoriesListView::_001GetItemText(
               string &str,
               index iItem,
               index iSubItem, 
               index iListItem)
{
   if(iSubItem == 0)
   {
      stringa stra;
      db_server *pDataCentral = (db_server *) &System.db();
/*      DBSongDirectorySet *pSet = pDataCentral->GetSongsDirsSet();
      pSet->GetStringArray(stra);

      str = stra[iItem];*/
      return true;
   }
   return false;

}

void CToolsOptionsSongDirectoriesListView::on_update(::view* pSender, LPARAM lHint, ::radix::object* pHint) 
{
   
}

count CToolsOptionsSongDirectoriesListView::_001GetItemCount()
{
   stringa stra;
   db_server *pDataCentral = (db_server *) &System.db();
   //DBSongDirectorySet *pSet = pDataCentral->GetSongsDirsSet();
   //pSet->GetStringArray(stra);

   //return stra.get_size();
   return 0;

}

void CToolsOptionsSongDirectoriesListView::_001InsertColumns()
{
   Column column;
   column.m_iSubItem = 0;
   column.m_iWidth = 400;
   _001AddColumn(column);
}
