#include "StdAfx.h"


MainDoc::MainDoc(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::document(papp),
   ::userbase::document(papp)
{
}

BOOL MainDoc::on_new_document()
{
   if (!::userbase::document::on_new_document())
      return FALSE;

   update_all_views(NULL, 0);

   return TRUE;
}

MainDoc::~MainDoc()
{
}

#ifdef _DEBUG
void MainDoc::assert_valid() const
{
   ::userbase::document::assert_valid();
}

void MainDoc::dump(dump_context & dumpcontext) const
{
   ::userbase::document::dump(dumpcontext);
}
#endif //_DEBUG

bool MainDoc::on_open_document(var varFile)
{
   devedge::application_interface * papp = dynamic_cast < devedge::application_interface * > (get_app());
   return papp->m_ptemplate_devedge->open_document_file(varFile) != NULL;
}


BOOL MainDoc::on_save_document(const char * lpszPathName)
{
   UNREFERENCED_PARAMETER(lpszPathName);
   return TRUE;
}