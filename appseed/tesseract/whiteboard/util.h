#pragma once

namespace whiteboard
{

   class CLASS_DECL_CA2_TESSERACT util
   {
   public:
      util();

      // Janeiro = 0
      static void get_month_text(string & str, int iMonth);
      static void get_month_abbr_text(string & str, int iMonth);
      static bool get_current_user_logon_time(whiteboard::time & time);
      static bool get_current_session_current_user_name(string & str);
      static void strip_file_extension(string & str);

   };

} // namespace whiteboard