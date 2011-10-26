#pragma once

#define WM_APP_NOTIFYICON WM_APP + 100
#define WM_APP_CALENDARICON WM_APP + 101
#define WM_APP_MRTS WM_APP + 102

namespace whiteboard
{

   enum e_time
   {
      TimeLastView,
      TimeLastChange,
      TimeGroup,
      TimePrivate,
   };

} // namespace whiteboard