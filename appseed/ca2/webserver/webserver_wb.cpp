#include "StdAfx.h"


namespace webserver
{


   wb::wb()
   {
   }
   
   var wb::check_board_privilege(var idAddress)
   {
      string strSql = eval("SELECT COUNT(tag_tag3.tag) FROM tag_tag3 INNER JOIN fontopus.fun_user ON fontopus.fun_user.id = '$secureuserid' AND fontopus.fun_user.securetag = tag_tag3.tag WHERE tag_tag3.tag3 = '" + idAddress.get_string() + "' AND tag_tag3.tag2 = 100000080");
      if(cyncedb().query_item(strSql) == 1)
         return true;
      strSql = eval("SELECT creator FROM tag_tag3 WHERE tag_tag3.tag = '" + idAddress.get_string() + "' AND tag_tag3.tag2 = 100000080");
      if(((string) cyncedb().query_item(strSql) == (string) gprop("secureuserid")))
         return true;
      strSql = eval("SELECT creator FROM tag_tag3 WHERE tag_tag3.tag = '" + idAddress.get_string() + "' AND tag_tag3.tag2 = 100000001 AND tag_tag3.tag3 = 10005");
      if(((string) cyncedb().query_item(strSql) == (string) gprop("secureuserid")))
         return true;
      //strSql = eval("SELECT creator FROM tag_tag3 WHERE tag_tag3.tag = '" + idAddress.get_string() + "' AND tag_tag3.tag2 = 100000002");
      //if(!((string) cyncedb().query_item(strSql) == (string) gprop("secureuserid")))
        // return false;
      return false;
   }

   var wb::get_address_type(var loc)
   {
      string sql = "SELECT tt2.tag FROM tag_tag3 INNER JOIN tag_tag3 as tt2 ON tt2.tag = tag_tag3.tag3 WHERE tt2.tag3 = 1000000038 AND tt2.tag2 = 100000001 AND tag_tag3.tag2 = 100000001 AND tag_tag3.tag = " + loc.get_string();
      return cyncedb().query_item(sql);
   }

   var wb::get_address_type_list_title(var id)
   {
      return pstr("wb:addresstype:listtitle:" + id.get_string());
   }

   var wb::get_address_type_name(var id)
   {
      switch((int) id)
      {
      case 10001:
         return "land";
      case 10002:
         return "province";
      case 10003:
         return "location";
      case 10004:
         return "site";
      case 10005:
         return "address";
      default:
         return gen::g_nullconst;
      }
   }
   var wb::get_address_type_id(var id)
   {
      if(id == "land")
         return 10001;
      if(id == "province")
         return 10002;
      if(id == "location")
         return 10003;
      if(id == "site")
         return 10004;
      if(id == "address" || id == "board")
         return 10005;
      return gen::g_nullconst;
   }

   var wb::get_address_path_name(var id, const char * pszStyle)
   {
      var a = array();
      var path = "";
      string strStyle;
      if(pszStyle == NULL)
      {
         strStyle = "title2";
      }
      else
      {
         strStyle = pszStyle;
      }
      while(true)
      {
         if(in_array((int) id, a) || id.is_empty() || id == 0)
            return path;
         string item = "<span class='" + get_address_type_name(get_address_type(id)) + "-" + strStyle + "'>";
         item += cynce().tag_name(id);
         if(strlen(path) > 0)
            item += "&nbsp;";
         item += "</span>";
         path = item + path;
         string strSql = "SELECT tag_tag3.tag3 FROM tag_tag3 WHERE tag_tag3.tag = '" + id.get_string() + "' AND tag_tag3.tag2 = 100000080";
         dprint(strSql);
         id = cyncedb().query_item(strSql);
      }
   }

   var wb::get_address_name_text(var id)
   {
      return cynce().tag_name(id);
   }

   var wb::get_address_path_name_text(var id)
   {
      var path = "";
      var item;
      while(true)
      {
         if(id.is_empty() || id == 0)
            return path;
         string item = cynce().tag_name(id);
         if(strlen(path) > 0)
            item += "/";
         path = item + path;
         string strSql = "SELECT tag_tag3.tag3 FROM tag_tag3 WHERE tag_tag3.tag = '" + id.get_string() + "' AND tag_tag3.tag2 = 100000080";
         dprint(strSql);
         id = cyncedb().query_item(strSql);
      }
      return path;
   }

   var wb::get_current_user_board()
   {
      string strSql = eval("SELECT fun_user.currentboard FROM fun_user WHERE fun_user.id = '$secureuserid'");
      return musicdb().query_item(strSql);
   }

   bool wb::create_loc(var parent, var tag, var type)
   {
      if(get_address_type_id(type) == "1005")
      {
         if(!check_create_board_privilege(parent))
            return false;
      }
      var tagid = cynce().create_tag_id(tag);
      cynce().tag_tag3_set(tagid, 100000001, get_address_type_id(type));
      cynce().tag_tag3_set(tagid, 100000080, parent);
      return true;
   }
   bool wb::check_create_board_privilege(var parent)
   {
      var owner = cyncedb().query_item("SELECT user FROM tag_history WHERE tag = "+ parent + " ORDER BY editdatetime LIMIT 1");
      dprint("owner=" + owner);
      if(owner.is_new())
         return false;
      if(owner != gprop("secureuserid").get_value())
         return false;
      return true;
   }

   bool wb::invite_to_board(var varEmail, var varName, var varBoard)
   {
      string strBoard = varBoard;
      string strEmail = varEmail;
      string strHash = fun().key1_generate()+fun().key1_generate()+fun().key1_generate();

      gprop("name") = varName;
      gprop("email") = strEmail;
      gprop("sender_first_name") = musicdb().query_item(eval("SELECT firstname FROM fun_user WHERE id = $secureuserid"));
      gprop("sender_name") = gprop("sender_first_name") + " " + musicdb().query_item(eval("SELECT CONCAT(lastname) FROM fun_user WHERE id = $secureuserid"));
      gprop("sender_email") = musicdb().query_item(eval("SELECT email FROM fun_user WHERE id = $secureuserid"));
      gprop("board_name") = get_address_name_text(strBoard);
      gprop("board_path") = get_address_path_name_text(strBoard);
      gprop("link") = "http://whiteboard.veriwell.net/accept_invitation_to_join_board?id=" + strBoard + "&email="+ strEmail + "&hash=" + strHash;
      if(((int)musicdb().query_item(eval("SELECT COUNT(firstname) FROM fun_user WHERE email='$email'"))) == 0)
      {
         gprop("link") = "https://fontopus.com/register?force_email=" + strEmail + "&ruri=" + urlencode(gprop("link"));
      }
   email email(get_app());
   string templ;
   templ = langstr("invite_to_board_email");
   dprint(templ);
   if(templ.has_char())
   {
      email.m_strBody = eval(templ);
   }
   else
   {
      if(((int)musicdb().query_item(eval("SELECT COUNT(firstname) FROM fun_user WHERE email='$email'"))) == 1)
      {
      email.m_strBody = eval("Hi $name,\r\n\
\r\n\
I am inviting you to join the whiteboard \"$board_name\".\r\n\
Click in the link below to join the whiteboard using the email <$email>\r\n\
you have already used to register in ca2:\r\n\
\r\n\
   $link\r\n\
\r\n\
Details:\r\n\
   Sender: $sender_name\r\n\
   Sender Email: $sender_email\r\n\
   Board Name: $board_name\r\n\
   Board Path: $board_path\r\n\
\r\n");
      }
      else
      {
      email.m_strBody = eval("Hi $name,\r\n\
\r\n\
I am inviting you to join the whiteboard \"$board_name\".\r\n\
We have found that you are not registered in ca2.\r\n\
You will need to first register in ca2 to join the whiteboard.\r\n\
Click in the link below to register in ca2\r\n\
and to join the whiteboard using the email <$email>:\r\n\
(You can later change the email address by merging another e-mail account)\r\n\
\r\n\
   $link\r\n\
\r\n\
Details:\r\n\
   Sender: $sender_name\r\n\
   Sender Email: $sender_email\r\n\
   Board Name: $board_name\r\n\
   Board Path: $board_path\r\n\
\r\n");
      }

   }
      
//      $headers  = 'MIME-Version: 1.0' . "\r\n";
//      $headers .= 'Content-type: text/plain; charset=utf-8' . "\r\n";

      
      email.m_strSenderName = gprop("g_siteregistersendername");
      email.m_addressSender = gprop("g_siteregistersenderaddress");
      email.m_strRecipientName = string(varName);
      email.m_addressRecipient = strEmail;

      templ = langstr("invite_to_board_email_subject");
      dprint(templ);
      if(templ.has_char())
      {
//         $site = site_getRootTitle($param_locale);
         email.m_strSubject = eval(templ);
      }
      else
      {
         email.m_strSubject = eval("$sender_first_name is inviting you to join whiteboard $board_name");
      }
      
      dprint("email=" + email.m_addressRecipient.to_string());
      dprint("subject=" + email.m_strSubject);
      dprint("body=" + email.m_strBody);
      dprint("headers=" + email.m_strHeaders);
/*      mb_language('uni');
      if(mb_send_mail(
         $email, 
         $subject,
         $body,
         $headers))
         return true;*/

      

      
      if(!System.email().utf8_mail(email))
         return false;
      
      string strSql;
      strSql = "INSERT INTO wb_invitation_to_board (`board`, `invitedatetime`, `email`, `hash`) VALUES('"+strBoard+"', NOW(), '"+ strEmail +"', '" + strHash + "');";
      musicdb().query(strSql);
      return true;
   }

   bool wb::check_invite_to_board_privilege(var parent)
   {
      var owner = cyncedb().query_item("SELECT user FROM tag_history WHERE tag = "+ parent + " ORDER BY editdatetime LIMIT 1");
      dprint("owner=" + owner);
      if(owner.is_new())
         return false;
      if(owner != gprop("secureuserid").get_value())
         return false;
      return true;
   }

   bool wb::create_board(var parent, var tag)
   {
      return create_loc(parent, tag, "board");
   }

   string wb::accept_invitation_to_board(var varEmail, var varBoard, var varHash)
   {
      if(string(musicdb().query_item(eval("SELECT email FROM fun_user WHERE id = $secureuserid")))
         != string(varEmail))
      {
         return "You should be logged in with the same e-mail address the invitation is addressed. You can later change this by merging anothr e-mail address and changing the current one.";
      }
      if(musicdb().query_item("SELECT COUNT(invitedatetime) FROM wb_invitation_to_board WHERE email = '"
         + varEmail + "' AND board = '" + varBoard + "' and hash = '" + varHash + "'") == 1)
      {
         string securetag =  string(musicdb().query_item(eval("SELECT securetag FROM fun_user WHERE id = $secureuserid")));
         if(strlen(securetag) == 0 || securetag == "0")
         {
            
            securetag = cynce().tag_id(string(musicdb().query_item(eval("SELECT CONCAT(firstname, ' ', lastname) FROM fun_user WHERE id = $secureuserid")))
               + " (" + fun().key1_generate() + ")");
            if(strlen(securetag) > 0 && securetag != "0")
            {
               musicdb().query(eval("UPDATE fun_user SET securetag = '"+securetag+"' WHERE id = $secureuserid"));
               securetag =  string(musicdb().query_item(eval("SELECT securetag FROM fun_user WHERE id = $secureuserid")));
            }
         }
         if(strlen(securetag) == 0 || securetag == "0")
         {
            return "coulld not find a secure tag for the user";
         }
         cynce().tag_tag3_set(securetag, 100000080, varBoard);
         musicdb().query(eval("INSERT INTO wb_user_address (`user`, `address`) VALUES('$secureuserid', '" + varBoard + "')"));
         return "Success! You are now connected to the board";
      }
      else
      {
         return "Some error occurred; Invitation seems to be invalid.";
      }
   }


} // namespace webserver


