#pragma once

#include "include/ihtml.h"
#include "include/guibase.h"

#ifdef _MSHTML_DLL
   #define CLASS_DECL_MSHTML  _declspec(dllexport)
#else
   #define CLASS_DECL_MSHTML  _declspec(dllimport)
#endif

#ifndef __AFXDISP_H__
	#include "cafx/cafxdisp.h"
#endif

#ifndef __exdisp_h__
	#include <exdisp.h>
#endif

#ifndef __mshtmhst_h__
#include <mshtmhst.h>
#endif

#ifndef __mshtml_h__
#include <mshtml.h>
#endif

#ifndef __mshtmcid_h__
#include <mshtmcid.h>
#endif


#include <exdispid.h>
#include <mshtmcid.h>	// CMDSETID_Forms3 definition
#include <mshtmhst.h>	// IDM_menu item definitions
#include <mshtml.h>


#include "html_view.h"
#include "stream_on_string.h"
#include "html_edit_ctrl_base.h"
#include "html_edit_view.h"
#include "html_edit_doc.h"
#include "mshtml.inl"

