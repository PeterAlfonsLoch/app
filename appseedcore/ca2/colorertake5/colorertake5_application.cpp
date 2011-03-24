#include "StdAfx.h"

namespace colorertake5
{

   application::application()
   {
      m_pparserfactory = NULL;
   }

   application::~application()
   {
   }

   bool application::initialize()
   {

      m_pparserfactory = new ParserFactory(this);

      return true;
   }

   ParserFactory & application::parser_factory()
   {
      return *m_pparserfactory;
   }

} //namespace colorertake5