// AlbumViewUpdateHint.cpp: implementation of the MediaLibraryViewUpdateHint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MediaLibraryViewUpdateHint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(MediaLibraryViewUpdateHint, CObject)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MediaLibraryViewUpdateHint::MediaLibraryViewUpdateHint()
{

}

MediaLibraryViewUpdateHint::~MediaLibraryViewUpdateHint()
{

}

bool MediaLibraryViewUpdateHint::IsTypeOf(EType etype)
{
   return m_etype == etype;
}

void MediaLibraryViewUpdateHint::SetType(EType etype)
{
   m_etype = etype;
}

