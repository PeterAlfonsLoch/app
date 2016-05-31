//#include "framework.h"


error_exception::error_exception(::ace::application * papp,const char * pszError):
object(papp),
::call_stack(papp),
::exception::base(papp)
{
   if(pszError == NULL)
   {
      debug_print(":error(NULL)");
   }
   else
   {
      debug_print(":error(\"%s\")",pszError);
   }

   m_strError = pszError;
}

error_exception::~error_exception()
{
}

bool error_exception::get_error_message(string & str,PUINT pnHelpContext)
{

   UNREFERENCED_PARAMETER(pnHelpContext);

   str = m_strError;

   return TRUE;
}



//#include "framework.h"


index_out_of_bounds::index_out_of_bounds(::ace::application * papp, const char * pszError) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   error_exception(papp, pszError)
{

   if (pszError == NULL)
   {

      debug_print(":index_out_of_bounds(NULL)");

   }
   else
   {

      debug_print(":index_out_of_bounds(\"%s\")", pszError);

   }

}


index_out_of_bounds::~index_out_of_bounds()
{

}
