#pragma once


namespace aura
{


   class CLASS_DECL_AURA application_ptra:
      virtual public spa(application)
   {
   public:


      application_ptra() { }


      application_ptra(const application_ptra & a):
         spa(application)(a)
      {

      }

      inline application_ptra & operator = (const application_ptra & a)
      {

         spa(application)::operator = (a);

         return *this;

      }


#if defined(MOVE_SEMANTICS)

      application_ptra(application_ptra && a):
         spa(application)(a)
      {

      }

      inline application_ptra & operator = (application_ptra && a)
      {

         spa(application)::operator = (a);

         return *this;

      }

#endif

      application * find_by_app_name(const string & strAppName);

      application * find_running_defer_try_quit_damaged(const string & strAppName);




   };


} // namespace aura




















