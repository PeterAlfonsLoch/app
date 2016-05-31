//#include "framework.h"

//extern thread_pointer < os_thread > t_posthread;
//extern thread_pointer < hthread > t_hthread;

CLASS_DECL_AURA bool __node_aura_pre_init()
{

   return true;

}


CLASS_DECL_AURA bool __node_aura_pos_init()
{

//   t_hthread = new hthread();
//
//    //t_hthread-
//
//   t_hthread->m_bRun = true;

   return TRUE;

}

void __clear_mq();

CLASS_DECL_AURA bool __node_aura_pre_term()
{
   __clear_mq();
   __node_term_cross_windows_threading();
//   if(t_hthread != NULL)
//   {
//
//      try
//      {
//
//         delete t_hthread;
//
//      }
//      catch(...)
//      {
//
//      }
//
//      t_hthread = NULL;
//
//   }
//
//   hthread::stop_all((1984 + 1977) * 49);

//   finalize_primitive_trace();

   return true;

}





CLASS_DECL_AURA bool __node_aura_pos_term()
{

   return true;

}







::file::path dir::sys_temp()
{



   return ::file::path(getenv("HOME")) / ".ca2tmp";

}


// http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
// http://stackoverflow.com/users/1275169/l3x
int get_proc_stat_core_count()
{

   string str = file_as_string_dup("/proc/stat");

   stringa stra;

   stra.add_lines(str);

   return stra.pred_get_count([](auto str){ return ::str::begins(str, "cpu"); });

}



// http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
// http://stackoverflow.com/users/1275169/l3x
int get_proc_cpuinfo_core_count()
{

   char str[256];

   int procCount = 0;

   FILE *fp;

   if( (fp = fopen("/proc/cpuinfo", "r")) )
   {

      while(fgets(str, sizeof str, fp))
      {

         if( !memcmp(str, "processor", 9) )
         {

            procCount++;

         }

      }

   }

if ( !procCount )
{
printf("Unable to get proc count. Defaulting to 2");
procCount=2;
}

printf("Proc Count:%d\n", procCount);
return 0;
}

int get_processor_count()
{

}



