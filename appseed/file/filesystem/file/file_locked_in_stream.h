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
      
      memory_size_t read(file_position_t startPos, void * data, memory_size_t size);

   };

   class locked_reader :
      virtual public ::file::reader
   {
   public:


      locked_in_stream *_lockedInStream;
      file_size_t _pos;


      void Init(locked_in_stream *lockedInStream, file_size_t startPos)
      {
         _lockedInStream = lockedInStream;
         _pos = startPos;
      }

      memory_size_t read(void *data, memory_size_t size);

   };


} // namespace file









