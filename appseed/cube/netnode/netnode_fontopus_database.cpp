#include "StdAfx.h"

fontopus_database::fontopus_database(::ca::application * papp) :
   ca(papp),
   ::mysql::database(papp),
   netnode::database(papp),
   m_cache_person_only_name(papp),
   m_cache_person(papp)
{
   m_iLastServer = 0;
   m_pmusicdatabasecache = new music_database_cache();
}

fontopus_database::~fontopus_database()
{
}

bool fontopus_database::initialize()
{
   return initialize(m_iLastServer);
}

bool fontopus_database::initialize(int iServer)
{
   m_iLastServer = iServer;
   if(iServer == 0)
   {
      if(!connect(
         "localhost",
         "fontopus_web",
         "5dCAzq43",
         "fontopus"))
      {
         if(!connect(
            "ca2.cc",
            "fontopus_web",
            "5dCAzq43",
            "fontopus"))
         {
            return false;
         }
      }
   }
   else if(iServer == 1)
   {
      if(!connect(
         "fontopus.com",
         "fontopus_web",
         "5dCAzq43",
         "fontopus"))
      {
         return false;
      }
   }
   else if(iServer == 2)
   {
      if(!connect(
         "localhost",
         "fontopus_web",
         "5dCAzq43",
         "gustavocc"))
      {
         if(!connect(
            "carlosgustavocecynlundgrenamacamilosasuketsumanuma.us.ca2.se",
            "fontopus_web",
            "5dCAzq43",
            "fontopus"))
         {
            return false;
         }
      }
   }
   return true;
}

bool fontopus_database::get_session(const char * pszId, gen::property_set & set)
{
   if(m_pmysql == NULL)
      return false;
   if(pszId == NULL)
      return false;
   if(strlen(pszId) == 0)
      return false;
   string strSql;
   strSql.Format("SELECT `value` FROM fun_session WHERE id = '%s'", string(pszId).Left(255));
   var var = query_item(strSql);
   if(var.is_new())
      return false;   
   System.base64().unserialize(var.get_string(), set);
   return true;
}

bool fontopus_database::set_session(const char * pszId, gen::property_set & set)
{
   if(m_pmysql == NULL)
      return false;
   string str;
   str = System.base64().serialize(set);
   str = real_escape_string(str);
   string strSql;
   strSql.Format("REPLACE INTO fun_session(`id`, `value`) VALUES ('%s', '%s')", string(pszId).Left(255), str);
   dprint("<h2>Going to query fontopus database " + strSql + "</h2>");
   until_here();
   bool bOk = netnode::database::query(strSql) != NULL;
   dprint("<h2>Queried fontopus database " + strSql + "</h2>");
   until_here();
   return bOk;
}


void fontopus_database::set_fun_session(const char * pszUserId, const char * pszSessId)
{
    session_id(fun_str_decrypt(pszUserId, pszSessId));
}

string fontopus_database::get_fun_session(const char * pszUserId)
{
   return fun_str_encrypt(pszUserId, session_id());
}


string fontopus_database::fun_str_encrypt(const char * pszUserId, const char * psz)
{
   dprint("fun_str_encrypt");
   string str;
   System.crypt().encrypt(str, psz, fun_user_get_key1(pszUserId));
   return str;
}

string fontopus_database::fun_str_decrypt(const char * pszUserId, const char * psz)
{
   dprint("fun_str_decrypt");
   string str;
   System.crypt().decrypt(str, psz, fun_user_get_key1(pszUserId));
   return str;
}


string fontopus_database::fun_user_get_key1(const char * pszUserId)
{
   if(m_pmysql == NULL)
      return "";
   string strKey1 = m_pinterface->get_manager()->m_strmapFunUserKey[pszUserId];
   if(strKey1.get_length() > 5)
      return strKey1;
   dprint("fun_user_get_key1");
   string strSql;
   strSql.Format("SELECT key1 FROM fun_user WHERE id = %s", pszUserId);
   strKey1 = query_item(strSql);
   if(strKey1.get_length() > 5)
   {
      m_pinterface->get_manager()->m_strmapFunUserKey.set_at(pszUserId, strKey1);
      return strKey1;
   }
   strKey1 = System.crypt().strkey();
   dprint("generatedkey = $key1");
   strSql.Format("UPDATE fun_user SET `key1` = '%s' WHERE id = %s LIMIT 1", strKey1, pszUserId);
   query(strSql);
   strSql.Format("SELECT key1 FROM fun_user WHERE id = %s", pszUserId);
   strKey1 = query_item(strSql);
   return strKey1;
}





var fontopus_database::_fun_get_dataclass(const char * pszId)
   {
      if(m_pmysql == NULL)
         return gen::g_nullconst;
      string identifier = real_escape_string(pszId);
      string strSql;
      strSql.Format("SELECT id FROM fun_dataclass WHERE `identifier` = '%s'", identifier);
      var id = query_item(strSql);
      if(!id.is_set())
      {
         strSql.Format("INSERT INTO fun_dataclass(`identifier`) VALUES ('%s')", identifier);
         query(strSql);
         id = get_insert_id();
      }
      return id;
   }
   
   
void fontopus_database::_fun_set_user_data(const char * pszUser, const char * pszKey, var var)
   {
      string strKey = _fun_get_dataclass(pszKey);
      string strValue = real_escape_string(var.get_string());
      string strSql;
      strSql.Format("REPLACE INTO fun_user_data(`user`, `class`, `data`) VALUES ('%s', '%s', '%s')",
         pszUser, strKey, strValue);
      query(strSql);
   }
 bool fontopus_database::_fun_get_user_data(const char * pszUser, const char * pszKey, var & var)
   {
      if(m_pmysql == NULL)
         return false;
      string strKey = _fun_get_dataclass(pszKey);
      string strSql;
      strSql.Format("SELECT `data` FROM fun_user_data WHERE user = '%s' AND class = '%s'",
         pszUser, strKey);
      class var item = query_item(strSql);
      if(!item.is_set())
         return false;
      var = item;
      return true;
   }

 bool fontopus_database::secure_email_available(const char * pszEmail)
   {
      if(m_pmysql == NULL)
         return false;
      if(!System.email().syntax_is_valid(pszEmail))
      {
         return false;
      }
      string strSql;
      strSql.Format("SELECT COUNT(*) FROM fun_user WHERE email = '%s'", pszEmail);
      var var = query_item(strSql);
      if(!var.is_set())
         return false;
      return var.get_integer() == 0;
   }


 bool fontopus_database::is_valid_pass_v1(const char * psz)
 {
      if(m_pmysql == NULL)
         return false;
    string str(psz);
    if(str.get_length() < 6)
       return false;
    return gen::str::has_all_v1(psz);
 }


string fontopus_database::secure_defer_register_login_email(
   const char * pszFirstName, 
   const char * pszLastName,
   const char * pszLogin, 
   const char * pszEmail,
   const char * pszRawPass,
   const char * pszInitialGroup,
   const char * pszRuri)
{
   if(m_pmysql == NULL)
      return "failed";
   if(!secure_email_available(pszEmail))
      return "failed";

   ::email::address addr(pszEmail);
   var varCount = query_item("SELECT COUNT(*) from veiev.site WHERE value = '" + addr.get_domain() + "'");                    
   bool bVeiev = varCount.get_integer() > 0;


   string strLoginForPassSalt(pszEmail);
   strLoginForPassSalt.make_lower();
   
   string strPass = System.crypt().v5_get_password_hash(pszRawPass);

   if(strPass.get_length() < 16)
      return "failed";

   string strPreHash;
   string str;
   strPreHash = pszLogin;
   strPreHash += pszEmail;
   str.Format("%d", System.math().RandRange(1000, 9999));
   strPreHash += str;
   str.Format("%d", System.math().RandRange(1000, 9999));
   strPreHash += str;
   str.Format("%d", System.math().RandRange(1000, 9999));
   strPreHash += str;
   str.Format("%d", System.math().RandRange(1000, 9999));
   strPreHash += str;
   str.Format("%d", System.math().RandRange(1000, 9999));
   strPreHash += str;
   string strHash = System.crypt().md5(strPreHash);
   string strSql;

   string strRequestRegisterDateTime(System.datetime().international().get_gmt_date_time());
   string strRegister;
   string strUserLevel;
   string strRegisterDateTime;
   if(bVeiev)
   {
      strRegister = "1";
      strUserLevel = "30";
      strRegisterDateTime = strRequestRegisterDateTime;
   }
   else
   {
      strRegister = "0";
      strUserLevel = "0";
      strRegisterDateTime = "0000-00-00 00:00:00";
   }
   strSql.Format("INSERT INTO fun_user (`firstname`, `lastname`, `login`, `email`, `password`, `hash`, `requestregisterdatetime`, `register`, `userlevel`, `registerdatetime`) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
      pszFirstName, pszLastName, pszLogin, pszEmail, strPass, strHash, strRequestRegisterDateTime, strRegister, strUserLevel, strRegisterDateTime);
   mysql::result * presult = query(strSql);
   if(presult == NULL)
      return "failed";
   string strUserId = get_insert_id();

   string strAgent;
   if(bVeiev)
   {
      strAgent = get_agent("veiev.cynce", pszEmail, strUserId);
   }
   
   string strGroupId;
   strGroupId.Format("%d", fun().get_group_id(pszInitialGroup));
   fun().add_user_group(str, strGroupId);
      
   gprop("insertid") = strUserId;
   dprint("insertid=$insertid");
      
   gprop("a") = strUserId;   
   gprop("b") = strHash;
   gprop("email") = pszEmail;
      
   if(gprop("g_site").get_string().is_empty())
   {
      //gprop("g_site") = site_getRootTitle($param_locale);
   }
   if(gprop("g_sitepath").get_string().is_empty())
   {
      //$g_sitepath = site_getRootPath($param_locale);
   }
/*   if(substr($sitepath, -1) != '/')
   {
      $sitepath .= '/';
   }*/
   email email(get_app());
   string templ;
   if(bVeiev)
   {
      templ = langstr("secure_register_login_email");
   }
   else
   {
       templ = langstr("secure_defer_register_login_email");
   }
   dprint(templ);
   if(gprop("g_siteregisteremail").get_string().find("?") < 0)
   {
      gprop("link") = eval("{$g_sitepath}{$g_siteregisteremail}?a=$a&b=$b&ruri=" + System.url().url_encode(pszRuri));
   }
   else
   {
      gprop("link") = eval("{$g_sitepath}{$g_siteregisteremail}&a=$a&b=$b&ruri=" + System.url().url_encode(pszRuri));
   }
   gprop("firstname") = pszFirstName;
   if(templ.has_char())
   {
      email.m_strBody = eval(templ);
   }
   else
   {
      if(bVeiev)
      {
      email.m_strBody = eval("Hi $firstname,\r\n\
\r\n\
We are registered in $g_site, and have a new email $email.\r\n\
\r\n\
$g_site\r\n\
Camilo Sasuke Tsumanuma\r\n");
      }
      else
      {
      email.m_strBody = eval("Hi $firstname,\r\n\
\r\n\
If you requested a registration in $g_site, please click in the link below to\r\n\
proceed with the registration:\r\n\
\r\n\
   $link\r\n\
\r\n\
$g_site\r\n\
Camilo Sasuke Tsumanuma\r\n");
      }

   }
      
//      $headers  = 'MIME-Version: 1.0' . "\r\n";
//      $headers .= 'Content-type: text/plain; charset=utf-8' . "\r\n";

      
      email.m_strSenderName = gprop("g_siteregistersendername");
      email.m_addressSender = gprop("g_siteregistersenderaddress");
      email.m_strRecipientName = string(pszFirstName) + " " + string(pszLastName);
      email.m_addressRecipient = pszEmail;

      templ = langstr("secure_defer_register_login_email_subject");
      dprint(templ);
      if(templ.has_char())
      {
//         $site = site_getRootTitle($param_locale);
         email.m_strSubject = eval(templ);
      }
      else
      {
         email.m_strSubject = eval("Your registration in $g_site");
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
      {
         strSql.Format("DELETE FROM fun_user WHERE `email` = '%s'", pszEmail);
         presult = query(strSql);
         if(bVeiev)
            return "failed_to_send_email";
         else
            return "failed";
      }
      if(bVeiev)
      {
         return "registered";
      }
      else
      {
         return "email";
      }

   }


   bool fontopus_database::secure_defer_register_a_b(const char * pszA, const char * pszB)
   {
      if(m_pmysql == NULL)
         return false;
//      print "xxx a=$a, b=$b";
      string strSql;
      strSql.Format("SELECT COUNT(*), `id` FROM fun_user WHERE `id`='%s' AND `hash`='%s' GROUP BY `id`", pszA, pszB);
      var var = query_rows(strSql);
      if(var.is_empty())
         return false;
      if(var.at(0).is_empty())
         return false;
      if(var.at(0).at(0).is_empty())
         return false;
      if(var.at(0).at(0).get_integer() <= 0)
         return false;
      return secure_make_available_a(var.at(0).at(1));
   }

   bool fontopus_database::secure_make_available_a(const char * pszA, int iLevel)
   {
      if(m_pmysql == NULL)
         return false;
      string strNow;
      class time time;
      time = time::get_current_time();
      time.FormatGmt(strNow, "%Y-%m-%d %H:%M:%S");
      string strSql;
      strSql.Format("UPDATE fun_user SET `register` = (`register` | 1), `userlevel` = '%d', `registerdatetime` = '%s' WHERE `id`='%s'", 
         iLevel, strNow, pszA);
      mysql::result * presult = query(strSql);
      return presult != NULL;
   }



   string fontopus_database::veriwell_get_class_string_item(const char * pszClassId)
   {
      if(m_pmysql == NULL)
         return "";
      var var = query_item("SELECT namestringid FROM class WHERE id = " + string(pszClassId));
      if(var.is_new())
         return "";
      return get_string(var);
   }


   string fontopus_database::get_string(var id, var langid)
   {
      if(langid == -1111111)
      {
         return get_lang_string(id, m_getstring_languageid);
      }
      else
      {
         return get_lang_string(id, langid);
      }
   }


   string fontopus_database::get_lang_string(var id, var languageid)
   {
      /*return "";
      /*if(is_array(m_stringtable[$languageid]))
      {
         if(isset(m_stringtable[$languageid][$id]))
         {
            return m_stringtable[$languageid][$id];
         }
      }*/
      //$db = m_db;
      //global $gc_mysql_metaobject_name_string;
      //$smm = $gc_mysql_metaobject_name_string;
      string sql = "SELECT string.value FROM string WHERE string.id = " + id + " AND string.languageid = " + languageid;
      return query_item(sql);
/*      var value = query_item(sql);
      if($value=== false)
         return false;
      if(!is_array(m_stringtable))
      {
         m_stringtable = base_array();
      }
      if(!is_array(m_stringtable[$languageid]))
      {
         m_stringtable[$languageid] = base_array();
      }
      m_stringtable[$languageid][$id] = $value;
      return $value;*/
   }


   var fontopus_database::insertLang(var lang)
   {
      gprop("i") = 40000;
      gprop("lang") = lang;
      while(gprop("i")  < 90000)
      {
         string sql = eval("INSERT INTO lang(id, lang, friendlyname) VALUES ('$i','$lang','$lang')");
         if(query(sql) != NULL)
            break;
         gprop("i")++;
      }
      return get_insert_id();
   }

   var fontopus_database::insertStyle(var style)
   {
      gprop("i") = 40000;
      gprop("style") = style;
      while(gprop("i")  < 90000)
      {
         string sql = eval("INSERT INTO style(id, style) VALUES ('$i','$style')");
         if(query(sql) != NULL)
            break;
         gprop("i")++;
      }
      return get_insert_id();
   }
   
   var fontopus_database::forceGetLangId(var lang)
   {
      var id = getLangId(lang);
      if(id.is_empty())
      {
         id = insertLang(lang);
      }
      return id;
   }

   var fontopus_database::forceGetStyleId(var style)
   {
      var id = getStyleId(style);
      if(id.is_empty())
      {
         id = insertStyle(style);
      }
      return id;
   }
   
   var fontopus_database::getLangId(var lang)
   {
      string strLang = lang;
      if(strLang == "se")
         return 11;
      else if(strLang.get_length() >= 1)
      {
         if(strLang[0] == 'a')
         {
            if(strLang == "at")
               return 22;
            else if(strLang == "ar")
               return 58;
         }
         else if(strLang[0] == 'e')
         {
            if(strLang == "en")
               return 0;
            else if(strLang == "es")
               return 3;
            else if(strLang == "en-uk")
               return 10;
         }
         else if(strLang[0] == 'p')
         {
            if(strLang == "pt-br")
               return 1;
            else if(strLang == "pt")
               return 8;
            else if(strLang == "pl")
               return 44;
         }
         else if(strLang[0] == 'i')
         {
            if(strLang == "it")
               return 2;
         }
         else if(strLang[0] == 'd')
         {
            if(strLang == "de")
               return 4;
            else if(strLang == "de_fuer_dich")
               return 488;
         }
         else if(strLang[0] == 'j')
         {
            if(strLang == "ja")
               return 7;
         }
         else if(strLang[0] == 'f')
         {
            if(strLang == "fr")
               return 9;
         }
         else if(strLang[0] == 'c')
         {
            if(strLang == "cn")
               return 67;
         }
         else if(strLang[0] == 'r')
         {
            if(strLang == "ru")
               return 59;
         }
         else if(strLang[0] == 'n')
         {
            if(strLang == "nl")
               return 56;
         }
         else if(strLang[0] == 'u')
         {
            if(strLang == "unk")
               return -1;
         }
      }
      return query_table_item("lang", "id", "`lang` = '" + strLang + "'", false);
   }

   var fontopus_database::getStyleId(var style)
   {
      string strStyle = style;
      if(strStyle == "se")
         return 11;
      if(strStyle == "at")
         return 22;
      if(strStyle == "carcc")
         return 1133;
      if(strStyle == "camcc")
         return 1107;
      if(strStyle == "en")
         return 0;
      if(strStyle == "pt-br")
         return 1;
      if(strStyle == "it")
         return 2;
      if(strStyle == "es")
         return 3;
      if(strStyle == "de")
         return 4;
      if(strStyle == "ja")
         return 7;
      if(strStyle == "pt")
         return 8;
      if(strStyle == "fr")
         return 9;
      if(strStyle == "en-uk")
         return 10;
      if(strStyle == "du")
         return 7714;
      if(strStyle == "bell")
         return 4000;
      if(strStyle == "mb")
         return 4001;
      if(strStyle == "mbpara")
         return 4002;
      if(strStyle == "carcc")
         return 1133;
      if(strStyle == "camcc")
         return 1107;
      if(strStyle == "veriwell")
         return 3500;
      if(strStyle == "veriwiki")
         return 3575;
      if(strStyle == "fontopus")
         return 5000;
      if(strStyle == "du")
         return 7714;
      if(strStyle == "ar")
         return 58;
      if(strStyle == "ru")
         return 59;
      if(strStyle == "cn")
         return 67;
      if(strStyle == "nl")
         return 56;
      if(strStyle == "pl")
         return 44;
      if(strStyle == "gpl")
         return 1033;
      if(strStyle == "unk")
         return -1;
      return query_table_item("style", "id", "`style` = '"+strStyle+"'", false);
   }

   music::song_ptr_array * fontopus_database::get_songs(
      var req_params, 
      var query,
      var song, 
      var lyrics, 
      var querystyle_arg, 
      var order, 
      int limitstart, 
      int limitcount,
      int & lastpage,
      int & totalcount,
      var cid,
      var aid,
      var topic,
      var funuid,
      var params,
      var flaga)
   {
      music::song_ptr_array * psonga = new music::song_ptr_array();
//      print "aaa".$funuid;   
//      print "fa=";
   //   print_r($flaga);
   
//      global $secureuserid;
//      global $param_locale;
//      global $param_style;
//      global $g_filter_classcondition;
//      global $g_exclude_classcondition;
//      global $g_filter_classflag1;
//      global $g_exclude_classflag1;
      
      var params_ex        = req_params;
         
      var lang             = gprop("g_base_param_locale");
      var style             = gprop("g_base_param_style");
      
      gprop("langid")      = get_lang_id(lang);
      gprop("styleid")     = get_style_id(style);
      gprop("limitstart")  = limitstart;
      gprop("limitcount")  = limitcount;
      
      //print "langid=$langid";
      //print "styleid=$styleid";
      
      var querystyle   = querystyle_arg;
      
      gprop("topictype") = calc_topic_type(topic);
      int iTopicType = gprop("topictype");

      gprop("aid") = aid;
      gprop("cid") = cid;
      
/*      
      if(isset($params_ex[0]['params']))
      {
         if(isset($params_ex[0]['params'][0]['topic']))
         {
            $querystyle = $params_ex[0]['params'][0]['topic'];
//            print "xxx";
         }
         if(isset($params_ex[0]['params'][0]['params']))
         {
            $querystyle_params = $params_ex[0]['params'][0]['params']; 
         }
         if(isset($params_ex[0]['params'][1]))
         {
            $order = $params_ex[0]['params'][1]['topic'];
         }
      }
*/
      string classcondition;
      if(strlen(cid) > 0)
      {
         stringa straClassId;
         straClassId.add_tokens(cid, ",", false);
         straClassId.QuickSort();
         straClassId.surround("<", ">");
         classcondition = "tmp_song.classida LIKE '%" + straClassId.implode("%") + "%' ";
      }
      if(gprop("g_filter_classflag1") != 0)
      {
         if(classcondition.has_char())
            classcondition += " AND ";
         classcondition += eval(" (tmp_song.classflag1 & '$g_filter_classflag1') != 0 ");
      }
      if(gprop("g_exclude_classflag1") !=0)
      {
         if(classcondition.has_char())
            classcondition += " AND ";
         classcondition += eval(" (tmp_song.classflag1 & '$g_exclude_classflag1') = 0 ");
      }
      
//      print "querystyle=$querystyle";
//      print "order=$order";

      var fun_userid;
      string leftouterjoin;
      string fun_field;
      
      bool bFun = fun().is_active();
      if(bFun)
      {
//         print "karaoke fun is enabled";
         if(querystyle == "fun")
         {
//            if(querystyle_params.is_set() && isset($querystyle_params[0]['topic']))
//            {
//               $fun_userid = $querystyle_params[0]['topic'];
//            }
//            else
            {
               fun_userid = gprop("secureuserid");
            }
         }
         if(funuid.get_string().has_char())
         {
            querystyle = "fun";
            fun_userid = funuid;
//               print 'xx';
         }
         leftouterjoin += " LEFT OUTER JOIN fun_user_class_song ON fun_user_class_song.song = song.id AND fun_user_class_song.user = $secureuserid ";
         fun_field = ", COUNT(fun_user_class_song.song) > 0";
//         $usersongida = fun_getUserSongId($secureuserid);
      //   print $fun_userid;
//      print "yyyy";
      }

      // Sort
//      global $gc_songtitle;
//      global $gc_click;
//      global $gc_performername;
      
//      $db = m_db;

      string fromappend;
      string sf_join_type;
      string innerjoin;
      string topic_table;
      string topic_field;
      string topic_field_append;
      string addwhereclause;
      string condition;
      var ida;
      var classida;
      var conds;
      
      gprop("groupby") = " topic_song.topic, topic_song.topictype ";
      if(gprop("topictype") == 2) // Cifras
      {
         dprint("<br>DB_READ:MAIN_MODE=cifras");
         sf_join_type = "LEFT OUTER JOIN";
         leftouterjoin += " LEFT OUTER JOIN chord ON chord.id = topic_song.topic ";
         innerjoin = eval(" INNER JOIN topic_song ON topic_song.topictype = $topictype AND topic_song.song = song.id INNER JOIN tmp_topic ON tmp_topic.topictype = $topictype AND tmp_topic.topic = topic_song.topic ");
         gprop("click_where") = "topic_song.topic";
         gprop("click_where_topictype") = "topic_song.topictype";
         gprop("topic_table") = "topic_song";
         gprop("topic_field") = "topic";
         gprop("topic_field_append") = ", topic_song.topic, topic_song.topictype, chord.comment ";
         gprop("click_type") = CLICK_CHORD_TOTAL;
      }
      else if(iTopicType == 1 || iTopicType == 1001) // Letras
      {
         dprint("<br>DB_READ:MAIN_MODE=letras");
         sf_join_type = "LEFT OUTER JOIN";
         leftouterjoin += " LEFT OUTER JOIN lyrics ON (topic_song.topictype = 1 AND lyrics.id = topic_song.topic) LEFT OUTER JOIN karfile_lyrics ON (topic_song.topictype = 1001 AND karfile_lyrics.karfile = topic_song.topic) ";
         innerjoin = " INNER JOIN topic_song ON topic_song.song = song.id INNER JOIN tmp_topic ON tmp_topic.topictype = topic_song.topictype AND tmp_topic.topic = topic_song.topic ";
         gprop("click_where") = "topic_song.topic";
         gprop("click_where_topictype") = "topic_song.topictype";
         gprop("topic_table") = "topic_song";
         gprop("topic_field") = "topic";
         gprop("topic_field_append") = ", topic_song.topic, topic_song.topictype, CASE topic_song.topictype WHEN 1 THEN lyrics.lyrics ELSE karfile_lyrics.lyrics END, lyrics.comment, IFNULL(lyrics.translation_language, -1) ";
         gprop("click_type") = CLICK_LYRICS_TOTAL;
         addwhereclause += " AND ((topic_song.topictype = 1 AND lyrics.id = topic_song.topic) OR (topic_song.topictype = 1001 AND karfile_lyrics.karfile = topic_song.topic)) ";
      }
      else
      {
         sf_join_type = "LEFT OUTER JOIN";
         innerjoin = eval(" INNER JOIN topic_song ON topic_song.topictype = $topictype AND topic_song.song = song.id INNER JOIN karfile ON karfile.id = topic_song.topic INNER JOIN tmp_topic ON tmp_topic.topictype = topic_song.topictype AND tmp_topic.topic = topic_song.topic ");
         gprop("click_where") = "topic_song.topic";
         gprop("click_where_topictype") = "topic_song.topictype";
         gprop("topic_table") = "topic_song";
         gprop("topic_field") = "topic";
         gprop("topic_field_append") = ", topic_song.topic, topic_song.topictype, karfile.filename ";
         gprop("click_type") = CLICK_KARAOKE_TOTAL;
      }
      
      
      if(song.get_string().has_char())
      {
         addwhereclause += " AND song.id = " + song.get_string() + " ";
      }
      else if(lyrics.get_string().has_char())
      {
         if(iTopicType != 1)
         {
            leftouterjoin += " LEFT OUTER JOIN lyrics ON (ts2.topictype = 1 AND lyrics.id = ts2.topic) LEFT OUTER JOIN karfile_lyrics ON (ts2.topictype = 1001 AND karfile_lyrics.karfile = ts2.topic) ";
            innerjoin += " INNER JOIN topic_song as ts2 ON ts2.song = song.id AND (ts2.topictype = 1 OR ts2.topictype = 1001)";
            addwhereclause += " AND (ts2.topictype = 1 AND ts2.topic = lyrics.id AND lyrics.lyrics LIKE '%" + lyrics.get_string() + "%') OR (ts2.topictype = 1001 AND ts2.topic = karfile_lyrics.karfile AND karfile_lyrics.lyrics LIKE '%" + lyrics.get_string() + "%') ";
         }
         else
         {
            addwhereclause += " AND ((topic_song.topictype = 1 AND lyrics.lyrics LIKE '%" + lyrics.get_string() + "%') OR (topic_song.topictype = 1001 AND karfile_lyrics.lyrics LIKE '%" + lyrics.get_string() + "%')) ";
         }
         
      }
      else if(query.get_string().has_char())
        {
         /*
         $regexpa = preg_split("/[\s!.,?\\/(){}[\]<>]+/", $query);
         $voida = base_array("the", "in", "of");
         $regexpa = array_diff($regexpa, $voida);
         $clausea = base_array();
         foreach($regexpa as $regexp)
         {
            $clausea[] = "song.title LIKE '%$regexp%'";
         }
         $clause = implode(" AND ", $clausea);
         $addwhereclause = " AND $clause ";
         */
    }
      else if(topic == "chord" && m_strMainMode != "cifras")
      {
         fromappend = ", chord_song ";
         addwhereclause = " AND chord_song.songid = song.id ";
      }
      
      if(classcondition.has_char())
      {
         if(addwhereclause.has_char())
         {
            addwhereclause += " AND ";
         }
         addwhereclause += classcondition;
      }
      
      bool perpertop;
      if(querystyle == SQS_PER_YEAR_TOP
        || querystyle == SQS_PER_MONTH_TOP
        || querystyle == SQS_PER_WEEK_TOP)
      {
         perpertop = true;
        }
        else
        {
         perpertop = false;
        }
      
      if(querystyle == SQS_PER_YEAR_TOP)
      {
         gprop("ppt_table") = "tmp_topic_click_year";
         dprint("<h4>year top</h4><br>");
         innerjoin += eval(" INNER JOIN tmp_topic_click_year ON tmp_topic_click_year.year = '"+ params["year"] +"' AND tmp_topic_click_year.langid='$langid' AND tmp_topic_click_year.styleid='$styleid' AND tmp_topic_click_year.click>0 AND tmp_topic_click_year.topic = $topic_table.$topic_field AND tmp_topic_click_year.type = $click_type ");
      }
      else if(querystyle == SQS_PER_MONTH_TOP)
      {
         gprop("ppt_table") = "tmp_topic_click_month";
         dprint("<h4>month top</h4><br>");
         innerjoin += eval(" INNER JOIN tmp_topic_click_month ON tmp_topic_click_month.year = '"+ params["year"] +"' AND tmp_topic_click_month.month = '"+ params["month"] +"' AND tmp_topic_click_month.langid='$langid' AND tmp_topic_click_month.styleid='$styleid' AND tmp_topic_click_month.click>0 AND tmp_topic_click_month.topic=$topic_table.$topic_field AND tmp_topic_click_month.type = $click_type");
      }
      else if(querystyle == SQS_PER_WEEK_TOP)
      {
         gprop("ppt_table") = "tmp_topic_click_week";
         dprint("<h4>week top</h4><br>");
         innerjoin += eval(" INNER JOIN tmp_topic_click_week ON tmp_topic_click_week.year = '"+ params["year"] +"' AND tmp_topic_click_week.month = '"+ params["month"] +"' AND tmp_topic_click_week.week = '"+ params["week"] +"' AND tmp_topic_click_week.langid='$langid' AND tmp_topic_click_week.styleid='$styleid' AND tmp_topic_click_week.click>0 AND tmp_topic_click_week.topic=$topic_table.$topic_field AND tmp_topic_click_week.type = $click_type");
      }


      if(strlen(aid) > 0)
      {
         innerjoin += " INNER JOIN topic_song as freetopictype_topic_song ON freetopictype_topic_song.song = song.id INNER JOIN topic_person ON topic_person.person = '$aid' AND topic_person.topic = topic_song.topic AND topic_person.topictype = freetopictype_topic_song.topictype ";
      }


      // copiei e adaptei de listPerformer.php
      if(order.is_empty())
      {
         order = ORDERBY_SONGNAME;
      }
      
      gprop("fieldappend") = "";
      gprop("songclick") = "tmp_topic_lang_style_click.click";
      
      
      bool defaultsql = true;
      
      string str;

      string sql;
      string sqlcount;
      
      if(querystyle == SQS_LAST_ACCESSES)
      {
         classcondition = "";
         sql = eval("SELECT typeid FROM click_type_group WHERE groupid = $click_type ");
         var types = query_items(sql);
         
//         $conda = base_array();
   //      foreach($types as $type)
      //   {
         //   $conda[] = "topic_click.type = $type";
//         }
   //      $conds = '('.implode(' OR ', $conda).')';
         conds = eval("topic_click.calc_topictype = '$topictype'");
         if(strlen(aid) > 0)
         {
            innerjoin = eval(" INNER JOIN topic_person ON topic_person.person = '$aid' AND topic_person.topic = topic_click.topic AND topic_person.topictype = topic_click.calc_topictype ");
         }
         else
         {
            innerjoin = "";
         }
         if(strlen(cid) > 0)
         {
            ida = classida;
            ida.stra().QuickSort();
            ida.stra().surround("'", "'");
            classcondition = ida.stra().implode(", ");
            classcondition = " AND topic_class.class IN (" + classcondition + ")";
            innerjoin += " INNER JOIN topic_class ON topic_class.topic = topic_click.topic AND topic_class.topictype = topic_click.calc_topictype";
         }
         
         // isrobot was put in ORDER BY clause to tip mysql to use the most optmized index.
         // it does not change order because it is constant
      
         sql = "SELECT topic_click.topic, topic_click.`datetime`, topic_click.`address`, topic_click.langid FROM topic_click "+innerjoin+" WHERE $conds AND isrobot = 0 AND langid = '$langid' AND styleid='$styleid' $classcondition GROUP BY topic_click.`datetime`, topic_click.`address` ORDER BY `datetime` DESC, `address` DESC";
         sqlcount = "SELECT COUNT(*) FROM topic_click "+innerjoin+" WHERE isrobot = 0 AND langid = '$langid' AND styleid='$styleid' AND $conds $classcondition";
//         print sql;
      //   print $sqlcount;
         defaultsql = false;
      }
      else if(querystyle == SQS_GLOBAL_TOP ||
            querystyle == SQS_LAST_YEAR_TOP ||
            querystyle == SQS_LAST_6_MONTH_TOP ||
            querystyle == SQS_LAST_3_MONTH_TOP||
            querystyle == SQS_LAST_MONTH_TOP ||
            querystyle == SQS_WEEK_TOP ||
            querystyle == SQS_24HOUR_TOP)
      {
         innerjoin += eval("INNER JOIN tmp_topic_lang_style_click ON tmp_topic_lang_style_click.langid = '$langid' AND  tmp_topic_lang_style_click.styleid = '$styleid' AND (tmp_topic_lang_style_click.topictype = $topictype");
         if(iTopicType == 1)
         {
            innerjoin += " OR tmp_topic_lang_style_click.topictype = 1001) ";
         }
         else
         {
            innerjoin += ") ";
         }
         gprop("groupby") = eval("GROUP BY $groupby");
         gprop("top_order") = "tmp_topic_lang_style_click.click DESC";
         gprop("top_where") = eval(" AND tmp_topic_lang_style_click.topic = $click_where ");
         int join_offset;
         if(querystyle == SQS_GLOBAL_TOP)
         {
            gprop("songclick") = "click";
            join_offset = 6;
         }
         else if(querystyle == SQS_LAST_YEAR_TOP)
         {
            gprop("songclick") = "clickLastYear";
            join_offset = 5;
         }
         else if(querystyle == SQS_LAST_6_MONTH_TOP)
         {
            gprop("songclick") = "clickLast6Month";
            join_offset = 4;
         }
         else if(querystyle == SQS_LAST_3_MONTH_TOP)
         {
            gprop("songclick") = "clickLast3Month";
            join_offset = 3;
         }
         else if(querystyle == SQS_LAST_MONTH_TOP)
         {
            gprop("songclick") = "clickLastMonth";
            join_offset = 2;
         }
         else if(querystyle == SQS_WEEK_TOP)
         {
            gprop("songclick") = "click7days";
            join_offset = 1;
         }
         else if(querystyle == SQS_24HOUR_TOP)
         {
            gprop("songclick") = "click24hours";
            join_offset = 0;
         }
         gprop("top_join") = "";
         for(gprop("i") = 2; gprop("i") <= 4; gprop("i")++)
         {
            gprop("type") = "";
            switch((int) ((int)gprop("i") + (int)join_offset))
            {
            case 2:
               gprop("type") = "click7days";
               break;
            case 3:
               gprop("type") = "clickLastMonth";
               break;
            case 4:
               gprop("type") = "clickLast3Month";
               break;
            case 5:
               gprop("type") = "clickLast6Month";
               break;
            case 6:
               gprop("type") = "clickLastYear";
               break;
            case 7:
               gprop("type") = "click";
               break;
            }
            if(strlen(gprop("type")) > 0)
            {
               gprop("top_order") += eval(", click$i.click DESC");
               gprop("top_join") += eval(" INNER JOIN tmp_topic_lang_style_click as click$i ON click$i.type = '$type'  AND click$i.langid = '$langid' AND  click$i.styleid = '$styleid' AND (click$i.topictype = $topictype");
               if(iTopicType == 1)
               {
                  gprop("top_join") += eval(" OR click$i.topictype = 1001) ");
               }
               else
               {
                  gprop("top_join") += ") ";
               }
               gprop("top_where") += eval("AND click$i.topic = $click_where AND click$i.topictype = $click_where_topictype ");
            }
         }
         sql = eval("SELECT DISTINCT SQL_CALC_FOUND_ROWS song.id, song.title, tmp_topic_lang_style_click.click as songclick, 'xxxperformer' as performer, tmp_song.karaokecount, tmp_song.lyricscount, tmp_song.chordcount, tmp_topic_lang_style_click.rank, tmp_song.classida, tmp_topic.performerida $fieldappend $topic_field_append $fun_field FROM $fromstart song "+fromappend+" INNER JOIN tmp_song ON tmp_song.song = song.id  "+innerjoin+" $top_join "+leftouterjoin+" WHERE tmp_topic_lang_style_click.type = '$songclick' $top_where ");
      }
      else if(querystyle == SQS_FUN)
      {
         innerjoin += eval(" INNER JOIN fun_user_class_song ON fun_user_class_song.song = tmp_song.song LEFT OUTER JOIN tmp_topic_lang_style_click ON tmp_topic_lang_style_click.langid = '$langid' AND  tmp_topic_lang_style_click.styleid = '$styleid'  AND tmp_topic_lang_style_click.type = 'click' AND tmp_topic_lang_style_click.topictype = $topictype AND tmp_topic_lang_style_click.topic = topic_song.topic ");
         gprop("groupby") = eval("GROUP BY $groupby");
         sql = "SELECT SQL_CALC_FOUND_ROWS song.id, song.title, tmp_topic_lang_style_click.click as songclick, 'xxxperformer' as performer, tmp_song.karaokecount, tmp_song.lyricscount, tmp_song.chordcount $fieldappend $topic_field_append, 1 FROM $fromstart song INNER JOIN tmp_song ON tmp_song.song = song.id "+fromappend+" "+innerjoin+" $top_join WHERE 1 ";
      }
      else if(perpertop)
      {
         gprop("songclick") = eval("SUM({$ppt_table}.click)");
         gprop("groupby") = eval("GROUP BY $groupby");
         sql = eval("SELECT SQL_CALC_FOUND_ROWS song.id, song.title, $songclick as songclick, 'xxxperformer' as performer, tmp_song.karaokecount, tmp_song.lyricscount, tmp_song.chordcount, tmp_song.classida, tmp_topic.performerida $fieldappend $topic_field_append FROM $fromstart song "+fromappend+" INNER JOIN tmp_song ON tmp_song.song = song.id  "+innerjoin+" WHERE 1 ");
      }
      else
      {
         
         if(flaga.array_contains("noclick"))
         {
            gprop("sc_field") = -1;
         }
         else
         {
            leftouterjoin += eval(" LEFT OUTER JOIN tmp_topic_lang_style_click ON tmp_topic_lang_style_click.langid = '$langid' AND  tmp_topic_lang_style_click.styleid = '$styleid'  AND tmp_topic_lang_style_click.type = 'click' AND tmp_topic_lang_style_click.topictype = $topictype AND tmp_topic_lang_style_click.topic = topic_song.topic AND topic_song.topictype = $topictype ");
            gprop("sc_field") = eval("$songclick as songclick");
         }

         gprop("groupby") = eval("GROUP BY $groupby");
         gprop("w1") = "1";
         sql = eval("SELECT SQL_CALC_FOUND_ROWS song.id, song.title, $sc_field, 'xxxperformer' as performer, tmp_song.karaokecount, tmp_song.lyricscount, tmp_song.chordcount, tmp_song.classida, tmp_topic.performerida $fieldappend $topic_field_append $fun_field FROM $fromstart song  "+fromappend+" INNER JOIN tmp_song ON tmp_song.song = song.id "+innerjoin+" "+leftouterjoin+" WHERE $w1 ");
      }


   
      if(defaultsql)
      {
         sqlcount = eval("SELECT COUNT(DISTINCT karfile.id) FROM song "+fromappend+" INNER JOIN tmp_song ON tmp_song.songfileid = karfile.id "+innerjoin+"  ");
         if(querystyle == SQS_FUN)
         {
            sql += eval(" AND song.id = fun_user_class_song.song AND fun_user_class_song.user = '$fun_userid' ");
            sqlcount += eval(" AND song.id = fun_user_class_song.song AND fun_user_class_song.user = '$fun_userid' ");
         }
         else if(querystyle == SQS_GLOBAL_TOP ||
            querystyle == SQS_LAST_YEAR_TOP ||
            querystyle == SQS_LAST_6_MONTH_TOP ||
            querystyle == SQS_LAST_3_MONTH_TOP||
            querystyle == SQS_LAST_MONTH_TOP ||
            querystyle == SQS_WEEK_TOP ||
            querystyle == SQS_24HOUR_TOP)
         {
            sqlcount = eval("SELECT COUNT(DISTINCT song.id) FROM song INNER JOIN tmp_topic_lang_style_click ON tmp_topic_lang_style_click.langid = '$langid' AND  tmp_topic_lang_style_click.styleid = '$styleid' WHERE tmp_topic_lang_style_click.type = '$topic_click'");
         }
         
         if(strlen(addwhereclause) > 0)
         {
            sql = sql +" AND " + addwhereclause;
            sqlcount = sqlcount + " AND " + addwhereclause;
         }
         
         sql = sql + " " + gprop("groupby");
         if(querystyle == SQS_GLOBAL_TOP)
         {
            sqlcount = eval("SELECT COUNT(DISTINCT topic_click.songfileid) FROM topic_click WHERE  (topic_click.flag1 & 1) = 0  AND topic_click.langid = '$langid'  AND topic_click.styleid = '$styleid' ");
         }
         
         //////////////////////////////////////////////////////////////////
         // ORDER BY
         
         if(querystyle == SQS_LAST_ACCESSES)
         {
         }
         else if(querystyle == SQS_LAST_INSERTIONS)
         {
            if(iTopicType == 2)
            {
               sql += " ORDER BY chord.insertiondatetime DESC, song.insertiondatetime DESC, song.title";
            }
            else if(iTopicType == 1)
            {
               sql += " ORDER BY lyrics.insertiondatetime DESC, song.insertiondatetime DESC, song.title";
            }
            else
            {
               sql += " ORDER BY song.insertiondatetime DESC, song.title";
            }
         }
         else if(querystyle == SQS_GLOBAL_TOP ||
               querystyle == SQS_LAST_YEAR_TOP ||
               querystyle == SQS_LAST_6_MONTH_TOP ||
               querystyle == SQS_LAST_3_MONTH_TOP||
               querystyle == SQS_LAST_MONTH_TOP ||
               querystyle == SQS_WEEK_TOP ||
               querystyle == SQS_24HOUR_TOP)
         {
            sql +=  eval("ORDER BY $top_order, song.title");
         }
         else if(perpertop)
         {
            sql += " ORDER BY songclick DESC, song.title";
         }
         else if(order == ORDERBY_SONGNAME)
         {
            sql += " ORDER BY song.title";
         }
         else if(order == ORDERBY_GLOBALCLICK)
         {
            sql += " ORDER BY songclick DESC, song.title";
         }
         else if(order == ORDERBY_PERFORMERNAME)
         {
            sql += " ORDER BY performer.name, song.title";
         }
         else
         {   
            sql += " ORDER BY song.title";
         }
         
      }
      
      sql += eval(" LIMIT $limitstart, $limitcount");
      
      var rowa= query_rows(eval(sql));

      int total_rows;
      if(querystyle == SQS_LAST_ACCESSES)
      {
         total_rows = query_item(sqlcount);
      }
      else
      {
         total_rows = query_item("SELECT FOUND_ROWS()");
         dprint("Total Rows: $total_rows <br>");
      }

      totalcount = total_rows;
      
      int recordcount = rowa.array_get_count();
      
//      int line = 0;

      var songidSource;
      var rowSource;

      stringa cache_performera;

      music::song * psong;

      var pperformerida;

        for(int i = 0; i < rowa.array_get_count(); i++)
        {
         var row = rowa.at(i);
         dprint_r(row);
           var songid    = row.at(0);
         psong = NULL;
         if(querystyle == SQS_LAST_ACCESSES)
          {
            var topicid = row.at(0);
            var topictype;
            if(topic == "chord")
            {
                psong = get_chord_song(topicid);
            }
            else if(topic == "lyrics")
            {
               dprint("getLyricsSong($topicid)");
                psong = get_lyrics_song(topicid, topictype);
            }
            else
            {
                psong = get_kar_file_song(topicid);
            }
            if(psong == NULL)
               continue;
         }
         else
         {
            psong = new music::song;
            psong->m_propertyset["id"]            = row.at(0);
            psong->m_propertyset["title"]          = row.at(1);
            psong->m_propertyset["click"]          = row.at(2);
            psong->m_propertyset["karaokecount"]   = row.at(4);
            psong->m_propertyset["lyricscount"]    = row.at(5);
            psong->m_propertyset["chordcount"]     = row.at(6);
         }
         if(querystyle == SQS_LAST_ACCESSES)
         {
            psong->m_propertyset["accessdatetime"] = row.at(1);
            throw not_implemented_exception();
            //psong->m_accesslang    = getLangFriendlyName(row[2]);
         }   
         else if(querystyle == SQS_GLOBAL_TOP ||
            querystyle == SQS_LAST_YEAR_TOP ||
            querystyle == SQS_LAST_6_MONTH_TOP ||
            querystyle == SQS_LAST_3_MONTH_TOP||
            querystyle == SQS_LAST_MONTH_TOP ||
            querystyle == SQS_WEEK_TOP ||
            querystyle == SQS_24HOUR_TOP)
         {
            psong->m_propertyset["rank"]           = row.at(7);
            psong->m_propertyset["classida"]       = cgcl_ltgt_to_array(row.at(8));
            pperformerida           = cgcl_ltgt_to_array(row.at(9));
            psong->m_propertyset["topic"]          = row.at(10);
            psong->m_propertyset["topictype"]      = row.at(11);
            if(iTopicType == 2)
            {
               psong->m_propertyset["chordcomment"]   = row.at(12);
            }
            else if(iTopicType == 1 || iTopicType == 1001)
            {
               psong->m_propertyset["lyrics"]         = row.at(12);
               psong->m_propertyset["lyricscomment"]   = row.at(13);
            }
            else
            {
               psong->m_propertyset["filename"]       = row.at(12);
               psong->m_propertyset["isfun"]      = bFun ? row.at(13) : false;
            }
         }
         else
         {
            psong->m_propertyset["classida"]      = cgcl_ltgt_to_array(row.at(7));
            pperformerida         = cgcl_ltgt_to_array(row.at(8));
//            psong->m_topic          = row[10];
//            psong->m_topictype      = row[11];
            psong->m_propertyset["topic"]          = row.at(9);
            psong->m_propertyset["topictype"]      = row.at(10);
            if(iTopicType == 2)
            {
               psong->m_propertyset["chordcomment"]   = row.at(11);
            }
            else if(iTopicType == 1 || iTopicType == 1001)
            {
               psong->m_propertyset["lyrics"]                  = row.at(11);
               psong->m_propertyset["lyricscomment"]            = row.at(12);
               psong->m_propertyset["translation_language"]   = row.at(13);
            }
            else
            {
               psong->m_propertyset["filename"]       = row.at(11);
            }
            psong->m_propertyset["isfun"]      = bFun ? row.at(12) : false;
         }
         music::person_info * ppersoninfo          = getPersonInfoExFromA(pperformerida, flaga);
         psong->m_propertyset["performers"]        = ppersoninfo->m_persons;
         psong->m_propertyset["pperformera"]       = ppersoninfo->m_persona;         
         psong->m_propertyset["performerida"]      = ppersoninfo->m_sida;         
         psong->m_propertyset["performerids"]      = ppersoninfo->m_sida.implode(",");
         psong->m_propertyset["type"]              = psong->calc_file_type();
         psong->m_propertyset["contenttype"]       = psong->calc_content_type();      
         psonga->add(psong);
      }
      lastpage = (recordcount < limitcount) || (totalcount - limitstart == limitcount);
      return psonga;
   }

































   music::song * fontopus_database::get_song(var id)
   {
      //global $secureuserid;
      //global $param_locale;
      //global $param_style;
      
      gprop("lang")       = gprop("g_base_param_locale");
      gprop("style")      = gprop("g_base_param_style");
      
      gprop("langid")       = get_lang_id(gprop("lang"));
      gprop("styleid")    = get_style_id(gprop("style"));

      gprop("id") = id;
      
//      bool bFun = fun().is_active();
      
      string sql = eval("SELECT song.id, song.title, SUM(tmp_song.lyricscount), SUM(tmp_song.chordcount), song_info.releaseyear, COUNT(karfile_song.karfileid) FROM song INNER JOIN tmp_song ON tmp_song.song = song.id LEFT OUTER JOIN song_info ON song_info.songid = song.id LEFT OUTER JOIN karfile_song ON karfile_song.songid = song.id WHERE song.id = $id GROUP BY song.id");
   
      var row = query_row(sql);
      if(row.is_empty())
         return NULL;

      music::song * psong                    = new music::song();
      music::person_info * pperformerinfo    = getPersonInfo(id, 0, 2);
      psong->m_propertyset["id"]             = row.at(0);
      var songid                               = psong->m_propertyset["id"];
      psong->m_propertyset["title"]          = row.at(1);
      psong->m_propertyset["click"]          = row.at(2);
      psong->m_propertyset["lyricscount"]      = row.at(3);
      psong->m_propertyset["chordcount"]      = row.at(4);
      psong->m_propertyset["karaokecount"]   = row.at(6);
      psong->m_propertyset["performers"]       = pperformerinfo->m_persons;
      psong->m_propertyset["pperformera"]    = pperformerinfo->m_persona;
      psong->m_propertyset["performerida"]   = pperformerinfo->m_sida;         
      psong->m_propertyset["performerids"]   = pperformerinfo->m_sida.implode(",");         
//      psong->m_isfun                           = bFun ? usersongida.contains(psong->m_id) : false;
      psong->m_propertyset["releaseyear"]      = row.at(5);
      return psong;
   }

   music::song_ptr_array * fontopus_database::get_song_files(var id)
   {
      //global $secureuserid;
      //global $param_locale;
      //global $param_style;
      
      gprop("lang")       = gprop("g_base_param_locale");
      gprop("style")      = gprop("g_base_param_style");
      
      gprop("langid")       = get_lang_id(gprop("lang"));
      gprop("styleid")    = get_style_id(gprop("style"));

      gprop("id") = id;
      
      bool bFun = fun().is_active();

      stringa usersongida;
      if(bFun)
      {
//         usersongida = fun_getUserSongId(gprop("secureuserid"));
      }

      string sql = eval("SELECT song.id, karfile.filename, song.title, tmp_song.lyricscount, tmp_song.chordcount, karfile.id, karfile.insertiondatetime, karfile.insertionuserid, karfile.sourceid, karfile.insertercomment, karfile.insertionsourcecomment FROM song INNER JOIN topic_song ON topic_song.song = song.id AND topic_song.topictype = 0 INNER JOIN karfile ON karfile.id = topic_song.topic  INNER JOIN tmp_song ON tmp_song.song = song.id WHERE song.id = $id");
   
      var rowa = query_rows(sql);
      music::song_ptr_array *  psonga = new music::song_ptr_array;
      for(int i = 0; i < rowa.get_count(); i++)
      {
         var row = rowa.at(i);
         music::song * psong                             = new music::song();
         music::person_info * pperformerinfo             = getPersonInfo(id, row.at(0), 2);
         psong->m_propertyset["id"]                      = row.at(0);
         psong->m_propertyset["filename"]                = row.at(1);
         psong->m_propertyset["title"]                   = row.at(2);
         psong->m_propertyset["lyricscount"]               = row.at(3);
         psong->m_propertyset["chordcount"]               = row.at(4);
         psong->m_propertyset["performers"]                = pperformerinfo->m_persons;
         psong->m_propertyset["pperformera"]             = pperformerinfo->m_persona;
         psong->m_propertyset["performerida"]            = pperformerinfo->m_sida;         
         psong->m_propertyset["performerids"]            = pperformerinfo->m_sida.implode(",");         
         psong->m_propertyset["type"]                     = psong->calc_file_type();
         psong->m_propertyset["contenttype"]               = psong->calc_content_type();               
         psong->m_propertyset["isfun"]                     = bFun ? usersongida.contains(psong->m_propertyset[id]) : false;
         psong->m_propertyset["fileid"]                  = row.at(5);
         psong->m_propertyset["topic"]                     = row.at(5);
         psong->m_propertyset["topictype"]               = 0;
         psong->m_propertyset["insertiondatetime"]       = row.at(6);
         psong->m_propertyset["insertionuserid"]         = row.at(7);
         psong->m_propertyset["insertionsourceid"]       = row.at(8);
         psong->m_propertyset["insertercomment"]         = row.at(9);
         psong->m_propertyset["insertionsourcecomment"]  = row.at(10);
         psonga->add(psong);
      }
      return psonga;
   }


   music::song * fontopus_database::get_kar_file_song(var karfileid)
   {
      //global $secureuserid;
      //global $param_locale;
      //global $param_style;
      
      gprop("lang")       = gprop("g_base_param_locale");
      gprop("style")      = gprop("g_base_param_style");
      
      gprop("langid")       = get_lang_id(gprop("lang"));
      gprop("styleid")    = get_style_id(gprop("style"));

      gprop("karfileid") = karfileid;
      
      bool bFun = fun().is_active();

      stringa usersongida;
      if(bFun)
      {
//         usersongida = fun_getUserSongId(gprop("secureuserid"));
      }
      
      string sql = eval("SELECT song.id, karfile.filename, song.title, karfile.id, tmp_song.lyricscount, tmp_song.chordcount, tmp_song.karaokecount FROM song INNER JOIN topic_song ON topic_song.song = song.id INNER JOIN karfile ON karfile.id = topic_song.topic AND topic_song.topictype = 0 INNER JOIN tmp_song ON song.id = tmp_song.song WHERE karfile.id = $karfileid");
   
      var row = query_row(sql);
      if(row.is_empty())
         return NULL;

      music::song * psong = new music::song();
      music::person_info * pperformerinfo       = getPersonInfo(karfileid, 0, 2);
      psong->m_propertyset["id"]             = row.at(0);
      psong->m_propertyset["filename"]       = row.at(1);
      psong->m_propertyset["title"]          = row.at(2);
      psong->m_propertyset["performers"]       = pperformerinfo->m_persons;
      psong->m_propertyset["pperformera"]    = pperformerinfo->m_persona;
      psong->m_propertyset["performerida"]   = pperformerinfo->m_sida;         
      psong->m_propertyset["performerids"]   = pperformerinfo->m_sida.implode(",");
      psong->m_propertyset["type"]            = psong->calc_file_type();
      psong->m_propertyset["contenttype"]   = psong->calc_content_type();               
      psong->m_propertyset["isfun"]      = bFun ? usersongida.contains(psong->m_propertyset["id"]) : false;
      psong->m_propertyset["topic"]         = row.at(3);
      psong->m_propertyset["lyricscount"]   = row.at(4);
      psong->m_propertyset["chordcount"]      = row.at(5);
      psong->m_propertyset["karaokecount"]   = row.at(6);
      return psong;
   }

   music::song * fontopus_database::get_song_kar_file(var songid, var index)
   {
      //global $secureuserid;
      //global $param_locale;
      //global $param_style;
      
      gprop("lang")       = gprop("g_base_param_locale");
      gprop("style")      = gprop("g_base_param_style");
      
      gprop("langid")    = get_lang_id(gprop("lang"));
      gprop("styleid")    = get_style_id(gprop("style"));

      gprop("songid")   = songid;
      gprop("iindexd")  = index;
      
      bool bFun = fun().is_active();

      stringa usersongida;
      if(bFun)
      {
//         usersongida = fun_getUserSongId(gprop("secureuserid"));
      }
      
      string sql = eval("SELECT song.id, karfile.filename, song.title, tmp_song.lyricscount, tmp_song.chordcount, song_info.releaseyear, karfile.id FROM song INNER JOIN topic_song ON topic_song.song = song.id INNER JOIN karfile ON karfile.id = topic_song.topic INNER JOIN tmp_song ON tmp_song.song = song.id WHERE karfile_song.songid = song.id  AND topic_song.topictype = 0  AND topic_song.topicindex, song.id = $songid ORDER BY karfile.id LIMIT $index, 1");
   
      var row = query_row(sql);
      if(row.is_empty())
         return NULL;

      music::song * psong = new music::song();
      music::person_info * pperformerinfo       = getPersonInfo(songid, 0, 2);
      psong->m_propertyset["id"]             = row.at(0);
      psong->m_propertyset["filename"]       = row.at(1);
      psong->m_propertyset["title"]          = row.at(2);
      psong->m_propertyset["lyricscount"]   = row.at(3);
      psong->m_propertyset["chordcount"]      = row.at(4);
      psong->m_propertyset["performers"]    = pperformerinfo->m_persons;
      psong->m_propertyset["pperformera"]    = pperformerinfo->m_persona;
      psong->m_propertyset["performerida"]   = pperformerinfo->m_sida;         
      psong->m_propertyset["performerids"]   = pperformerinfo->m_sida.implode(",");         
      psong->m_propertyset["type"]            = psong->calc_file_type();
      psong->m_propertyset["contenttype"]   = psong->calc_content_type();               
      psong->m_propertyset["isfun"]      = bFun ? usersongida.contains(psong->m_propertyset["id"]) : false;
      psong->m_propertyset["releaseyear"]   = row.at(6);
      psong->m_propertyset["fileid"]         = row.at(7);
      return psong;
   }
   music::song * fontopus_database::get_lyrics_song(var topic, var topictype)
   {
      //global $secureuserid;
      //global $param_locale;
      //global $param_style;
      
      gprop("lang")       = gprop("g_base_param_locale");
      gprop("style")      = gprop("g_base_param_style");
      
      gprop("langid")       = get_lang_id(gprop("lang"));
      gprop("styleid")    = get_style_id(gprop("style"));

      gprop("topic") = topic;
      gprop("topictype") = topictype;
      
      bool bFun = fun().is_active();

      stringa usersongida;
      if(bFun)
      {
//         usersongida = fun_getUserSongId(gprop("secureuserid"));
      }
      string sql;

      if(topictype == 1)
      {
         sql = eval("SELECT song.id, lyrics.lyrics, song.title, lyrics.id, tmp_song.lyricscount, tmp_song.chordcount, tmp_song.karaokecount, lyrics.comment FROM song INNER JOIN topic_song ON topic_song.song = song.id INNER JOIN lyrics ON lyrics.id = topic_song.topic AND topic_song.topictype = $topictype INNER JOIN tmp_song ON song.id = tmp_song.song WHERE lyrics.id = $topic");
      }
      else if(topictype == 1001)
      {
         sql = eval("SELECT song.id, karfile_lyrics.lyrics, song.title, karfile_lyrics.karfile, tmp_song.lyricscount, tmp_song.chordcount, tmp_song.karaokecount, '' FROM song INNER JOIN topic_song ON topic_song.song = song.id INNER JOIN karfile_lyrics ON karfile_lyrics.karfile = topic_song.topic AND topic_song.topictype = $topictype INNER JOIN tmp_song ON song.id = tmp_song.song WHERE karfile_lyrics.karfile = $topic");
      }
         
      var row = query_row(sql);
      if(row.is_empty())
         return NULL;

      music::song * psong = new music::song();
      music::person_info * pperformerinfo       = getPersonInfoEx(topic, topictype, 2);
      psong->m_propertyset["id"]          = row.at(0);
      psong->m_propertyset["lyrics"]       = row.at(1);
      psong->m_propertyset["title"]       = row.at(2);
      psong->m_propertyset["performers"]    = pperformerinfo->m_persons;
      psong->m_propertyset["pperformera"]    = pperformerinfo->m_persona;
      psong->m_propertyset["performerida"]   = pperformerinfo->m_sida;         
      psong->m_propertyset["performerids"]   = pperformerinfo->m_sida.implode(",");
      psong->m_propertyset["type"]         = psong->calc_file_type();
      psong->m_propertyset["contenttype"]   = psong->calc_content_type();               
      psong->m_propertyset["isfun"]   = bFun ? usersongida.contains(psong->m_propertyset["id"]) : false;
      psong->m_propertyset["topic"]      = row.at(3);
      psong->m_propertyset["lyricscount"]   = row.at(4);
      psong->m_propertyset["chordcount"]   = row.at(5);
      psong->m_propertyset["karaokecount"]   = row.at(6);
      return psong;
   }

   music::song * fontopus_database::get_song_lyrics(var songid, var index)
   {
      //global $secureuserid;
      //global $secureuserid;
      //global $param_locale;
      //global $param_style;
      
      gprop("lang")       = gprop("g_base_param_locale");
      gprop("style")      = gprop("g_base_param_style");
      
      gprop("langid")       = get_lang_id(gprop("lang"));
      gprop("styleid")    = get_style_id(gprop("style"));

      gprop("songid") = songid;
      gprop("index") = index;
      
      bool bFun = fun().is_active();

      stringa usersongida;
      if(bFun)
      {
//         usersongida = fun_getUserSongId(gprop("secureuserid"));
      }
      
      string sql = eval("SELECT song.id, CASE topic_song.topictype WHEN 1 THEN lyrics.lyrics ELSE karfile_lyrics.lyrics END, song.title, tmp_song.lyricscount, tmp_song.chordcount, topic_song.topic, topic_song.topictype, tmp_song.karaokecount, lyrics.comment FROM song INNER JOIN topic_song ON topic_song.song = song.id INNER JOIN tmp_song ON tmp_song.song = song.id LEFT OUTER JOIN lyrics ON lyrics.id = topic_song.topic AND topic_song.topictype = 1 LEFT OUTER JOIN karfile_lyrics ON karfile_lyrics.karfile = topic_song.topic AND topic_song.topictype = 1001 WHERE topic_song.song = song.id AND (topic_song.topictype = 1 OR topic_song.topictype = 1001) AND song.id = $songid ORDER BY topic_song.topicindex, lyrics.id LIMIT $index, 1");
   
      var row = query_row(sql);
      if(row.is_empty())
         return NULL;

      music::song * psong = new music::song();
      music::person_info * pperformerinfo          = getSongTopicTypeRolePersonInfo(row.at(0), 0, 2);
      psong->m_propertyset["id"]             = row.at(0);
      psong->m_propertyset["lyrics"]          = row.at(1);
      psong->m_propertyset["title"]          = row.at(2);
      psong->m_propertyset["lyricscount"]      = row.at(3);
      psong->m_propertyset["chordcount"]      = row.at(4);
      psong->m_propertyset["performers"]       = pperformerinfo->m_persons;
      psong->m_propertyset["pperformera"]       = pperformerinfo->m_persona;
      psong->m_propertyset["performerida"]      = pperformerinfo->m_sida;         
      psong->m_propertyset["performerids"]      = pperformerinfo->m_sida.implode(",");         
      psong->m_propertyset["type"]            = psong->calc_file_type();
      psong->m_propertyset["contenttype"]      = psong->calc_content_type();               
      psong->m_propertyset["isfun"]      = bFun ? usersongida.contains(psong->m_propertyset["id"]) : false;
//      psong->m_propertyset["releaseyear   = row[6];
      psong->m_propertyset["topic"]         = row.at(5);
      psong->m_propertyset["topictype"]      = row.at(6);
      psong->m_propertyset["karaokecount"]      = row.at(7);
      psong->m_propertyset["lyricscomment"]   = row.at(8);
      psong->m_propertyset["topic"]         = row.at(9);
      return psong;
   }
   music::song * fontopus_database::get_chord_song(var chordid)
   {
      //global $secureuserid;
      //global $param_locale;
      //global $param_style;
      
      gprop("lang")       = gprop("g_base_param_locale");
      gprop("style")      = gprop("g_base_param_style");
      
      gprop("langid")       = get_lang_id(gprop("lang"));
      gprop("styleid")    = get_style_id(gprop("style"));

      gprop("chordid") = chordid;
      
      bool bFun = fun().is_active();

      stringa usersongida;
      if(bFun)
      {
//         usersongida = fun_getUserSongId(gprop("secureuserid"));
      }
      
      string sql = eval("SELECT song.id, chord.chords, song.title, chord.id, tmp_song.lyricscount, tmp_song.chordcount, tmp_song.karaokecount FROM song INNER JOIN topic_song ON topic_song.song = song.id INNER JOIN chord ON chord.id = topic_song.topic AND topic_song.topictype = 2 INNER JOIN tmp_song ON song.id = tmp_song.song WHERE chord.id = $chordid");
      var row = query_row(sql);
      if(row.is_empty())
         return NULL;

      music::song * psong = new music::song();
      music::person_info * pperformerinfo       = getPersonInfo(chordid, 2, 2);
      psong->m_propertyset["id"]             = row.at(0);
      psong->m_propertyset["filename"]       = row.at(1);
      psong->m_propertyset["title"]          = row.at(2);
      psong->m_propertyset["performers"]    = pperformerinfo->m_persons;
      psong->m_propertyset["pperformera"]    = pperformerinfo->m_persona;
      psong->m_propertyset["performerida"]   = pperformerinfo->m_sida;         
      psong->m_propertyset["performerids"]   = pperformerinfo->m_sida.implode(",");
      psong->m_propertyset["type"]            = psong->calc_file_type();
      psong->m_propertyset["contenttype"]   = psong->calc_content_type();               
      psong->m_propertyset["isfun"]      = bFun ? usersongida.contains(psong->m_propertyset["id"]) : false;
      psong->m_propertyset["topic"]         = row.at(3);
      psong->m_propertyset["lyricscount"]   = row.at(4);
      psong->m_propertyset["chordcount"]      = row.at(5);
      psong->m_propertyset["karaokecount"]   = row.at(6);
      return psong;
   }

   music::song * fontopus_database::get_song_chord(var songid, var index)
   {
      //global $secureuserid;
      //global $param_locale;
      //global $param_style;
      
      gprop("lang")       = gprop("g_base_param_locale");
      gprop("style")      = gprop("g_base_param_style");
      
      gprop("langid")       = get_lang_id(gprop("lang"));
      gprop("styleid")    = get_style_id(gprop("style"));

      gprop("songid") = songid;
      gprop("index") = index;
      
      bool bFun = fun().is_active();

      stringa usersongida;
      if(bFun)
      {
//         usersongida = fun_getUserSongId(gprop("secureuserid"));
      }
      
      
      string sql = eval("SELECT song.id, chord.chords, song.title, tmp_song.lyricscount, tmp_song.chordcount, chord.id, tmp_song.karaokecount FROM song INNER JOIN topic_song ON topic_song.song = song.id INNER JOIN chord ON chord.id = topic_song.topic INNER JOIN tmp_song ON tmp_song.song = song.id WHERE topic_song.song = song.id AND topic_song.topictype = 2  AND song.id = $songid ORDER BY topic_song.topicindex, chord.id LIMIT $index, 1");
   
      var row = query_row(sql);
      if(row.is_empty())
         return NULL;

      music::song * psong = new music::song();
      music::person_info * pperformerinfo       = getSongTopicTypeRolePersonInfo(row.at(0), 0, 2);
      psong->m_propertyset["id"]             = row.at(0);
      psong->m_propertyset["filename"]       = row.at(1);
      psong->m_propertyset["title"]          = row.at(2);
      psong->m_propertyset["lyricscount"]   = row.at(3);
      psong->m_propertyset["chordcount"]      = row.at(4);
      psong->m_propertyset["performers"]    = pperformerinfo->m_persons;
      psong->m_propertyset["pperformera"]    = pperformerinfo->m_persona;
      psong->m_propertyset["performerida"]   = pperformerinfo->m_sida;         
      psong->m_propertyset["performerids"]   = pperformerinfo->m_sida.implode(",");         
      psong->m_propertyset["type"]            = psong->calc_file_type();
      psong->m_propertyset["contenttype"]   = psong->calc_content_type();               
      psong->m_propertyset["isfun"]      = bFun ? usersongida.contains(psong->m_propertyset["id"]) : false;
//      psong->m_propertyset["releaseyear   = row[6];
      psong->m_propertyset["fileid"]         = row.at(5);
      psong->m_propertyset["karaokecount"]  = row.at(6);
      return psong;
   }
   music::song * fontopus_database::get_topic_song(var topic, var topictype)
   {
      if(topictype == 0)
      {
         return get_kar_file_song(topic);
      }
      else if(topictype == 1 || topictype == 1001)
      {
         return get_lyrics_song(topic, topictype);
      }
      else if(topictype == 2)
      {
         return get_chord_song(topic);
      }
      else
      {
         return NULL;
      }
   }




















































































   music::person_info * fontopus_database::getSongTopicTypeRolePersonInfo(var songid, var topictype, var role)
   {
      gprop("songid") = songid;
      gprop("topictype") = topictype;
      gprop("role") = role;
      string sql = eval("SELECT topic_person.person FROM topic_person INNER JOIN topic_song ON topic_person.topictype = topic_song.topictype AND topic_person.topic = topic_song.topic WHERE topic_person.topictype = $topictype AND topic_person.role = $role AND topic_song.song = $songid");
      var rowa = query_rows(sql);
      music::person_info * ppersoninfo = new music::person_info;
      for(int i = 0; i < rowa.array_get_count(); i++)
      {
         var row = rowa.at(i);
         var personid                   = row.at(0);
         music::person * pperson  = get_person(personid);
         if(pperson == NULL)
            continue;
         ppersoninfo->m_ida.vara().add(personid);
         ppersoninfo->m_namea.vara().add(pperson->m_propertyset["name"]);
         ppersoninfo->m_persona.add(pperson);
      }
      ppersoninfo->m_sida = ppersoninfo->m_ida;
      ppersoninfo->m_sida.inta().QuickSort(true);
      ppersoninfo->m_persons = ppersoninfo->m_namea.implode(" - ");
      return ppersoninfo;
   }

   music::person_info * fontopus_database::getPersonInfo(var topicid, var topictype, var role)
   {
      gprop("topicid") = topicid;
      gprop("topictype") = topictype;
      gprop("role") = role;
      string sql = eval("SELECT topic_person.person FROM topic_person WHERE topic_person.topictype = $topictype AND topic_person.role = $role AND topic_person.topic = $topicid");
      var rowa = query_rows(sql);
      music::person_info * ppersoninfo = new music::person_info;
      for(int i = 0; i < rowa.array_get_count(); i++)
      {
         var row = rowa.at(i);
         var personid                   = row.at(0);
         music::person * pperson  = get_person(personid);
         if(pperson == NULL)
            continue;
         ppersoninfo->m_ida.vara().add(personid);
         ppersoninfo->m_namea.vara().add(pperson->m_propertyset["name"]);
         ppersoninfo->m_persona.add(pperson);
      }
      ppersoninfo->m_sida = ppersoninfo->m_ida;
      ppersoninfo->m_sida.inta().QuickSort();
      ppersoninfo->m_persons = ppersoninfo->m_namea.implode(" - ");
      return ppersoninfo;
   }

   music::person_info * fontopus_database::getPersonInfoEx(var topicid, var topictype, var role, var flaga)
   {
      gprop("topicid") = topicid;
      gprop("topictype") = topictype;
      gprop("role") = role;
      var a;
      string sql;
      if(role == 2)
      {
         sql = eval("SELECT tmp_topic.performerida FROM tmp_topic WHERE topic = $topicid AND topictype = $topictype");
         var item = query_item(sql);
         a = cgcl_ltgt_to_array(item);
      }
      else
      {
         sql = eval("SELECT DISTINCT topic_person.person FROM topic_song INNER JOIN topic_song as s2 ON s2.song = topic_song.song INNER JOIN topic_person ON topic_person.topic = s2.topic AND topic_person.topictype = s2.topictype WHERE topic_song.topic = $topicid AND topic_song.topictype = $topictype AND topic_person.role = $role");
         a = query_items(sql);
      }
      return getPersonInfoExFromA(a, flaga);
   }

   music::person_info * fontopus_database::getPersonInfoExFromA(var personida, var flaga)
   {
      music::person_info * ppersoninfo = new music::person_info;
      for(int i = 0; i < personida.array_get_count(); i++)
      {
         var personid = personida.at(i);
         music::person * pperson = get_person(personid, flaga);
         if(pperson == NULL)
            continue;
         ppersoninfo->m_ida.vara().add(personid);
         ppersoninfo->m_namea.vara().add(pperson->m_propertyset["name"]);
         ppersoninfo->m_persona.add(pperson);
      }
      ppersoninfo->m_sida = ppersoninfo->m_ida;
      ppersoninfo->m_sida.inta().QuickSort();
      ppersoninfo->m_persons = ppersoninfo->m_namea.implode(" - ");
      return ppersoninfo;
   }





























































































































   int fontopus_database::get_lang_id(const char * pszLang)
   {
      if(!strcmp("se", pszLang))
         return 11;
      else if(!strcmp("at", pszLang))
         return 22;
      else if(!strcmp("en", pszLang))
         return 0;
      else if(!strcmp("pt-br", pszLang))
         return 1;
      else if(!strcmp("it", pszLang))
         return 2;
      else if(!strcmp("es", pszLang))
         return 3;
      else if(!strcmp("de", pszLang))
         return 4;
      else if(!strcmp("ja", pszLang))
         return 7;
      else if(!strcmp("pt", pszLang))
         return 8;
      else if(!strcmp("fr", pszLang))
         return 9;
      else if(!strcmp("en-uk", pszLang))
         return 10;
      else if(!strcmp("de_fuer_dich", pszLang))
         return 488;
      else if(!strcmp("cn", pszLang))
         return 67;
      else if(!strcmp("ar", pszLang))
         return 58;
      else if(!strcmp("ru", pszLang))
         return 59;
      else if(!strcmp("nl", pszLang))
         return 56;
      else if(!strcmp("pl", pszLang))
         return 44;
      else if(!strcmp("unk", pszLang))
         return -1;
      else
         return query_item("SELECT id FROM lang WHERE lang = '" + string(pszLang) + "'", -1);
   }

   int fontopus_database::get_style_id(const char * pszStyle)
   {
      if(!strcmp("carcc", pszStyle))
         return 1133;
      else if(!strcmp("camcc", pszStyle))
         return 1107;
      else if(!strcmp("se", pszStyle))
         return 11;
      else if(!strcmp("at", pszStyle))
         return 22;
      else if(!strcmp("en", pszStyle))
         return 0;
      else if(!strcmp("pt-br", pszStyle))
         return 1;
      else if(!strcmp("it", pszStyle))
         return 2;
      else if(!strcmp("es", pszStyle))
         return 3;
      else if(!strcmp("de", pszStyle))
         return 4;
      else if(!strcmp("ja", pszStyle))
         return 7;
      else if(!strcmp("pt", pszStyle))
         return 8;
      else if(!strcmp("fr", pszStyle))
         return 9;
      else if(!strcmp("en-uk", pszStyle))
         return 10;
      else if(!strcmp("du", pszStyle))
         return 7714;
      else if(!strcmp("bell", pszStyle))
         return 4000;
      else if(!strcmp("mb", pszStyle))
         return 4001;
      else if(!strcmp("mbpara", pszStyle))
         return 4002;
      else if(!strcmp("veriwell", pszStyle))
         return 3500;
      else if(!strcmp("veriwiki", pszStyle))
         return 3575;
      else if(!strcmp("fontopus", pszStyle))
         return 5000;
      else if(!strcmp("du", pszStyle))
         return 7714;
      else if(!strcmp("ar", pszStyle))
         return 58;
      else if(!strcmp("ru", pszStyle))
         return 59;
      else if(!strcmp("cn", pszStyle))
         return 67;
      else if(!strcmp("nl", pszStyle))
         return 56;
      else if(!strcmp("pl", pszStyle))
         return 44;
      else if(!strcmp("gpl", pszStyle))
         return 1033;
      else if(!strcmp("unk", pszStyle))
         return -1;
      else 
         return query_item("SELECT id FROM style WHERE `style` = '" + string(pszStyle) + "'", -1);
   }


   int fontopus_database::calc_topic_type(var topic)
   {
      if(topic == "chord")
      {
         return 2;
      }
      else if(topic == "lyrics")
      {
         return 1;
      }
      else if(topic == "karaoke")
      {
         return 0;
      }
      else if(topic.get_type() == var::type_integer)
      {
         return topic.get_type();
      }
      else if(m_strMainMode == "cifras")
      {
         return 2;
      }
      else if(m_strMainMode == "letras")
      {
         return 1;
      }
      else
      {
         return 0;
      }
   }

   mysql::result * fontopus_database::query(const char * pszSql)
   {
      dprint("fontopus_database::query");
      prof_enter("fontopus_database::query");
      mysql::result * presult = netnode::database::query(pszSql);
      prof_leave("fontopus_database::query");
      return presult;
   }

   var fontopus_database::query_item(const char * pszSql, var varDefault)
   {
      dprint("fontopus_database::query_item");
      prof_enter("fontopus_database::query_item");
      var var = netnode::database::query_item(pszSql, varDefault);
      prof_leave("fontopus_database::query_item");
      return var;
   }

   var fontopus_database::query_items(const char * pszSql)
   {
      dprint("fontopus_database::query_items");
      prof_enter("fontopus_database::query_items");
      var var = netnode::database::query_items(pszSql);
      prof_leave("fontopus_database::query_items");
      return var;
   }

   var fontopus_database::query_row(const char * pszSql)
   {
      dprint("fontopus_database::query_row");
      prof_enter("fontopus_database::query_row");
      var var = netnode::database::query_row(pszSql);
      prof_leave("fontopus_database::query_row");
      return var;
   }

   var fontopus_database::query_rows(const char * pszSql)
   {
      dprint("fontopus_database::query_rows");
      prof_enter("fontopus_database::query_rows");
      var var = netnode::database::query_rows(pszSql);
      prof_leave("fontopus_database::query_rows");
      return var;
   }
   
   string fontopus_database::veriwell_getclassstring_item(var classid)
   {
      var item = query_table_item("class", "namestringid", "id = " + classid);
      if(!item)
         return "";
      return item;
   }

   var fontopus_database::perpertop_getYears()
   {
      gprop("lang")       = gprop("g_base_param_locale");
      gprop("style")      = gprop("g_base_param_style");
      gprop("langid")       = get_lang_id(gprop("lang"));
      gprop("styleid")    = get_style_id(gprop("style"));
      string sql = eval("SELECT DISTINCT tmp_topic_click_year.year FROM tmp_topic_click_year WHERE langid='$langid' AND styleid='$styleid' ORDER BY year ");
      return query_items(sql);
   }

   var fontopus_database::perpertop_getMonths(var year)
   {
      gprop("lang")       = gprop("g_base_param_locale");
      gprop("style")      = gprop("g_base_param_style");
      gprop("langid")       = get_lang_id(gprop("lang"));
      gprop("styleid")    = get_style_id(gprop("style"));
      gprop("year")  = year;
      string sql = eval("SELECT DISTINCT tmp_topic_click_month.month FROM tmp_topic_click_month WHERE langid='$langid' AND styleid='$styleid' AND tmp_topic_click_month.year = '$year' ORDER BY month");
      return query_items(sql);
   }

   var fontopus_database::perpertop_getWeeks(var year, var month)
   {
      gprop("lang")       = gprop("g_base_param_locale");
      gprop("style")      = gprop("g_base_param_style");
      gprop("langid")       = get_lang_id(gprop("lang"));
      gprop("styleid")    = get_style_id(gprop("style"));
      gprop("year")  = year;
      gprop("month")  = month;
      string sql = eval("SELECT DISTINCT tmp_topic_click_week.week FROM tmp_topic_click_week WHERE langid='$langid' AND styleid='$styleid' AND tmp_topic_click_week.year = '$year' AND tmp_topic_click_week.month = '$month' ORDER BY week");
      return query_items(sql);
   }



















// transforms "1,2,3" into "%<1>%<2>%<3>%"
string ida_to_condition(string list)
{
   stringa ida;
   ida.explode(",", list);
   ida.QuickSort();
   ida.surround("<", ">");
   return '%' + ida.implode("%") + '%';
}

// transforms "<1><2><3>" into {1,2,3}
var cgcl_ltgt_to_array(string str)
{
   str = str.Mid(1, str.get_length() - 2);
   str.replace("><", ".");
   class var var;
   var.stra().explode(".", str);
   return var;
}





   var fontopus_database::get_useragent_id_ex(var useragent)
   {
      gprop("useragent") = real_escape_string(useragent);
      var item = query_item(eval("SELECT id FROM useragent WHERE useragent.useragent = '$useragent'"));
      if(item.is_empty())
      {
         query(eval("INSERT INTO useragent(`useragent`) VALUES ('$useragent')"));
         return get_insert_id();
      }
      else
      {
         return item;
      }
   }


   var fontopus_database::register_song_click(var songid, var address, var http_referer, var lang, var style, var referer, var type)
   {
//      bool isrobot = 0;
      var hostname = gprop("g_hostname");
      gprop("hostname") = hostname;
      gprop("songid") = songid;
      gprop("address") = address;
      gprop("http_referer") = http_referer;
      gprop("lang") = lang;
      gprop("style") = style;
      gprop("referer") = referer;
      gprop("type") = type;
      gprop("isrobot") = 0;
   
      ////////////////////////////////////////////////////////////////////////////
      //
      //    song_click_partial update
      //
      //    song_click has data from the minimal detail interval in topic_click_compiled
      //      currnetly one hour
      //    for security margin, three hours are taken.
      
      if(net_hostname_is_spider(hostname, inheader("user-agent")))
      {
         gprop("isrobot") = 1;
      }

      /*      if($_SERVER['HTTP_HOST'] === "kar2.veriwell.net")
      {
         $flag1 |= 1;
      }*/
//      print "flag1=$flag1";
      
      gprop("useragent") = get_useragent_id_ex(inheader("USER-AGENT"));

      gprop("langid") = forceGetLangId(lang);
      gprop("styleid") = forceGetStyleId(style);
      gprop("now") = System.datetime().international().get_gmt_date_time();
      string sql = eval("INSERT INTO `topic_click` (`topic`, `type`, `datetime`, `address`, `hostname`, `http_referer`, `lang`, `style`, `langid`, `styleid`, `referer`, `isrobot`, `useragent`) VALUES ('$topicid', '$type', '$now', '$address', '$hostname', '$http_referer', '$lang', '$style', '$langid', '$styleid', '$referer', '$isrobot', '$useragent');");
      //   echo $sql;
      mysql::result * presult = query(sql);
      var song_click_id = get_insert_id();
      
      sql = eval("INSERT INTO `tmp_topic_last_access` (`topic`,`type`, `datetime`, `address`, `hostname`, `http_referer`, `lang`, `style`, `langid`, `styleid`, `referer`, `isrobot`) VALUES ('$topicid', '$type', '$now', '$address', '$hostname', '$http_referer', '$lang', '$style', '$langid', '$styleid', '$referer', '$isrobot');");
      presult = query(sql);
   
      /* commented dec 2009
      $dry_datetime = datetime_strtotime("90 day ago", timestamp_getToday());
      $sql = "DELETE FROM tmp_topic_last_access WHERE tmp_song_last_access.datetime < '$dry_datetime'";
      $this->query($sql);
      if($verbose)
      {
         $time2 = microtime(true);
         $delta = debug_delta($time1, $time2);
         $time1 = $time2;
         print "<h3>clean tmp_topic_last_access</h3>";
         print $sql;         
         print "<br>";
         print "delta: $delta<br>";
         flush();
      }
      */
      
//      $time = time();
//      $lastupdate = $this->db_read->get_prop_bigint("last_tmp_song_click_update");
//      $timeout = strtotime(TIMEOUT_STRTOTIME_REGISTER_SONG_CLICK_FULL_UPDATE, $lastupdate);
//      if(!$lastupdate || $time > $timeout)
//      {
//         $this->db_read->set_prop_bigint("last_tmp_song_click_update", $time);
//         $this->karaoke_update_tmp_song_clickdistinct1(isset($_GET['debug']));
//      }
//      else
   //   {
//         if(($flag1 & 1) == 0)
   //      {
      //      $this->update_tmp_song_clickdistinct1_item($song_click_id, $songid, $langid, $styleid, isset($_GET['debug']));
         //}
      //}
//      if(!$isrobot)
   //   {
      //   $this->update_tmp_song_clickdistinct1_item($song_click_id, $topicid, $langid, $styleid, isset($_GET['debug']));
//      }
   
      return true;
   }





      ::music::song_source * fontopus_database::get_song_source(var sourceid)
   {
      string sql = "SELECT name, url, email FROM song_source WHERE id = " + sourceid;
      var row = query_row(sql);
      if(row.array_get_count() == 3)
      {
         ::music::song_source * psource = new music::song_source;
         psource->m_strName    = row.at(0);
         psource->m_strUrl    = row.at(1);
         psource->m_strEmail    = row.at(2);
         return psource;
      }
      else
      {
         return NULL;
      }
      
   }
   
      /*
   function getPerformer($performerid)
   {
      if(array_key_exists($performerid, $this->cache_performer))
      {
         return $this->cache_performer[$performerid];
      }
      $sql = "SELECT performer.name FROM performer WHERE performer.id = $performerid";
      $result = $this->query($sql);
      if($row = fonto_fetch_row($result))
      {
         $performer             = new MusicPerformer();
         $performer->id       = $performerid;
         $performer->name       = $row[0];         
         $this->cache_performer[$performerid] = $performer;
         return $performer;
      }
      else
      {
         $this->cache_performer[$performerid] = NULL;
         return NULL;
      }
   }*/

   music::person * fontopus_database::get_person(var personid, var flaga)
   {
      music::person * pperson = NULL;
      gprop("personid") = personid;
      if(flaga.array_contains("onlypersonname"))
      {
         gen::property & prop = m_cache_person_only_name[personid.get_string()];
         if(prop.is_set())
         {
            pperson = prop.ca2<music::person>();
            pperson->m_pinterface = m_pinterface;
            return pperson;
         }         string sql = "SELECT person.name FROM person WHERE person.id = $personid";
         var row = query_row(sql);
         if(row.is_array())
         {
            pperson                   = new music::person();
            pperson->m_ulFlags &= ~(unsigned long) ::ca::ca::flag_auto_clean;
            pperson->m_pinterface->unkeep(pperson);
            pperson->m_bUnkeep = false;
            //pperson->m_pinterface   = NULL; // fontopus database lifetime isgenerally greater than interface lifetime
            pperson->m_propertyset["id"]             = personid;
            pperson->m_propertyset["name"]          = row.at(0);         
         }
         m_cache_person_only_name[personid.get_string()] = pperson;
         return pperson;
      }
      else
      {
         gen::property & prop = m_cache_person[personid.get_string()];
         if(prop.is_set())
         {
            pperson = prop.ca2<music::person>();
            pperson->m_pinterface = m_pinterface;
            return pperson;
         }
         gprop("lang")       = gprop("g_base_param_locale");
         gprop("style")      = gprop("g_base_param_style");
         
         gprop("langid")       = get_lang_id(gprop("lang"));
         gprop("styleid")    = get_style_id(gprop("style"));
         string sql = eval("SELECT person.name, tmp_person.songcount, SUM(tmp_person_lang_style_click.click) FROM person LEFT OUTER JOIN tmp_person ON tmp_person.person = person.id LEFT OUTER JOIN tmp_person_lang_style_click ON tmp_person_lang_style_click.person = person.id AND tmp_person_lang_style_click.langid = $langid AND tmp_person_lang_style_click.styleid = $styleid AND tmp_person_lang_style_click.type = 'click' WHERE person.id = $personid GROUP BY person.id");
         var row = query_row(sql);
         if(row.is_array())
         {
            pperson                   = new music::person();
            pperson->m_ulFlags &= ~(unsigned long) ::ca::ca::flag_auto_clean;
            pperson->m_pinterface->unkeep(pperson);
            pperson->m_bUnkeep = false;
            //pperson->m_pinterface   = NULL; // fontopus database lifetime isgenerally greater than interface lifetime
            pperson->m_propertyset["id"]             = personid;
            pperson->m_propertyset["name"]          = row.at(0);         
            pperson->m_propertyset["songcount"]    = row.at(1);
            pperson->m_propertyset["click"]          = row.at(2);
         }
         m_cache_person[personid.get_string()] = pperson;
         return pperson;
      }
   }
/*      
   function getPerformerUrl(&$performer)
   {
      $performer->urlinfo = $this->getPerformerUrlInfo($performer->id);
      return $performer;
   }
   function getPerformerUrlInfo($aid)
   {
      $sql = "SELECT performer_url.url, performer_url.title FROM performer_url WHERE performer_url.performerid = {$aid};";
      $result = $this->query($sql);
      $urlinfo = array();
      while($row = fonto_fetch_row($result))
      {
         $urlinfoitem = array();
         $urlinfoitem['url'] = $row[0];
         $urlinfoitem['title'] = $row[1];
         if($urlinfoitem['title'] == "")
         {
            $urlinfoitem['title'] = $urlinfoitem['url'];
         }
         $urlinfo[] = $urlinfoitem;
      }
      return $urlinfo;
   }
*/
   /*
   function getClass($classid)
   {
//      print "getPerformer($performerid)";
      $db = $this->db;
      $class = new MusicClass();
      $class->id       = $classid;
      $sql = "SELECT class.name FROM class WHERE class.id = $classid;";
      $result = $this->query($sql);
      if($result === false)
      {
         return null;
      }
      else if($row = fonto_fetch_row($result))
      {
//         print $row[0];
         $class->name = $row[0];
      }
      else
      {
         return null;
      }
      return $class;
/*      $sql = "SELECT performer_url.url, performer_url.title FROM performer_url WHERE performer_url.performerid = $performerid;";
      $result = mysql_query($sql, $db);
      $urlinfo = array();
      while($row = fonto_fetch_row($result))
      {
         $urlinfoitem = array();
         $urlinfoitem['url'] = $row[0];
         $urlinfoitem['title'] = $row[1];
         if($urlinfoitem['title'] == "")
         {
            $urlinfoitem['title'] = $urlinfoitem['url'];
         }
         $urlinfo[] = $urlinfoitem;
      }
      $performer->urlinfo = $urlinfo;
      return $performer;*/
   //}



      // MusicDatabase::getSongClassesForPerformers
   //
   // CLASSA calculation   
   var fontopus_database::get_song_classes_for_performers(var song)
   {
      string sql = "SELECT DISTINCT class FROM topic_class INNER JOIN topic_song ON topic_song.topic = topic_class.topic AND topic_song.topictype = topic_class.topictype WHERE topic_song.song = " + song;
      var rows = query(sql);   
      var classa;
      for(index i = 0; i < rows.array_get_count(); i++)
      {
         string strClass = rows.at(i);
         classa.vara().add(var(get_class_for_performers(1, "", strClass)));
      }
      return classa;
   }


   // Retrieve a class as for song perfomers retrieval
   // level tells the limit down in the hierarchy that children classes are retrieved
   music::category * fontopus_database::get_class_for_performers(int level, string order, string classa)
   {
      gprop("g_languageid") = m_getstring_languageid;
      
      //global $gc_mysql_metaobject_name_string;
      //$smm = $gc_mysql_metaobject_name_string;      
      
      var classida;
      classida.stra().explode(",", classa);
      string classid = classida.stra().pop();

     string sql = eval("SELECT DISTINCT class.id, class.namestringid, COUNT(DISTINCT song_performer.performerid) AS performercount, COUNT(song.id) as songcount, parentid FROM song INNER JOIN topic_class ON topic_class.topic = song.id INNER JOIN class ON topic_class.class = class.id INNER JOIN song_performer ON song_performer.songid = song.id LEFT OUTER JOIN class_language ON (class.id = class_language.classid AND class_language.languageid = $g_languageid) WHERE class.id = "+classid+" GROUP BY class.id ORDER BY ISNULL(class_language.listorder), class_language.listorder, class.id");
      
      var row = query_row(sql);

      ::music::category * pclass = NULL;      
      if(row.array_get_count() > 0)
      {
         var classid          = row.at(0);
         var classname          = get_string(row.at(1));
         var performercount    = row.at(2);
         var songcount          = row.at(3);
         var parentid          = row.at(4);
         
         pclass                     = new music::category();
         pclass->m_id               = classid;
         pclass->m_navid            = classa;
         pclass->m_name             = classname;
         pclass->m_performercount   = performercount;
         pclass->m_songcount        = songcount;
         pclass->m_parentid         = parentid;
         pclass->m_childrenclass    = get_classes_for_performers(level - 1, order, "");
         
      }
      return pclass;
   }

   // Retrieve Song Classes   
   // The first level contains all parent class children
   // parent class may be a existent composite set of song classes
   // separator between song classes in the composite is a comma
   var fontopus_database::get_classes_for_performers(int level,  string order, string parentclass, int topictype)
   {
      if(level < 1)
         return var();
         
      //global $g_filter_classcondition;
      //global $g_exclude_classcondition;
         
//      global $g_languageid;

/*      if($topic == 'chord')
      {
         $maintable = 'song_chord';
         $mainid = 'songid';
         $topicCondition = ' tmp_class_2.chordcount > 0';         
         $iperformer = 4;
         $iitem = 5;
      }
      else // if($topic == 'song')
      {
         $maintable = 'song';
         $mainid = 'id';
         $topicCondition = ' tmp_class_2.songcount > 0';
         $iperformer = 2;
         $iitem = 3;
      }*/
      
      
      dprint("getClassesForPerformers(topictype)" + gen::str::itoa(topictype));
      
      string topicCondition = "tmp_class_2.topictype = " + gen::str::itoa(topictype);
      
      
      string langid = gen::str::itoa(m_getstring_languageid);
      

      //global $gc_mysql_metaobject_name_string;
      //$smm = $gc_mysql_metaobject_name_string;      
      
      string classcondition = "";
      string sortparentclass;
      var ida;
      if(strlen(parentclass) > 0)
      {
         gprop("classida").stra().explode(",", parentclass);
         gprop("classida").inta().QuickSort();
         sortparentclass = gprop("classida").stra().implode(",");
         ida = gprop("classida");
         ida.stra().surround("<", ">");
         
         //$classcondition = implode("%", $ida);
//         $classcondition = " tmp_class.parentclassida LIKE '%".$classcondition."%' ";
         classcondition = ida.stra().implode("");
         classcondition = " AND tmp_class_2.parentclassida = '" + classcondition + "' ";

//         print $sql;
      }
      if(strlen(gprop("g_filter_classcondition")) > 0)
      {
         classcondition += " AND tmp_class_2.parentclassida LIKE '%" + gprop("g_filter_classcondition") + "%' AND '" + gprop("g_filter_classcondition") + "' LIKE CONCAT('%<', tmp_class_2.classid, '>%') ";
      }
      if(strlen(gprop("g_exclude_classcondition")) > 0)
      {
         classcondition += " AND tmp_class_2.parentclassida NOT LIKE '%" + gprop("g_exclude_classcondition") + "%'  AND '" + gprop("g_exclude_classcondition") + "' NOT LIKE CONCAT('%<', tmp_class_2.classid, '>%') ";
      }
      
      string sql = "SELECT DISTINCT class.id, class.namestringid, MAX(tmp_class_2.performercount), MAX(tmp_class_2.songcount), parentid FROM tmp_class_2 INNER JOIN class ON class.id = tmp_class_2.classid LEFT OUTER JOIN class_language ON class_language.classid = class.id AND class_language.languageid = '"+ langid +"' WHERE " + topicCondition + classcondition + " GROUP BY class.id ORDER BY ISNULL(class_language.listorder), class_language.listorder, class.id";
      
//      print $sql;
      
//      print $sql;
      
      var rows = query_rows(sql);
      
      var classa;
      var classida;
      var navid;
      for(index i = 0; i < rows.array_get_count(); i++)
      {
         var row = rows.at(i);
         var classid          = row.at(0);
         if(is_array(classida))
         {
            if(in_array(classid , classida))
               continue;
         }
         var classname          = get_string(row.at(1));
         var performercount    = row.at(2);
         var songcount          = row.at(3);
         var parentid          = row.at(5);
         
         if(strlen(parentclass) > 0)
         {
            navid = parentclass+","+classid;
         }
         else
         {
            navid = classid;
         }
         
         ::music::category * pclass                   = new music::category();
         pclass->m_id               = classid;
         pclass->m_navid            = navid;
         pclass->m_name            = classname;
         pclass->m_performercount   = performercount;
         pclass->m_songcount         = songcount;
         pclass->m_parentid        = parentid;
         //pclass->m_childrenclass   = get_classes_for_performers(level - 1, order, navid, topic);
         pclass->m_childrenclass   = get_classes_for_performers(level - 1, order, navid);
         
         classa.vara().add(pclass);
      }
      return classa;
   }

	var fontopus_database::get_performers(var classid,  var namequerycode, var order, var topic, var query)
	{
      if(topic.is_empty())
         topic = "song";
		return get_performers_by_class(classid, namequerycode, order, topic, query);
	}
	
	var  fontopus_database::get_performers_by_class(var classid, var namequerycode, var order, var topic, var query)
	{
      if(topic.is_empty())
         topic = "song";
		
		dprint("getPerformersByClass(topic)=" + topic);
		
		string maintable;
      string mainid;
      string count_field;
      string classida_field;
      var topictype;
      string topictypecondition;
		if(topic == "song")
		{
			maintable = "song";
			mainid = "id";
			count_field = "topiccount";
			classida_field = "classida";
			topictype = 0;
			topictypecondition = "tmp_person.topictype = " + topictype;
		}
		else if(topic == "cifras" || topic == 2)
		{
			maintable = "song_chord";
		   mainid = "songid";
			count_field = "topiccount";
			classida_field = "chord_classida";
			topictype = 2;
			topictypecondition = "tmp_person.topictype = " + topictype;
		}
		else if(topic == "letras" || topic == 1)
		{
			maintable = "song_chord";
			mainid = "songid";
			count_field = "topiccount";
			classida_field = "chord_classida";
			topictype = 1;
			topictypecondition = "(tmp_person.topictype = 1 OR tmp_person.topictype = 1001)";
		}
		else
		{
			maintable = "song";
			mainid = "id";
			count_field = "topiccount";
			classida_field = "classida";
			topictype = 0;
		}
		
		string lang = gprop("param_locale");
		string style = gprop("param_style");
		
		var langid 	= getLangId(lang);
		var styleid 	= getStyleId(style);
		
		
		if(order.is_empty())
		{
			order = ORDERBY_PERFORMERNAME;
		}	
		
		string classcondition = "";
		
      var classida;
      var ida;
		if(strlen(classid) > 0)
		{
			classida = explode(",", classid);
			classida.stra().QuickSort();

         ida = classida.stra();
         ida.stra().surround("<", ">");
			
			classcondition = ida.implode("%");
			classcondition = " AND tmp_person.classida LIKE '%" +  classcondition + "%' ";
	
		}
      
		if(strlen(gprop("g_filter_classcondition")) > 0)
		{
			classcondition += " AND tmp_person.classida LIKE '%" + gprop("g_filter_classcondition") + "%' ";
		}
		if(strlen(gprop("g_exclude_classcondition")) > 0)
		{
			classcondition += " AND tmp_person.classida NOT LIKE '%" + gprop("g_exclude_classcondition") +  "%' ";
		}
      string namecondition;
		if(strlen(query) > 0)
		{
         string str;
         str = query;
         str.replace(" ", "%"); // preg_replace "\s"
			query = "%" + str + "%";
			namecondition += " AND person.name LIKE '$query'";
		}
		
		string sql = "SELECT person.id, person.name, tmp_person_lang_style_click.click as personclick, tmp_person.`" + count_field + "`, person.latin_name FROM person LEFT OUTER JOIN tmp_person ON person.id = tmp_person.person AND " + topictypecondition + " LEFT OUTER JOIN tmp_person_lang_style_click ON person.id = tmp_person_lang_style_click.person AND tmp_person_lang_style_click.langid = '" + langid + "' AND tmp_person_lang_style_click.styleid = '" + styleid + "' AND tmp_person_lang_style_click.type='click' WHERE tmp_person.topiccount > 0" + classcondition + " " + namecondition;

      string strRegExp = gprop("p_nameregexp");

		if(strRegExp.has_char())
		{
			if(gen::str::begins_eat(strRegExp, "kp-"))
			{
				sql += " AND person.katakana_prefix REGEXP '" + strRegExp + "'";
			}
			else
			{
				sql += " AND IFNULL(person.latin_name, person.name) REGEXP '" + gprop("p_nameregexp")+"'"; + "'";
			}
		}
		
      string namequerycoderegexp;
		if(strlen(namequerycode) > 0)
		{
			namequerycoderegexp = music().music_performer_get_reg_exp(namequerycode);
			if(gen::str::begins_eat(namequerycoderegexp, "kp-"))
			{
				sql += " AND person.katakana_prefix REGEXP '" + namequerycoderegexp + "'";
			}
			else
			{
				sql += " AND IFNULL(person.latin_name, person.name) REGEXP '" + namequerycoderegexp + "'";
			}
		}

		if(order == ORDERBY_PERFORMERNAME)
		{
			sql += " GROUP BY person.id ORDER BY IFNULL(person.latin_name, person.name)";
		}
		else if(order == ORDERBY_CLICK)
		{
			sql += " GROUP BY person.id ORDER BY personclick DESC, IFNULL(person.latin_name, person.name)";
		}
		else
		{
			// by name
			sql += " GROUP BY person.id ORDER BY IFNULL(person.latin_name, person.name)";
		}
		dprint("$sql");
	   var rowa = query_rows(sql);
		int line = 0;
		var performera;
		for(int i = 0; i < rowa.array_get_count(); i++)
		{
         var & row = rowa.at(i);
			var & id 				= row.at(0);
			var & name				= row.at(1);
			var & click 			= row.at(2);
			var & songcount 		= row.at(3);
			var & latinname		= row.at(4);
			
         music::performer * pperformer = new music::performer;
			pperformer->m_id 				   = id;
			pperformer->m_name 				= name;
			pperformer->m_click 			   = click;
			pperformer->m_songcount 		= songcount;
			pperformer->m_queryclassid	   = classid;
			pperformer->m_latinname		   = latinname;
			
			performera.vara().add(pperformer);
		}
		return performera;
	}


music_database_cache & fontopus_database::cache()
{
   return *m_pmusicdatabasecache;
}


bool fontopus_database::is_karfile_licensed(__int64 iKarFileId)
{
   string strSql;
   strSql.Format("SELECT filename, nessie, `key`, `size`, mimetype, extension FROM karfile WHERE id = %I64d", iKarFileId);
   var row = query_row(strSql);
   if(row.is_empty())
      return false;
   return low_fs_is_licensed(gprop("secureuserid"), row.at(1), row.at(2), row.at(3), row.at(4), row.at(5));
}