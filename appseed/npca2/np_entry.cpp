/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. 
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or 
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

//////////////////////////////////////////////////////////////
//
// Main plugin entry point implementation -- exports from the 
// plugin library
//
#include "npca2.h"




NPError OSCALL NP_Shutdown()
{
   if(pfn_NS_PluginShutdown != NULL)
   {
      pfn_NS_PluginShutdown();
   }
   return NPERR_NO_ERROR;
}




//
// Some exports are different on different platforms
//

/**************************************************/
/*                                                */
/*                   Windows                      */
/*                                                */
/**************************************************/
#ifdef XP_WIN

NPError OSCALL NP_Initialize(NPNetscapeFuncs* aNPNFuncs)
{

   if(!defer_check())
      return NPERR_GENERIC_ERROR;

   NPError rv = pfn_fillNetscapeFunctionTable(aNPNFuncs);
   if(rv != NPERR_NO_ERROR)
      return rv;

   return pfn_NS_PluginInitialize();

}

NPError OSCALL NP_GetEntryPoints(NPPluginFuncs* aNPPFuncs)
{

   if(!defer_check())
      return NPERR_GENERIC_ERROR;

   return pfn_fillPluginFunctionTable(aNPPFuncs);

}

#endif //XP_WIN

/**************************************************/
/*                                                */
/*                    Unix                        */
/*                                                */
/**************************************************/
#ifdef XP_UNIX

NPError NP_Initialize(NPNetscapeFuncs* aNPNFuncs, NPPluginFuncs* aNPPFuncs)
{
  NPError rv = fillNetscapeFunctionTable(aNPNFuncs);
  if(rv != NPERR_NO_ERROR)
    return rv;

  rv = fillPluginFunctionTable(aNPPFuncs);
  if(rv != NPERR_NO_ERROR)
    return rv;

  return NS_PluginInitialize();
}

char * NP_GetMIMEDescription(void)
{
  return NPP_GetMIMEDescription();
}

NPError NP_GetValue(void *future, NPPVariable aVariable, void *aValue)
{
  return NS_PluginGetValue(aVariable, aValue);
}

#endif //XP_UNIX

/**************************************************/
/*                                                */
/*                     Mac                        */
/*                                                */
/**************************************************/
#ifdef XP_MAC

#if !TARGET_API_MAC_CARBON
QDGlobals* gQDPtr; // Pointer to Netscape's QuickDraw globals
#endif

short gResFile; // Refnum of the plugin's resource file

NPError Private_Initialize(void)
{
  NPError rv = NS_PluginInitialize();
  return rv;
}

void Private_Shutdown(void)
{
  NS_PluginShutdown();
  __destroy_global_chain();
}

void SetUpQD(void);

void SetUpQD(void)
{
  ProcessSerialNumber PSN;
  FSSpec              myFSSpec;
  Str63               name;
  ProcessInfoRec      infoRec;
  OSErr               result = noErr;
  CFragConnectionID   connID;
  Str255              errName;

  // Memorize the plugin¹s resource file refnum for later use.
  gResFile = CurResFile();

#if !TARGET_API_MAC_CARBON
  // Ask the system if CFM is available.
  long response;
  OSErr err = Gestalt(gestaltCFMAttr, &response);
  Boolean hasCFM = BitTst(&response, 31-gestaltCFMPresent);

  if (hasCFM) {
    // GetProcessInformation takes a process serial number and 
    // will give us back the name and FSSpec of the application.
    // See the Process Manager in IM.
    infoRec.processInfoLength = sizeof(ProcessInfoRec);
    infoRec.processName = name;
    infoRec.processAppSpec = &myFSSpec;

    PSN.highLongOfPSN = 0;
    PSN.lowLongOfPSN = kCurrentProcess;

    result = GetProcessInformation(&PSN, &infoRec);
  }
	else
    // If no CFM installed, assume it must be a 68K app.
    result = -1;		

  if (result == noErr) {
    // Now that we know the app name and FSSpec, we can call GetDiskFragment
    // to get a connID to use in a subsequent call to FindSymbol (it will also
    // return the address of ³main² in app, which we ignore).  If GetDiskFragment 
    // returns an error, we assume the app must be 68K.
    Ptr mainAddr; 	
    result =  GetDiskFragment(infoRec.processAppSpec, 0L, 0L, infoRec.processName,
                              kReferenceCFrag, &connID, (Ptr*)&mainAddr, errName);
  }

  if (result == noErr) {
    // The app is a PPC code fragment, so call FindSymbol
    // to get the exported ³qd² symbol so we can access its
    // QuickDraw globals.
    CFragSymbolClass symClass;
    result = FindSymbol(connID, "\pqd", (Ptr*)&gQDPtr, &symClass);
  }
  else {
    // The app is 68K, so use its A5 to compute the address
    // of its QuickDraw globals.
    gQDPtr = (QDGlobals*)(*((long*)SetCurrentA5()) - (sizeof(QDGlobals) - sizeof(GrafPtr)));
  }
#endif /* !TARGET_API_MAC_CARBON */
}

NPError main(NPNetscapeFuncs* nsTable, NPPluginFuncs* pluginFuncs, NPP_ShutdownUPP* unloadUpp);

#if !TARGET_API_MAC_CARBON
#pragma export on
#if GENERATINGCFM
RoutineDescriptor mainRD = BUILD_ROUTINE_DESCRIPTOR(uppNPP_MainEntryProcInfo, main);
#endif
#pragma export off
#endif /* !TARGET_API_MAC_CARBON */


NPError main(NPNetscapeFuncs* aNPNFuncs, NPPluginFuncs* aNPPFuncs, NPP_ShutdownUPP* aUnloadUpp)
{
  NPError rv = NPERR_NO_ERROR;

  if (aUnloadUpp == NULL)
    rv = NPERR_INVALID_FUNCTABLE_ERROR;

  if (rv == NPERR_NO_ERROR)
    rv = fillNetscapeFunctionTable(aNPNFuncs);

  if (rv == NPERR_NO_ERROR) {
    // defer static constructors until the global functions are initialized.
    __InitCode__();
    rv = fillPluginFunctionTable(aNPPFuncs);
  }

  *aUnloadUpp = NewNPP_ShutdownProc(Private_Shutdown);
  SetUpQD();
  rv = Private_Initialize();
	
  return rv;
}
#endif //XP_MAC
