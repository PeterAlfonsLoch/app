#include "StdAfx.h"


GoodMixerDoc::GoodMixerDoc(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::document(papp),
   MixerDoc(papp)
{
}

GoodMixerDoc::~GoodMixerDoc()
{
}


#ifdef _DEBUG
void GoodMixerDoc::assert_valid() const
{
   MixerDoc::assert_valid();
}

void GoodMixerDoc::dump(dump_context & dumpcontext) const
{
   MixerDoc::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// GoodMixerDoc commands

/*CRuntimeClass * GoodMixerDoc::GetSliderRuntimeClass()
{
   return &typeid(CSliderV017);
}
*/