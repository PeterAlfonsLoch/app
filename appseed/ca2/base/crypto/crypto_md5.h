#pragma once


#ifndef METROWIN

#include <openssl/md5.h>

#endif


namespace crypto
{


   namespace md5 
   {


      class CLASS_DECL_ca2 context :
         public object
      {
      public:


         bool                    m_bEnd;

         ::primitive::memory     m_memoryDigest;

#ifdef METROWIN

         ::Windows::Security::Cryptography::Core::CryptographicHash ^ m_hash;

#else
         MD5_CTX                 m_ctx;

#endif
      
         context(sp(base_application) papp);
         virtual ~context();

         void update(const void * data, size_t size);

         void get(primitive::memory_base & mem);

         string to_hex(); // 32 characters

         void defer_finalize();

         void reset();

      };


   } // namespace md5


} // namespace crypto



