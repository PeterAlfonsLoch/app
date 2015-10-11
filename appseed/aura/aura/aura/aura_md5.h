#pragma once

/////////////////////////////////////////////////////
//
//    md5 implementation
//    intentional duplication because spa
//    needs md5
//
namespace aura
{


   /////////////////////////////////////////////////////
   //
   //    md5 implementation
   //    intentional duplication because spa
   //    needs md5
   //
   class CLASS_DECL_AURA md5
   {
   public:

      typedef unsigned       int uint4;
      typedef unsigned short int uint2;
      typedef unsigned      char uchar;

      typedef struct
      {
         size_t            lo;
         size_t            hi;
         uint4             a;
         uint4             b;
         uint4             c;
         uint4             d;
         uchar             buffer[64];
         uint4             block[16];
      } context;

      context     m_ctx;
      uchar       m_uchaDigest[16];

      md5();

      void	            initialize();
      void	            update(void * pdata,size_t nInputLen);
      void	            finalize();
      unsigned char *   digest();
      string       to_string();
      void *            body(void *data,uint4 size);

   };


} // namespace aura







