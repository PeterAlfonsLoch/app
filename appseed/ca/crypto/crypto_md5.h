#pragma once


namespace crypto
{


   namespace md5 
   {


      class CLASS_DECL_ca context :
         public ::radix::object
      {
      public:


         bool                    m_bEnd;

         ::primitive::memory     m_memoryDigest;

#ifdef METROWIN

         ::Windows::Security::Cryptography::Core::CryptographicHash ^ m_hash;

#else
         MD5_CTX                 m_ctx;

#endif
      
         context(::ca::application * papp);
         virtual ~context();

         void update(const void * data, size_t size);

         void get(void * digest); // 16 bytes

         string to_hex(); // 32 characters

         void defer_finalize();

         void reset();

      };


   } // namespace md5


} // namespace crypto



