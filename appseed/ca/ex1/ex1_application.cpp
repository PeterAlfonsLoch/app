#include "StdAfx.h"

#if defined(LINUX)
#include <dlfcn.h>
#endif


namespace ex1
{

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

      HMODULE hmodule = ::LoadLibraryA("os.dll");
      PFN_ca2_factory_exchange pfn_ca2_factory_exchange = (PFN_ca2_factory_exchange) ::GetProcAddress(hmodule, "ca2_factory_exchange");
      pfn_ca2_factory_exchange(this);
#elif defined(LINUX)
      System.factory().creatable_large < ::ex1::file_exception > ();

      void * pdl = ::dlopen("os.so", RTLD_NOW);
      PFN_ca2_factory_exchange pfn_ca2_factory_exchange = (PFN_ca2_factory_exchange) ::dlsym(pdl, "ca2_factory_exchange");
      pfn_ca2_factory_exchange(this);
#else
      return NULL; // not implemented... yet!! you may start!!
#endif
   }


   void application::on_request(::ca::create_context * pcreatecontext)
   {
      ::radix::application::on_request(pcreatecontext);
   }


} // namespace ex1
