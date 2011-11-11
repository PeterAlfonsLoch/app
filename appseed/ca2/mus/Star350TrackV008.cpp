#include "StdAfx.h"

Star350TrackV008::Star350TrackV008()
{

}

Star350TrackV008::~Star350TrackV008()
{

}

Star350TrackV008 & Star350TrackV008::operator =(Star350TrackV008 &eventSrc)
{
    m_chunkHeader    = eventSrc.m_chunkHeader;
    m_events         = eventSrc.m_events;
    return *this;
}