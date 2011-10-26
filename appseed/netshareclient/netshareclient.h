#pragma once

#include "include/ca2.h"


#ifdef _CA2_FONTOPUS_NETSHARECLIENT_DLL
    #define CLASS_DECL_CA2_NETSHARECLIENT  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_NETSHARECLIENT  _declspec(dllimport)
#endif


namespace netshareclient
{

   class application;


} // namespace netshareclient


#undef App
#define App(pcaapp) (pcaapp->cast_app < ::netshareclient::application > ())


#include "area.h"
#include "tunnel.h"
#include "thread.h"
#include "netshareserver.h"
#include "document.h"
#include "frame.h"
#include "view.h"


#include "netshareclient_main_view.h"

#include "netshareclient_list_interface.h"
#include "netshareclient_list.h"

#include "netshareclient_tree_item.h"
#include "netshareclient_tree_data.h"
#include "netshareclient_tree_interface.h"
#include "netshareclient_tree.h"


#include "application.h"

