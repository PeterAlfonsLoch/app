#include "StdAfx.h"
#include "AlbumDoc.h"

AlbumDoc::AlbumDoc(::ca::application * papp) :
   ca(papp),
   ::ca::data_container(papp),
   ::document(papp),
   ::userbase::document(papp)
{
}


BOOL AlbumDoc::on_new_document()
{
   if (!::userbase::document::on_new_document())
      return FALSE;
   return TRUE;
}

AlbumDoc::~AlbumDoc()
{
}



#ifdef _DEBUG
void AlbumDoc::assert_valid() const
{
   ::userbase::document::assert_valid();
}

void AlbumDoc::dump(dump_context & dumpcontext) const
{
   ::userbase::document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// AlbumDoc serialization

/*
void AlbumDoc::Serialize(CArchive& ar)
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
