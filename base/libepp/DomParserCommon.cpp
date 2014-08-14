/* 
* libepp-nicbr 1.10 on 2010-14-10 2009 Registro.br
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
* 1. Redistribution of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
* 
* THIS SOFTWARE IS PROVIDED BY REGISTRO.BR ``AS IS AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIE OF FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
* EVENT SHALL REGISTRO.BR BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*/
/* $Id: DomParserCommon.cpp 1068 2010-07-12 13:58:26Z eduardo $ */

#include "StdAfx.h"

//#include <xercesc/framework/MemBufInputSource.hpp>


//XERCES_CPP_NAMESPACE_USE

namespace libepp 
{

   DomParserCommon::DomParserCommon(::ca::application * papp) :
      ca(papp),
      _parser(papp)
   {
/*      try {
         XMLPlatformUtils::Initialize();
      } catch (const XMLException& to_catch) {
         // throws XmlException
         string message = str_transcode(to_catch.getMessage());
         throw XmlException(XmlException::PARSER_INITIALIZE_EXCEPTION,
            "Could not initialize the XML parser", message);
      }*/

      /// Instantiate the DOM parser.
      //_parser = new DomParser();

      //_parser->setErrorHandler(&_error_handler);
   }

   DomParserCommon::~DomParserCommon()
   {
      //delete _parser;

      // Call the termination method
      //XMLPlatformUtils::Terminate();
   }

   void DomParserCommon::enable_validation(const string& schemas_dir)
   {
      string local_schemas_dir = schemas_dir;
      if (schemas_dir == "")
         local_schemas_dir = SCHEMASDIR;

      //_parser->setDoNamespaces(true);
      //_parser->setDoSchema(true);
      //_parser->setValidationSchemaFullChecking(true);
      //_parser->setValidationScheme(DomParser::Val_Always);

      /*string schema_location =
         "urn:ietf:params:xml:ns:epp-1.0 " + 
         local_schemas_dir + "/epp-1.0.xsd "
         "urn:ietf:params:xml:ns:eppcom-1.0 " + 
         local_schemas_dir + "/eppcom-1.0.xsd "
         "urn:ietf:params:xml:ns:contact-1.0 " + 
         local_schemas_dir + "/contact-1.0.xsd "
         "urn:ietf:params:xml:ns:domain-1.0 " + 
         local_schemas_dir + "/domain-1.0.xsd "
         "urn:ietf:params:xml:ns:host-1.0 " + 
         local_schemas_dir + "/host-1.0.xsd " +
         "urn:ietf:params:xml:ns:brdomain-1.0 " +
         local_schemas_dir + "/brdomain-1.0.xsd "
         "urn:ietf:params:xml:ns:brorg-1.0 " +
         local_schemas_dir + "/brorg-1.0.xsd " +
         "urn:ietf:params:xml:ns:secDNS-1.0 " +
         local_schemas_dir + "/secDNS-1.0.xsd " +
         "urn:ietf:params:xml:ns:ipnetwork-1.0 " +
         local_schemas_dir + "/ipnetwork-1.0.xsd "
         "urn:ietf:params:xml:ns:asn-1.0 " +
         local_schemas_dir + "/asn-1.0.xsd";

      _parser->setExternalSchemaLocation(schema_location);*/
   }

   void DomParserCommon::disable_validation()
   {
      /*_parser->setDoNamespaces(false);
      _parser->setDoSchema(false);
      _parser->setValidationSchemaFullChecking(false);
      _parser->setValidationScheme(DomParser::Val_Never);*/
   }

   string DomParserCommon::str_transcode(const char * to_transcode)
   {
      // ca2 - presumabily, developers should ensure this => - always work with utf8 since input to output
      return to_transcode;
      // XMLString::transcode() already converts from UTF-8 to the local
      // code-page, which we're assuming is ISO-8859-1.
      /*char *str = XMLString::transcode(to_transcode);
      string ret_str;
      if (str == 0) {
         ret_str = "";
      } else {
         ret_str = str;
      }
      XMLString::release(&str);
      return ret_str;*/
   }

   string DomParserCommon::get_xmlns(xml::node * pnode)
   {
      
      string xmlns;

      if(pnode->attr_at(0) != NULL && gen::str::begins(pnode->attr_at(0)->name(), "xmlns")) 
      {
         xmlns = pnode->attr_at(0)->name() + "=\"" + pnode->attr_at(0)->get_string() + "\"";
      }

      return xmlns;

   }

   void DomParserCommon::fill_postal_info(xml::node *n, PostalInfo *postal_info)
   {
      bool look_children = false;
      if (str_transcode(n->get_name()) == "contact:postalInfo") 
      {
         look_children = true;

         if(n->attr("type").has_char()) 
         {
            postal_info->set_type(n->attr("type"));
         }
      }

      if (n->get_type() == xml::node_element)
      {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "contact:name") 
         {
            postal_info->set_name(str_transcode(n->get_text()));
         }
         else if (elem_name == "contact:org") 
         {
            postal_info->set_org(str_transcode(n->get_text()));
         }
         else if (elem_name == "contact:addr") 
         {
            look_children = true;
         }
         else if (elem_name == "contact:street") 
         {
            if (postal_info->get_str1().is_empty()) 
            {
               postal_info->set_str1(str_transcode(n->get_text()));
            }
            else if (postal_info->get_str2().is_empty()) 
            {
               postal_info->set_str2(str_transcode(n->get_text()));
            }
            else if (postal_info->get_str3().is_empty()) 
            {
               postal_info->set_str3(str_transcode(n->get_text()));
            }
         } 
         else if (elem_name == "contact:city") 
         {
            postal_info->set_city(str_transcode(n->get_text()));
         }
         else if (elem_name == "contact:sp") 
         {
            postal_info->set_sp(str_transcode(n->get_text()));
         }
         else if (elem_name == "contact:pc") 
         {
            postal_info->set_pc(str_transcode(n->get_text()));
         }
         else if (elem_name == "contact:cc") 
         {
            postal_info->set_cc(str_transcode(n->get_text()));
         }
      }

      if (look_children) 
      {
         xml::node *child;
         for (child = n->first_child(); child != 0; child = child->get_next_sibling()) 
         {
               fill_postal_info(child, postal_info);
         }
      }
   }

   void DomParserCommon::fill_ds_info(xml::node *n, DSInfo *ds_info) 
   {
      bool look_children = false;

      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "secDNS:dsData") {
            look_children = true;
         } else if (elem_name == "secDNS:keyTag") {
            ds_info->set_key_tag(atoi(str_transcode(n->get_text())));
         } else if (elem_name == "secDNS:alg") {
            ds_info->set_algo(atoi(str_transcode(n->get_text())));
         } else if (elem_name == "secDNS:digestType") {
            int digest_type = atoi(str_transcode(n->get_text()));
            ds_info->set_digest_type(digest_type);
         } else if (elem_name == "secDNS:digest") {
            ds_info->set_digest(str_transcode(n->get_text()));
         } else if (elem_name == "secDNS:maxSigLife") {
            ds_info->set_max_sig_life(atoi(str_transcode(n->get_text())));
         } else if (elem_name == "secDNS:keyData") {
            KeyData keyData;
            fill_key_data(n, &keyData);
            ds_info->set_key_data(keyData);
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_ds_info(child, ds_info);
         }
      }
   }

   void DomParserCommon::fill_key_data(xml::node *n, KeyData *keyData)
   {
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "secDNS:keyData") {
            xml::node *child;

            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() != xml::node_element) {
                     continue;
                  }
                  string curr_name = str_transcode(child->get_name());
                  if (curr_name == "secDNS:flags") {
                     keyData->set_flags(atoi(str_transcode(child->get_text())));
                  } else if (curr_name == "secDNS:protocol") {
                     keyData->set_protocol(atoi(str_transcode(child->get_text())));
                  } else if (curr_name == "secDNS:alg") {
                     keyData->set_algorithm(atoi(str_transcode(child->get_text())));
                  } else if (curr_name == "secDNS:pubKey") {
                     keyData->set_pub_key(str_transcode(child->get_text()));
                  }       
            }
         }
      }
   }

   IpRange DomParserCommon::fill_ipRange(xml::node *n)
   {
      IpRange ipRange;

      if(n->attr("version").has_char()) 
      {
         ipRange.set_version(n->attr("version"));
      }

      if (n->attr("avail").has_char()) 
      {
         if (n->attr("avail") == "1") 
         {
            ipRange.set_available(true);
         } 
         else 
         {
            ipRange.set_available(false);
         }
      }

      xml::node *child;
      for (child = n->first_child(); child != 0; child = child->get_next_sibling())
      {
         string e_name = str_transcode(child->get_name());
         if (e_name == "ipnetwork:startAddress") 
         {
            ipRange.set_ipBegin(str_transcode(child->get_text()));
         }
         else if (e_name == "ipnetwork:endAddress") 
         {
            ipRange.set_ipEnd(str_transcode(child->get_text()));
         }
      }

      return ipRange;
   }

   ReverseDns DomParserCommon::fill_reverseDns(xml::node *n)
   {
      ReverseDns reverseDns;
      xml::node *child;
      for (child = n->first_child(); child != 0; child = child->get_next_sibling()) 
      {
            string e_name = str_transcode(child->get_name()); 
            if (e_name == "ipnetwork:ipRange") 
            {
               reverseDns.ipRange = fill_ipRange(child);
            }
            else if (e_name == "ipnetwork:hostName") 
            {
               reverseDns.nameservers.add(str_transcode(child->get_text()));
            }
      }

      return reverseDns;
   }

   IpRange DomParserCommon::fill_brorg_ipRange(xml::node *n)
   {
      IpRange ipRange;

      if(n->attr("version").has_char())
      {
         ipRange.set_version(n->attr("version"));
      }

      if(n->attr("avail").has_char()) 
      {
         if(n->attr("avail") == "1")
         {
            ipRange.set_available(true);
         }
         else 
         {
            ipRange.set_available(false);
         }
      }

      xml::node *child;
      for (child = n->first_child(); child != 0; child = child->get_next_sibling()) 
      {
         string e_name = str_transcode(child->get_name());
         if (e_name == "brorg:startAddress") 
         {
            ipRange.set_ipBegin(str_transcode(child->get_text()));
         }
         else if (e_name == "brorg:endAddress") 
         {
            ipRange.set_ipEnd(str_transcode(child->get_text()));
         }
      }

      return ipRange;
   }

   /*string_to_string_map DomParserCommon::get_attributes(xml::node *n)
   {
      string_to_string_map attributes;

      if (n->m_etype != xml::node_element) {
         return attributes;
      }

      DOMNamedNodeMap *attrs = n->getAttributes();
      for (unsigned int i = 0; i < attrs->get_count(); ++i) {
         DOMAttr *attr_node = (DOMAttr*) attrs->item(i);
         string curr_name = str_transcode(attr_node->getName());
         attributes[curr_name] = str_transcode(attr_node->getValue());
      }

      return attributes;
   }*/

   /*string_to_string_map DomParserCommon::get_children_simple(xml::node *n)
   {
      string_to_string_map children;

      if (n->m_etype != xml::node_element) {
         return children;
      }

      xml::node *child;
      for (child = n->first_child(); child != 0;
         child = child->get_next_sibling()) {
            if (child->m_etype != xml::node_element) {
               continue;
            }
            string curr_name = str_transcode(child->get_name());
            children[curr_name] = str_transcode(child->get_text());
      }

      return children;
   }*/

   xml::node *DomParserCommon::parse(const char * xml_payload)
   {

      if(!_parser.load(xml_payload))
      {
         throw XmlException(XmlException::UNEXPECTED_PARSER_EXCEPTION, "An unexpected exception occurred in XML Parser");
      }

      return _parser.get_root();
   }

} // namespace libepp