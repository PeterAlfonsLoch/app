#pragma once


namespace webserver
{


   class CLASS_DECL_ca cynce :
      virtual public dynamic_source::ptr
   {
   public:
      var value_rows(var type, var plus_taga, var minus_taga);
      var value_user(const char * type, const char * id);
      var value_tags(const char  * type, var valueid);
      var value_taga(const char * type, var valueid);
      var user_value_rows(const char * type, const char * $userid, var taga);
      var object_taga(var valueid);

      bool tags_match(var taga1, var taga2);
      bool tags_contains(var taga1, var taga2);

      var valueid(var type, var value);
      bool set_object(var creator, var editdatetime, var type, var value, var owner, var name, var description, var taga);
      bool update_object(var object, var editdatetime, var type, var value, var owner, var name, var description, var taga);
      bool insert_object(var creator, var editdatetime, var type, var value, var owner, var name, var description, var taga);
      bool update_object(var object, var editdatetime, var type, var value, var owner, var name, var description);
      bool update_value_tags(var editdatetime, var object, var addtags, var removetags, var creator);
      bool insert_value_tags(var editdatetime, var object, var taga, var creator);
      bool remove_value_tags(var editdatetime, var object, var taga, var creator);
      bool insert_value_tag(var editdatetime, var object, var tag, var creator);
      bool remove_value_tag(var editdatetime, var object, var tag, var creator);

      bool set_ambient(var id);
      var objecttype_id(const char * name);
      string objecttype_field(const char * name);
      // pick random tag with the specified title 
      // and create a new tag if a tag with the 
      // specified title does not exist.
      var tag_id(const char * title); 
      // create a new tag with the specified title
      // even if a tag with the specified title 
      // already exist.
      var create_tag_id(const char * title);
      var object_id(var objecttype, var objectid, var owner);
      var tag_consume_min_count(const char * name);
      var tag_consume_max_count(const char * name);
      var user_tag(const char * pszId);
      var get_current_user_secure_tag();
      var tag_title_id(var tag);
      var now_editdatetime();
      var taga_from_tagids(var tagids);
      var get_request_topic();
      var value_ids(var plus_taga, var minus_taga);
      var objecttype_name(var id);
      var value(const char * type, const char * id);
      var tag_name(const char * id);
      var tag_namea(const char * id);

      bool tag_tag3_set(var tag, var tag2, var tag3);
      bool tag_tag3_set(var tag, var tag2, var tag3, var editdatetime, var userid);

   };


} // namespace webserver


