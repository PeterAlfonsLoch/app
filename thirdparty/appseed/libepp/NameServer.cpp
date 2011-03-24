#include "StdAfx.h"


namespace libepp
{

   string NSIPAddr::get_xml() const
   {

      string str;

      str += "<domain:hostAddr";
      if(version.has_char()) 
      {
         str += " ip='" + Application.xml().special_chars(version) + "'";
      }
      str += ">" + Application.xml().special_chars(addr) + "</domain:hostAddr>";

      return str;

   }


   string NSIPAddrArray::get_xml() const
   {

      string str;

      for(int j = 0; j < get_count(); j++)
      {
         str += element_at(j).get_xml();
      }

      return str;

   }


   string NameServer::get_xml() const
   {
    
      string str;
      
      
      str = "<domain:hostAttr>";
      str += "<domain:hostName>" + Application.xml().special_chars(name) + "</domain:hostName>";
      str += ips.get_xml();
      str += "</domain:hostAttr>";

      return str;

   }


   string NameServerArray::get_xml() const
   {

      string str;

      str += "<domain:ns>";
      for(int i = 0; i < get_count(); i++) 
      {
         str += element_at(i).get_xml();
      }
      str += "</domain:ns>";

      return str;

   }

} // namespace libepp