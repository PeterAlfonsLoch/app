#include "framework.h"

namespace database
{

   axis::axis()
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

   axis::~axis() 
   {
      disconnect();      // Disconnect if connected to axis
   }

   int32_t axis::connectFull(const char *newHost, const char *newPort, const char *newDb, const char *newLogin, const char *newPasswd) 
   {
      host = newHost;
      port = newPort;
      db = newDb;
      login = newLogin;
      passwd = newPasswd;
      return connect();
   }

} // namespace database

