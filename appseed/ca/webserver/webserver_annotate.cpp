#include "StdAfx.h"

namespace webserver
{

::webserver::note * annotate::get(var user, var objectid)
{
   string strSql;
   strSql.Format("SELECT cyncecc.object.objectid, cyncecc.object.name, `text`, MIN(`editdatetime`), MAX(`editdatetime`) FROM note LEFT OUTER JOIN cyncecc.object ON cyncecc.object.objecttype = 3 AND cyncecc.object.objectid = note.id LEFT OUTER JOIN cyncecc.object_history ON cyncecc.object_history.object = cyncecc.object.object WHERE cyncecc.object.object = %s GROUP BY cyncecc.object.object, note.id", 
      objectid.get_string());
   var row = musicdb().query_row(strSql);
   ::webserver::note * pnote = new ::webserver::note();
   pnote->m_user = user;
   pnote->m_object = objectid;
   pnote->m_note = row[0];
   pnote->m_title = row[1];
   pnote->m_text = row[2];
   pnote->m_insertiondatetime = row[3];
   pnote->m_modifieddatetime = row[4];
   pnote->m_tags = cynce().value_tags("fontopus.note", row[0]);
   pnote->m_taga = cynce().value_taga("fontopus.note", row[0]);
   return pnote;
}


var annotate::set(var user, var object, var title, var text, var tag)
{
   string editdatetime = System.datetime().international().get_gmt_date_time();
   if(strlen(object) == 0 || object == "new")
   {
      return cynce().insert_object(user, editdatetime,
         "fontopus.note", text, user, title, editdatetime, array());
   }
   else
   {
      var var = cynce().update_object(object, editdatetime,
         "fontopus.note", text, user, title, editdatetime);

      cynce().insert_value_tags(editdatetime, object, tag, user);

      return var;
   }
}
   
var annotate::insert(var user, var title, var text)
   {
      string strSql;
      strSql.Format("SELECT MAX(note) FROM note WHERE user = %d", user.get_integer());
      var maxid = musicdb().query_item(strSql);
      var note = maxid + 1;
      title= musicdb().real_escape_string(title);
      text= musicdb().real_escape_string(text);
      strSql.Format("INSERT INTO note(`user`, `note`, `title`, `text`, `insertiondatetime`, `modifieddatetime`) VALUES ('%d', '%d', '%s', '%s', NOW(), NOW())",
         user.get_integer(), user.get_integer(), title.get_string(), text.get_string());
      musicdb().query(strSql);
      return note;
   }

   var annotate::update(var user, var note, var title, var text)
   {
      title= musicdb().real_escape_string(title);
      text= musicdb().real_escape_string(text);
      string strSql;
      strSql.Format("UPDATE note SET `title` = '%s', `text` = '%s', modifieddatetime = NOW() WHERE `user` = %d AND `note` = %d",
         title.get_string(), text.get_string(), user.get_integer(), note.get_integer());
      musicdb().query(strSql);
      return note;
   }

   void annotate::get_user_summary_list(var user, base_array < ::webserver::note_summary * > & summary_list)
   {
      string strSql;
      strSql.Format("SELECT note, title, insertiondatetime, modifieddatetime FROM note WHERE user = %d ORDER BY modifieddatetime DESC",
         user.get_integer());
      var rowa = musicdb().query_rows(strSql);
      
      for(int i = 0; i < rowa.array_get_count(); i++)
      {
         var row = rowa.at(i);
         ::webserver::note_summary * psummary = new ::webserver::note_summary();
         psummary->m_user = user;
         psummary->m_note = row[0];
         psummary->m_title = row[1];
         psummary->m_insertiondatetime = row[2];
         psummary->m_modifieddatetime = row[3];
         summary_list.add(psummary);
      }
   }


} // namespace webserver