#include "StdAfx.h"

namespace sqlite
{
extern int callback(void * res_ptr,int ncol, char** reslt,char** cols);

//************* base implementation ***************

base::base(::ca::application * papp) :
   ca(papp)
{

  active = false;
  _in_transaction = false;      // for transaction

  error = "Unknown database error";//S_NO_CONNECTION;
  host = "localhost";
  port = "";
  db = "sqlite.db";
  login = "root";
  passwd, "";
  conn = NULL;
}

base::~base()
{
  disconnect();
}


database::set * base::CreateDataset() const
{
   return new class set((base*)this);
}

int base::status(void)
{
  if (active == false) return DB_CONNECTION_NONE;
  return DB_CONNECTION_OK;
}

int base::setErr(int err_code)
{
  switch (err_code) {
  case SQLITE_OK: error ="Successful result";
    break;
  case SQLITE_ERROR: error = "SQL error or missing database";
    break;
  case SQLITE_INTERNAL: error = "An internal logic error in SQLite";
    break;
  case SQLITE_PERM: error ="Access permission denied";
    break;
  case SQLITE_ABORT: error = "Callback routine requested an abort";
    break;
  case SQLITE_BUSY: error = "The database file is locked";
    break;
  case SQLITE_LOCKED: error = "A table in the database is locked";
    break;
  case SQLITE_NOMEM: error = "A malloc() failed";
    break;
  case SQLITE_READONLY: error = "Attempt to write a readonly database";
    break;
  case SQLITE_INTERRUPT: error = "Operation terminated by sqlite_interrupt()";
    break;
  case  SQLITE_IOERR: error = "Some kind of disk I/O error occurred";
    break;
  case  SQLITE_CORRUPT: error = "The database disk image is malformed";
    break;
  case SQLITE_NOTFOUND: error = "(Internal Only) Table or record not found";
    break;
  case SQLITE_FULL: error = "Insertion failed because database is full";
    break;
  case SQLITE_CANTOPEN: error = "Unable to open the database file";
    break;
  case SQLITE_PROTOCOL: error = "base lock protocol error";
    break;
  case SQLITE_EMPTY:  error = "(Internal Only) base table is is_empty";
    break;
  case SQLITE_SCHEMA: error = "The database schema changed";
    break;
  case SQLITE_TOOBIG: error = "Too much data for one row of a table";
    break;
  case SQLITE_CONSTRAINT: error = "Abort due to contraint violation";
    break;
  case SQLITE_MISMATCH:  error = "Data type mismatch";
    break;
  default : error = "Undefined SQLite error";
  }
  return err_code;
}

const char *base::getErrorMsg() {
   return error;
}

int base::connect()
{
   disconnect();
   if(sqlite3_open(db, (sqlite3 * *) &conn) == SQLITE_OK)
   {
      //cout << "Connected!\n";
      char* err = NULL;
      if(setErr(sqlite3_exec((sqlite3 *) getHandle(),"PRAGMA empty_result_callbacks=ON",NULL,NULL,&err)) != SQLITE_OK)
      {
         fprintf(stderr,"Error: %s",err);
         throw database::DbErrors(getErrorMsg());
      }
      active = true;
      return DB_CONNECTION_OK;
   }
   return DB_CONNECTION_NONE;
}

void base::disconnect(void) {
  if (active == false) return;
  sqlite3_close((sqlite3 *) conn);
  active = false;
};

int base::create() {
  return connect();
};

int base::drop() {
  if (active == false) return DB_ERROR;
  disconnect();
  if (!_unlink(db))
     return DB_ERROR;
  return DB_COMMAND_OK;
};


long base::nextid(const char* sname) {
  if (!active) return DB_UNEXPECTED_RESULT;
  int id;
  database::result_set res;
  char sqlcmd[512];
  sprintf(sqlcmd,"select nextid from %s where seq_name = '%s'",sequence_table, sname);
  if (last_err = sqlite3_exec((sqlite3 *) getHandle(),sqlcmd,&callback,&res,NULL) != SQLITE_OK) {
    return DB_UNEXPECTED_RESULT;
    }
  if (res.records.get_size() == 0) {
    id = 1;
    sprintf(sqlcmd,"insert into %s (nextid,seq_name) values (%d,'%s')",sequence_table,id,sname);
    if (last_err = sqlite3_exec((sqlite3 *) conn,sqlcmd,NULL,NULL,NULL) != SQLITE_OK) return DB_UNEXPECTED_RESULT;
    return id;
  }
  else {
    id = res.records[0][0].get_integer()+1;
    sprintf(sqlcmd,"update %s set nextid=%d where seq_name = '%s'",sequence_table,id,sname);
    if (last_err = sqlite3_exec((sqlite3 *) conn,sqlcmd,NULL,NULL,NULL) != SQLITE_OK) return DB_UNEXPECTED_RESULT;
    return id;
  }
  return DB_UNEXPECTED_RESULT;
}


// methods for transactions
// ---------------------------------------------
void base::start_transaction() {
  if (active) {
    sqlite3_exec((sqlite3 *) conn,"begin",NULL,NULL,NULL);
    _in_transaction = true;
  }
}

void base::commit_transaction() {
  if (active) {
    sqlite3_exec((sqlite3 *) conn,"commit",NULL,NULL,NULL);
    _in_transaction = false;
  }
}

void base::rollback_transaction() {
  if (active) {
    sqlite3_exec((sqlite3 *) conn,"rollback",NULL,NULL,NULL);
    _in_transaction = false;
  }
}

string base::escape(const char * psz)
{
   string str(psz);
   str.replace("\'", "\'\'");
   str.replace("\"", "\"\"");
   return str;
}

}
