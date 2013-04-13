#include "framework.h"


namespace user
{

   
   tool_cmd_ui::tool_cmd_ui(sp(::ca::application) papp) :
      ca(papp),
      cmd_ui(papp)
   {
   }
      
   tool_cmd_ui::~tool_cmd_ui()
   {
   }



} // namespace user