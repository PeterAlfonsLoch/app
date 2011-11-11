#pragma once

class XFInfoHeader;
class ::mus::midi::file;
class midi_track;
class midi_event_v008;
class primitive::memory;

class CLASS_DECL_ca midi_event_base
{
public:
   
   static DWORD GetVDWord(byte * hpbImage, DWORD dwLeft, DWORD * pDw);
   static DWORD SetVDWord(byte * hpbImage, DWORD dwLeft,      DWORD dw);

   virtual midi_event_base & operator = (const midi_event_base & eventSrc);
   virtual midi_event_base & operator = (const midi_event_v008 & eventSrc);

   virtual imedia::position GetDelta() const  = 0;
   virtual void SetDelta(imedia::position tkDelta) = 0;
   virtual imedia::position get_position() const = 0;
   virtual void SetPosition(imedia::position tkPosition) =  0;
   virtual BYTE GetFullType() const = 0;
   virtual void SetFullType(BYTE bValue) = 0;
   virtual BYTE get_type() const = 0;
   virtual void set_type(BYTE bValue) = 0;
   virtual BYTE GetTrack() const = 0;
   virtual void SetTrack(BYTE bValue) = 0;
   virtual BYTE GetMetaType() const = 0;
   virtual void SetMetaType(BYTE bValue) = 0;
   virtual BYTE GetChB1() const = 0;
   virtual void SetChB1(BYTE bValue) = 0;
   virtual BYTE GetChB2() const = 0;
   virtual void SetChB2(BYTE bValue) = 0;
   virtual BYTE GetNotePitch() const = 0;
   virtual void SetNotePitch(BYTE bValue) = 0;
   virtual BYTE GetNoteVelocity() const = 0;
   virtual void SetNoteVelocity(BYTE bValue) = 0;

   // Image
   virtual byte * GetImage() const = 0;
   virtual int GetImageSize() const = 0;
   virtual void SetImage(byte * hpbImage) = 0;
   virtual void SetImageSize(int iSize) = 0;

   // Parameter
   virtual byte * GetParam() const = 0;
   virtual int GetParamSize() const = 0;
   virtual void SetParam(void * pVoid, int iSize) = 0;
   virtual void SetParam(primitive::memory & memstorage);
   virtual VMSRESULT SetParam(ex1::file & file, int iLength = -1) = 0;
   
   
   virtual int GetPitchBendLevel() const;
   virtual int GetFlags() const = 0;
   virtual void SetFlags(int iFlag) = 0;
   virtual void clear() = 0;

                                       
                                       
};   
