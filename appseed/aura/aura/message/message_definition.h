
#pragma once



namespace message
{


   enum e_message
   {

      message_create = USER_MESSAGE,
      message_event = WM_APP + 1000,
      message_property = WM_APP + 1001,
      message_pos_create = WM_USER + 193,
      message_frame_initial_update

   };


   CLASS_DECL_AXIS UINT translate_to_os_message(UINT uiMessage);


   class base;


   enum e_prototype
   {
      PrototypeNone,
      PrototypeMouse,
      PrototypeScroll,
      PrototypeSize,
      PrototypeMove,
      PrototypeMeasureItem,
      PrototypeCreate,
      PrototypeActivate,
      PrototypeNcActivate,
      PrototypeEraseBkgnd,
      PrototypeShowWindow,
      PrototypeSetCursor,
      PrototypeTimer,
      PrototypeMouseWheel,
      PrototypeInitMenuPopup,
      PrototypeNcHitTest,
      PrototypeKey,
      PrototypeNotify,
      PrototypeUpdateCommandUserInterface,
      PrototypeCtlColor,
      PrototypeCtlColorReflect,
      PrototypeSetFocus,
      PrototypeCommand,
      PrototypeWindowPos,
      PrototypeNcCalcSize,
      PrototypeOnDraw

   };


   class ::signal * CreateSignal();


} // namespace message
