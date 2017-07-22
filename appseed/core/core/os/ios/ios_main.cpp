//
//  ios_main.cpp
//  core
//
//  Created by Camilo Sasuke Tsumanuma on 21/07/17.
//  Copyright © 2017 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "ios_main.h"


int32_t CLASS_DECL_BASE ios_core_main(int32_t argc, char * argv[])
{
   
   if(!defer_core_init())
      return -1;
   
   setlocale(LC_ALL,"");
   
   ui_application_main(argc, argv);
   
   ui_app_run(argc, argv);
   
   defer_core_term();
   
   return 0;
   
   
}
