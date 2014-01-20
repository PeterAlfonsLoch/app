#include "framework.h"


CLASS_DECL_BASE int_bool ui_get_cursor_pos(POINT * ppt)
{

   return ::GetCursorPos(ppt);

}