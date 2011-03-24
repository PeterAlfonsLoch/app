// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace ex1
{

   class limited_input_stream:
      public input_stream
   {
      input_stream *    _stream;
      uint64            _virtPos;
      uint64            _physPos;
      uint64            _size;
      uint64         _startOffset;

      DWORD_PTR SeekToPhys()
      { 
         return _stream->seek((INT_PTR) _physPos, seek_begin); 
      }
   public:
      void SetStream(input_stream *stream)
      { 
         _stream = stream; 
      }

      HRESULT InitAndSeek(uint64 startOffset, uint64 size)
      {
         _startOffset = startOffset;
         _physPos = startOffset;
         _virtPos = 0;
         _size = size;
         return SeekToPhys();
      }

      DWORD_PTR read(void * data, DWORD_PTR size);
      DWORD_PTR seek(INT_PTR offset, e_seek seekOrigin);

   };

   HRESULT CreateLimitedInStream(input_stream *inStream, uint64 pos, uint64 size, reader * * resStream);

} // namespace ex1