#include "framework.h"


form_child_frame::form_child_frame(sp(::aura::application) papp) :
   element(papp),
   simple_child_frame(papp)
{
}