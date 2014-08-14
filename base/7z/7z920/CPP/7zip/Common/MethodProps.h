// MethodProps.h

#ifndef __7Z_METHOD_PROPS_H
#define __7Z_METHOD_PROPS_H

#include "../../Common/MyVector.h"

#include "../../Windows/PropVariant.h"

#include "MethodId.h"

struct CProp
{
  PROPID Id;
  NWindows::NCOM::CPropVariant Value;
};

struct method
{
  method_id Id;
  gen::property_set Props;
};

struct method_mode
{
  array_ptr_alloc<method> Methods;
  #ifndef _7ZIP_ST
  UInt32 NumThreads;
  #endif

  method_mode()
      #ifndef _7ZIP_ST
      : NumThreads(1)
      #endif
  {}
  bool is_empty() const { return Methods.is_empty() ; }
};

HRESULT SetMethodProperties(const method &method, const UInt64 *inSizeForReduce, IUnknown *coder);

#endif
