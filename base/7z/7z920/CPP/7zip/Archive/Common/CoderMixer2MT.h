// CoderMixer2MT.h

#ifndef __CODER_MIXER2_MT_H
#define __CODER_MIXER2_MT_H

#include "CoderMixer2.h"
#include "../../../Common/MyCom.h"
#include "../../Common/StreamBinder.h"
#include "../../Common/VirtThread.h"

namespace NCoderMixer {

struct CCoder2: public CCoderInfo2, public CVirtThread
{
  HRESULT Result;
  array_ptr_alloc< CMyComPtr<::ex1::reader> > InStreams;
  array_ptr_alloc< CMyComPtr<ISequentialOutStream> > OutStreams;
  base_array<::ex1::reader*> InStreamPointers;
  base_array<ISequentialOutStream*> OutStreamPointers;

  CCoder2(UInt32 numInStreams, UInt32 numOutStreams);
  void SetCoderInfo(const UInt64 **inSizes, const UInt64 **outSizes);
  virtual void Execute();
  void Code(ICompressProgressInfo *progress);
};


/*
  SetBindInfo()
  for each coder
    AddCoder[2]()
  SetProgressIndex(UInt32 coderIndex);
 
  for each file
  {
    ReInit()
    for each coder
      SetCoderInfo
    Code
  }
*/

class CCoderMixer2MT:
  public ICompressCoder2,
  public CCoderMixer2,
  public CMyUnknownImp
{
  CBindInfo _bindInfo;
  array_ptr_alloc<CStreamBinder> _streamBinders;
  int _progressCoderIndex;

  void AddCoderCommon();
  HRESULT Init(::ex1::reader **inStreams, ISequentialOutStream **outStreams);
  HRESULT ReturnIfError(HRESULT code);
public:
  array_ptr_alloc<CCoder2> _coders;
  MY_UNKNOWN_IMP

  STDMETHOD(Code)(::ex1::reader **inStreams,
      const UInt64 **inSizes,
      UInt32 numInStreams,
      ISequentialOutStream **outStreams,
      const UInt64 **outSizes,
      UInt32 numOutStreams,
      ICompressProgressInfo *progress);

  HRESULT SetBindInfo(const CBindInfo &bindInfo);
  void AddCoder(ICompressCoder *coder);
  void AddCoder2(ICompressCoder2 *coder);
  void SetProgressCoderIndex(int coderIndex) {  _progressCoderIndex = coderIndex; }

  void ReInit();
  void SetCoderInfo(UInt32 coderIndex, const UInt64 **inSizes, const UInt64 **outSizes)
    {  _coders[coderIndex].SetCoderInfo(inSizes, outSizes); }
  UInt64 GetWriteProcessedSize(UInt32 binderIndex) const
    {  return _streamBinders[binderIndex].ProcessedSize; }
};

}
#endif
