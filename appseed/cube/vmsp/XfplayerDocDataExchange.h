#pragma once

class XfplayerDoc;

#include "document.h"

class XfplayerDocDataExchange :
   public vmsp::DocumentDataExchange
{
public:
   XfplayerDocDataExchange(vmsp::DocumentInterface * pdoc);
   virtual ~XfplayerDocDataExchange();
   XfplayerDoc * get_document();

   int GetSongEncoding();

};

