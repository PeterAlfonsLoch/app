#pragma once

class Star350EventV008;

class CLASS_DECL_ca Star350EventBase
{
public:

    enum EventType
    {
        EventTypeMidi                       = 0x00,
        EventTypeMidiTimeSignature          = 0x01,
        EventTypeMidiTempo                  = 0x02,
        EventTypeMidiKeySignature           = 0x03,
        EventTypeMidiSysEx                  = 0x0D,
        EventTypeMidiMeta                   = 0x0F,
        EventTypeText                       = 0x41,
        EventTypeCopyright                  = 0x42,
        EventTypeTrackName                  = 0x43,
        EventTypeInstrumentName             = 0x44,
        EventTypeMidiLyric                  = 0x45,
        EventTypeMarker                     = 0x46,
        EventTypeLyrics                     = 0x10,
        EventTypeLineBreak                  = 0x11,
        EventTypeNextLine                   = 0x12,
        EventTypeImage                      = 0x13,
        EventType123                        = 0x0e
    };

   virtual imedia::position GetDuration() const  = 0;
   virtual void SetDuration(imedia::position tkDelta) = 0;

   virtual int GetStar350Type() const  = 0;
   virtual void SetStar350Type(int iType) = 0;

   virtual WORD GetLyricsOffset() const  = 0;
   virtual void GetLyricsOffset(WORD iOffset) = 0;
    
   virtual WORD GetLyricsCount() const  = 0;
   virtual void GetLyricsCount(WORD iCount) = 0;
   
};   


