#include "StdAfx.h"

MidiTrackBase::MidiTrackBase(::ca::application * papp) :
   ca(papp)
{

}

MidiTrackBase::~MidiTrackBase()
{

}

bool MidiTrackBase::IsType(e_type e_type)
{
   return get_type() == e_type;
}
