#include "StdAfx.h"
#include <string>
#include "../spares/resource.h"
#include "spalib.h"
#include "dir.h"
#include "file.h"
#include "http1.h"
#include "md5.h"
#include "str.h"
#include "XMLite.h"
#include <shellapi.h>

focus * g_pfocus = NULL;


focus::focus()
{
   m_pnext = NULL;
}