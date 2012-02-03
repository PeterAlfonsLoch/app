#include "StdAfx.h"

namespace webserver
{

namespace fun
{


   double user::get_credit()
   {
      string strSql;
      strSql.Format(" SELECT SUM(value) FROM fun_user_credit_history WHERE user = %d", m_iId);
      var var = musicdb().query_item(strSql);
      if(var.is_new())
         return 0.0;
      return var.get_integer() / 100.0;
   }

   bool user::votagus(const char * pszId)
   {
      string strAppName = pstr("aaaaaaplication." + string(pszId) + ".name");
      string strAppDescription = pstr("aaaaaaplication." + string(pszId) + ".description");
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
         Application.file().put_contents("C:\\ca2\\ca2shop.log", log);
         return false;
      }
      Application.file().put_contents("C:\\ca2\\ca2shop.log", log);

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

   void user::prepare()
   {
      m_strName = m_strFirstName + " " + m_strLastName;
   }


}    // namespace fun



} // namespace webserver