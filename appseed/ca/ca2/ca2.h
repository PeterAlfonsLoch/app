#pragma once


#include "ca2/cubebase/cubebase.h"


namespace cube
{


   class application;
   class cube;


} // namespace cube



#define cubeApp(pcaapp) (*pcaapp->m_pappCube)
#define cubeApplication (cubeApp(get_app()))
#undef App
#define App(pcaapp) cubeApp(pcaapp)



#include "ca2/user/user.h"
#include "ca2/uinteraction/uinteraction.h"
#include "ca2/userbase/userbase.h"
#include "ca2/html/html.h"
#include "ca2/userex/userex.h"

#include "ca2_wait_message_dialog.h"
#include "ca2_message_box.h"
#include "ca2_network_configuration.h"
#include "ca2_keyboard_layout.h"


#include "ca2/fs/fs.h"
#include "ca2/filemanager/filemanager.h"
#include "ca2/fontopus/fontopus.h"
#include "ca2/mail/mail.h"


#include "app/appseed/ca2/hi5/hi5.h"


#include "ca2_application.h"







