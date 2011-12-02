#include "StdAfx.h"

namespace acube
{

   application::application()
   {
   }

   application::~application()
   {
   }

   ::ax::application * application::get_system()
   {
      return new application();
   }



} //namespace cube


