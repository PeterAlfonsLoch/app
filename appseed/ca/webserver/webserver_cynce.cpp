#include "StdAfx.h"


namespace webserver
{

var cynce::value_rows(var type, var plus_taga, var minus_taga)
{
   gen::property_set set(get_app());

   set["user_tag"] = get_current_user_secure_tag();
   set["secureuserid"] = gprop("secureuserid");
   set["type"] = type;
   set["typeid"] = objecttype_id(type);
   set["field"] = objecttype_field(type);
   set["type_tag"] = string(type) + "_tag";

   string join1;

   stringa where1;
   stringa having1;
   string str;
   var tags;

   stringa stra2;

   where1.add(set.eval(" (`object`.`objecttype` = $typeid)"));

   join1 = "INNER JOIN object ON object.objectid = $type.id ";

   set["index"] = 0;
   for(int i = 0; i < plus_taga.array_get_count(); i++)
   {
      tags.stra().remove_all();
      tags.stra().explode("-", plus_taga.at(i));
      stra2.remove_all();
      stra2.add("`object_tag$index`.`tag` = '" +tags.at(0)+"'");
      for(int i = 2; i <= tags.array_get_count(); i++)
      {
         stra2.add("`object_tag$index`.`tag" + gen::str::itoa(i) +"` = '" +tags.at(i - 1)+"'");
      }

      join1 += set.eval("INNER JOIN `object_tag` as `object_tag$index` ON `object_tag$index`.object = `object`.object ");

      where1.add("(" +set.eval(stra2.implode(" AND ")) + ")");
      //         foreach($minus_taga as $tag2)
      //      {
      //      $where1 .= " AND `$type_tag$index`.`tagid` != '$tag2'";
      //}
      set["index"]++;
   }
   for(int i = 0; i < minus_taga.array_get_count(); i++)
   {
      stra2.remove_all();
      tags.stra().remove_all();
      tags.stra().explode("-", minus_taga.at(i));
      stra2.add("`object_tag$index`.`tag` = '" +tags.at(0)+"'");
      for(int i = 2; i <= tags.array_get_count(); i++)
      {
         stra2.add("`object_tag$index`.`tag" + gen::str::itoa(i) +"` = '" +tags.at(i - 1)+"'");
      }

      join1 += set.eval("LEFT OUTER JOIN `object_tag` as `object_tag$index` ON `object_tag$index`.object = `object`.object AND (" +set.eval(stra2.implode(" AND ")) + ") ");

      having1.add(set.eval(" COUNT(`object_tag$index`.`object`) = 0"));
      //         foreach($minus_taga as $tag2)
      //      {
      //      $where1 .= " AND `$type_tag$index`.`tagid` != '$tag2'";
      //}
      set["index"]++;
   }
   set["inde2"] = set["index"] + 1;

   join1 += set.eval("LEFT OUTER JOIN `object_tag` as `object_tag$index` ON `object_tag$index`.object = `object`.object AND `object_tag$index`.`tag` = '8833751' ");

   join1 += set.eval("LEFT OUTER JOIN `object` as `obj2` ON `obj2`.object = `object`.object AND obj2.creator =  $secureuserid ");

   having1.add(set.eval(" (COUNT(`object_tag$index`.`object`) = 0 OR COUNT(obj2.object) > 0)"));

   set["index"] = set["index2"] + 1;

   if(where1.get_count() > 0)
   {
      set["where"] = " WHERE " + where1.implode(" AND ");
   }
   if(having1.get_count() > 0)
   {
      set["having"] = " HAVING " + having1.implode(" AND ");
   }

   set["join1"] = join1;

   string sql = set.eval("SELECT $type.id, $type.$field FROM $type $join1 $where GROUP BY $type.id $having");
   dprint(sql);
   var rows = cyncedb().query_rows(sql);
   return rows;
}


var cynce::value_user(const char * type, const char * id)
{
   string sql = "SELECT `{$type}_history`.user, CONCAT(fontopus.fun_user.firstname, ' ', fontopus.fun_user.lastname) FROM  `{$type}_history` INNER JOIN fontopus.fun_user ON  `{$type}_history`.user = fontopus.fun_user.id WHERE `{$type}_history`.`{$type}` = '$id' LIMIT 1";
   gen::property_set set(get_app());
   set["type"] = type;
   set["id"] = id;
   set.replace_ex1(sql);
   dprint(sql);
   var row = cyncedb().query_row(sql);
   return row;
}

var cynce::user_value_rows(const char * type, const char * userid, var taga)
{
   string str;
   string join1;
   gen::property_set set(get_app());
   set["type"] = type;
   set["userid"] = userid;

   int index = 0;
   string where1 = "`object_history`.userid = '$userid'";
   set.replace_ex1(where1);
   for(int i = 0; i < taga.array_get_count(); i++)
   {
      set["index"] = index;

      str = "INNER JOIN `object_tag` as `object_tag$index` ON `object_tag$index`.object = `object`.object INNER JOIN `tag` as `tag$index` ON `tag$index`.`id` = `$type_tag$index`.`tag` ";
      set.replace_ex1(str);
      join1 += str;

      str = " AND `tag$index`.`title` = '$tag'";
      set.replace_ex1(str);
      where1 += str;

      index++;
   }

   string sql = "SELECT $type.id, $type.value FROM $type INNER JOIN  `{$type}_history` ON `{$type}_history`.`{$type}id` = $type.`id` $join1 WHERE $where1 GROUP BY $type.id ORDER BY `{$type}_history`.`editdatetime` DESC";
   set.replace_ex1(sql);
   dprint(sql);
   var rows = cyncedb().query_rows(sql);
   return rows;
}

/*
bool cynce::set_user_value(const char * type, const char * creatorid, var taga, var value, const char * ownerid)
{
   var rows = user_value_rows(type, userid, taga);
   var editdatetime = now_editdatetime();
   if(rows.array_get_count() > 0)
   {
      return update_value(editdatetime, type, rows.vara()[0].vara()[0], creatorid, taga, value, ownerid);
   }
   else
   {
      return insert_value(editdatetime, type, creatorid, taga, value, ownerid);
   }
}
*/
var cynce::valueid(var type, var value)
{
   gen::property_set set(get_app());
   set["type"] = type;
   set["typeid"] = objecttype_id(type);
   set["value"] = cyncedb().real_escape_string(value);
   set["field"] = objecttype_field(type);

   string sql = "SELECT id FROM $type WHERE $field = '$value'";
   set.replace_ex1(sql);
   var varId = cyncedb().query_item(sql);
   if(!varId.is_new())
      return varId;

   sql = "INSERT INTO $type (`$field`) VALUES ('$value')";
   set.replace_ex1(sql);
   dprint(sql);
   if(cyncedb().query(sql) == NULL)
      return ::var(::var::e_type::type_null);

   return cyncedb().get_insert_id();
}

bool cynce::update_object(var object, var editdatetime, var type, var value, var owner, var name, var description)
{
   gen::property_set set(get_app());
   set["editdatetime"] = editdatetime.is_empty() ? System.datetime().international().get_gmt_date_time() : editdatetime;
   set["object"] = object;
   set["objecttype"] = objecttype_id(type);
   set["objectid"] = valueid(type, value);
   set["owner"] = owner;
   set["name"] = name.is_empty() ? editdatetime : cyncedb().real_escape_string(name);
   set["description"] = cyncedb().real_escape_string(description);

   string sql = "UPDATE `object` SET `objecttype` = $objecttype, `objectid` = $objectid, `owner` = $owner, `name` = '$name', `description` = '$description' WHERE `object` = '$object'";
   set.replace_ex1(sql);
   dprint(sql);
   if(cyncedb().query(sql) == NULL)
      return false;

   sql = "INSERT INTO `object_history` (`object`, `objecttype`, `objectid`, `editdatetime`, `owner`, `name`, `description`) VALUES ('$object', '$objecttype', '$objectid', '$editdatetime', '$owner', '$name', '$description')";
   set.replace_ex1(sql);
   dprint(sql);
   if(cyncedb().query(sql) == NULL)
      return false;

   return true;
}

var cynce::object_id(var objecttype, var objectid, var owner)
{
   gen::property_set set(get_app());
   set["objecttype"] = objecttype;
   set["objectid"] = objectid;
   set["owner"] = owner;

   string sql = "SELECT `object` FROM `object` WHERE `objecttype` = '$objecttype' AND `objectid` = '$objectid' AND `owner` = '$owner'";
   set.replace_ex1(sql);
   dprint(sql);
   return cyncedb().query_item(sql);
}

bool cynce::set_object(var creator, var editdatetime, var type, var value, var owner, var name, var description, var taga)
{
   gen::property_set set(get_app());
   set["creator"] = creator;
   set["editdatetime"] = editdatetime.is_empty() ? System.datetime().international().get_gmt_date_time() : editdatetime;
   set["objecttype"] = objecttype_id(type);
   set["objectid"] = valueid(type, value);
   set["owner"] = owner;
   set["name"] = name.is_empty() ? editdatetime : cyncedb().real_escape_string(name);
   set["description"] = cyncedb().real_escape_string(description);
   var object = object_id(set["objecttype"], set["objectid"], owner);

   if(object.is_new())
   {
      return insert_object(creator, editdatetime, type, value, owner, name, description, taga);
   }
   else
   {
      return update_object(object, editdatetime, type, value, owner, name, description, taga);
   }

}


bool cynce::update_object(var object, var editdatetime, var type, var value, var owner, var name, var description, var taga)
{
   gen::property_set set(get_app());
   set["editdatetime"] = editdatetime.is_empty() ? System.datetime().international().get_gmt_date_time() : editdatetime;
   set["objecttype"] = objecttype_id(type);
   set["objectid"] = valueid(type, value);
   set["owner"] = owner;
   set["name"] = name.is_empty() ? editdatetime : cyncedb().real_escape_string(name);
   set["description"] = cyncedb().real_escape_string(description);
   set["object"] = object;

   string sql = "UPDATE `object` SET `objecttype` = '$objecttype', `objectid` = '$objectid', `owner` = '$owner', `name` = '$name', `description` = '$description' WHERE object = '$object'";
   set.replace_ex1(sql);
   dprint(sql);
   if(cyncedb().query(sql) == NULL)
      return false;


   sql = "INSERT INTO `object_history` (`object`, `objecttype`, `objectid`, `editdatetime`, `owner`, `name`, `description`) VALUES ('$object', '$objecttype', '$objectid', '$editdatetime', '$owner', '$name', '$description')";
   set.replace_ex1(sql);
   dprint(sql);
   if(cyncedb().query(sql) == NULL)
      return false;

   return insert_value_tags(editdatetime, set["object"], taga, owner);
}


bool cynce::insert_object(var creator, var editdatetime, var type, var value, var owner, var name, var description, var taga)
{
   gen::property_set set(get_app());
   set["creator"] = creator;
   set["editdatetime"] = editdatetime.is_empty() ? System.datetime().international().get_gmt_date_time() : editdatetime;
   set["objecttype"] = objecttype_id(type);
   set["objectid"] = valueid(type, value);
   set["owner"] = owner;
   set["name"] = name.is_empty() ? editdatetime : cyncedb().real_escape_string(name);
   set["description"] = cyncedb().real_escape_string(description);

   string sql = "INSERT `object` (`creator`, `objecttype`, `objectid`, `owner`, `name`, `description`) VALUES ('$creator', '$objecttype', '$objectid', '$owner', '$name', '$description')";
   set.replace_ex1(sql);
   dprint(sql);
   if(cyncedb().query(sql) == NULL)
      return false;

   set["object"] = cyncedb().get_insert_id();

   sql = "INSERT INTO `object_history` (`object`, `objecttype`, `objectid`, `editdatetime`, `owner`, `name`, `description`) VALUES ('$object', '$objecttype', '$objectid', '$editdatetime', '$owner', '$name', '$description')";
   set.replace_ex1(sql);
   dprint(sql);
   if(cyncedb().query(sql) == NULL)
      return false;

   return insert_value_tags(editdatetime, set["object"], taga, creator);
}

var cynce::objecttype_id(const char * name)
{
   string strName(name);
   if(strName == "ttext")
      return 0;
   else if(strName == "mtext")
      return 1;
   else if(strName == "fontopus.fun_bookmark")
      return 2;
   else
      return cyncedb().query_item("SELECT id FROM objecttype WHERE name = '" + strName + "'");
}

string cynce::objecttype_field(const char * name)
{
   string strName(name);
   if(strName == "ttext")
      return "value";
   else if(strName == "mtext")
      return "value";
   else if(strName == "fontopus.fun_bookmark")
      return "url";
   else
      return cyncedb().query_item("SELECT field FROM objecttype WHERE name = '" + strName + "'");
}

var cynce::tag_id(const char * title)
{
   var tagid;
   single_lock sl(&get_manager()->m_mutexTagId);
   if(get_manager()->m_tagid.Lookup(title, tagid))
   {
      return tagid;
   }
   else
   {
      string strEscapeTitle = cyncedb().real_escape_string(title);
      tagid = cyncedb().query_item("SELECT id FROM tag WHERE title = '" + strEscapeTitle + "'");
      if(!tagid.is_new())
      {
         get_manager()->m_tagid[title] = tagid;
         return tagid;
      }
      string sql = eval("INSERT INTO tag (`title`, `creator`, `user`) VALUES ('" + strEscapeTitle + "', $secureuserid, $secureuserid)");
      dprint(sql);
      if(cyncedb().query(sql) == NULL)
         return ::var(::var::e_type::type_null);
      tagid = cyncedb().get_insert_id();
      string editdatetime = System.datetime().international().get_gmt_date_time();
      sql = eval("INSERT INTO tag_history (tag, `title`, editdatetime, user) VALUES ('" + tagid.get_string() + "', '" + strEscapeTitle + "', '" +editdatetime+"', $secureuserid)");
      dprint(sql);
      if(cyncedb().query(sql) == NULL)
         return ::var(::var::e_type::type_null);
      get_manager()->m_tagid[title] = tagid;
      return tagid;
   }
}

var cynce::create_tag_id(const char * title)
{
   var tagid;
   single_lock sl(&get_manager()->m_mutexTagId);
   string strEscapeTitle = cyncedb().real_escape_string(title);
   string sql = eval("INSERT INTO tag (`title`, `creator`, `user`) VALUES ('" + strEscapeTitle + "', $secureuserid, $secureuserid)");
   dprint(sql);
   if(cyncedb().query(sql) == NULL)
      return ::var(::var::e_type::type_null);
   tagid = cyncedb().get_insert_id();
   string editdatetime = System.datetime().international().get_gmt_date_time();
   sql = eval("INSERT INTO tag_history (tag, `title`, editdatetime, user) VALUES ('" + tagid.get_string() + "', '" + strEscapeTitle + "', '" +editdatetime+"', $secureuserid)");
   dprint(sql);
   if(cyncedb().query(sql) == NULL)
      return ::var(::var::e_type::type_null);
   get_manager()->m_tagid[title] = tagid;
   return tagid;
}

var cynce::tag_consume_min_count(const char * name)
{
   return cyncedb().query_item("SELECT consumemincount FROM tag WHERE id = '" + string(name) + "'");
}

var cynce::tag_consume_max_count(const char * name)
{
   return cyncedb().query_item("SELECT consumemaxcount FROM tag WHERE id = '" + string(name) + "'");
}

var cynce::value_tags(const char  * type, var valueid)
{
   gen::property_set set(get_app());
   set["object"] = object_id(objecttype_id(type), valueid, gprop("secureuserid"));

   string sql = "SELECT tag.title FROM tag INNER JOIN `object_tag` ON tag.id =  `object_tag`.tag WHERE `object_tag`.object = $object";
   set.replace_ex1(sql);
   dprint(sql);
   return cyncedb().query_items(sql);
}

var cynce::value_taga(const char * type, var valueid)
{
   gen::property_set set(get_app());
   set["object"] = object_id(objecttype_id(type), valueid, gprop("secureuserid"));

   string sql = "SELECT `object_tag`.tag, `object_tag`.tag2, `object_tag`.tag3, `object_tag`.tag4, `object_tag`.tag5 FROM `object_tag` WHERE `object_tag`.object = $object";
   set.replace_ex1(sql);
   dprint(sql);

   var rows = cyncedb().query_rows(sql);

   stringa lines;
   for(int i = 0; i < rows.array_get_count(); i++)
   {
      var row = rows.at(i);
      string line = row.at(0);
      for(int j = 1; j <= 4; j++)
      {
         if(row.at(j) != 0)
         {
            line += "-" + row.at(j);
         }
      }
      lines.add(line);
   }
   return lines;
}

var cynce::object_taga(var object)
{
   string sql = "SELECT `object_tag`.tag, `object_tag`.tag2, `object_tag`.tag3, `object_tag`.tag4, `object_tag`.tag5  FROM `object_tag` WHERE `object_tag`.object = '" + object.get_string() +"'";
   dprint(sql);
   var rows = cyncedb().query_rows(sql);
   stringa lines;
   for(int i = 0; i < rows.array_get_count(); i++)
   {
      var row = rows.at(i);
      string line = row.at(0);
      if(!row.at(1).is_new())
      {
         line += "-" + row.at(1);
      }
      if(!row.at(2).is_new())
      {
         line += "-" + row.at(2);
      }
      if(!row.at(3).is_new())
      {
         line += "-" + row.at(3);
      }
      if(!row.at(4).is_new())
      {
         line += "-" + row.at(4);
      }
      lines.add(line);
   }
   return lines;
}

bool cynce::tags_match(var taga1, var taga2)
{
   return tags_contains(taga1, taga2) && tags_contains(taga2, taga1);
}

bool cynce::tags_contains(var taga1, var taga2)
{
   for(int i = 0; i < taga2.array_get_count(); i++)
   {
      var tag2 = taga2.at(i);
      if(!taga1.array_contains(tag2))
         return false;
   }
   return true;
}

bool cynce::update_value_tags(var editdatetime, var object, var addtags, var removetags, var creator)
{
   if(!insert_value_tags(editdatetime, object, addtags, creator))
         return false;
   if(!remove_value_tags(editdatetime, object, removetags, creator))
         return false;
   return true;
}

bool cynce::insert_value_tags(var editdatetime, var object, var taga, var creator)
{
   for(int i = 0; i < taga.array_get_count(); i++)
   {
      if(!insert_value_tag(editdatetime, object, taga.at(i), creator))
         return false;
   }
   return true;
}

bool cynce::remove_value_tags(var editdatetime, var object, var taga, var creator)
{
   for(int i = 0; i < taga.array_get_count(); i++)
   {
      if(!remove_value_tag(editdatetime, object, taga.at(i), creator))
         return false;
   }
   return true;
}

bool cynce::insert_value_tag(var editdatetime, var object, var tag, var creator)
{
   string sql;
   var tags;
   tags.stra().add_tokens(tag, "-", false);

   gen::property_set set(get_app());
   set["editdatetime"] = editdatetime;
   set["object"] = object;
   set["tag1"] = tags.array_get_count() > 0 ? tags.at(0) : "0";
   set["tag2"] = tags.array_get_count() > 1 ? tags.at(1) : "0";
   set["tag3"] = tags.array_get_count() > 2 ? tags.at(2) : "0";
   set["tag4"] = tags.array_get_count() > 3 ? tags.at(3) : "0";
   set["tag5"] = tags.array_get_count() > 4 ? tags.at(4) : "0";
   set["creator"] = creator;

   sql = "INSERT INTO `object_tag` (`object`, `tag`, `tag2`, `tag3`, `tag4`, `tag5`, `creator`) VALUES ('$object', '$tag1', '$tag2', '$tag3', '$tag4', '$tag5', '$creator')";
   set.replace_ex1(sql);
   dprint(sql);
   if(cyncedb().query(sql) == NULL)
      return false;

   sql = "INSERT INTO `object_tag_history` (`object`, `tag`, `tag2`, `tag3`, `tag4`, `tag5`, `editdatetime`, `creator`) VALUES ('$object', '$tag1', '$tag2', '$tag3', '$tag4', '$tag5', '$editdatetime', '$creator')";
   dprint(sql);
   set.replace_ex1(sql);
   if(cyncedb().query(sql) == NULL)
      return false;

   return true;
}

bool cynce::remove_value_tag(var editdatetime, var object, var tag, var creator)
{
   string sql;
   var tags;
   tags.stra().add_tokens(tag, "-", false);

   gen::property_set set(get_app());
   set["editdatetime"] = editdatetime;
   set["object"] = object;
   set["tag1"] = tags.array_get_count() > 0 ? tags.at(0) : "0";
   set["tag2"] = tags.array_get_count() > 1 ? tags.at(1) : "0";
   set["tag3"] = tags.array_get_count() > 2 ? tags.at(2) : "0";
   set["tag4"] = tags.array_get_count() > 3 ? tags.at(3) : "0";
   set["tag5"] = tags.array_get_count() > 4 ? tags.at(4) : "0";
   set["creator"] = creator;

   sql = "DELETE FROM `object_tag` WHERE `object` = $object AND `tag` =  $tag1 AND `tag2` =  $tag2 AND `tag3` =  $tag3 AND `tag4` =  $tag4 AND `tag5` =  $tag5 LIMIT 1";
   set.replace_ex1(sql);
   dprint(sql);
   if(cyncedb().query(sql) == NULL)
      return false;

   return true;
}

var cynce::tag_title_id(var tag)
{
   return cyncedb().query_item("SELECT id FROM tag WHERE title = '"+ tag.get_string() +"'");
}

var cynce::now_editdatetime()
{
   return System.datetime().str().get_gmt_date_time();
}

var cynce::taga_from_tagids(var tagids)
{
   var tagida;
   tagida.stra().explode(",", tagids);
   var taga;
   for(int i = 0; i < tagida.array_get_count(); i++)
   {
      string tagid = tagida.at(i);
      taga.stra().add(cyncedb().query_item("SELECT title FROM tag WHERE id = '" + tagid + "'").get_string());
   }
   return taga;
}


bool cynce::set_ambient(var id)
{
   gen::property_set set(get_app());
   set["id"] = id;
   set["secureuserid"] = gprop("secureuserid");
   string sql;
   sql = "UPDATE user SET tag = '$id' WHERE id = $secureuserid LIMIT 1";
   set.replace_ex1(sql);

   if(cyncedb().query(sql) != NULL)
   {
      print("Set Ambient Success");
      return true;
   }
   else
   {
      print("Set Ambient Failure");
      return false;
   }

}

var cynce::get_request_topic()
{

   string req = inattr("REQUEST");

   strsize pos = req.find('?');

   if(pos < 0)
      return req.Mid(1);
   else
      return req.Mid(1, pos - 1);

}

var cynce::get_current_user_secure_tag()
{
   return user_tag(gprop("secureuserid"));
}


var cynce::user_tag(const char * pszId)
{
   string tagid;
   if(get_manager()->m_usersecuretagid.Lookup(pszId, tagid))
   {
      return tagid;
   }
   else
   {
      string sql =
         "SELECT securetag FROM fontopus.fun_user WHERE id = "
         + string(pszId) +
         " AND ca2associate = '1' AND register = '1' LIMIT 1";
      tagid = cyncedb().query_item(sql);
      get_manager()->m_usersecuretagid[pszId] = tagid;
      return tagid;
   }
}


var cynce::value_ids(var plus_taga, var minus_taga)
{
   string sql;
   string join1;
   string str;

   gen::property_set set(get_app());
   set["type"] = "object";
   set["user_tag"] = get_current_user_secure_tag();

   stringa where1;
   stringa having1;

   dprint("cynce_value_ids");
   dprint("plus=");
   dprint(plus_taga.stra().implode(","));
   dprint(";minus=");
   dprint(minus_taga.stra().implode(","));

   int index = 0;
   for(int i = 0; i < plus_taga.array_get_count(); i++)
   {
      var tag = plus_taga.at(i);
      set["index"] = index;
      stringa a;
      a.explode("-", tag);
      if(a.get_count() == 1)
      {
         str = "LEFT OUTER JOIN `$type_tag` as `$type_tag$index` ON `$type_tag$index`.{$type} = `{$type}`.id AND (`$type_tag$index`.`tag` = '$tag') ";
         set.replace_ex1(str);
         join1 += str;
      }
      else
      {
         str = "LEFT OUTER JOIN `$type_tag` as `$type_tag$index` ON `$type_tag$index`.{$type} = `{$type}`.id AND (`$type_tag$index`.`tag` = '{$a[0]}' AND `$type_tag$index`.`tag2` = '{$a[1]}') ";
         set.replace_ex1(str);
         join1 += str;
      }
      str = " COUNT(`$type_tag$index`.`{$type}`) > 0";
      having1.add(str);

      //      $join1 .= "INNER JOIN `$type_tag` as `$type_tag$index` ON `$type_tag$index`.{$type} = `{$type}`.id  ";
      //         $where1[] = " `$type_tag$index`.`tag` = '$tag'";
      //         foreach($minus_taga as $tag2)
      //      {
      //      $where1 .= " AND `$type_tag$index`.`tagid` != '$tag2'";
      //}
      index++;
   }
   for(int i = 0; i < minus_taga.array_get_count(); i++)
   {
      var tag = minus_taga[i];
      set["index"] = index;
      stringa a;
      a.explode("-", tag);
      if(a.get_count() == 1)
      {
         join1 += set.eval("LEFT OUTER JOIN `$type_tag` as `$type_tag$index` ON `$type_tag$index`.{$type} = `{$type}`.id AND (`$type_tag$index`.`tag` = '$tag') ");
      }
      else
      {
         join1 += set.eval("LEFT OUTER JOIN `$type_tag` as `$type_tag$index` ON `$type_tag$index`.{$type} = `{$type}`.id AND (`$type_tag$index`.`tag` = '{$a[0]}' AND `$type_tag$index`.`tag2` = '{$a[1]}') ");
      }
      having1.add(set.eval(" COUNT(`$type_tag$index`.`{$type}`) = 0"));
      //         foreach($minus_taga as $tag2)
      //      {
      //      $where1 .= " AND `$type_tag$index`.`tagid` != '$tag2'";
      //}
      index++;
   }
   int index2 = index + 1;
   set["index2"] = index2;
   set["index"] = index;
   join1 += set.eval("LEFT OUTER JOIN `$type_tag` as `$type_tag$index` ON `$type_tag$index`.{$type} = `{$type}`.id AND `$type_tag$index`.`tag` = '8' ");
   join1 += set.eval("LEFT OUTER JOIN `$type_tag` as `$type_tag$index2` ON `$type_tag$index2`.{$type} = `{$type}`.id  LEFT OUTER JOIN tag_tag as tt1 ON tt1.tag = `$type_tag$index2`.`tag`  LEFT OUTER JOIN tag_tag as tt2 ON tt1.tag2 = tt2.tag1 AND tt2.tag2 = $user_tag");
   having1.add(set.eval(" (COUNT(`$type_tag$index`.`{$type}`) = 0 OR COUNT(tt2.tag1) > 0)"));
   index = index2 + 1;
   set["index"] = index;

   if(where1.get_count() > 0)
   {
      set["where"] = " WHERE " + where1.implode(" AND ");
   }
   if(having1.get_count() > 0)
   {
      set["having"] = " HAVING " + having1.implode(" AND ");
   }


   sql = set.eval("SELECT $type.type, $type.id FROM $type $join1 $where GROUP BY $type.id $having");
   dprint(sql);
   var rows = cyncedb().query_rows(sql);
   return rows;
}

var cynce::objecttype_name(var id)
{
   return cyncedb().query_item("SELECT name FROM objecttype WHERE id = " + id.get_string());
}

var cynce::value(const char * type, const char * id)
{
   string sql = "SELECT `{$type}`.value FROM `{$type}` WHERE `{$type}`.id = '$id' LIMIT 1";
   gen::property_set set(get_app());
   set["type"] = type;
   set["id"] = id;
   set.replace_ex1(sql);
   dprint(sql);
   var value = cyncedb().query_item(sql);
   return value;
}

var cynce::tag_name(const char * id)
{
   string tagname;
   single_lock sl(&get_manager()->m_mutexTagName);
   if(get_manager()->m_tagname.Lookup(id, tagname))
   {
      return tagname;
   }
   else
   {
      tagname = cyncedb().query_item("SELECT t1.title FROM tag as t1 WHERE t1.id = '" + string(id) +"'");
      get_manager()->m_tagname.set_at(id, tagname);
      return tagname;
   }

}

var cynce::tag_namea(const char * id)
{
   var ida;
   ida.stra().explode("-", id);
   var a;
   for(int i = 0; i < ida.array_get_count(); i++)
   {
      var item = ida.at(i);
      a.stra().add(tag_name(item).get_string());
   }
   return a;
}

bool cynce::tag_tag3_set(
      var tag,
      var tag2,
      var tag3,
      var editdatetime,
      var creator)
{
   if(NULL == cyncedb().query("REPLACE INTO tag_tag3 (tag, tag2, tag3, creator) VALUES ('"+ tag +"', '"+ tag2 +"', '"+ tag3 +"', '" + creator + "')"))
   {
      return false;
   }
   if(NULL == cyncedb().query("INSERT INTO tag_tag3_history (editdatetime, tag, tag2, tag3, creator) VALUES ('"+ editdatetime +"', '"+ tag +"', '"+ tag2 +"', '"+ tag3 + "', '"+ creator +"')"))
   {
      return false;
   }
   return true;
}


bool cynce::tag_tag3_set(
      var tag,
      var tag2,
      var tag3)
{
   string editdatetime = System.datetime().international().get_gmt_date_time();
   return tag_tag3_set(tag, tag2, tag3, editdatetime, gprop("secureuserid"));
}


} // namespace webserver
