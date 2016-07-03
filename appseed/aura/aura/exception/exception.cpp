//#include "framework.h"


namespace exception
{


   exception::exception()
   {

      debug_print("log:exception");
      //::MessageBox(NULL,"abc123","abc123",MB_OK);


      m_bHandled = false;

      m_bContinue = true;

   }

   exception::exception(e_context_switcher_failed efail)
   {
      //debug_print("log:exception");
      //::MessageBox(NULL,"abc123","abc123",MB_OK);
      m_bLog = efail != failure_no_log;

      if(m_bLog)
      {
         debug_print("log:exception");
      }

      m_bHandled = false;

      m_bContinue = true;

   }


   exception::~exception()
   {
      if(m_bLog)
      {

         if(m_bContinue)
         {
            m_strException += "-continue";
         }
         else
         {
            m_strException += "-should_not_continue(fatal_exception_instance_candidate)";
         }

         if(m_bHandled)
         {
            m_strException += "-explicitly_handled";
         }
         else
         {
            m_strException += "-not_handled_explicitly";
         }

         debug_print("\n");

      }

   }


   void exception::Delete()
   {

      delete this;

   }

   void rethrow(exception * pe)
   {

      throw pe;

   }

   const char * exception::what() const throw()
   {

      return m_strMessage;

   }


   result::result(std::initializer_list < exception * > list)
   {

      forallref(list)
      {

         add(item);

      }

   }

} // namespace exception


#ifdef APPLE_IOS



#else

thread_object < string > t_strNote;


string __get_thread_note()
{
   return t_strNote->c_str();
}
void __set_thread_note(const char * pszNote)
{
   t_strNote->operator=(pszNote);
}

#endif






errno_t c_runtime_error_check(errno_t error)
{
   switch(error)
   {
      case ENOMEM:
         throw memory_exception(get_thread_app());
         break;
      case EINVAL:
      case ERANGE:
         throw invalid_argument_exception(get_thread_app());
         break;
#if defined(WINDOWS)
      case STRUNCATE:
#endif
      case 0:
         break;
      default:
         throw invalid_argument_exception(get_thread_app());
         break;
   }
   return error;
}

void __cdecl __clearerr_s(FILE *stream)
{
#ifdef WINDOWS
   C_RUNTIME_ERROR_CHECK(::clearerr_s(stream));
#else
   clearerr(stream);
   C_RUNTIME_ERROR_CHECK(errno);
#endif
}



namespace exception
{

   CLASS_DECL_AURA void throw_interface_only(::aura::application * papp)
   {
      throw interface_only_exception(papp);
   }

   CLASS_DECL_AURA void throw_not_implemented(::aura::application * papp)
   {
      throw not_implemented(papp);
   }

} // namespace exception















