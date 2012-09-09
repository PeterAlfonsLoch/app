#include "framework.h"


namespace ca
{


   type_info::type_info(const id & id)
   {

      m_id              = id;
      m_pfactoryitem    = NULL;

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

      m_id              = pinfo->m_id;
      m_pfactoryitem    = pinfo->m_pfactoryitem;
      m_spmutex         = pinfo->m_spmutex;

   }


   type_info::type_info(const type_info & info)
   {

      m_id              = info.m_id;
      m_pfactoryitem    = info.m_pfactoryitem;
      m_spmutex         = info.m_spmutex;

   }


   type_info::type_info(const std_type_info & info)
   {

      m_id              = info.name();
      m_pfactoryitem    = NULL;

   }


   type_info::type_info(const std_type_info * pinfo)
   {

      m_id              = pinfo->name();
      m_pfactoryitem    = NULL;

   }


   type_info::type_info(const char * pszRawName)
   {

      m_id              = pszRawName;
      m_pfactoryitem    = NULL;

   }


   type_info & type_info::operator = (const type_info * pinfo)
   {

      m_id              = pinfo->m_id;
      m_pfactoryitem    = pinfo->m_pfactoryitem;
      m_spmutex         = pinfo->m_spmutex;

      return *this;

   }


   type_info & type_info::operator = (const std_type_info & info)
   {

      m_id              = info.name();
      m_pfactoryitem    = NULL;
      m_spmutex         = ::ca::null();

      return *this;

   }


   type_info & type_info::operator = (::ca::type_info info)
   {

      m_id              = info.m_id;
      m_pfactoryitem    = info.m_pfactoryitem;
      m_spmutex         = info.m_spmutex;

      return *this;

   }


   type_info & type_info::operator = (const id & id)
   {

      m_id              = id;
      m_pfactoryitem    = NULL;
      m_spmutex         = ::ca::null();

      return *this;

   }


   type_info & type_info::operator = (const char * psz)
   {

      m_id              = psz;
      m_pfactoryitem    = NULL;
      m_spmutex         = ::ca::null();

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

      return m_id == info.name();

   }


   bool type_info::operator != (const std_type_info & info) const
   {

      return m_id != info.name();

   }


   bool type_info::operator == (const char * pszRawName) const
   {

      return m_id == pszRawName;

   }


   bool type_info::operator != (const char * pszRawName) const
   {

      return m_id != pszRawName;

   }


   const char * type_info::name() const
   {

      return m_id;

   }


   void type_info::name(const char * pszRawName)
   {

      m_id              = pszRawName;
      m_pfactoryitem    = NULL;
      m_spmutex         = ::ca::null();

   }


   ptra * type_info::new_ptra()
   {

      return new ptra();

   }


} //  namespace ca


CLASS_DECL_ca bool operator == (const std_type_info & info1, ::ca::type_info info2)
{

   return !strcmp(info1.name(), info2.name());

}

CLASS_DECL_ca bool operator != (const std_type_info & info1, ::ca::type_info info2)
{

   return !strcmp(info1.name(), info2.name());

}

