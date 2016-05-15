#pragma once


enum e_message
{

   message_system = WM_APP + 1984,
   message_berdge,
   message_display_change,
   MessageBaseWndGetProperty,
   MessageProperty,
   MessageGeneralEvent,
   message_simple_command,
   message_set_schema,
};

enum e_system_message
{

   system_message_command = 49,
   system_message_user = 77,
   system_message_meta = 51,
   system_message_pred = 84,
   system_message_register_dependent_thread = 90,
   system_message_unregister_dependent_thread = 91,

};



