// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once

namespace ex1
{

   class clustered_input_stream:
      public input_stream
   {
      uint64 _virtPos;
      uint64 _physPos;
      uint32 _curRem;
   public:
      input_stream * Stream;
      uint64 StartOffset;
      uint64 Size;
      int BlockSizeLog;
      uint64_array Vector;

      DWORD_PTR SeekToPhys()
      { 
         return Stream->seek((INT_PTR) _physPos, seek_begin); 
      }

      HRESULT InitAndSeek()
      {
         _curRem = 0;
         _virtPos = 0;
         _physPos = StartOffset;
         if (Vector.get_size() > 0)
         {
            _physPos = StartOffset + (Vector[0] << BlockSizeLog);
            return SeekToPhys();
         }
         return S_OK;
      }

      DWORD_PTR read(void * data, DWORD_PTR size);
      DWORD_PTR seek(INT_PTR offset, e_seek seekOrigin);
   };


} // namespace ex1