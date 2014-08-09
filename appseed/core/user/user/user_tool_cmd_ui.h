#pragma once


namespace user
{

   class tool_cmd_ui :
      public cmd_ui        // class private to this file !
   {
   public: // re-implementations only


      tool_cmd_ui(sp(::base::application) papp);
      virtual ~tool_cmd_ui();

      virtual void Enable(bool bOn);
      virtual void SetCheck(int32_t nCheck);
      virtual void SetText(const char * lpszText);
   };

   struct toolbar_data
   {
      WORD wVersion;
      WORD wWidth;
      WORD wHeight;
      WORD wItemCount;
      //WORD aItems[wItemCount]

      WORD* items()
         { return (WORD*)(this+1); }
   };

} // namespace user

