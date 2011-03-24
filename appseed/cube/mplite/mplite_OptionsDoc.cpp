#include "StdAfx.h"
#include "OptionsDoc.h"


OptionsDoc::OptionsDoc(::ca::application * papp) :
   ca(papp),
   ::ca::data_container(papp),
   ::document(papp),
   ::userbase::document(papp),
   ::fs::document(papp),
   ::filemanager::document(papp)
{
   m_pfsdata = System.fs();
}

BOOL OptionsDoc::on_new_document()
{
   if (!::userbase::document::on_new_document())
      return FALSE;
   return TRUE;
}

OptionsDoc::~OptionsDoc()
{
}

#ifdef _DEBUG
void OptionsDoc::assert_valid() const
{
   ::userbase::document::assert_valid();
}

void OptionsDoc::dump(dump_context & dumpcontext) const
{
   ::userbase::document::dump(dumpcontext);
}
#endif //_DEBUG

