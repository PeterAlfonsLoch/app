/**
 **   \file SSLInitializer.cpp
 **   \date  2007-04-30
 **   \author grymse@alhem.net
**/
/*
Copyright (C) 2007  Anders Hedstrom

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include "base/net/net_sockets.h"
#ifdef HAVE_OPENSSL
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>


#ifdef DEBUG
#define DEB(x) x
#else
#define DEB(x)
#endif

extern "C" void SSLInitializer_SSL_locking_function(int32_t mode, int32_t n, const char * file, int32_t line);
extern "C" unsigned long SSLInitializer_SSL_id_function();
extern "C" void SSLInitializer_rand_seed(const void * buf, int32_t num);
extern "C" int32_t SSLInitializer_rand_bytes(uchar * buf, int32_t num);
extern "C" void SSLInitializer_rand_cleanup();
extern "C" void SSLInitializer_rand_add(const void * buf, int32_t num, double entropy);
extern "C" int32_t SSLInitializer_rand_pseudorand(uchar * buf, int32_t num);
extern "C" int32_t SSLInitializer_rand_status();

namespace sockets
{


   map < int32_t,int32_t,mutex *,mutex *>  * g_pmapMutex = NULL;

   mutex * g_pmutexMap = NULL;


   #ifdef LINUX
// ssl_sigpipe_handle ---------------------------------------------------------
void ssl_sigpipe_handle( int x ) {
    /* Ignore broken pipes */
}
   #endif


   RAND_METHOD rand_meth;

   ::base::system * g_psystem = NULL;



   SSLInitializer::SSLInitializer(sp(::aura::application) papp) :
      element(papp)
   {



      TRACE("SSLInitializer()\n");

      bio_err = NULL;
      m_rand_size = 1024;

      g_psystem = &Sys(papp->m_pbasesystem);

      /* An error write context */
      bio_err = BIO_new_fp(stderr, BIO_NOCLOSE);

      g_pmapMutex = new map < int32_t,int32_t,mutex *,mutex *>;

      g_pmutexMap = new mutex(get_app());

      /* Global system initialization*/
      SSL_library_init();
      SSL_load_error_strings();
      OpenSSL_add_all_algorithms();
      CRYPTO_set_locking_callback(SSLInitializer_SSL_locking_function);
      CRYPTO_set_id_callback(SSLInitializer_SSL_id_function);


 /* Ignore broken pipes which would cause our program to terminate
    prematurely */

      rand_meth.add = &SSLInitializer_rand_add;
      rand_meth.bytes = &SSLInitializer_rand_bytes;
      rand_meth.cleanup = &SSLInitializer_rand_cleanup;
      rand_meth.pseudorand = &SSLInitializer_rand_pseudorand;
      rand_meth.seed = &SSLInitializer_rand_seed;
      rand_meth.status = &SSLInitializer_rand_status;

      RAND_set_rand_method(&rand_meth);



   /*   char *randfile =
      char *home = getenv("HOME");
      if (!randfile && !home)
      {
         char *homepath = getenv("HOMEPATH");
         if (homepath)
         {
            Utility::SetEnv("HOME", homepath);
         }
      }*/

      //primitive::memory memstorage;
      //memstorage.allocate(5000);
      //memstorage.allocate(5000);
      //System.math().gen_rand(memstorage.get_data(), memstorage.get_size());

      /*for(int32_t i = 0; i < memstorage.get_size(); i += 3)
      {
         int32_t iValue = System.math().RandRange(0, 0x00ffffff);
         memstorage.get_data()[i] = iValue & 0xff;
         memstorage.get_data()[i+1] = (iValue >> 8) & 0xff;
         memstorage.get_data()[i+2] = (iValue >> 16) & 0xff;
      }*/

      /*m_rand_file = System.file().time_square();
      //*path = 0;
      //RAND_file_name(path, 512);
      //if (*path)
      //{



      int32_t iWritten = RAND_write_file(m_rand_file);
      m_rand_size = iWritten;
      //}
      //else
      //{
   //TRACE("SSLInitializer: no random file generated\n");
   //   }

      ::file::binary_buffer_sp spfile(allocer());

      spfile->open(m_rand_file, ::file::type_binary | ::file::mode_read);


      //memstorage.FullLoad(spfile);

      /* Load randomness */
      /*if (!m_rand_file.get_length())
      {
   TRACE("SSLInitializer: PRNG not initialized\n");
      }*/
      /*RAND_add(
            memstorage.get_data(),
            memstorage.get_size(),
            memstorage.get_size());*/

      //RAND_seed(memstorage.get_data(), memstorage.get_size());

   }


   SSLInitializer::~SSLInitializer()
   {
//      TRACE("~SSLInitializer()\n");
      //DeleteRandFile();
      // %! delete mutexes


      if(g_pmapMutex != NULL)
      {
         delete g_pmapMutex;

         g_pmapMutex = NULL;
      }

      if(g_pmutexMap != NULL)
      {
         delete g_pmutexMap;

         g_pmutexMap = NULL;
      }

   }


   void SSLInitializer::DeleteRandFile()
   {
      if (m_rand_file.get_length())
      {
         System.file().del(m_rand_file);
      }
   }




} // namespace sockets



   
   extern "C" void SSLInitializer_SSL_locking_function(int32_t mode, int32_t n, const char * file, int32_t line)
   {
      UNREFERENCED_PARAMETER(file);
      UNREFERENCED_PARAMETER(line);


      synch_lock sl(::sockets::g_pmutexMap);
      
      mutex * pmutex;
      if(!::sockets::g_pmapMutex->Lookup(n,pmutex))
      {
         ::sockets::g_pmapMutex->operator [](n) = new mutex(get_thread_app());
      }
      if (mode & CRYPTO_LOCK)
      {
         ::sockets::g_pmapMutex->operator [](n)->lock();
      }
      else
      {
         ::sockets:: g_pmapMutex->operator [](n)->unlock();
      }
   }


   
   extern "C" unsigned long SSLInitializer_SSL_id_function()
   {
#ifdef WIN32
      return ::GetCurrentThreadId();
#else
      return (unsigned long) (int_ptr) ::pthread_self();
#endif
   }

extern "C" void SSLInitializer_rand_seed(const void * buf, int32_t num)
{
  UNREFERENCED_PARAMETER(buf);
  UNREFERENCED_PARAMETER(num);
}

extern "C" int32_t SSLInitializer_rand_bytes(uchar * buf, int32_t num)
{
  ::sockets::g_psystem->math().gen_rand(buf, num);
  return num;
}

extern "C" void SSLInitializer_rand_cleanup()
{
}

extern "C" void SSLInitializer_rand_add(const void * buf, int32_t num, double entropy)
{
  UNREFERENCED_PARAMETER(buf);
  UNREFERENCED_PARAMETER(num);
  UNREFERENCED_PARAMETER(entropy);
}

extern "C" int32_t SSLInitializer_rand_pseudorand(uchar * buf, int32_t num)
{
  ::sockets::g_psystem->math().gen_rand(buf, num);
  return num;
}

extern "C" int32_t SSLInitializer_rand_status()
{
  return 1024;
}


#endif // HAVE_OPENSSL
