// pane_view_update_hint.cpp: implementation of the pane_view_update_hint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pane_view_update_hint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(pane_view_update_hint, base_object)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

pane_view_update_hint::pane_view_update_hint()
{

}

pane_view_update_hint::~pane_view_update_hint()
{

}

bool pane_view_update_hint::IsTypeOf(EType etype)
{
   return m_etype == etype;
}

void pane_view_update_hint::SetType(EType etype)
{
   m_etype = etype;
}
