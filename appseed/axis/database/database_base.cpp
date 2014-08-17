#include "framework.h"

namespace database
{

   base::base()
   {
      active = false;   // No connection yet
      error = "";//S_NO_CONNECTION;
      host = "";
      port = "";
      db = "";
      login = "";
      passwd = "";
      sequence_table = "db_sequence";
   }

   base::~base() 
   {
      disconnect();      // Disconnect if connected to base
   }

   int32_t base::connectFull(const char *newHost, const char *newPort, const char *newDb, const char *newLogin, const char *newPasswd) 
   {
      host = newHost;
      port = newPort;
      db = newDb;
      login = newLogin;
      passwd = newPasswd;
      return connect();
   }

} // namespace database

