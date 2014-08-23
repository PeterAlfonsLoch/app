#include "framework.h"


simple_exception::simple_exception(sp(::axis::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{
      printf(":simple");
}

simple_exception::simple_exception(sp(::axis::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{
      if(pszMessage == NULL)
      {
         printf(":simple(NULL)");
      }
      else
      {
         printf(":simple(\"%s\")",pszMessage);
      }

   m_strMessage = pszMessage;

}

simple_exception::~simple_exception()
{

}

bool simple_exception::get_error_message(string & str, PUINT pnHelpContext)
{

   str = what();

   return true;

}



