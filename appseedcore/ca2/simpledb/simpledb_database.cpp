#include "StdAfx.h"

namespace simpledb
{

   base::base(::ca::application * papp) :
      ca(papp),
      m_spfileMeta(papp),
      m_nodeMeta(papp)
   {
   }

   int base::connect()
   {
      string strMetaPath;

      strMetaPath = System.dir().ca2("database/" + db, "meta.xml");

      if(!m_spfileMeta->open(strMetaPath, ::ex1::file::type_binary | ::ex1::file::mode_read_write | ::ex1::file::shareExclusive))
         return DB_ERROR;

      if(!m_nodeMeta.load(m_spfileMeta))
         return DB_ERROR;

      return DB_COMMAND_OK;
   }

   table * base::get_table(const char * pszName)
   {
      table * ptable = NULL;
      string strName(pszName);
      strName.make_lower();
      if(!m_mapTable.Lookup(strName, ptable))
      {
         ptable = create_table(strName);
         m_mapTable.set_at(strName, ptable);
      }
      return ptable;
   }

   table * base::create_table(const char * pszName)
   {
      return new table(this, pszName);
   }

   set * base::create_dataset()
   {
      return new ::simpledb::set();
   }

      
} // namespace simpledb