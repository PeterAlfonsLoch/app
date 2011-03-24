#pragma once

namespace veiev
{

   class CLASS_DECL_CA2_VEIEV document :
      public ::userbase::document
   {
   public:


      enum e_hint
      {
         hint_veiev_profile_changed = 1024,
         hint_open_veiev_profile,
      };

      string                     m_strOpenVeievProfileId;
      ::fontopus::user *    m_pprofile;
      ::user::place_holder *     m_pholderVeievList;


      document(::ca::application * papp);
	   virtual ~document();

      void set_profile(::fontopus::user * pacc);
      void open_veiev_profile(const char * pszId);

   
      DECL_GEN_VSIGNAL(data_on_after_change);

	   virtual BOOL on_new_document();

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      BOOL on_open_document(const char * lpszPathName);

   };

} // namespace veiev