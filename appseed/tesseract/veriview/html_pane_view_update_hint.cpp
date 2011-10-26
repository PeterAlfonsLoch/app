// html_pane_view_update_hint.cpp: implementation of the html_pane_view_update_hint class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "html_pane_view_update_hint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// IMPLEMENT_DYNAMIC(html_pane_view_update_hint, base_object)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

html_pane_view_update_hint::html_pane_view_update_hint()
{

}

html_pane_view_update_hint::~html_pane_view_update_hint()
{

}

bool html_pane_view_update_hint::IsTypeOf(EType etype)
{
   return m_etype == etype;
}

void html_pane_view_update_hint::SetType(EType etype)
{
   m_etype = etype;
}
