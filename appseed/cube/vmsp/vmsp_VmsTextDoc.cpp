#include "StdAfx.h"
#include "VmsTextDoc.h"

CVmsTextDoc::CVmsTextDoc(::ca::application * papp) :
   ca(papp),
   ::ca::data_container(papp),
   ::document(papp),
   ::userbase::document(papp)
{
}

BOOL CVmsTextDoc::on_new_document()
{
   if (!::userbase::document::on_new_document())
      return FALSE;
   return TRUE;
}

CVmsTextDoc::~CVmsTextDoc()
{
}



#ifdef _DEBUG
void CVmsTextDoc::assert_valid() const
{
   ::userbase::document::assert_valid();
}

void CVmsTextDoc::dump(dump_context & dumpcontext) const
{
   ::userbase::document::dump(dumpcontext);
}
#endif //_DEBUG


