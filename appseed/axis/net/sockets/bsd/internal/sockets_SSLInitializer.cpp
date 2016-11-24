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
#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "axis/net/net_sockets.h"


#ifdef HAVE_OPENSSL
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/engine.h>
#include <openssl/conf.h>


#include <openssl/conf.h>



#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

#include <pthread.h>

#endif

#ifdef DEBUG
#define DEB(x) x
#else
#define DEB(x)
#endif

extern void *OPENSSL_UplinkTable[];

extern "C" void SSLInitializer_SSL_locking_function(int32_t mode, int32_t n, const char * file, int32_t line);
extern "C" unsigned long SSLInitializer_SSL_id_function();
extern "C"
#if defined(METROWIN) || defined(LINUX)
void
#else
int
#endif
SSLInitializer_rand_seed(const void * buf, int32_t num);
extern "C" int32_t SSLInitializer_rand_bytes(uchar * buf, int32_t num);
extern "C" void SSLInitializer_rand_cleanup();
extern "C"
extern "C"
#if defined(METROWIN) || defined(LINUX)
void
#else
int
#endif
SSLInitializer_rand_add(const void * buf, int num, double entropy);
extern "C" int32_t SSLInitializer_rand_pseudorand(uchar * buf, int32_t num);
extern "C" int32_t SSLInitializer_rand_status();

#ifdef _UWP
extern "C"
__declspec(dllimport)
void OPENSSL_UplinkAll();
#endif

namespace sockets
{

    static void *(*malloc_func)(size_t) = ace_memory_alloc;
    static void *default_malloc_ex(size_t num, const char *file, int line)
    {
        return malloc_func(num);
    }
    static void *(*malloc_ex_func)(size_t, const char *file, int line)
        = default_malloc_ex;

    static void *(*realloc_func)(void *, size_t) = ace_memory_realloc;
    static void *default_realloc_ex(void *str, size_t num,
        const char *file, int line)
    {
        return realloc_func(str, num);
    }
    static void *(*realloc_ex_func)(void *, size_t, const char *file, int line)
        = default_realloc_ex;
    void default_free_ex(void * p, const char *file, int line) {
       if (p == NULL)
          return;
       ace_memory_free(p);
    }

    void crypto_memory_free_func(void * p)
    {
        if (p == NULL)
            return;
        ace_memory_free(p);
    }
    static void(*free_func)(void *) = crypto_memory_free_func;

    static void *(*malloc_locked_func)(size_t) = ace_memory_alloc;
    static void *default_malloc_locked_ex(size_t num, const char *file, int line)
    {
        return malloc_locked_func(num);
    }
    static void *(*malloc_locked_ex_func)(size_t, const char *file, int line)
        = default_malloc_locked_ex;

    static void(*free_locked_func)(void *) = ace_memory_free;



    /* may be changed as long as 'allow_customize_debug' is set */
    /* XXX use correct function pointer types */
#ifdef CRYPTO_MDEBUG
    /* use default functions from mem_dbg.c */
    static void(*malloc_debug_func)(void *, int, const char *, int, int)
        = CRYPTO_dbg_malloc;
    static void(*realloc_debug_func)(void *, void *, int, const char *, int, int)
        = CRYPTO_dbg_realloc;
    static void(*free_debug_func)(void *, int) = CRYPTO_dbg_free;
    static void(*set_debug_options_func)(long) = CRYPTO_dbg_set_options;
    static long(*get_debug_options_func)(void) = CRYPTO_dbg_get_options;
#else
    /* applications can use CRYPTO_malloc_debug_init() to select above case
    * at run-time */
    static void(*malloc_debug_func)(void *, int, const char *, int, int) = NULL;
    static void(*realloc_debug_func)(void *, void *, int, const char *, int, int)
        = NULL;
    static void(*free_debug_func)(void *, int) = NULL;
    static void(*set_debug_options_func)(long) = NULL;
    static long(*get_debug_options_func)(void) = NULL;
#endif



   map < int32_t, int32_t, mutex *, mutex *>  * g_pmapMutex = NULL;

   mutex * g_pmutexMap = NULL;


#ifdef LINUX
   // ssl_sigpipe_handle ---------------------------------------------------------
   void ssl_sigpipe_handle(int x)
   {
      /* Ignore broken pipes */
   }
#endif


   RAND_METHOD rand_meth;


   ::aura::system * g_psystem = NULL;


   SSLInitializer::SSLInitializer(::aura::application * papp) :
      ::object(papp)
   {

      thisstart;

#ifdef _UWP

      OPENSSL_UplinkAll();

#endif

      CRYPTO_set_mem_functions(&default_malloc_ex, &default_realloc_ex, &default_free_ex);

      m_rand_size = 1024;

      g_psystem = papp->m_paurasystem;

      /* An error write context */

      g_pmapMutex = new map < int32_t, int32_t, mutex *, mutex *>;

      g_pmutexMap = new mutex(get_app());

      thisok << 1;

#if OPENSSL_API_COMPAT < 0x10100000L

      CRYPTO_set_locking_callback(SSLInitializer_SSL_locking_function);
      CRYPTO_set_id_callback(SSLInitializer_SSL_id_function);

      SSL_load_error_strings();
      SSL_library_init();

#endif

      thisok << 2;

      rand_meth.add = &SSLInitializer_rand_add;
      rand_meth.bytes = &SSLInitializer_rand_bytes;
      rand_meth.cleanup = &SSLInitializer_rand_cleanup;
      rand_meth.pseudorand = &SSLInitializer_rand_pseudorand;
      rand_meth.seed = &SSLInitializer_rand_seed;
      rand_meth.status = &SSLInitializer_rand_status;

      RAND_set_rand_method(&rand_meth);

      //ENGINE_load_openssl();
      //ENGINE_load_dynamic();
#ifndef OPENSSL_NO_STATIC_ENGINE
      //ENGINE_load_4758cca();
      //ENGINE_load_aep();
      //ENGINE_load_atalla();
      //ENGINE_load_chil();
      //ENGINE_load_cswift();
      ////ENGINE_load_gmp();
      //ENGINE_load_nuron();
      //ENGINE_load_sureware();
      //ENGINE_load_ubsec();
#endif
      //ENGINE_load_cryptodev();
      //ENGINE_load_builtin_engines();


      /* Ignore broken pipes which would cause our program to terminate
         prematurely */


//      bio_err = BIO_new_fp(stderr, BIO_NOCLOSE);


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

         //memory memstorage;
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

         ::file::buffer_sp spfile(allocer());

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

//      BIO_free(bio_err);

//      bio_err = NULL;
      //ENGINE_cleanup();
      //sk_SSL_COMP_free(SSL_COMP_get_compression_methods());
      //SSL_COMP_free_compression_methods(); .
      //ERR_free_strings();
      //EVP_cleanup();

//      ERR_remove_state(0);



      //EVP_cleanup();

      //ERR_free_strings();

      //CRYPTO_cleanup_all_ex_data();

      //ENGINE_cleanup();

      //CONF_modules_unload(1);

      //CONF_modules_free();

      //sk_SSL_COMP_free(SSL_COMP_get_compression_methods());

      //RAND_cleanup();

      //      TRACE("~SSLInitializer()\n");
            //DeleteRandFile();
            // %! delete mutexes


      if (g_pmapMutex != NULL)
      {

         for (auto i : *g_pmapMutex)
         {

            delete i.m_element2;

         }
         delete g_pmapMutex;

         g_pmapMutex = NULL;
      }

      if (g_pmutexMap != NULL)
      {
         delete g_pmutexMap;

         g_pmutexMap = NULL;
      }

   }


   void SSLInitializer::DeleteRandFile()
   {

      if (m_rand_file.get_length())
      {

         Application.file().del(m_rand_file);

      }

   }


} // namespace sockets

#if OPENSSL_API_COMPAT < 0x10100000L
extern "C" void SSLInitializer_SSL_locking_function(int32_t mode, int32_t n, const char * file, int32_t line)
{

   UNREFERENCED_PARAMETER(file);

   UNREFERENCED_PARAMETER(line);

   synch_lock sl(::sockets::g_pmutexMap);

   mutex * pmutex = NULL;

   if (::sockets::g_pmapMutex != NULL && !::sockets::g_pmapMutex->Lookup(n, pmutex))
   {

      ::sockets::g_pmapMutex->operator [](n) = new mutex(NULL);

      if (!::sockets::g_pmapMutex->Lookup(n, pmutex))
      {

         return;

      }

   }

   if (pmutex == NULL)
   {

      return;

   }

   sl.unlock();

   if (mode & CRYPTO_LOCK)
   {

      pmutex->lock();

   }
   else
   {

      pmutex->unlock();

   }

}

#endif

extern "C" unsigned long SSLInitializer_SSL_id_function()
{

//#ifdef WIN32

   return (unsigned long) ::GetCurrentThreadId();

//#else
//
//   unsigned long ul = (unsigned long)(int_ptr) ::pthread_self();
//
//   return ul;
//
//#endif
//
}

extern "C"
#if defined(METROWIN) || defined(LINUX)
void
#else
int
#endif
SSLInitializer_rand_seed(const void * buf, int32_t num)
{
   UNREFERENCED_PARAMETER(buf);
   UNREFERENCED_PARAMETER(num);
#if defined(METROWIN) || defined(LINUX)
#else
   return 1;
#endif
}

extern "C" int32_t SSLInitializer_rand_bytes(uchar * buf, int32_t num)
{
   ::sockets::g_psystem->math().gen_rand(buf, num);
   return num;
}

extern "C" void SSLInitializer_rand_cleanup()
{
}

extern "C"
#if defined(METROWIN) || defined(LINUX)
void
#else
int
#endif
SSLInitializer_rand_add(const void * buf, int num, double entropy)
{
   UNREFERENCED_PARAMETER(buf);
   UNREFERENCED_PARAMETER(num);
   UNREFERENCED_PARAMETER(entropy);
#if defined(METROWIN) || defined(LINUX)
#else
   return 1;
#endif
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



