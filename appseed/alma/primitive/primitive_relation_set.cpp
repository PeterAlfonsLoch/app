#include "framework.h"


relation_set::relation_set(sp(::base::application) papp) :
element(papp),
property_set(papp, true, true)
{

}


relation_set::~relation_set()
{

}






