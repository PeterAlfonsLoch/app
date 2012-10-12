#include "framework.h"

#if defined(LINUX) || defined(MACOS)
#include <dlfcn.h>
#endif


namespace ex1
{

   HMODULE g_hmoduleOs = NULL;

   application::application()
   {
   }

   application::~application()
   {
   }

typedef  void (* PFN_ca2_factory_exchange)(::ca::application * papp);

   void application::Ex1OnFactoryExchange()
   {
#ifdef WIN32

      System.factory().creatable_large < ::ex1::file_exception > ();

      if(g_hmoduleOs == NULL)
      {
         g_hmoduleOs = ::LoadLibraryA("os.dll");
      }

      if(g_hmoduleOs != NULL)
      {
         PFN_ca2_factory_exchange pfn_ca2_factory_exchange = (PFN_ca2_factory_exchange) ::GetProcAddress(g_hmoduleOs, "ca2_factory_exchange");
         pfn_ca2_factory_exchange(this);
      }

#elif defined(LINUX)
      System.factory().creatable_large < ::ex1::file_exception > ();

      void * pdl = ::dlopen("os.so", RTLD_NOW);
      PFN_ca2_factory_exchange pfn_ca2_factory_exchange = (PFN_ca2_factory_exchange) ::dlsym(pdl, "ca2_factory_exchange");
      pfn_ca2_factory_exchange(this);
#else
      System.factory().creatable_large < ::ex1::file_exception > ();
      
      void * pdl = ::dlopen("os.dylib", RTLD_LOCAL);
      PFN_ca2_factory_exchange pfn_ca2_factory_exchange = (PFN_ca2_factory_exchange) ::dlsym(pdl, "ca2_factory_exchange");
      pfn_ca2_factory_exchange(this);
#endif
   }


   void application::on_request(::ca::create_context * pcreatecontext)
   {
      ::radix::application::on_request(pcreatecontext);
   }


} // namespace ex1
