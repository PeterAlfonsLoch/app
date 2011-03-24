#include "StdAfx.h"


namespace ca
{
   type_info::type_info(id id)
   {
      m_id = id;
   }

   type_info::type_info()
   {
   }

   type_info::~type_info()
   {
   }

   type_info::type_info(const type_info * pinfo)
   {
      m_id = pinfo->m_id;
   }

   type_info::type_info(const type_info & info)
   {
      m_id = info.m_id;
   }

   type_info::type_info(const std_type_info & info)
   {
      m_id = info.raw_name();
   }
   
   type_info::type_info(const std_type_info * pinfo)
   {
      m_id = pinfo->raw_name();
   }

   type_info::type_info(const char * pszRawName)
   {
      m_id = pszRawName;
   }

   type_info & type_info::operator = (const type_info * pinfo)
   {
      m_id = pinfo->m_id;
      return *this;
   }

   type_info & type_info::operator = (const std_type_info & info)
   {
      m_id = info.raw_name();
      return *this;
   }

   type_info & type_info::operator = (::ca::type_info info)
   {
      m_id = info.m_id;
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
      return m_id == info.raw_name();
   }
   bool type_info::operator != (const std_type_info & info) const
   {
      return m_id != info.raw_name();
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


   CLASS_DECL_ca bool operator == (const std_type_info & info1, ::ca::type_info info2)
   {
      return !strcmp(info1.raw_name(), info2.raw_name());
   }

   CLASS_DECL_ca bool operator != (const std_type_info & info1, ::ca::type_info info2)
   {
      return !strcmp(info1.raw_name(), info2.raw_name());
   }


} //  namespace ca