// MidiTrackV008.h: interface for the Star350TrackV008 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAR350TRACKV008_H__36745CE8_53E7_4B48_B176_9A86F03D9140__INCLUDED_)
#define AFX_STAR350TRACKV008_H__36745CE8_53E7_4B48_B176_9A86F03D9140__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLASS_DECL_ca Star350TrackV008
{
public:
   Star350TrackV008();
   virtual ~Star350TrackV008();

   Star350TrackV008 & operator =(Star350TrackV008 &eventSrc);
   STAR350CHUNKHDR    m_chunkHeader;    
   base_array<Star350EventV008, Star350EventV008 &> m_events;

};

#endif // !defined(AFX_STAR350TRACKV008_H__36745CE8_53E7_4B48_B176_9A86F03D9140__INCLUDED_)
