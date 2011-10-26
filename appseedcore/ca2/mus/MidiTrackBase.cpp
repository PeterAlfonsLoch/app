#include "StdAfx.h"

midi_track_base::midi_track_base(::ca::application * papp) :
   ca(papp)
{

}

midi_track_base::~midi_track_base()
{

}

bool midi_track_base::IsType(e_type e_type)
{
   return get_type() == e_type;
}
