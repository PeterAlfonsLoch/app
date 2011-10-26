// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace ex1
{

   class limited_input_stream:
      public byte_input_stream
   {
      byte_input_stream *    _stream;
      uint64            _virtPos;
      uint64            _physPos;
      uint64            _size;
      uint64         _startOffset;

      uint64_t SeekToPhys()
      { 
         return _stream->seek((INT_PTR) _physPos, seek_begin); 
      }
   public:
      void SetStream(byte_input_stream *stream)
      { 
         _stream = stream; 
      }

      //HRESULT InitAndSeek(uint64 startOffset, uint64 size)
      uint64_t InitAndSeek(uint64 startOffset, uint64 size)
      {
         _startOffset = startOffset;
         _physPos = startOffset;
         _virtPos = 0;
         _size = size;
         return SeekToPhys();
      }

      ::primitive::memory_size read(void * data, ::primitive::memory_size size);
      file_position seek(file_offset offset, e_seek seekOrigin);

   };

   reader * create_limited_input_stream(byte_input_stream *inStream, uint64 pos, uint64 size);

} // namespace ex1