#include "framework.h"
#include "sqlite3.h"


namespace sqlite
{
   extern int32_t callback(void * res_ptr,int32_t ncol, char** reslt,char** cols);

   set::set(sp(::aura::application) papp) :
      element(papp),
      ::database::set()
   {
      errmsg      = NULL;
      haveError   = false;
      db          = NULL;
   }


   set::set(base * newDb) :
      element(newDb->get_app()),
      ::database::set(newDb)
   {
      errmsg      = NULL;
      haveError = false;
      db = newDb;
   }

   set::~set()
   {
      //  if(errmsg != NULL)
      //  {
      //      sqlite_free_table(&errmsg);
      // }
   }



   //--------- protected functions implementation -----------------//

   void * set::handle()
   {
      if (db != NULL)
      {
         base* psqdb = dynamic_cast<base*>(db);
         return psqdb->getHandle();
      }
      else return NULL;
   }

   void set::make_query(stringa &_sql)
   {
      string query;

      try
      {

         if(autocommit)
            db->start_transaction();

         if(db == NULL)
            throw database::DbErrors("No base Connection");

         //close();

         for (int32_t i = 0; i <_sql.get_size(); i++)
         {
            query = _sql.element_at(i);
            char* err=NULL;
            set::parse_sql(query);
            //cout << "Executing: "<<query<<"\n\n";
            if (db->setErr(sqlite3_exec((sqlite3 *) this->handle(),query,NULL,NULL,&err))!=SQLITE_OK)
            {
               fprintf(stderr,"Error: %s",err);
               throw database::DbErrors(db->getErrorMsg());
            }
         } // end of for


         if(db->in_transaction() && autocommit)
            db->commit_transaction();

         active = true;
         ds_state = database::dsSelect;
         refresh();

      } // end of try
      catch(...)
      {
         if (db->in_transaction()) db->rollback_transaction();
      }
   }


   void set::make_insert()
   {
      make_query(insert_sql);
      last();
   }


   void set::make_edit()
   {
      make_query(update_sql);
   }


   void set::make_deletion()
   {
      make_query(delete_sql);
   }


   void set::fill_fields()
   {
      //cout <<"rr "<<result.records.size()<<"|" << frecno <<"\n";
      if ((db == NULL)
      || (result.record_header.get_size() == 0)
      || (result.records.get_size() < frecno))
         return;

      if (fields_object.get_size() == 0) // Filling columns name
      {
         fields_object.set_size(result.record_header.get_size());
         edit_object.set_size(result.record_header.get_size());
         for (int32_t i = 0; i < result.record_header.get_size(); i++)
         {
            fields_object[i].m_properties    = result.record_header[i];
            edit_object[i].m_properties      = result.record_header[i];
         }
      }

      //Filling result
      if (result.records.get_size() != 0)
      {
         for (int32_t i = 0; i < result.records[frecno].get_size(); i++)
         {
            fields_object[i].m_value   = result.records[frecno][i];
            edit_object[i].m_value     = result.records[frecno][i];
         }
      }
      else
         for (int32_t i = 0; i < result.record_header.get_size(); i++)
         {
            fields_object[i].m_value = "";
            edit_object[i].m_value = "";
         }

   }

   bool set::exec(const char * sql)
   {
      if (!handle())
      {
         TRACE("vmssqlite::set::exec: No base Connection");
         m_strQueryErrorMessage = "No base Connection";
         m_strDatabaseErrorMessage = "No base Connection";
         return false;
      }
      exec_res.record_header.remove_all();
      exec_res.records.remove_all();
      //if ((strncmp("select",sql,6) == 0) || (strncmp("SELECT",sql,6) == 0))
      if((m_iLastResult = db->setErr(sqlite3_exec((::sqlite3::sqlite3 *) handle(),sql,&callback,&exec_res,&errmsg))) == SQLITE_OK)
      {
         m_strQueryErrorMessage = "";
         m_strDatabaseErrorMessage = "";
         return true;
      }
      else
      {
         m_strQueryErrorMessage = errmsg;
         m_strDatabaseErrorMessage = db->getErrorMsg();
         TRACE("vmssqlite::set::exec: Error %s, %s", errmsg, db->getErrorMsg());
         return false;
      }
   }

   bool set::exec()
   {
      return exec(sql);
   }

   const void * set::getExecRes()
   {
      return &exec_res;
   }


   bool set::query(const char *query)
   {
      if(db == NULL)
      {
         TRACE("set::query: base is not Defined");
         m_strQueryErrorMessage = "base is not defined";
         m_strDatabaseErrorMessage = "base is not defined";
         return false;
      }
      if(dynamic_cast<base*>(db) == NULL)
      {
         TRACE("set::query: base is not valid");
         m_strQueryErrorMessage = "base is not valid";
         m_strDatabaseErrorMessage = "base is not valid";
         return false;
      }
      if(dynamic_cast<base*>(db)->getHandle() == NULL)
      {
         TRACE("set::query: No base connection");
         m_strQueryErrorMessage = "No base Connection";
         m_strDatabaseErrorMessage = "No base Connection";
         return false;
      }
      if(strncmp("select",query,6) != 0)
      {
         TRACE("set::query: Must be select SQL");
         return false;
      }

      close();

      if(db->setErr(sqlite3_exec((::sqlite3::sqlite3 *) handle(),query,&callback,&result,&errmsg)) == SQLITE_OK)
      {
         m_strQueryErrorMessage = "";
         m_strDatabaseErrorMessage = "";
         active = true;
         ds_state = database::dsSelect;
         first();
         return true;
      }
      else
      {
         m_strQueryErrorMessage = errmsg;
         m_strDatabaseErrorMessage = db->getErrorMsg();
         TRACE("set::query: Error: %s, %s", errmsg, db->getErrorMsg());
         return false;
      }
   }

   void set::open(const char * sql)
   {
      set_select_sql(sql);
      open();
   }

   void set::open()
   {
      if (!select_sql.is_empty())
      {
         //cout <<select_sql <<"  open\n\n";
         query(select_sql);
      }
      else
      {
         ds_state = database::dsInactive;
      }
   }


   void set::close()
   {
      ::database::set::close();
      result.record_header.remove_all();
      result.records.remove_all();
      edit_object.remove_all();
      fields_object.remove_all();
      ds_state = database::dsInactive;
      active = false;
   }


   void set::cancel()
   {
      if ((ds_state == database::dsInsert) || (ds_state==database::dsEdit))
      {
         if(result.record_header.get_size())
         {
            ds_state = database::dsSelect;
         }
         else
         {
            ds_state = database::dsInactive;
         }
      }
   }


   ::count set::num_rows()
   {
      return result.records.get_size();
   }


   bool set::eof()
   {
      return feof;
   }


   bool set::bof()
   {
      return fbof;
   }


   void set::first()
   {
      ::database::set::first();
      this->fill_fields();
      //cout << "In first "<< fields_object.size()<<"\n";
   }

   void set::last()
   {
      ::database::set::last();
      fill_fields();
   }

   void set::prev()
   {
      ::database::set::prev();
      fill_fields();
   }

   void set::next()
   {
      ::database::set::next();
      if (!eof())
         fill_fields();
   }


   bool set::seek(index pos)
   {
      if (ds_state == database::dsSelect)
      {
         set::seek(pos);
         fill_fields();
         return true;
      }
      return false;
   }



   long set::nextid(const char *seq_name)
   {
      if(handle())
         return db->nextid(seq_name);
      else
         return DB_UNEXPECTED_RESULT;
   }

   bool set::remove_row()
   {
      if(feof || fbof)
      {
         return false;
      }

      result.records.remove_at(frecno);

      fbof = feof = (num_rows()==0)? true: false;

      return true;
   }

   bool set::SetFieldValue(const char *f_name, const var &value)
   {
      bool found = false;
      if(ds_state == database::dsSelect)
      {
         for (int32_t i=0; i < fields_object.get_size(); i++)
         {
            if(result.record_header[i].name == f_name)
            {
               result.records[frecno][i] = value;
               found = true;
            }
         }
         if (!found)
         {
            throw database::DbErrors("Field not found: %s",f_name);
         }
         return true;
      }
      else
      {
         return set::SetFieldValue(f_name, value);
      }
      throw database::DbErrors("Not in Insert or Edit or Select state");
      //  return false;
   }

   bool set::SetFieldValue(index iFieldIndex, const var &value)
   {
      if(ds_state == database::dsSelect)
      {
         if(iFieldIndex >= 0 && iFieldIndex < result.record_header.get_size())
         {
            result.records[frecno][iFieldIndex] = value;
            return true;
         }
         else
         {
            throw database::DbErrors("Field not found: %d",iFieldIndex);
         }
      }
      else
      {
         ASSERT(FALSE);
         //      return set::SetFieldValue(f_name, value);
      }
      throw database::DbErrors("Not in Insert or Edit or Select state");
      //  return false;
   }

   var & set::FieldValueAt(index iFieldIndex)
   {
      //if(ds_state == dsSelect)
      {
         if(iFieldIndex >= 0 && iFieldIndex < result.record_header.get_size())
         {
            return result.records[frecno][iFieldIndex];
         }
         else
         {
            throw database::DbErrors("Field not found: %d",iFieldIndex);
         }
      }
      //   else
      {
         ASSERT(FALSE);
         //return set::SetFieldValue(f_name, value);

      }
      throw database::DbErrors("Not in Insert or Edit or Select state");
      //  return false;
   }


   int32_t set::GetFieldIndex(const char *f_name)
   {

      for (int32_t i=0; i < fields_object.get_size(); i++)
      {

         if(result.record_header[i].name == f_name)
         {

            return i;

         }

      }

      return -1;

   }


   bool set::find_first(const char * fieldname, var & value)
   {
      int32_t iFound = -1;
      if(ds_state == database::dsSelect)
      {
         int32_t i;
         for(i=0; i < fields_object.get_size(); i++)
            if(result.record_header[i].name == fieldname)
            {
               iFound = i;
               break;
            }
            if (iFound < 0) throw database::DbErrors("Field not found: %s",fieldname);
            ::count iNumRows = num_rows();
            for(i=0; i < iNumRows; i++)
               if(result.records[i][iFound] == value)
               {
                  seek(i);
                  return true;
               }

               return false;
      }
      throw database::DbErrors("not in Select state");
   }

   void set::query_items(stringa & stra, const char * pszSql)
   {
      if(query(pszSql))
      {
         first();
         while(!eof())
         {
            stra.add(FieldValueAt(0).get_string());
            next();
         }
      }
   }


   /**********************************************************************
   * Copyright (ca) 2002, Leo Seib, Hannover
   *
   * Project:CSQLiteDataset C++ Dynamic Library
   * Module: CSQLiteDataset class realisation file
   * Author: Leo Seib      E-Mail: lev@almaty.pointstrike.net
   * begin: 5/04/2002
   *
   * Permission is hereby granted, free of charge, to any person obtaining a copy
   * of this software and associated documentation files (the "Software"), to deal
   * in the Software without restriction, including without limitation the rights
   * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   * copies of the Software, and to permit persons to whom the Software is
   * furnished to do so, subject to the following conditions:
   *
   * The above copyright notice and this permission notice shall be included in
   * all copies or substantial portions of the Software.
   *
   * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
   * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   * THE SOFTWARE.
   *
   **********************************************************************/
   //************* Callback function ***************************

   int32_t callback(void * res_ptr,int32_t ncol, char** reslt,char** cols){

      database::result_set* r = (database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);
      ::count sz = r->records.get_size();

      //if (reslt == NULL ) cout << "EMPTY!!!\n";
      if (r->record_header.get_size() <= 0)
      {
         r->record_header.set_size(ncol, 32);
         for (index i=0; i < ncol; i++)
         {
            r->record_header[i].name = cols[i];
            if(cols[i + ncol] != NULL)
            {
               string str(cols[i + ncol]);
               str.make_lower();
               if(str == "integer")
               {
                  r->record_header[i].type = database::DataTypeLong;
               }
               else if(str == "string")
               {
                  r->record_header[i].type = database::DataTypeString;
               }
               else if(str == "numeric")
               {
                  r->record_header[i].type = database::DataTypeDouble;
               }
            }
         }
      }


      database::record rec;
      var v;

      if (reslt != NULL)
      {
         for (int32_t i=0; i<ncol; i++)
         {
            if (reslt[i] == NULL)
            {
               v = "";
               v.set_type(var::type_null);
            }
            else
            {
               //if(r->record_header[i].type == vmssqlite::DataTypeDouble)
               //{
               // v.SetDouble(strtod(reslt[i], NULL));
               //}
               //if(r->record_header[i].type == vmssqlite::DataTypeLong)
               //{
               // v.SetLong(atoi(reslt[i]));
               //}
               //else
               //{
               // string str;
               //::str::international::utf8_to_unicode(str, reslt[i]);
               v = reslt[i];
               //}
            }
            rec.set_at_grow(i, v);//(long)5;//reslt[i];
         }
         r->records.set_at_grow(sz, rec);
      }
      //cout <<"Fsz:"<<r->record_header.size()<<"\n";
      // cout << "Recs:"<<r->records.size() <<" m_value |" <<reslt<<"|"<<cols<<"|"<<"\n\n";
      return 0;
   }



} // namespace vmssqlite
