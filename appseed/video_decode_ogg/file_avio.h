#pragma once


class CLASS_DECL_VIDDEC_OGG file_avio
{
public:


   byte *                  m_puchData;
   DWORD                   m_dwSize;
   ::ex1::filesp           m_spfile;


   file_avio();
   virtual ~file_avio();

   static int read(void * opaque, uint8_t * buf, int buf_size);
   static int write(void * opaque, unsigned char * buf, int buf_size);
   static int64_t seek(void *opaque, int64_t offset, int whence);

//   AVIOContext * alloc_context(::ex1::file * pfile, int iWrite);

};
