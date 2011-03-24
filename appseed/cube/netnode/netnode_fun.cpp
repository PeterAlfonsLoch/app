#include "StdAfx.h"

string fun::key1_generate()
{
   string str;
   string strTotal;
   for(int i = 0; i < 84; i++)
   {
      str.Format("%d", System.math().RandRange(0, 19841977));
      strTotal += str;
   }
   str = System.crypt().md5(strTotal);
   return str;
}

string fun::key1_generate_sessid()
{
   return key1_generate() + key1_generate() + key1_generate();
}

double fun::user::get_credit()
{
   string strSql;
   strSql.Format(" SELECT SUM(value) FROM fun_user_credit_history WHERE user = %d", m_iId);
   var var = musicdb().query_item(strSql);
   if(var.is_new())
      return 0.0;
   return var.get_integer() / 100.0;
}

bool fun::user::votagus(const char * pszId)
{
   string strAppName = pstr("ca2app." + string(pszId) + ".name");
   string strAppDescription = pstr("ca2app." + string(pszId) + ".description");
   double dDollar = 1.00;   
   var productid;
   var product = musicdb().query_row("SELECT t.type, t.days, t.trialwindow, p.license, p.licensetype, p.id FROM fun_product as p INNER JOIN fun_license as l ON l.id = p.license INNER JOIN fun_licensetype as t ON p.licensetype = t.id WHERE t.type = '1ymaintenance' AND l.strid = '"+ string(pszId)+"'");
   if(!product.is_empty())
   {
      productid = product.at(5);
   }
   var product2 = musicdb().query_row("SELECT t.type, t.days, t.trialwindow, l.strid, '', p.brl, p.id, p.license, t.id FROM fun_product as p INNER JOIN fun_license as l ON l.id = p.license INNER JOIN fun_licensetype as t ON t.id = p.licensetype  WHERE p.id = " + productid);
   int iValue = atoi(product2.at(5));   

   if(iValue < 0)
      return false;

   string datetime = System.datetime().international().get_gmt_date_time();
   string strSql = "INSERT INTO fun_user_credit_history(user, `datetime`, `value`, `operation`, `transaction`, `license`, `product`, `shop`) VALUES ('"+gen::str::itoa(m_iId)+"', '"+ datetime + "', '"+gen::str::itoa(-iValue)+"', '1000', 'acquiring "+ pszId +"','"+product.at(3)+"','"+product.at(5)+"', 0)";
   if(!musicdb().query(strSql))
   {
      return false;
   }   
   var rowLicense;
   string log = Application.file().as_string("C:\\ca2\\ca2shop.log");
   strSql = "REPLACE INTO fun_user_license (user, product, shop, startdatetime, enddatetime) VALUES ("+gen::str::itoa(m_iId)+", " + product.at(5)+", 0, '" +datetime+ "', '" +datetime+ "' + INTERVAL "+product.at(1)+" DAY)";
   dprint(strSql);
   mysql::result * presult = musicdb().query(strSql);
   if(presult != NULL)
   {
      strSql = "SELECT startdatetime, enddatetime FROM fun_user_license WHERE user = "+gen::str::itoa(m_iId)+" AND product = " + product.at(5);
      dprint(strSql);
      rowLicense = musicdb().query_row(strSql);
      log += "user license enabled\n";
                  
      strSql = "INSERT INTO fun_user_license_history SET user ="+gen::str::itoa(m_iId)+", product = " + product.at(5)+", shop = 0, startdatetime = '" + rowLicense.at(0) + "', enddatetime = '" + rowLicense.at(1) + "', `value` = " + gen::str::itoa(iValue) + ", free = " + gen::str::itoa(iValue == 0 ? 1 : 0);
      dprint(strSql);
      mysql::result * presult2 = musicdb().query(strSql);
      if(presult2 == NULL)
      {
         log += "sql=" + strSql + "\n";
         log += "Failed to update license history\n";
      }
      else
      {
         log += "user license history updated\n";
      }
   }
   else
   {
      log += "sql=" + strSql + "\n";
      log += "Failed to update license status\n";
      string strSql = "DELETE FROM fun_user_credit_history WHERE user = '"+gen::str::itoa(m_iId)+"' AND `datetime` = '"+ datetime + "' AND  `value` = '"+gen::str::itoa(iValue)+"' AND `operation` = '1000' AND  `product` = '"+product.at(5)+"'";
      if(!musicdb().query(strSql))
      {
         log += "sql=" + strSql + "\n";
         log += "Failed to refund credit\n";
      }   
      System.file().put_contents("C:\\ca2\\ca2shop.log", log);
      return false;
   }
   System.file().put_contents("C:\\ca2\\ca2shop.log", log);

   double dCredit = get_credit();
   double dPrice = double(iValue) / (dDollar * 100.0);
   class ::email email(get_app());
   email.m_strRecipientName = m_strName;
   email.m_addressRecipient = m_strEmail;
   email.m_strBody.Format(
unitext("Olá %s,\r\n\
\r\n\
Recentemente, você contribuiu com um projeto ca2!\r\n\
Você adquiriu a licença do programa:\r\n\
\r\n\
\r\n\
        %s\r\n\
        %s\r\n\
        Pelo período que vai de %s a %s.\r\n\
\r\n\
\r\n\
        Pelo valor de $%0.2f.\r\n\
        Seu crédito era de $%0.2f.\r\n\
        Seu saldo atual é de $%0.2f.\r\n\
\r\n\
\r\n\
Para consultar estes e outros dados, entre o site ca2shop e acesse o link Licenças de Software.\r\n\
\r\n\
        http://ca2shop.com/\r\n\
\r\n\
Lá estarão listadas as licenças, suas validades e o link para o download dos respectivos aplicativos.\r\n\
\r\n\
Atenciosamente,\r\n\
Camilo Sasuke Tsumanuma\r\n\
shop@ca2mail.com\r\n\
\r\n\
Para mais detalhes sobre o projeto ca2, acesse:\r\n\
http://ca2.cc/"), m_strFirstName, strAppName, strAppDescription, rowLicense.at(0).get_string(),
rowLicense.at(1).get_string(), dPrice, dCredit + dPrice, dCredit);
      
   email.m_strSubject = unitext("[ca2 : ")+ strAppName + unitext("] Nova licença do projeto ca2");
   email.m_strSenderName = "Camilo Sasuke Tsumanuma";
   email.m_addressSender = "camilo@ca2shop.com";      
      
   dprint("email=" + email.m_addressRecipient.to_string());
   dprint("subject=" + email.m_strSubject);
   dprint("body=" + email.m_strBody);
   dprint("headers=" + email.m_strHeaders);
   System.email().utf8_mail(email);

   return true;
}

fun::user * fun::get_user(int iId, bool bGetMergeAccounts)
{
   string strSql;
   strSql.Format(" SELECT `firstname` , `lastname` , `imageid` , `email`, `merge`, `currentboard` FROM `fun_user` WHERE `id` = %d", iId);
   var var = musicdb().query_row(strSql);
   if(var.is_new())
      return NULL;
   user * puser = new user;
   keep(puser);
   puser->m_iId = iId;
   puser->m_strFirstName = var.propset().at(0);
   puser->m_strLastName = var.propset().at(1);
   puser->m_iImage = var.propset().at(2);
   puser->m_strEmail = var.propset().at(3);
   int iMerge = var.propset().at(4);
   puser->m_strCurrentBoard = var.propset().at(5);
   puser->m_iMergeId = -1;
   if(bGetMergeAccounts && !var.propset().at(4).is_null() && iMerge != 0)
   {
      strSql.Format("SELECT `id` FROM `fun_user` WHERE `merge` = %d", iMerge);
      class var mergea = musicdb().query_items(strSql);
      for(int i = 0; i < mergea.array_get_count(); i++)
      {
         if(mergea.at(i).get_integer() != iId)
         {
            user * puserMerge = get_user(mergea.at(i).get_integer(), false);
            puser->m_userptraMerge.add(puserMerge);
            puser->m_iMergeId = iMerge;
            puserMerge->m_iMergeId = iMerge;
         }
      }
      for(int i = 0; i < puser->m_userptraMerge.get_count(); i++)
      {
         user * puserMerge = puser->m_userptraMerge[i];
         puserMerge->m_userptraMerge.add(puser);
         for(int j = 0; j < puser->m_userptraMerge.get_count(); j++)
         {
            if(i != j)
            {
               puserMerge->m_userptraMerge.add(puser->m_userptraMerge[j]);
            }
         }
      }
   }
   puser->prepare();
   return puser;
}



void fun::user::prepare()
{
   m_strName = m_strFirstName + " " + m_strLastName;
}

bool fun::add_user_group(const char * pszUser, const char * pszGroup)
{
   string strSql;
   strSql.Format("INSERT INTO fun_user_group(`user`, `group`) VALUES ('%s', '%s')", pszUser, pszGroup);
   return musicdb().query(strSql) != NULL;
}


int fun::get_group_id(const char * pszGroup)
{
   string strSql;
   strSql.Format("SELECT id FROM fun_group WHERE name = '%s'", pszGroup);
   return musicdb().query_item(strSql);
}


bool fun::is_active()
{
   return false;
}


var fun::get_user_friend_id(int iId)
{
   string strSql;
   strSql.Format("SELECT DISTINCT `f1`.`userid2` FROM `fun_user_user` as f1, `fun_user_user` as f2 WHERE `f1`.`userid1` = '%d' AND `f1`.`userid2` = `f2`.`userid1`  AND `f2`.`userid2` = '%d'",
      iId, iId);
   var varRows = musicdb().query_items(strSql);
   varRows.vara() = varRows.vara(); // force creation of an base_array
   return varRows;
}



void fun::agenda_create_event(gen::property_set set)
{
   string strSql;

   set["topic"] = musicdb().real_escape_string(set["topic"]);
   set["remark"] = musicdb().real_escape_string(set["remark"]);
   set["appointmentid"] = cynce().tag_id(set["appointment"]);

   strSql = 
      "INSERT INTO fun_agenda(`user`, `insertiondatetime`, `startdatetime`, `index`, `appointment`, `topic`, `value`) VALUES ('"+
      gstr("secureuserid") + "', NOW(), '$time', " +
      "(SELECT IFNULL(MAX(a2.index), 1) FROM fun_agenda as a2 WHERE a2.user = '" + gstr("secureuserid") + "' AND a2.startdatetime = NOW()) ,'$appointmentid', '$topic', '$remark')";

   strSql = set.eval(strSql);

   musicdb().query(strSql);
   outheader("Location") = "calendar?query=" + urlencode(set["time"]);
   exit(0);
}

string fun::get_user_string(const char * pszUser, const char * pszKey)
{
   var id = musicdb().query_item("SELECT id FROM fun_data_key WHERE `key` = '" + musicdb().real_escape_string(pszKey)+"'");
   
   if(id.get_type() == var::type_bool && !id)
   {
      return "";
   }
   else
   {
      return musicdb().query_item("SELECT value FROM fun_user_string WHERE user = '" + string(pszUser) + "' AND `key` = '" + id.get_string() + "'").get_string();
   }
}

void fun::set_user_string(const char * pszUser, const char * pszKey, const char * pszValue)
{
   var id = musicdb().query_item("SELECT id FROM fun_data_key WHERE `key` = '" + musicdb().real_escape_string(pszKey)+"'");
   
   if(id.get_type() == var::type_bool && !id)
   {

      musicdb().query("INSERT INTO fun_data_key(`key`) VALUES('"+musicdb().real_escape_string(pszKey)+"')");
      id = musicdb().get_insert_id();
   }
   musicdb().query("REPLACE INTO fun_user_string(`user`, `key`, `value`) VALUES('" + string(pszUser) + "', '"+id.get_string()+"', '"+musicdb().real_escape_string(pszValue)+"')");
}


var fun::get_status(const char * pszId)
{
   string strSql;
   if(pszId == NULL || strlen(pszId) == 0 || gstr("secureuserid") == pszId)
   {
      strSql = "SELECT tag.title FROM cyncecc.tag as tag INNER JOIN cyncecc.tag_tag3 as tag_tag ON tag.id = tag_tag.tag3 INNER JOIN fun_user ON fun_user.securetag = tag_tag.tag WHERE tag_tag.tag2 = 1000000024 AND fun_user.id = '" + gstr("secureuserid") + "' LIMIT 11";
   }
   else
   {
      strSql = "SELECT tag.title FROM cyncecc.tag as tag INNER JOIN cyncecc.tag_tag3 as tag_tag ON tag.id = tag_tag.tag3 INNER JOIN fun_user ON fun_user.securetag = tag_tag.tag INNER JOIN fun_user_user ON userid1 = fun_user.id WHERE userid2 = '" + gstr("secureuserid") + "' AND tag_tag.tag2 = 1000000024 AND fun_user.id = '" + string(pszId) + "' LIMIT 11";
   }

   var var = musicdb().query_items(strSql);
   if(var.is_array())
   {
      if(var.stra().get_count() >= 11)
      {
         var.stra().remove("...");
         var.stra().add("...");
      }
      var.stra().remove("");
      return var.stra().implode(", ");
   }
   else
      return var;
}

var fun::set_status(const char * pszStatus)
{
   var id = cynce().tag_id(pszStatus);
   if(id.is_new())
      return false;
   
   var securetag = musicdb().query_item("SELECT securetag FROM fun_user WHERE id = '"+ gstr("secureuserid") +"'");
   cyncedb().query("DELETE FROM tag_tag3 WHERE tag = "+securetag+" AND tag2 = '1000000024'");
   cynce().tag_tag3_set(securetag, "1000000024", id);
   return id;
}


var fun::get_user_friend(int iId)
{
   class var varFriendId = get_user_friend_id(iId);
   class var varFriend;
   for(int i = 0; i < varFriendId.array_get_count(); i++)
   {
      varFriend.vara().add(get_user(varFriendId.at(i)));
   }
   return varFriend;
}

bool fun::license_karfile(__int64 iKarFileId)
{
   string strSql;
   strSql.Format("SELECT karfile.filename, karfile.nessie, karfile.`key`, karfile.`size`, karfile.mimetype, karfile.extension, song.title FROM karfile INNER JOIN topic_song ON topic_song.topic = karfile.id INNER JOIN song ON song.id = topic_song.song  WHERE topic_song.topictype = 0 AND karfile.id = %I64d", iKarFileId);
   var row = musicdb().query_row(strSql);
   if(row.is_empty())
      return false;
   string strServer = System.url().get_server(request("karfile_url"));
   string strDir;
   if(strServer.has_char())
   {
      strDir = "uifs://Music/Download/From " + strServer;
   }
   else
   {
      strDir = "uifs://Music/Download/From unknown server";
   }
   fs_dir_mk(strDir);
   string strUser;
   __int64 iFolder;
   low_folder(strUser, iFolder, strDir);
   low_fs_add_user_file(gprop("secureuserid"), iFolder, row.at(1), row.at(2), row.at(3), row.at(4), row.at(5), row.at(6), false);
   low_fs_license(gprop("secureuserid"), row.at(1), row.at(2), row.at(3), row.at(4), row.at(5));
   return musicdb().is_karfile_licensed(iKarFileId);
}