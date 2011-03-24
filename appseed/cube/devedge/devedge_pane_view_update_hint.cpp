#include "StdAfx.h"
#include "pane_view_update_hint.h"


PaneViewUpdateHint::PaneViewUpdateHint()
{

}

PaneViewUpdateHint::~PaneViewUpdateHint()
{

}

bool PaneViewUpdateHint::is_type_of(e_type e_type)
{
   return m_etype == e_type;
}

void PaneViewUpdateHint::set_type(e_type e_type)
{
   m_etype = e_type;
}
