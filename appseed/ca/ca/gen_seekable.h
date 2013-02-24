#pragma once


#include "gen_stream_base.h"


namespace gen
{


   class CLASS_DECL_ca stream_get_size :
      virtual public stream_base
   {
   public:
      virtual int32_t GetSize(uint64_t * psize) const = 0;
   };

   enum e_seek
   {
      seek_begin     = 0x0,
      seek_current   = 0x1,
      seek_end       = 0x2
   };


   class CLASS_DECL_ca seekable :
      virtual public stream_base
   {
   public:

      virtual void seek_to_begin();
      virtual file_position seek_to_end();

      virtual file_position seek(file_offset offset, e_seek seekOrigin);
      virtual file_position get_position() const;

   };


} // namespace gen


