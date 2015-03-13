// LockedStream.h
#pragma once


namespace file
{

   class locked_in_stream
   {
   public:

      
      sp(istream)     _stream;
      critical_section     _criticalSection;


      void Init(istream *stream)
      { 
         _stream = stream; 
      }
      
      ::primitive::memory_size read(file_position startPos, void * data, ::primitive::memory_size size);

   };

   class locked_reader :
      virtual public ::file::reader
   {
   public:


      locked_in_stream *_lockedInStream;
      file_size _pos;


      void Init(locked_in_stream *lockedInStream, file_size startPos)
      {
         _lockedInStream = lockedInStream;
         _pos = startPos;
      }

      ::primitive::memory_size read(void *data, ::primitive::memory_size size);

   };


} // namespace file









