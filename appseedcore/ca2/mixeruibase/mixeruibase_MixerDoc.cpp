#include "StdAfx.h"
#include "MixerDoc.h"


MixerDoc::MixerDoc(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::document(papp),
   ::userbase::document(papp)
{
}

BOOL MixerDoc::on_new_document()
{

   if(!::userbase::document::on_new_document())
      return FALSE;

   return TRUE;
}

MixerDoc::~MixerDoc()
{

}


 // BEGIN_MESSAGE_MAP(MixerDoc, ::userbase::document)
   //{{AFX_MSG_MAP(MixerDoc)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MixerDoc diagnostics

#ifdef _DEBUG
void MixerDoc::assert_valid() const
{
   ::userbase::document::assert_valid();
}

void MixerDoc::dump(dump_context & dumpcontext) const
{
   ::userbase::document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MixerDoc serialization
/*
void MixerDoc::Serialize(CArchive& ar)
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
// MixerDoc commands

