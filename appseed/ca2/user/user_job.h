#pragma once


namespace user
{

   class CLASS_DECL_ca job :
      virtual public ::ax::job
   {
   public:


      // pointer holder use intention:
      // cascading ph - pointer holder - references would avoid this view
      // and other ph's referenced directly or indirectly by m_pview
      // to be deleted while the job is not finished or canceled.
      ph(::view)        m_pview;

      job(::ax::application * papp);
      virtual ~job();


      virtual int run() = 0;

   };

} // namespace user