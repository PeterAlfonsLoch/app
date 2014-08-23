#include "framework.h"


namespace simpledb
{


   base::base(sp(::aura::application) papp) :
      element(papp),
      m_spfileMeta(papp),
      m_xmldocumentMeta(papp)
   {
   }

   int32_t base::connect()
   {
      string strMetaPath;

      strMetaPath = System.dir().element("database/" + db, "meta.xml");

      try
      {
         if(!m_spfileMeta->open(strMetaPath, ::file::type_binary | ::file::mode_read_write | ::file::share_exclusive))
            return DB_ERROR;
      }
      catch(...)
      {
         strMetaPath = System.dir().appdata("database/" + db, "meta.xml");
         try
         {
            if(!m_spfileMeta->open(strMetaPath, ::file::type_binary | ::file::mode_read_write | ::file::share_exclusive))
               return DB_ERROR;
         }
         catch(...)
         {
            return DB_ERROR;
         }
      }

      ::file::input_stream is(m_spfileMeta);

      if(!m_xmldocumentMeta.load(is))
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

   ::simpledb::set * base::create_dataset() const
   {
      return new ::simpledb::set(const_cast < ::simpledb::base * > (this));
   }


   class ::database::set * base::CreateDataset() const
   {
      return create_dataset();
   }

   int32_t base::setErr(int32_t err_code)
   {
      m_iErrorCode = err_code;
      return m_iErrorCode;
   }


   long base::nextid(const char* sname)
   {
      UNREFERENCED_PARAMETER(sname);
      if (!active)
         return DB_UNEXPECTED_RESULT;
      /*int32_t id;
      database::result_set res;
      char sqlcmd[512];
      sprintf(sqlcmd,"select nextid from %s where seq_name = '%s'",sequence_table, sname);
      if(last_err = sqlite3_exec((::sqlite3::sqlite3 *) getHandle(),sqlcmd,&callback,&res,NULL) != SQLITE_OK)
      {
         return DB_UNEXPECTED_RESULT;
      }
      if (res.records.get_size() == 0)
      {
         id = 1;
         sprintf(sqlcmd,"insert into %s (nextid,seq_name) values (%d,'%s')",sequence_table,id,sname);
         if (last_err = sqlite3_exec((::sqlite3::sqlite3 *) conn,sqlcmd,NULL,NULL,NULL) != SQLITE_OK) return DB_UNEXPECTED_RESULT;
         return id;
      }
      else
      {
         id = res.records[0][0].int32()+1;
         sprintf(sqlcmd,"update %s set nextid=%d where seq_name = '%s'",sequence_table,id,sname);
         if (last_err = sqlite3_exec((::sqlite3::sqlite3 *) conn,sqlcmd,NULL,NULL,NULL) != SQLITE_OK) return DB_UNEXPECTED_RESULT;
         return id;
      }*/
      return DB_UNEXPECTED_RESULT;
   }

} // namespace simpledb
