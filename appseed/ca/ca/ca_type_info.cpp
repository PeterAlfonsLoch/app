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


   type_info::type_info(const string & strName)
   {

      m_id              = strName;
      m_pfactoryitem    = NULL;

   }


   type_info & type_info::operator = (const type_info & info)
   {

      m_id              = info.m_id;
      m_pfactoryitem    = info.m_pfactoryitem;
      m_spmutex         = info.m_spmutex;

      return *this;

   }


   type_info & type_info::operator = (const std_type_info & info)
   {

      m_id              = info.name();
      m_pfactoryitem    = NULL;
      m_spmutex         = ::ca::null();

      return *this;

   }


   type_info & type_info::operator = (const string & strName)
   {

      m_id              = strName;
      m_pfactoryitem    = NULL;
      m_spmutex         = ::ca::null();

      return *this;

   }


   type_info & type_info::operator = (const id & id)
   {

      m_id              = id;
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


   void type_info::name(const string & strName)
   {

      m_id              = strName;
      m_pfactoryitem    = NULL;
      m_spmutex         = ::ca::null();

   }


   const char * type_info::name() const
   {

      return m_id;

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

