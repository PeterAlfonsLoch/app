#include "framework.h"


#ifndef WINDOWS


string demangle (const char* name);


#include <cxxabi.h>

string demangle (const char* name)
{
   
   int status = -4;
   char* res = abi::__cxa_demangle(name, 0, 0, &status);
   return (status == 0) ? res : name;
}

#endif


namespace ca
{


   type_info::type_info(const id & id, const class id & idFriendly)
   {

      m_id              = id;
      m_idFriendly      = idFriendly;
      m_pfactoryitem    = NULL;

   }


   type_info::type_info()
   {

      m_pfactoryitem = NULL;

   }

   type_info::~type_info()
   {

   }


   type_info::type_info(const type_info & info)
   {

      m_id              = info.m_id;
      m_idFriendly      = info.m_idFriendly;
      m_pfactoryitem    = info.m_pfactoryitem;
      m_spmutex         = info.m_spmutex;

   }


   type_info::type_info(const std_type_info & info)
   {

#ifdef WINDOWS
      m_idFriendly      = info.name();
      m_id              = info.raw_name();
#elif defined(MACOS)
      m_idFriendly      = demangle(info.name());
      m_id              = info.name();
#else
      m_idFriendly      = demangle(info.name());
      m_id              = info.name();
#endif
      m_pfactoryitem    = NULL;

   }


   type_info::type_info(const string & strName, const string & strFriendlyName)
   {

      m_id              = strName;
      m_idFriendly      = strFriendlyName;
      m_pfactoryitem    = NULL;

   }


   type_info & type_info::operator = (const type_info & info)
   {

      m_id              = info.m_id;
      m_idFriendly      = info.m_idFriendly;
      m_pfactoryitem    = info.m_pfactoryitem;
      m_spmutex         = info.m_spmutex;

      return *this;

   }


   type_info & type_info::operator = (const std_type_info & info)
   {

#ifdef WINDOWS
      m_idFriendly      = info.name();
      m_id              = info.raw_name();
#elif defined(MACOS)
      m_idFriendly      = demangle(info.name());
      m_id              = info.name();
#else
      m_idFriendly      = demangle(info.name());
      m_id              = info.name();
#endif
      m_pfactoryitem    = NULL;
      m_spmutex         = ::ca::null();

      return *this;

   }


   bool type_info::operator == (const ::ca::type_info & info) const
   {

      return m_id == info.m_id;

   }


   bool type_info::operator == (const std_type_info & info) const
   {

      return m_id == info.name();

   }


   bool type_info::operator == (const string & strName) const
   {

      return m_id == strName;

   }


   bool type_info::operator == (const id & id ) const
   {

      return m_id == id ;

   }


   bool type_info::operator != (const ::ca::type_info & info) const
   {

      return m_id != info.m_id;

   }


   bool type_info::operator != (const std_type_info & info) const
   {

      return m_id != info.name();

   }


   bool type_info::operator != (const string & strName) const
   {

      return m_id != strName;

   }


   bool type_info::operator != (const id & id ) const
   {

      return m_id != id ;

   }


   const char * type_info::name() const
   {

      return m_id;

   }

   const char * type_info::friendly_name() const
   {
      
      return m_idFriendly;
      
   }
   

   ptra * type_info::new_ptra()
   {

      return new ptra();

   }


} //  namespace ca


CLASS_DECL_ca bool operator == (const std_type_info & info1, const ::ca::type_info & info2)
{

   return !strcmp(info1.name(), info2.name());

}

CLASS_DECL_ca bool operator != (const std_type_info & info1, const ::ca::type_info & info2)
{

   return !strcmp(info1.name(), info2.name());

}

