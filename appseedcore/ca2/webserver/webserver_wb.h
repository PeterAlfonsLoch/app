#pragma once


namespace webserver
{

   class CLASS_DECL_ca wb :
      public dynamic_source::ptr
   {
   public:
      wb();

      var check_board_privilege(var idAdress);
      bool check_invite_to_board_privilege(var idAdress);
      var get_address_type(var loc);
      var get_address_type_list_title(var id);
      var get_address_type_name(var id);
      var get_address_type_id(var id);
      var get_address_path_name(var id, const char * pszStyle = NULL);
      var get_address_path_name_text(var id);
      var get_address_name_text(var id);
      var get_current_user_board();
      bool create_loc(var parent, var tag, var type);
      bool check_create_board_privilege(var parent);
      bool create_board(var parent, var tag);
      bool invite_to_board(var email, var name,  var board);
      string accept_invitation_to_board(var varEmail, var varBoard, var varHash);

   };


} // namespace webserver


