#pragma once

#include "database_definition.h"

namespace database
{

   class set;
   /******************* Class database definition ********************

   represents  connection with database server;

   ******************************************************************/
   class CLASS_DECL_AXIS base :
      virtual public ::object
   {
   public:
      bool     active;
      string   error; // Error description
      string   host, port, db, login, passwd; //Login info
      string   sequence_table; //Sequence table for nextid

      /* constructor */
      base();
      /* destructor */
      virtual ~base();
      virtual class set *CreateDataset() const = 0;
      /* sets a new host name */
      void setHostName(const char *newHost) { host = newHost; }
      /* gets a host name */
      string getHostName() const { return host; }
      /* sets a new port */
      void setPort(const char *newPort) { port = newPort; }
      /* gets a port */
      string getPort() const { return port; }
      /* sets a new database name */
      void setDatabase(const char *newDb) { db = newDb; }
      /* gets a database name */
      string getDatabase() const { return db; }
      /* sets a new login to database */
      void setLogin(const char *newLogin) { login = newLogin; }
      /* gets a login */
      string getLogin() const { return login; }
      /* sets a password */
      void setPasswd(const char *newPasswd) { passwd = newPasswd; }
      /* gets a password */
      string getPasswd() const { return passwd; }
      /* active status is OK state */
      virtual bool isActive() const { return active; }
      /* set new name of sequence table */
      void setSequenceTable(const char *new_seq_table) { sequence_table = new_seq_table; };
      /* get name of sequence table */
      const char *getSequenceTable() { return sequence_table; }


      /* virtual methods that must be overloaded in derived classes */

      virtual int32_t init() { return DB_COMMAND_OK; }
      virtual int32_t status() { return DB_CONNECTION_NONE; }
      virtual int32_t setErr(int32_t err_code)=0;
      virtual const char *getErrorMsg() { return error; }

      virtual int32_t connect() { return DB_COMMAND_OK; }
      virtual int32_t connectFull( const char *newDb, const char *newHost=NULL,
         const char *newLogin=NULL, const char *newPasswd=NULL,const char *newPort=NULL);
      virtual void disconnect() { active = false; }
      virtual int32_t reset() { return DB_COMMAND_OK; }
      using ::request_interface::create;
      virtual int32_t create() { return DB_COMMAND_OK; }
      virtual int32_t drop() { return DB_COMMAND_OK; }
      virtual long nextid(const char* seq_name)=0;

      /* virtual methods for transaction */

      virtual void start_transaction() {};
      virtual void commit_transaction() {};
      virtual void rollback_transaction() {};

      virtual bool in_transaction() {return false;};

   };

} // namespace database

