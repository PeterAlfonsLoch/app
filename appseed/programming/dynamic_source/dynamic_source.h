#pragma once


#include "filesystem/fs/fs.h"


#include "axis/net/net_sockets.h"


namespace dynamic_source
{
   
   class script_instance;
   class script_manager;



} // namespace dynamic_source



struct CLASS_DECL_PROGRAMMING file_time
{


#ifdef WINDOWS
   FILETIME                         creation;
   FILETIME                         modified;
#else
   __time_t                         creation;
   __time_t                         access;
   __time_t                         modified;
#endif

   file_time()
   {
      ZERO(creation);
      ZERO(modified);

   }

   bool operator == (const file_time & t) const
   {
      if(&t == this)
         return true;
      return !memcmp(&creation,&t.creation,sizeof(creation))
         && !memcmp(&modified,&t.modified,sizeof(modified));
   }

};

CLASS_DECL_PROGRAMMING void get_file_time(const char * psz,file_time & time);

CLASS_DECL_PROGRAMMING void get_file_time(const char * psz,FILETIME & creation,FILETIME & modified);

inline file_time get_file_time(const char * psz)
{

   file_time time ={};

   get_file_time(psz,time);

   return time;

}

#include "dynamic_source_exit_exception.h"
#include "dynamic_source_session.h"


#include "dynamic_source_script_interface.h"
#include "dynamic_source_script_instance.h"
#include "dynamic_source_script.h"
#include "dynamic_source_script_cache.h"
#include "dynamic_source_script_compiler.h"


#include "dynamic_source_library_class.h"


#include "dynamic_source_httpd_socket.h"


#include "dynamic_source_script_manager.h"




