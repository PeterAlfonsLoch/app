// CoderMixer2MT.cpp

#include "StdAfx.h"

#include "CoderMixer2MT.h"

namespace NCoderMixer {

CCoder2::CCoder2(UInt32 numInStreams, UInt32 numOutStreams):
    CCoderInfo2(numInStreams, numOutStreams)
{
  InStreams.Reserve(NumInStreams);
  InStreamPointers.Reserve(NumInStreams);
  OutStreams.Reserve(NumOutStreams);
  OutStreamPointers.Reserve(NumOutStreams);
}

void CCoder2::Execute() { Code(NULL); }

void CCoder2::Code(ICompressProgressInfo *progress)
{
  InStreamPointers.Clear();
  OutStreamPointers.Clear();
  UInt32 i;
  for (i = 0; i < NumInStreams; i++)
  {
    if (InSizePointers[i] != NULL)
      InSizePointers[i] = &InSizes[i];
    InStreamPointers.add((::ex1::reader *)InStreams[i]);
  }
  for (i = 0; i < NumOutStreams; i++)
  {
    if (OutSizePointers[i] != NULL)
      OutSizePointers[i] = &OutSizes[i];
    OutStreamPointers.add((ISequentialOutStream *)OutStreams[i]);
  }
  if (Coder)
    Result = Coder->Code(InStreamPointers[0], OutStreamPointers[0],
        InSizePointers[0], OutSizePointers[0], progress);
  else
    Result = Coder2->Code(&InStreamPointers.Front(), &InSizePointers.Front(), NumInStreams,
      &OutStreamPointers.Front(), &OutSizePointers.Front(), NumOutStreams, progress);
  {
    int i;
    for (i = 0; i < InStreams.get_count(); i++)
      InStreams[i].Release();
    for (i = 0; i < OutStreams.get_count(); i++)
      OutStreams[i].Release();
  }
}

static void SetSizes(const UInt64 **srcSizes, base_array<UInt64> &sizes,
    base_array<const UInt64 *> &sizePointers, UInt32 numItems)
{
  sizes.Clear();
  sizePointers.Clear();
  for (UInt32 i = 0; i < numItems; i++)
  {
    if (srcSizes == 0 || srcSizes[i] == NULL)
    {
      sizes.add(0);
      sizePointers.add(NULL);
    }
    else
    {
      sizes.add(*srcSizes[i]);
      sizePointers.add(&sizes.Back());
    }
  }
}


void CCoder2::SetCoderInfo(const UInt64 **inSizes, const UInt64 **outSizes)
{
  SetSizes(inSizes, InSizes, InSizePointers, NumInStreams);
  SetSizes(outSizes, OutSizes, OutSizePointers, NumOutStreams);
}

//////////////////////////////////////
// CCoderMixer2MT

HRESULT CCoderMixer2MT::SetBindInfo(const CBindInfo &bindInfo)
{
  _bindInfo = bindInfo;
  _streamBinders.Clear();
  for (int i = 0; i < _bindInfo.BindPairs.get_count(); i++)
  {
    _streamBinders.add(CStreamBinder());
    RINOK(_streamBinders.Back().CreateEvents());
  }
  return S_OK;
}

void CCoderMixer2MT::AddCoderCommon()
{
  const CCoderStreamsInfo &c = _bindInfo.Coders[_coders.get_count()];
  CCoder2 threadCoderInfo(c.NumInStreams, c.NumOutStreams);
  _coders.add(threadCoderInfo);
}

void CCoderMixer2MT::AddCoder(ICompressCoder *coder)
{
  AddCoderCommon();
  _coders.Back().Coder = coder;
}

void CCoderMixer2MT::AddCoder2(ICompressCoder2 *coder)
{
  AddCoderCommon();
  _coders.Back().Coder2 = coder;
}


void CCoderMixer2MT::ReInit()
{
  for (int i = 0; i < _streamBinders.get_count(); i++)
    _streamBinders[i].ReInit();
}


HRESULT CCoderMixer2MT::Init(::ex1::reader **inStreams, ISequentialOutStream **outStreams)
{
  /*
  if (_coders.get_count() != _bindInfo.Coders.get_count())
    throw 0;
  */
  int i;
  for (i = 0; i < _coders.get_count(); i++)
  {
    CCoder2 &coderInfo = _coders[i];
    const CCoderStreamsInfo &coderStreamsInfo = _bindInfo.Coders[i];
    coderInfo.InStreams.Clear();
    UInt32 j;
    for (j = 0; j < coderStreamsInfo.NumInStreams; j++)
      coderInfo.InStreams.add(NULL);
    coderInfo.OutStreams.Clear();
    for (j = 0; j < coderStreamsInfo.NumOutStreams; j++)
      coderInfo.OutStreams.add(NULL);
  }

  for (i = 0; i < _bindInfo.BindPairs.get_count(); i++)
  {
    const CBindPair &bindPair = _bindInfo.BindPairs[i];
    UInt32 inCoderIndex, inCoderStreamIndex;
    UInt32 outCoderIndex, outCoderStreamIndex;
    _bindInfo.FindInStream(bindPair.InIndex, inCoderIndex, inCoderStreamIndex);
    _bindInfo.FindOutStream(bindPair.OutIndex, outCoderIndex, outCoderStreamIndex);

    _streamBinders[i].CreateStreams(
        &_coders[inCoderIndex].InStreams[inCoderStreamIndex],
        &_coders[outCoderIndex].OutStreams[outCoderStreamIndex]);

    CMyComPtr<ICompressSetBufSize> inSetSize, outSetSize;
    _coders[inCoderIndex].QueryInterface(IID_ICompressSetBufSize, (void **)&inSetSize);
    _coders[outCoderIndex].QueryInterface(IID_ICompressSetBufSize, (void **)&outSetSize);
    if (inSetSize && outSetSize)
    {
      const UInt32 kBufSize = 1 << 19;
      inSetSize->SetInBufSize(inCoderStreamIndex, kBufSize);
      outSetSize->SetOutBufSize(outCoderStreamIndex, kBufSize);
    }
  }

  for (i = 0; i < _bindInfo.InStreams.get_count(); i++)
  {
    UInt32 inCoderIndex, inCoderStreamIndex;
    _bindInfo.FindInStream(_bindInfo.InStreams[i], inCoderIndex, inCoderStreamIndex);
    _coders[inCoderIndex].InStreams[inCoderStreamIndex] = inStreams[i];
  }
  
  for (i = 0; i < _bindInfo.OutStreams.get_count(); i++)
  {
    UInt32 outCoderIndex, outCoderStreamIndex;
    _bindInfo.FindOutStream(_bindInfo.OutStreams[i], outCoderIndex, outCoderStreamIndex);
    _coders[outCoderIndex].OutStreams[outCoderStreamIndex] = outStreams[i];
  }
  return S_OK;
}

HRESULT CCoderMixer2MT::ReturnIfError(HRESULT code)
{
  for (int i = 0; i < _coders.get_count(); i++)
    if (_coders[i].Result == code)
      return code;
  return S_OK;
}

STDMETHODIMP CCoderMixer2MT::Code(::ex1::reader **inStreams,
      const UInt64 ** /* inSizes */,
      UInt32 numInStreams,
      ISequentialOutStream **outStreams,
      const UInt64 ** /* outSizes */,
      UInt32 numOutStreams,
      ICompressProgressInfo *progress)
{
  if (numInStreams != (UInt32)_bindInfo.InStreams.get_count() ||
      numOutStreams != (UInt32)_bindInfo.OutStreams.get_count())
    return E_INVALIDARG;

  Init(inStreams, outStreams);

  int i;
  for (i = 0; i < _coders.get_count(); i++)
    if (i != _progressCoderIndex)
    {
      RINOK(_coders[i].Create());
    }

  for (i = 0; i < _coders.get_count(); i++)
    if (i != _progressCoderIndex)
      _coders[i].Start();

  _coders[_progressCoderIndex].Code(progress);

  for (i = 0; i < _coders.get_count(); i++)
    if (i != _progressCoderIndex)
      _coders[i].WaitFinish();

  RINOK(ReturnIfError(E_ABORT));
  RINOK(ReturnIfError(E_OUTOFMEMORY));

  for (i = 0; i < _coders.get_count(); i++)
  {
    HRESULT result = _coders[i].Result;
    if (result != S_OK && result != E_FAIL && result != S_FALSE)
      return result;
  }

  RINOK(ReturnIfError(S_FALSE));

  for (i = 0; i < _coders.get_count(); i++)
  {
    HRESULT result = _coders[i].Result;
    if (result != S_OK)
      return result;
  }
  return S_OK;
}

}
