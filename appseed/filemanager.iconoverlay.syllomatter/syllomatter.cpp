#include "StdAfx.h"


filemanager::iconoverlayer * filemanager_iconoverlayer_create(::ca::application * papp)
{
   return new filemanager::syllomatter::iconoverlayer(papp);
}


void filemanager_iconoverlayer_destroy(filemanager::iconoverlayer * piconoverlayer)
{
   delete piconoverlayer;
}
