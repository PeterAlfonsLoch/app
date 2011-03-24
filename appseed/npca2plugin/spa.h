#pragma once

// spa is certainly installed
// ca2 may not be installed
// if ca2 is installed, it may not be up-to-date.
// so certainly if spa is installed,
// CRT functions can be called and also
// spalib.dll function can be called
#include "../../../ccvotagus/source/spalib/spalib.h"
#include "../../../ccvotagus/source/install_spaboot/install_spaboot.h"

int APIENTRY ca2_cube_install(const char * pszId);