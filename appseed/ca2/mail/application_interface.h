#pragma once

namespace mail
{

class CLASS_DECL_ca application_interface : 
   virtual public ::radix::object
{
public:
   application_interface(::ca::application * papp);
   virtual ~application_interface();

   void InitializeMail();


   array_del_ptr < mail::account, mail::account & > m_accounta;

   void TimerStep();


   folder_list * m_pfolderlist;
   mail_list * m_pmaillist;

};

inline application_interface & app(::ca::application * papp)
   {
      return *(dynamic_cast < application_interface * > (papp));
   }

} // namespace mail