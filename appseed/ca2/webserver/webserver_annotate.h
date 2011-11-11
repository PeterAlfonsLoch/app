#pragma once


namespace webserver
{


   class CLASS_DECL_ca annotate :
      public dynamic_source::ptr
   {
   public:
      using dynamic_source::ptr::get;
      webserver::note * get(var user, var objectid);
      var set(var user, var note, var title, var text, var tag);
      var insert(var user, var title, var text);
      var update(var user, var note, var title, var text);
      void get_user_summary_list(var user, base_array < webserver::note_summary * > & summarry_list);
   };


} // namespace webserver


