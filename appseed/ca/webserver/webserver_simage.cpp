#include "StdAfx.h"


namespace webserver
{


   simage_accepta::simage_accepta(var root)
   {
      m_propsetAccept.set_app(::ca::get_thread()->m_papp);
      m_root = root;
   }


} // namespace webserver
