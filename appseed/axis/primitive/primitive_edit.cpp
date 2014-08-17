#include "framework.h"


axis_edit::axis_edit(sp(::base::application) papp) :
   element(papp)
{
}

axis_edit::~axis_edit()
{
}

void axis_edit::apply()
{

   m_spdata->edit(this);
   on_apply();

}

void axis_edit::on_apply()
{
}

