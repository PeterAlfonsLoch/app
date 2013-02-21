#pragma once

namespace userpresence
{

      class CLASS_DECL_ca presence :
         virtual public ::gen::object
      {
      public:

         enum e_predefined_status
         {
            status_online     = 1000000006,
            status_offline    = 1000000025,
         };


         uint32_t          m_dwLastActivity;
         int64_t        m_iShortStatusCynceTag;
         string         m_strLongStatus;


         presence(::ca::application * papp);
         virtual ~presence();

         virtual void report_activity();


         virtual void defer_pulse_user_presence();
         virtual void pulse_user_presence();

      };


} // namespace userpresence


