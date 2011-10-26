#include "StdAfx.h"

namespace webserver
{

namespace fun
{

   friend_search::friend_search(int iPage)
   {
	   m_iPage = iPage;
      m_iFunUserCount = fun().get_active_user_count();
	   m_iRecordsPerPage = 10;
	   m_iPageCount = (m_iFunUserCount + 1) / m_iRecordsPerPage;
	   m_iStartRecord = m_iPage * m_iRecordsPerPage;
	   m_usera = get_friends(m_iStartRecord, m_iRecordsPerPage);
   }

   var friend_search::get_friends(int iStartRecord, int iRecordsPerPage)
   {
      var usera;
      string strSql;
      strSql.Format("SELECT id, firstname, lastname, imageid, email FROM fun_user WHERE register = 1 ORDER BY firstname LIMIT %d, %d ", iStartRecord, iRecordsPerPage);
      var rows = musicdb().query_rows(strSql);
      for(int i = 0; i < rows.array_get_count(); i++)
	   {
         var row = rows.at(i);
		   var id			= row[0];
		   var firstname 	= row[1];
		   var lastname 	= row[2];
		   var imageid 	= row[3];
		   var email 		= row[4];

		   ::webserver::fun::user * puser               = new ::webserver::fun::user();
		   puser->m_iId 				   = id;
		   puser->m_strFirstName		= firstname;
		   puser->m_strLastName		   = lastname;
         puser->m_iImage		      = imageid;
		   puser->m_strEmail 			= email;

		   puser->prepare();

		   usera.vara().add(puser);
	   }
	   return usera;
   }

   void friend_search::print_nav()
   {
      int iPage = 0;
	   for(; iPage < m_iPageCount; iPage++)
	   {
		   if(iPage == m_iPage)
		   {
			   print("<strong><big>");
			   print(gen::str::itoa(iPage));
			   print("</big></strong>");
		   }
		   else
		   {
			   print("<a href=\"/fun/FriendSearch?page=" + gen::str::itoa(iPage) + "\">");
			   print(gen::str::itoa(iPage));
			   print("</a>");
		   }
		   print("&nbsp;&nbsp;&nbsp;");
	   }
	   print("<br><br>");
   }

   void friend_search::print_friends()
   {
	   print("<table>");
	   for(int i = 0; i < m_usera.vara().get_count(); i++)
	   {
         ::webserver::fun::user * puser = m_usera.vara()[i].ca2 < ::webserver::fun::user >();
		   print("<tr>");
		   print( "<td>");
		   print( "<a href=\"/fun/Home?user={"+gen::str::itoa(puser->m_iId)+"}\">");
		   print( "<img src=\"/img?...."+gen::str::itoa(puser->m_iImage)+".80\">");
		   print( "</a>");
		   print( "</td>");
		   print( "<td>");
		   print( "<a href=\"/fun?Home&user={$user->id}\">");
		   print( puser->m_strFirstName);
		   print( "</a>");
		   print( "</td>");
		   print( "</tr>");
	   }
	   print( "</table>");
   }

} // namespace fun

} // namespace webserver
