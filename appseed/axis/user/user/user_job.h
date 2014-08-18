#pragma once


namespace user
{


   class CLASS_DECL_AXIS job :
      virtual public ::job
   {
   public:


      // pointer holder use intention:
      // cascading ph - pointer holder - references would avoid this view
      // and other ph's referenced directly or indirectly by m_pview
      // to be deleted while the job is not finished or canceled.
      sp(::user::impact)        m_pview;


      job(sp(::axis::application) papp);
      virtual ~job();


      virtual int32_t run() = 0;

   };


} // namespace user




