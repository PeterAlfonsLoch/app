#include "StdAfx.h"

namespace netnode
{

   simage_accepta::simage_accepta(var root)
   {
      m_propsetAccept.set_app(::ca::get_thread()->m_papp);
      m_root = root;
   }

} // namespace netnode