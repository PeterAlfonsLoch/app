// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace file
{


   class clustered_istream:
      public istream
   {
      uint64_t _virtPos;
      uint64_t _physPos;
      uint64_t _curRem;
   public:
      istream * Stream;
      uint64_t StartOffset;
      uint64_t Size;
      int32_t BlockSizeLog;
      uint64_array Vector;

      uint64_t SeekToPhys()
      {
         return Stream->seek((file_offset_t) _physPos, seek_begin);
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

      memory_size_t read(void * data, memory_size_t size);
      file_position_t seek(file_offset_t offset, e_seek seekOrigin);
   };


} // namespace file


