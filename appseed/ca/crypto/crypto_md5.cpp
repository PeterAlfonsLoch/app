#include "framework.h"


namespace crypto
{


   namespace md5 
   {


      context::context()
      {

         m_bEnd = false;

#ifdef METROWIN

         ::Windows::Security::Cryptography::Core::HashAlgorithmProvider ^ provider = 
            ::Windows::Security::Cryptography::Core::HashAlgorithmProvider::OpenAlgorithm(
               ::Windows::Security::Cryptography::Core::HashAlgorithmNames::Md5);

         m_hash = provider->CreateHash();

#else
         
         MD5_Init(&m_ctx);

#endif

      }


      void context::update(const void * data, size_t size)
      {

         if(m_bEnd)
            throw "invalid state exception";

#ifdef METROWIN

         m_hash->Append(::Windows::Security::Cryptography::CryptographicBuffer::CreateFromByteArray(ref new Platform::Array < unsigned char, 1U > ((unsigned char *) data, size)));

#else

         size_t pos = 0;

         size_t read;

         while(pos < size)
         {

            read = min(size - pos, 0xffffffffu);

            MD5_Update(&m_ctx, &data[pos], read);

            pos += read;

         }

#endif

      }

      void context::get(void * digest) // 16 bytes - 32 hex characters
      {

         defer_finalize();

         memcpy(digest, m_memoryDigest.get_data(), m_memoryDigest.get_size());

      }


      string context::get() // 16 bytes - 32 hex characters
      {

         defer_finalize();

         return m_meoryDigest.to_hex();

      }

      void context::defer_finalize()
      {

         if(!m_bEnd)
         {

#ifdef METROWIN

            buf.set_os_stream_buffer(m_hash->GetValueAndReset());


#else
         
            MD5_Final(m_memoryDigest.allocate(16), &m_ctx);

#endif

         }

      }

      void context::reset()
      {

         if(!m_bEnd)
         {

#ifdef METROWIN

            m_hash->GetValueAndReset();

#endif

         }

#ifndef METROWIN

         MD5_Init(&m_ctx);

#endif

         m_bEnd = false;

      }

      

   } // namespace md5


} // namespace crypto


