//
//  macos_main.cpp
//  aura
//
//  Created by Carlos Gustavo Cecyn Lundgren on 8/2/15.
//
//

//
//  main.cpp
//  app
//
//  Created by Carlos Gustavo Cecyn Lundgren on 15/05/14.
//  Copyright (c) 2014 Camilo Sasuke Tsumanuma. All rights reserved.
//



uint32_t __run_system_main_param(main_param * pparam)
{
   
   string strCommandLine;
   
   bool bColon = false;
   
   for(int32_t i = 0; i < pparam->argc; i++)
   {
      
      if(i > 0)
      {
         
         strCommandLine += " ";
         
      }
      
      if(strcmp(pparam->argv[i], ":") == 0)
      {
         
         strCommandLine     += ":";
         
         bColon = true;
         
      }
      else if(bColon)
      {
         
         strCommandLine     += pparam->argv[i];
         
         
      }
      else
      {
         
         strCommandLine     += "\"";
         
         strCommandLine     += pparam->argv[i];
         
         strCommandLine     += "\"";
         
      }
      
   }
   
   return __run_system_command_line(strCommandLine);
   
}


uint32_t __run_system_command_line(const char * pszCommandLine)
{
   
   int32_t nReturnCode = 0;
   
   ::aura::system * psystem = create_aura_system();
   
   ::macos::main_init_data * pinitmaindata   = new ::macos::main_init_data;
   
   pinitmaindata->m_hInstance                = NULL;
   
   pinitmaindata->m_hPrevInstance            = NULL;
   
   pinitmaindata->m_strCommandLine           = pszCommandLine;
   
   pinitmaindata->m_vssCommandLine           = pinitmaindata->m_strCommandLine;
   
   pinitmaindata->m_nCmdShow                 = SW_SHOW;
   
   
   psystem->init_main_data(pinitmaindata);
   
   psystem->m_bAutoDelete                    = false;
   
   //MessageBox(NULL, "box1", "box1", MB_ICONINFORMATION);
   
   bool bOk = true;
   
   try
   {
      
      if(psystem->begin_synch())
      {
         
         bOk = true;
         
      }
      
   }
   catch(...)
   {
      
   }
   
   try
   {
      
      if(!bOk)
      {
         
         if(psystem->m_iReturnCode == 0)
         {
            
            return -1;
            
         }
         
         return psystem->m_iReturnCode;
         
      }
      
      
   }
   catch(...)
   {
      
      return -1;
      
   }
   
  
   
   return nReturnCode;
   
   
   
}




