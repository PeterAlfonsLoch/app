#pragma once


namespace tesseract
{

namespace mail
{

   class CLASS_DECL_CA2_TESSERACT document :
      public ::userbase::document
   {
   public:

      enum e_hint
      {
         hint_email_changed = 1024,
         hint_open_email,
      };

      string                  m_strOpenEmailId;
      ::mail::account *               m_paccount;
      ::user::place_holder *  m_pholderMailList;


      document(::ca::application * papp);
      virtual ~document();
      
      DECL_GEN_VSIGNAL(data_on_after_change)

      void set_account(::mail::account * pacc);
      void open_email(const char * pszId);


   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

   } // namespace mail


} // namespace tesseract


