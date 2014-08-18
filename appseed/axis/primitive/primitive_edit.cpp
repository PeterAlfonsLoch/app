#include "framework.h"


base_edit::base_edit(sp(::axis::application) papp) :
   element(papp)
{
}

base_edit::~base_edit()
{
}

void base_edit::apply()
{

   m_spdata->edit(this);
   on_apply();

}

void base_edit::on_apply()
{
}

