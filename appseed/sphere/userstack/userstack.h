#pragma once


#include "app/appseed/sphere/command/command.h"


namespace userstack
{

   class view;
   class pane_view;
   class document;


   enum EPaneView
   {
      PaneViewNone,
      PaneViewContextMenu,
      PaneViewWinActionArea,
      PaneViewFileManager,
      PaneViewThreeActionLaunch,
      PaneViewConfiguration,
      PaneViewFileProperties,
   };




} // namespace userstack

#include "userstack_view.h"
#include "userstack_document.h"
#include "userstack_frame.h"
#include "userstack_form_callback.h"
#include "userstack_pane_view.h"
#include "userstack_pane_view_update_hint.h"


#include "userstack_application.h"



