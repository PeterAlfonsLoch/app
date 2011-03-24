#include "StdAfx.h"
#include "np.h"
#include "../ca2/id3lib/sized_types.h"

#undef new

extern NPNetscapeFuncs NPNFuncs;


extern "C" NPError _fillPluginFunctionTable(NPPluginFuncs* aNPPFuncs)
{
  if(aNPPFuncs == NULL)
    return NPERR_INVALID_FUNCTABLE_ERROR;

  // Set up the plugin function table that Netscape will use to
  // call us. Netscape needs to know about our version and size   
  // and have a UniversalProcPointer for every function we implement.

  aNPPFuncs->version       = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
#ifdef XP_MAC
  aNPPFuncs->newp          = NewNPP_NewProc(Private_New);
  aNPPFuncs->destroy       = NewNPP_DestroyProc(Private_Destroy);
  aNPPFuncs->setwindow     = NewNPP_SetWindowProc(Private_SetWindow);
  aNPPFuncs->newstream     = NewNPP_NewStreamProc(Private_NewStream);
  aNPPFuncs->destroystream = NewNPP_DestroyStreamProc(Private_DestroyStream);
  aNPPFuncs->asfile        = NewNPP_StreamAsFileProc(Private_StreamAsFile);
  aNPPFuncs->writeready    = NewNPP_WriteReadyProc(Private_WriteReady);
  aNPPFuncs->write         = NewNPP_WriteProc(Private_Write);
  aNPPFuncs->print         = NewNPP_PrintProc(Private_Print);
  aNPPFuncs->event         = NewNPP_HandleEventProc(Private_HandleEvent);	
  aNPPFuncs->urlnotify     = NewNPP_URLNotifyProc(Private_URLNotify);			
  aNPPFuncs->getvalue      = NewNPP_GetValueProc(Private_GetValue);
  aNPPFuncs->setvalue      = NewNPP_SetValueProc(Private_SetValue);
#else
  aNPPFuncs->newp          = NPP_New;
  aNPPFuncs->destroy       = NPP_Destroy;
  aNPPFuncs->setwindow     = NPP_SetWindow;
  aNPPFuncs->newstream     = NPP_NewStream;
  aNPPFuncs->destroystream = NPP_DestroyStream;
  aNPPFuncs->asfile        = NPP_StreamAsFile;
  aNPPFuncs->writeready    = NPP_WriteReady;
  aNPPFuncs->write         = NPP_Write;
  aNPPFuncs->print         = NPP_Print;
  aNPPFuncs->event         = NPP_HandleEvent;
  aNPPFuncs->urlnotify     = NPP_URLNotify;
  aNPPFuncs->getvalue      = NPP_GetValue;
  aNPPFuncs->setvalue      = NPP_SetValue;
#endif
#ifdef OJI
  aNPPFuncs->javaClass     = NULL;
#endif

  return NPERR_NO_ERROR;
}

extern "C" NPError _fillNetscapeFunctionTable(NPNetscapeFuncs* aNPNFuncs)
{
  if(aNPNFuncs == NULL)
    return NPERR_INVALID_FUNCTABLE_ERROR;

  if(HIBYTE(aNPNFuncs->version) > NP_VERSION_MAJOR)
    return NPERR_INCOMPATIBLE_VERSION_ERROR;

  if(aNPNFuncs->size < sizeof(NPNetscapeFuncs))
    return NPERR_INVALID_FUNCTABLE_ERROR;

  NPNFuncs.size             = aNPNFuncs->size;
  NPNFuncs.version          = aNPNFuncs->version;
  NPNFuncs.geturlnotify     = aNPNFuncs->geturlnotify;
  NPNFuncs.geturl           = aNPNFuncs->geturl;
  NPNFuncs.posturlnotify    = aNPNFuncs->posturlnotify;
  NPNFuncs.posturl          = aNPNFuncs->posturl;
  NPNFuncs.requestread      = aNPNFuncs->requestread;
  NPNFuncs.newstream        = aNPNFuncs->newstream;
  NPNFuncs.write            = aNPNFuncs->write;
  NPNFuncs.destroystream    = aNPNFuncs->destroystream;
  NPNFuncs.status           = aNPNFuncs->status;
  NPNFuncs.uagent           = aNPNFuncs->uagent;
  NPNFuncs.memalloc         = aNPNFuncs->memalloc;
  NPNFuncs.memfree          = aNPNFuncs->memfree;
  NPNFuncs.memflush         = aNPNFuncs->memflush;
  NPNFuncs.reloadplugins    = aNPNFuncs->reloadplugins;
#ifdef OJI
  NPNFuncs.getJavaEnv       = aNPNFuncs->getJavaEnv;
  NPNFuncs.getJavaPeer      = aNPNFuncs->getJavaPeer;
#endif
  NPNFuncs.getvalue         = aNPNFuncs->getvalue;
  NPNFuncs.setvalue         = aNPNFuncs->setvalue;
  NPNFuncs.invalidaterect   = aNPNFuncs->invalidaterect;
  NPNFuncs.invalidateregion = aNPNFuncs->invalidateregion;
  NPNFuncs.forceredraw      = aNPNFuncs->forceredraw;
  NPNFuncs.getstringidentifier = aNPNFuncs->getstringidentifier;
  NPNFuncs.getproperty = aNPNFuncs->getproperty;
  NPNFuncs.setproperty = aNPNFuncs->setproperty;
  NPNFuncs.releaseobject = aNPNFuncs->releaseobject;
  NPNFuncs.releasevariantvalue = aNPNFuncs->releasevariantvalue;
  return NPERR_NO_ERROR;
}
