#include "StdAfx.h"
#include "CDDeviceListView.h"
#include "CDBrowseDoc.h"

CDDeviceListView::CDDeviceListView(::ca::application * papp) :
   ca(papp),
   ::user::form(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::user::list(papp),
   ::user::form_list(papp),
   ::userbase::form_list(papp),
   simple_list_view(papp)
{
}

CDDeviceListView::~CDDeviceListView()
{
}


 // BEGIN_MESSAGE_MAP(CDDeviceListView, simple_list_view)
   //{{AFX_MSG_MAP(CDDeviceListView)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDeviceListView drawing

void CDDeviceListView::OnDraw(::ca::graphics * pgraphics)
{
   ::userbase::document* pDoc = get_document();
   // TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDDeviceListView diagnostics

#ifdef _DEBUG
void CDDeviceListView::assert_valid() const
{
   simple_list_view::assert_valid();
}

void CDDeviceListView::dump(dump_context & dumpcontext) const
{
   simple_list_view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDDeviceListView message handlers

bool CDDeviceListView::CacheCDList()
{
/*   CDLIST cdlist;
   GETCDHAND cdh;

   ZeroMemory( &cdlist, sizeof(cdlist) );
   GetCDList( &cdlist );

   if ( cdlist.num == 0 )
      return false;

   ZeroMemory( &cdh, sizeof(cdh) );
   cdh.size     = sizeof(GETCDHAND);
   cdh.ver      = 1;
   cdh.ha       = cdlist.cd[0].ha;
   cdh.tgt      = cdlist.cd[0].tgt;
   cdh.lun      = cdlist.cd[0].lun;
   cdh.readType  = CDR_ANY;      // set for autodetect

   return GetCDHandle( &cdh );*/
   return true;
}

void CDDeviceListView::on_update(::view* pSender, LPARAM lHint, ::radix::object* pHint) 
{
}

index CDDeviceListView::_001GetItemCount()
{
   CCDBrowseDoc * pdoc = (CCDBrowseDoc *) get_document();
   return pdoc->m_cddeviceitema.get_size();
}


bool CDDeviceListView::_001GetItemText(string &str, index iItem, index iSubItem, index iListItem)
{
   //str.Format(L"%d", iItem);
   return true;
}