#include "StdAfx.h"

namespace webserver
{

cynce_database::cynce_database(::ca::application * papp) :
   ca(papp),
   ::mysql::database(papp),
   webserver::database(papp)
{
}

bool cynce_database::initialize()
{
   if(!connect(
      Application.m_strDatabaseServerHost,
      "carcyncelos",
      "11grenlundvotaguscynceloscarAptomlJporCarlosGustavoCecynLundgren",
      "cyncecc"))
   {
		if(Application.m_strDatabaseServerHost == "localhost"
		|| !connect(
			"localhost",
			"carcyncelos",
			"11grenlundvotaguscynceloscarAptomlJporCarlosGustavoCecynLundgren",
			"cyncecc"))
		{
			if(Application.m_strDatabaseServerHost == "votagus.net"
			|| !connect(
				"votagus.net",
				"carcyncelos",
				"11grenlundvotaguscynceloscarAptomlJporCarlosGustavoCecynLundgren",
				"cyncecc"))
			{
				return false;
			}
		}
   }
   return true;
}


} // namespace webserver