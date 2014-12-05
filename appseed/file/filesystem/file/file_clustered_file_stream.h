// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace file
{


   class clustered_input_stream:
      public input_stream
   {
      uint64_t _virtPos;
      uint64_t _physPos;
      uint64_t _curRem;
   public:
      input_stream * Stream;
      uint64_t StartOffset;
      uint64_t Size;
      int32_t BlockSizeLog;
      uint64_array Vector;

      uint64_t SeekToPhys()
      {
         return Stream->seek((file_offset) _physPos, seek_begin);
      }

      uint64_t InitAndSeek()
      {
         _curRem = 0;
         _virtPos = 0;
         _physPos = StartOffset;
         if (Vector.get_size() > 0)
         {
            _physPos = StartOffset + (Vector[0] << BlockSizeLog);
            return SeekToPhys();
         }
         return 0;
      }

      ::primitive::memory_size read(void * data, ::primitive::memory_size size);
      file_position seek(file_offset offset, e_seek seekOrigin);
   };


} // namespace file


