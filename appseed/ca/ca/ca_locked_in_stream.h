// LockedStream.h
// at sector8J on afternoon of 13/01/2011 - Thursday
#pragma once


namespace ca
{

   class locked_in_stream
   {
   public:

      
      sp(byte_input_stream)     _stream;
      critical_section     _criticalSection;


      void Init(byte_input_stream *stream)
      { 
         _stream = stream; 
      }
      
      ::primitive::memory_size read(file_position startPos, void * data, ::primitive::memory_size size);

   };

   class locked_reader :
      virtual public ::ca::reader
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

} // namespace ca