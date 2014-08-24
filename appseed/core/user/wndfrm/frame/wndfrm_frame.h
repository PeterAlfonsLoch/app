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





#include "wndfrm_frame_enum.h"

#include "wndfrm_frame_frame.h"


#include "wndfrm_frame_constants.h"

#include "wndfrm_frame_control_box_button.h"
#include "wndfrm_frame_work_set_down_up_interface.h"
#include "wndfrm_frame_sys_menu_manager.h"

#include "wndfrm_frame_appearance.h"

#include "wndfrm_frame_dock_manager.h"
#include "wndfrm_frame_size_manager.h"
#include "wndfrm_frame_move_manager.h"

#include "wndfrm_frame_work_set_listener_array.h"
#include "wndfrm_frame_work_set_down_up_interface.h"
#include "wndfrm_frame_work_set.h"
#include "wndfrm_frame_work_set_client_interface.h"
#include "wndfrm_frame_work_set_listener.h"
#include "wndfrm_frame_up_down_target.h"
