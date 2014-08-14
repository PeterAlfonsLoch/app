#include "StdAfx.h"


namespace libepp
{

   string NSIPAddr::get_xml(::ca::application * papp) const
   {

      string str;

      str += "<domain:hostAddr";
      if(version.has_char()) 
      {
         str += " ip='" + Sys(papp).xml().special_chars(version) + "'";
      }
      str += ">" + Sys(papp).xml().special_chars(addr) + "</domain:hostAddr>";

      return str;

   }


   string NSIPAddrArray::get_xml(::ca::application * papp) const
   {

      string str;

      for(int j = 0; j < get_count(); j++)
      {
         str += element_at(j).get_xml(papp);
      }

      return str;

   }


   string NameServer::get_xml(::ca::application * papp) const
   {
    
      string str;
      
      
      str = "<domain:hostAttr>";
      str += "<domain:hostName>" + Sys(papp).xml().special_chars(name) + "</domain:hostName>";
      str += ips.get_xml(papp);
      str += "</domain:hostAttr>";

      return str;

   }


   string NameServerArray::get_xml(::ca::application * papp) const
   {

      string str;

      str += "<domain:ns>";
      for(int i = 0; i < get_count(); i++) 
      {
         str += element_at(i).get_xml(papp);
      }
      str += "</domain:ns>";

      return str;

   }

} // namespace libepp