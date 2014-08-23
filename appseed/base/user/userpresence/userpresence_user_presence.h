#pragma once


namespace userpresence
{


   class CLASS_DECL_BASE presence :
      virtual public ::object
   {
   public:

      
      enum e_predefined_status
      {
         
         status_online     = 1000000006,
         status_offline    = 1000000025
            
      };


      uint32_t          m_dwLastActivity;
      uint32_t          m_dwLastPulse;
      int64_t        m_iShortStatusWayTag;
      string         m_strLongStatus;


      presence(sp(::aura::application) papp);
      virtual ~presence();

      virtual void report_activity();


      virtual void defer_pulse_user_presence();
      virtual void pulse_user_presence();

   };


} // namespace userpresence



