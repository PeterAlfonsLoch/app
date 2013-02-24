#pragma once


#include "ca/cubebase/cubebase.h"


namespace cube
{


   class application;
   class cube;


} // namespace cube



#define cubeApp(pcaapp) (*pcaapp->m_pappCube)
#define cubeApplication (cubeApp(get_app()))
#undef App
#define App(pcaapp) cubeApp(pcaapp)



#include "ca/user/user.h"
#include "ca/uinteraction/uinteraction.h"
#include "ca/userbase/userbase.h"
#include "ca/html/html.h"
#include "ca/userex/userex.h"

#include "cube_wait_message_dialog.h"
#include "cube_message_box.h"
#include "cube_network_configuration.h"
#include "cube_keyboard_layout.h"


#include "ca/fs/fs.h"
#include "ca/filemanager/filemanager.h"
#include "ca/fontopus/fontopus.h"
#include "ca/mail/mail.h"


#include "app/appseed/ca/hi5/hi5.h"


#include "cube_application.h"


#include "app/appseed/ca/bergedge/bergedge.h"


#include "cube_library.h"


#include "cube_cube.h"







