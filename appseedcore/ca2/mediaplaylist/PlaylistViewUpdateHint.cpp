#include "StdAfx.h"

PlaylistViewUpdateHint::PlaylistViewUpdateHint()
{

}

PlaylistViewUpdateHint::~PlaylistViewUpdateHint()
{

}

int PlaylistViewUpdateHint::GetHint()
{
    return m_iHint;
}

void PlaylistViewUpdateHint::SetHint(int iHint)
{
    m_iHint = iHint;
}

void PlaylistViewUpdateHint::AddAttachableView(::userbase::view *pview)
{
   m_viewpaAttachable.add(pview);
}

void PlaylistViewUpdateHint::GetAttachableViews(base_array < ::userbase::view *, ::userbase::view * > & viewpa)
{
   viewpa = m_viewpaAttachable;
}

bool PlaylistViewUpdateHint::is_type_of(EHint ehint)
{
   return m_iHint == ehint;
}
