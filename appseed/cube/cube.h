#pragma once

#include "include/ca2.h"

#ifdef _CA2_FONTOPUS_CUBE_DLL
    #define CLASS_DECL_CA2_CUBE  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_CUBE  _declspec(dllimport)
#endif


namespace cube
{
   class application;
} // namespace cube


#undef App
#define App(pcaapp) (cube::app_cast(pcaapp))


#include "acube_application.h"

#include "winservice_filesystemsize/winservice_filesystemsize.h"
#include "biteditor/biteditor.h"
#include "eluce/eluce.h"
#include "mplite/mplite.h"
#include "netnodecfg/netnodecfg.h"
#include "paint/paint.h"
#include "rtprx/rtprx.h"
#include "rtptx/rtptx.h"
#include "status/status.h"
#include "i2com/i2com.h"
#include "tarsila/tarsila.h"
#include "vericalc/vericalc.h"
#include "verifile/verifile.h"
#include "verisimplevideo/verisimplevideo.h"
#include "syllomatter/syllomatter.h"
#include "veriedit/veriedit.h"
#include "vmsp/vmsp.h"
#include "whiteboard/whiteboard.h"
#include "netnode/netnode.h"
#include "devedge/devedge.h"
#include "veriview/veriview.h"


#include "application.h"
