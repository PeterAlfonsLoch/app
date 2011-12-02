#pragma once


#include "ex1_seekable.h"
#include "ca/ca_smart_pointer.h"


namespace ex1
{

   class writer;
   class reader;


   typedef ::ca::smart_pointer < reader > reader_sp;


   class CLASS_DECL_ca reader :
      virtual public seekable
   {
   public:


      ::ex1::reader_sp       m_spreader;


      reader();
      reader(reader * preader);
      reader(const reader & preader);
      virtual ~reader();


      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual file_position find(const void * pFind, ::primitive::memory_size size, const file_position * limit);

      virtual void write(writer & writer);

      reader & operator = (const reader & reader);

      virtual bool is_reader_null();
      virtual bool is_reader_set();

      virtual void close();

      virtual void To(string & str, ::primitive::memory_position iStart = 0, ::primitive::memory_position iEnd = -1);

   };


   typedef reader readable;

} // namespace ex1


