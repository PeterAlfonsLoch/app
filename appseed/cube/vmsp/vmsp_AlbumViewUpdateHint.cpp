#include "StdAfx.h"
#include "AlbumViewUpdateHint.h"


AlbumViewUpdateHint::AlbumViewUpdateHint()
{

}
AlbumViewUpdateHint::AlbumViewUpdateHint(AlbumViewUpdateHint & uh)
{
   operator = (uh);
}


AlbumViewUpdateHint::~AlbumViewUpdateHint()
{

}

VMSRESULT AlbumViewUpdateHint::copy(AlbumViewUpdateHint &uh)
{
    m_i     = uh.m_i;
    m_str   = uh.m_str;
    m_iKey  = uh.m_iKey;
    return VMSR_SUCCESS;
}

AlbumViewUpdateHint & AlbumViewUpdateHint::operator =(AlbumViewUpdateHint &uh)
{
   if(this != &uh)
   {
      copy(uh);
   }
   return *this;
}
