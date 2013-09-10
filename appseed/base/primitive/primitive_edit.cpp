#include "framework.h"


base_edit::base_edit(sp(base_application) papp) :
   base_element(papp)
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

