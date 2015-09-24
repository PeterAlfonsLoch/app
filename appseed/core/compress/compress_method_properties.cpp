// MethodProps.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "framework.h"

namespace libcompress
{

   static const uint64_t k_LZMA = 0x030101;
   static const uint64_t k_LZMA2 = 0x21;

   #define IUnknown object

   HRESULT SetMethodProperties(const method &method, const file_size_t *inSizeForReduce, sp(element)coder)
   {
      bool tryReduce = false;
      uint32_t reducedDictionarySize = 1 << 10;
      if (inSizeForReduce != 0 && (method.Id == k_LZMA || method.Id == k_LZMA2))
      {
         for (;;)
         {
            const uint32_t step = (reducedDictionarySize >> 1);
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
            if (reducedDictionarySize >= ((uint32_t)3 << 30))
               break;
            reducedDictionarySize += step;
         }
      }

      {
         ::count numProps = method.Props.get_count();
         smart_pointer < ::libcompress::set_coder_properties_interface > setCoderProperties;
         setCoderProperties = coder;
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
               for (int32_t i = 0; i < numProps; i++)
               {
                  const property &prop = method.Props[i];
                  propIDs.add(atoi(prop.name()));
                  var &value = values[i];
                  value = prop.get_value();
                  // if (tryReduce && prop.Id == NCoderPropID::kDictionarySize && value.vt == VT_UI4 && reducedDictionarySize < value.ulVal)
                  if (tryReduce)
                     if (atoi(prop.name()) == NCoderPropID::kDictionarySize)
                        if (value.is_integer())
                           if (reducedDictionarySize < value.uint32())
                              value = (uint64_t) reducedDictionarySize;
               }
               smart_pointer < ::libcompress::set_coder_properties_interface > setCoderProperties;
               setCoderProperties = coder;
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
      smart_pointer<::libcompress::write_coder_properties_interface> writeCoderProperties;
      coder->QueryInterface(IID_ICompressWriteCoderProperties, (void **)&writeCoderProperties);
      if (writeCoderProperties != NULL)
      {
      CSequentialOutStreamImp *outStreamSpec = new CSequentialOutStreamImp;
      smart_pointer<ISequentialOutStream> outStream(outStreamSpec);
      outStreamSpec->Init();
      RINOK(writeCoderProperties->WriteCoderProperties(outStream));
      size_t size = outStreamSpec->GetSize();
      filterProps.SetCapacity(size);
      memmove(filterProps, outStreamSpec->GetBuffer(), size);
      }
      */
      return S_OK;
   }


} // namespace libcompress
