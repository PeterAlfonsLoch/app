#include "StdAfx.h"

cynce_database::cynce_database(::ca::application * papp) :
   ca(papp),
   ::mysql::database(papp),
   netnode::database(papp)
{
}

bool cynce_database::initialize()
{
   if(!connect(
      "localhost",
      "carcyncelos",
      "11grenlundvotaguscynceloscarAptomlJporCarlosGustavoCecynLundgren",
      "cyncecc"))
   {
      if(!connect(
         "votagus.net",
         "carcyncelos",
         "11grenlundvotaguscynceloscarAptomlJporCarlosGustavoCecynLundgren",
         "cyncecc"))
      {
         return false;
      }
   }
   return true;
}
