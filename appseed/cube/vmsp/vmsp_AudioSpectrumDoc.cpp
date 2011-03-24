#include "StdAfx.h"
#include "AudioSpectrumDoc.h"


AudioSpectrumDoc::AudioSpectrumDoc(::ca::application * papp) :
   ca(papp),
   ::ca::data_container(papp),
   ::document(papp),
   ::userbase::document(papp)
{
}

BOOL AudioSpectrumDoc::on_new_document()
{
   if (!::userbase::document::on_new_document())
      return FALSE;
   return TRUE;
}

AudioSpectrumDoc::~AudioSpectrumDoc()
{
}



#ifdef _DEBUG
void AudioSpectrumDoc::assert_valid() const
{
   ::userbase::document::assert_valid();
}

void AudioSpectrumDoc::dump(dump_context & dumpcontext) const
{
   ::userbase::document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// AudioSpectrumDoc serialization

/*
void AudioSpectrumDoc::Serialize(CArchive& ar)
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
// AudioSpectrumDoc commands
