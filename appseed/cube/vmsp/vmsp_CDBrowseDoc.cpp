#include "StdAfx.h"
#include "CDBrowseDoc.h"


CCDBrowseDoc::CCDBrowseDoc(::ca::application * papp) :
   ca(papp),
   ::ca::data_container(papp),
   ::document(papp),
   ::userbase::document(papp)
{
}

BOOL CCDBrowseDoc::on_new_document()
{
   if (!::userbase::document::on_new_document())
      return FALSE;
   CacheCDList();
   return TRUE;
}

CCDBrowseDoc::~CCDBrowseDoc()
{
}


 // BEGIN_MESSAGE_MAP(CCDBrowseDoc, ::userbase::document)
   //{{AFX_MSG_MAP(CCDBrowseDoc)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDBrowseDoc diagnostics

#ifdef _DEBUG
void CCDBrowseDoc::assert_valid() const
{
   ::userbase::document::assert_valid();
}

void CCDBrowseDoc::dump(dump_context & dumpcontext) const
{
   ::userbase::document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCDBrowseDoc serialization

/*
void CCDBrowseDoc::Serialize(CArchive& ar)
{
   if (ar.IsStoring())
   {
      // TODO: add storing code here
   }
   else
   {
      // TODO: add loading code here
   }
}
*/

/////////////////////////////////////////////////////////////////////////////
// CCDBrowseDoc commands

void CCDBrowseDoc::CacheCDList()
{
   CDLIST cdlist;
   GETCDHAND cdh;

   ZeroMemory( &cdlist, sizeof(cdlist) );
   throw not_implemented_exception();
   // akrip commented
   // GetCDList( &cdlist );

   m_cddeviceitema.remove_all();
   CCDDeviceItem di;
   for(int i = 0; i < cdlist.num; i++)
   {
      ZeroMemory( &di.m_cdhandle, sizeof(di.m_cdhandle) );
      di.m_cdhandle.size     = sizeof(GETCDHAND);
      di.m_cdhandle.ver      = 1;
      di.m_cdhandle.ha       = cdlist.cd[0].ha;
      di.m_cdhandle.tgt      = cdlist.cd[0].tgt;
      di.m_cdhandle.lun      = cdlist.cd[0].lun;
      di.m_cdhandle.readType  = CDR_ANY;      // set for autodetect
      throw not_implemented_exception();
      // akrip commented
      // GetCDHandle( &di.m_cdhandle );
      m_cddeviceitema.add(di);
   }

}
