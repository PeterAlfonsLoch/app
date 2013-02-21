#pragma once

#include "gen_byte_stream.h"

namespace gen
{

   class CLASS_DECL_ca output_stream2 :
      virtual public byte_output_stream
   {
   public:
      output_stream2();
      output_stream2(writer * pwriter);
      virtual ~output_stream2();

      output_stream2 & operator << (uchar uch);
      output_stream2 & operator << (uint16_t ui);
      output_stream2 & operator << (int32_t i);
      output_stream2 & operator << (uint32_t ui);
      output_stream2 & operator << (LPCRECT lpcrect);
      output_stream2 & operator << (byte_serializable & serializable);
      output_stream2 & operator << (const char * psz);
      output_stream2 & operator << (const string & str);
   };


}
