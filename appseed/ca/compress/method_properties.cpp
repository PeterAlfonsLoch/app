// MethodProps.cpp
// at Sector8J from 7-zip on afternoon of 14/01/2001 - Friday

#include "StdAfx.h"

/*#include "../../Common/MyCom.h"

#include "../ICoder.h"

#include "MethodProps.h"*/

static const uint64 k_LZMA = 0x030101;
static const uint64 k_LZMA2 = 0x21;

namespace compress
{

   HRESULT SetMethodProperties(const method &method, const file_size *inSizeForReduce, ca::ca *coder)
   {
      bool tryReduce = false;
      uint32 reducedDictionarySize = 1 << 10;
      if (inSizeForReduce != 0 && (method.Id == k_LZMA || method.Id == k_LZMA2))
      {
         for (;;)
         {
            const uint32 step = (reducedDictionarySize >> 1);
            if (reducedDictionarySize >= *inSizeForReduce)
            {
               tryReduce = true;
               break;
            }
            reducedDictionarySize += step;
            if (reducedDictionarySize >= *inSizeForReduce)
            {
               tryReduce = true;
               break;
            }
            if (reducedDictionarySize >= ((uint32)3 << 30))
               break;
            reducedDictionarySize += step;
         }
      }

      {
         count numProps = method.Props.m_propertya.get_size();
         ::ca::smart_pointer<::compress::set_coder_properties_interface> setCoderProperties;
         setCoderProperties = dynamic_cast<::compress::set_coder_properties_interface *>(coder);
         if (setCoderProperties == NULL)
         {
            if (numProps != 0)
               return E_INVALIDARG;
         }
         else
         {
            int_array propIDs;
            var *values = new var[numProps];
            HRESULT res = S_OK;
            try
            {
               for (int i = 0; i < numProps; i++)
               {
                  const gen::property &prop = method.Props.m_propertya[i];
                  propIDs.add(atoi(prop.name()));
                  var &value = values[i];
                  value = prop.get_value();
                  // if (tryReduce && prop.Id == NCoderPropID::kDictionarySize && value.vt == VT_UI4 && reducedDictionarySize < value.ulVal)
                  if (tryReduce)
                     if (atoi(prop.name()) == NCoderPropID::kDictionarySize)
                        if (value.get_integer() == VT_UI4)
                           if (reducedDictionarySize < value.get_ulong())
                              value = reducedDictionarySize;
               }
               ::ca::smart_pointer<::compress::set_coder_properties_interface> setCoderProperties;
               setCoderProperties = dynamic_cast<::compress::set_coder_properties_interface *>(coder);
               res = setCoderProperties->SetCoderProperties(&propIDs.first_element(), values, (uint32_t) numProps);
            }
            catch(...)
            {
               delete []values;
               throw;
            }
            delete []values;
            RINOK(res);
         }
      }

      /*
      CMyComPtr<ICompressWriteCoderProperties> writeCoderProperties;
      coder->QueryInterface(IID_ICompressWriteCoderProperties, (void **)&writeCoderProperties);
      if (writeCoderProperties != NULL)
      {
      CSequentialOutStreamImp *outStreamSpec = new CSequentialOutStreamImp;
      CMyComPtr<ISequentialOutStream> outStream(outStreamSpec);
      outStreamSpec->Init();
      RINOK(writeCoderProperties->WriteCoderProperties(outStream));
      size_t size = outStreamSpec->GetSize();
      filterProps.SetCapacity(size);
      memmove(filterProps, outStreamSpec->GetBuffer(), size);
      }
      */
      return S_OK;
   }

} // namespace compress
