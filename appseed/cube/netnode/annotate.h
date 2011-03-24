#pragma once

class CLASS_DECL_CA2_CUBE annotate :
   public ptr
{
public:
   using ptr::get;
   ca2::note * get(var user, var objectid);
   var set(var user, var note, var title, var text, var tag);
   var insert(var user, var title, var text);
   var update(var user, var note, var title, var text);
   void get_user_summary_list(var user, base_array < ca2::note_summary * > & summarry_list);
};