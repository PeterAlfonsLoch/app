#pragma once


namespace icube
{


   CLASS_DECL_ca system *  create_system();
   CLASS_DECL_ca void      destroy_system(system * & psystem);


   CLASS_DECL_ca int       ca2_cube_install(const char * pszId);

} // namespace icube