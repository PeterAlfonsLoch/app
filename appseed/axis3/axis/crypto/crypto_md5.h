#pragma once


typedef struct MD5state_st MD5_CTX;

namespace crypto
{


   namespace md5
   {


      class CLASS_DECL_BASE context :
         public object
      {
      public:

#if defined METROWIN && defined(__cplusplus_winrt)

         class os_data
         {
         public:

            ::Windows::Security::Cryptography::Core::CryptographicHash ^ m_hash;


         };


#else

         class os_data;

#endif

         bool                    m_bEnd;

         ::primitive::memory     m_memoryDigest;

#if defined METROWIN

         os_data * m_posdata;

#else
         MD5_CTX *                m_pctx;

#endif

         context(sp(::base::application) papp);
         virtual ~context();

         void update(const void * data, size_t size);

         void get(primitive::memory_base & mem);

         string to_hex(); // 32 characters

         void defer_finalize();

         void reset();

      };


   } // namespace md5


} // namespace crypto



