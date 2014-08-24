#pragma once


namespace user
{


   class front_end_schema;


   namespace wndfrm
   {


      namespace frame
      {


         class WorkSet;
         class UpDownTarget;
         class WorkSetListener;
         class WorkSetListenerArray;
         class appearance;


         enum EBorder
         {

            BorderNone = 0,
            BorderTop = 1,
            BorderRight = 2,
            BorderBottom = 4,
            BorderLeft = 8,
            BorderAll = BorderTop | BorderRight | BorderBottom | BorderLeft,

         };



      } // namespace frame


   } // namespace wndfrm


} // namespace user





#include "uinteraction_frame_enum.h"

#include "uinteraction_frame_frame.h"


#include "uinteraction_frame_constants.h"

#include "uinteraction_frame_control_box_button.h"
#include "uinteraction_frame_work_set_down_up_interface.h"
#include "uinteraction_frame_sys_menu_manager.h"

#include "uinteraction_frame_appearance.h"

#include "uinteraction_frame_dock_manager.h"
#include "uinteraction_frame_size_manager.h"
#include "uinteraction_frame_move_manager.h"

#include "uinteraction_frame_work_set_listener_array.h"
#include "uinteraction_frame_work_set_down_up_interface.h"
#include "uinteraction_frame_work_set.h"
#include "uinteraction_frame_work_set_client_interface.h"
#include "uinteraction_frame_work_set_listener.h"
#include "uinteraction_frame_up_down_target.h"
