#include "framework.h"


namespace ca
{


   type_info::type_info(id id)
   {
      m_id = id;
      m_pfactoryitem = NULL;
   }

   type_info::type_info()
   {
      m_pfactoryitem = NULL;
   }

   type_info::~type_info()
   {
   }

   type_info::type_info(const type_info * pinfo)
   {
      m_id = pinfo->m_id;
      m_pfactoryitem = pinfo->m_pfactoryitem;
      m_spmutex = pinfo->m_spmutex;
   }

   type_info::type_info(const type_info & info)
   {
      m_id = info.m_id;
      m_pfactoryitem = info.m_pfactoryitem;
      m_spmutex = info.m_spmutex;
   }

   type_info::type_info(const std_type_info & info)
   {
#ifdef WINDOWS
      m_id = info.raw_name();
#else
      m_id = info.name();
#endif
      m_pfactoryitem = NULL;
   }

   type_info::type_info(const std_type_info * pinfo)
   {
#ifdef WINDOWS
      m_id = pinfo->raw_name();
#else
      m_id = pinfo->name();
#endif
      m_pfactoryitem = NULL;
   }

   type_info::type_info(const char * pszRawName)
   {
      m_id = pszRawName;
      m_pfactoryitem = NULL;
   }

   type_info & type_info::operator = (const type_info * pinfo)
   {
      m_id = pinfo->m_id;
      m_pfactoryitem = pinfo->m_pfactoryitem;
      m_spmutex = pinfo->m_spmutex;
      return *this;
   }

   type_info & type_info::operator = (const std_type_info & info)
   {
#ifdef WINDOWS
      m_id = info.raw_name();
#else
      m_id = info.name();
#endif
      return *this;
   }

   type_info & type_info::operator = (::ca::type_info info)
   {
      m_id = info.m_id;
      m_pfactoryitem = info.m_pfactoryitem;
      m_spmutex = info.m_spmutex;
      return *this;
   }

   type_info & type_info::operator = (id id)
   {
      m_id = id;
      return *this;
   }

   type_info & type_info::operator = (const char * psz)
   {
      m_id = psz;
      return *this;
   }

   bool type_info::operator == (::ca::type_info info) const
   {
      return m_id == info.m_id;
   }

   bool type_info::operator != (::ca::type_info info) const
   {
      return m_id != info.m_id;
   }

   bool type_info::operator == (const std_type_info & info) const
   {
      #ifdef WINDOWS
      return m_id == info.raw_name();
      #else
      return m_id == info.name();
      #endif
   }
   bool type_info::operator != (const std_type_info & info) const
   {
       #ifdef WINDOWS
      return m_id != info.raw_name();
      #else
      return m_id != info.name();
      #endif
   }

   bool type_info::operator == (const char * pszRawName) const
   {
      return m_id == pszRawName;
   }
   bool type_info::operator != (const char * pszRawName) const
   {
      return m_id != pszRawName;
   }

   const char * type_info::raw_name() const
   {
      return m_id;
   }

   void type_info::raw_name(const char * pszRawName)
   {
      m_id = pszRawName;
   }

   ptra * type_info::new_ptra()
   {
      return new ptra();
   }


} //  namespace ca


CLASS_DECL_ca bool operator == (const std_type_info & info1, ::ca::type_info info2)
{
   #ifdef WINDOWS
   return !strcmp(info1.raw_name(), info2.raw_name());
   #else
   return !strcmp(info1.name(), info2.raw_name());
   #endif
}

CLASS_DECL_ca bool operator != (const std_type_info & info1, ::ca::type_info info2)
{
   #ifdef WINDOWS
   return !strcmp(info1.raw_name(), info2.raw_name());
   #else
   return !strcmp(info1.name(), info2.raw_name());
   #endif
}

