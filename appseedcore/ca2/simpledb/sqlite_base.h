#pragma once

namespace sqlite
{

   /***************** Class base definition ******************

          class 'base' connects with Sqlite-server

   ******************************************************************/

   class CLASS_DECL_ca base :
      public ::database::base
   {
   protected:
   /* connect descriptor */
     void * conn; // sqlite3 *
     bool _in_transaction;
     int last_err;

   public:
   /* default constructor */
     base(::ca::application * papp);
   /* destructor */
     ~base();

     ::database::set *CreateDataset() const; 

   /* func. returns connection handle with SQLite-server */
     void * getHandle() {  return conn; } // sqlite3 *
   /* func. returns current status about SQLite-server connection */
     virtual int status();
     virtual int setErr(int err_code);
   /* func. returns error message if error occurs */
     virtual const char *getErrorMsg();
     
   /* func. connects to database-server */
     virtual int connect();
   /* func. disconnects from database-server */
     virtual void disconnect();
   /* func. creates new database */
     virtual int create();
   /* func. deletes database */
     virtual int drop();

     virtual long nextid(const char* seq_name);

   /* virtual methods for transaction */

     virtual void start_transaction();
     virtual void commit_transaction();
     virtual void rollback_transaction();

     bool in_transaction() {return _in_transaction;}; 

     string escape(const char * psz);

   };

} // namespace vmssqlite

