// pane_view_update_hint.cpp: implementation of the pane_view_update_hint class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "pane_view_update_hint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace loginstartup
{

// IMPLEMENT_DYNAMIC(pane_view_update_hint, base_object)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

pane_view_update_hint::pane_view_update_hint()
{

}

pane_view_update_hint::~pane_view_update_hint()
{

}

bool pane_view_update_hint::is_type_of(etype etype)
{
   return m_etype == etype;
}

void pane_view_update_hint::set_type(etype etype)
{
   m_etype = etype;
}

} // namespace loginstartup