#pragma once


#ifndef WINDOWS


struct win_handle
{

   enum e_type
   {

      type_file,
      type_thread

   };

   e_type m_etype;


   struct file
   {


      FILE * m_pfile;


   };


   struct thread
   {


       pthread_t m_thread;


   };

   union
   {


      file     m_file;
      thread   m_thread;

      
   };



};


#endif


#include "windows_types.h"


#include "windows_gdi.h"


#include "windows_user.h"


#include "windows_thread.h"


#include "windows_ole_automation.h"



