#pragma once


#ifndef WINDOWS


struct win_handle
{

   enum e_type
   {
      type_file,
      type_thread,
   };

   e_type m_etype;
   union
   {
      struct
      {
         FILE * m_pfile;
      } m_file;
      struct
      {
         pthread_t m_thread;
      } m_thread;
   };



};


#endif


#include "windows_types.h"


#include "windows_gdi.h"


#include "windows_user.h"


#include "windows_thread.h"


#include "windows_ole_automation.h"



