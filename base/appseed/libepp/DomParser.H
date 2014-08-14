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
/* $Id: DomParser.H 1060 2010-07-06 13:18:18Z rafael $ */
/** @file DomParser.H
*  @brief EPP DomParser Class
*/
#pragma once



namespace libepp 
{

   /// EPP DomParser Class
   class DomParser : public DomParserCommon
   {
   public:

      DomParser(::ca::application * papp);

      /// Parse method to be used by the Unit Test to validate commands
      /**
      @param xml_payload Command (in XML format) to be validated
      */
      void parse_command(const char *xml_payload);

      /// Parse the response to a login command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a response
      */
      void parse_login_response(const char *xml_payload, Response *response);

      /// Parse the response to a logout command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a response
      */
      void parse_logout_response(const char *xml_payload, Response *response);

      /// Parse the response to a connect or hello command
      /**
      @param xml_payload XML to be parsed
      @param greeting Pointer to a greeting response
      */
      void parse_greeting(const char *xml_payload, Greeting *greeting);

      /// Parse the response to a contact check command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a contact check response
      */
      void parse_contact_check_response(const char *xml_payload,
         ContactCheckResponse *response);

      /// Parse the response to a contact create command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a contact create response
      */
      void parse_contact_create_response(const char *xml_payload, ContactCreateResponse *response);

      /// Parse the response to a contact info command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a contact info response
      */
      void parse_contact_info_response(const char *xml_payload, ContactInfoResponse *response);

      /// Parse the response to a contact transfer command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a contact transfer response
      */
      void parse_contact_transfer_response(const char *xml_payload, ContactTransferResponse *response);

      /// Parse the response to a contact update command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a response
      */
      void parse_contact_update_response(const char *xml_payload, Response *response);

      /// Parse the response to a domain check command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a domain check response
      */
      void parse_domain_check_response(const char *xml_payload, DomainCheckResponse *response);

      /// Parse the response to a domain create command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a domain create response
      */
      void parse_domain_create_response(const char *xml_payload, DomainCreateResponse *response);

      /// Parse the response to a domain info command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a domain info response
      */
      void parse_domain_info_response(const char *xml_payload, DomainInfoResponse *response);

      /// Parse the response to a domain transfer command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a domain transfer response
      */
      void parse_domain_transfer_response(const char *xml_payload, DomainTransferResponse *response);

      /// Parse the response to a domain renew command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a domain renew response
      */
      void parse_domain_renew_response(const char *xml_payload, DomainRenewResponse *response);

      /// Parse the response to a domain update command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a response
      */
      void parse_domain_update_response(const char *xml_payload, Response *response);

      /// Parse the response to a domain delete command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a response
      */
      void parse_domain_delete_response(const char *xml_payload, Response *response);

      /// Parse the response to a ip range create command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a ip range create response
      */
      void parse_ipnetwork_create_response(const char *xml_payload, IpNetworkCreateResponse *response);

      /// Parse the response to a ip range check command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a ip range check response
      */
      void parse_ipnetwork_check_response(const char *xml_payload, IpNetworkCheckResponse *response);

      /// Parse the response to a ip range delete command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a ip range delete response
      */
      void parse_ipnetwork_delete_response(const char *xml_payload, Response *response);

      /// Parse the response to a ip range renew command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a ip range renew response
      */
      void parse_ipnetwork_renew_response(const char *xml_payload, 
         IpNetworkRenewResponse *response);

      /// Parse the response to a ip range transfer command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a ip range transfer response
      */
      void parse_ipnetwork_transfer_response(const char *xml_payload, 
         IpNetworkTransferResponse *response);

      /// Parse the response to a ip range info command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a ip range info response
      */
      void parse_ipnetwork_info_response(const char *xml_payload, IpNetworkInfoResponse *response);

      /// Parse the response to a ip range update command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a ip range update response
      */
      void parse_ipnetwork_update_response(const char *xml_payload, Response *response);

      /// Parse the response to an asn check command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a asn check response
      */
      void parse_asn_check_response(const char *xml_payload, AsnCheckResponse *response);

      /// Parse the response to an asn create command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a asn create response
      */
      void parse_asn_create_response(const char *xml_payload, AsnCreateResponse *response);

      /// Parse the response to an asn delete command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a asn delete response
      */
      void parse_asn_delete_response(const char *xml_payload, Response *response);

      /// Parse the response to an asn renew command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a asn renew response
      */
      void parse_asn_renew_response(const char *xml_payload, AsnRenewResponse *response);

      /// Parse the response to an asn transfer command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a asn transfer response
      */
      void parse_asn_transfer_response(const char *xml_payload, AsnTransferResponse *response);

      /// Parse the response to an asn info command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a asn info response
      */
      void parse_asn_info_response(const char *xml_payload, AsnInfoResponse *response);

      /// Parse the response to an asn update command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a asn update response
      */
      void parse_asn_update_response(const char *xml_payload, Response *response);

      /// Parse the response to a poll command
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a poll response
      */
      void parse_poll_response(const char *xml_payload, PollResponse *response);


      string get_contacts_xml(const char * pszEnclose, const char * pszTag, string_to_string_map & contacts, bool bEmptyIfNoContacts = true);
      string get_contacts_xml(const char * pszTag, string_to_string_map & contacts, bool bEmptyIfNoContacts = true);

   protected:
      /// Parse the response
      /**
      @param xml_payload XML to be parsed
      @param response Pointer to a response
      */
      void parse_response(const char *xml_payload, Response *response);

      /// Gets data from an extValue element
      /**
      @param n Pointer to a node of the document tree
      @param value value sub-element of extValue
      @param xmlns value sub-element's attribute
      @param reason reason sub-element of extValue
      */
      void get_extValue_info(xml::node *n, string &value, string &xmlns,
         string &reason);

      /// Fills a result part of a Response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a Response object
      */
      void fill_result(xml::node *n, Response *response);

      /// Fills a Response object 
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a Response object
      */
      void fill_response(xml::node *n, Response *response);  

      /// Fills a Greeting object
      /**
      @param n Pointer to a node of the document tree
      @param greeting Pointer to a greeting object
      */
      void fill_greeting(xml::node *n, Greeting *greeting);

      /// Fills a Contact check response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a contact check response
      */
      void fill_contact_check_response(xml::node *n, ContactCheckResponse *response);

      /// Fills a Contact info response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a contact info response
      */
      void fill_contact_info_response(xml::node *n, ContactInfoResponse *response);

      /// Fills a Contact transfer response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a contact transfer response
      */
      void fill_contact_transfer_response(xml::node *n, ContactTransferResponse *response);

      /// Fills a Contact create response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a contact create response
      */
      void fill_contact_create_response(xml::node *n, ContactCreateResponse *response);  

      /// Fills a Contact PanData response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a PanData response
      */
      void fill_contact_pandata_response(xml::node *n, PanDataResponse *response);

      /// Fills a Domain check response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a domain check response
      */
      void fill_domain_check_response(xml::node *n, DomainCheckResponse *response);

      /// Fills a Domain info response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a domain info response
      */
      void fill_domain_info_response(xml::node *n, DomainInfoResponse *response);

      /// Fills a Domain transfer response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a domain transfer response
      */
      void fill_domain_transfer_response(xml::node *n, DomainTransferResponse *response);

      /// Fills a Domain create response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a domain create response
      */
      void fill_domain_create_response(xml::node *n, DomainCreateResponse *response);

      /// Fills a Domain renew response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a domain renew response
      */
      void fill_domain_renew_response(xml::node *n, DomainRenewResponse *response);

      /// Fills a Domain PanData response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a PanData response
      */
      void fill_domain_pandata_response(xml::node *n, PanDataResponse *response);

      /// Fills a ip range create response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a ip range create response
      */ 
      void fill_ipnetwork_create_response(xml::node *n, IpNetworkCreateResponse *response);

      /// Fills a ip range check response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a ip range check response
      */ 
      void fill_ipnetwork_check_response(xml::node *n, IpNetworkCheckResponse *response);

      /// Fills a ip range renew response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a ip range renew response
      */ 
      void fill_ipnetwork_renew_response(xml::node *n, IpNetworkRenewResponse *response);

      /// Fills a ip range transfer response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a ip range transfer response
      */ 
      void fill_ipnetwork_transfer_response(xml::node *n, IpNetworkTransferResponse *response);

      /// Fills a ip range info response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a ip range info response
      */ 
      void fill_ipnetwork_info_response(xml::node *n, IpNetworkInfoResponse *response);

      /// Fills an asn check response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to an asn check response
      */ 
      void fill_asn_check_response(xml::node *n, AsnCheckResponse *response);

      /// Fills an asn create response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to an asn create response
      */ 
      void fill_asn_create_response(xml::node *n, AsnCreateResponse *response);

      /// Fills an asn renew response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to an asn renew response
      */ 
      void fill_asn_renew_response(xml::node *n, AsnRenewResponse *response);

      /// Fills an asn transfer response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to an asn transfer response
      */ 
      void fill_asn_transfer_response(xml::node *n, AsnTransferResponse *response);

      /// Fills an asn info response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to an asn info response
      */ 
      void fill_asn_info_response(xml::node *n, AsnInfoResponse *response);

      /// Fills a Poll response object
      /**
      @param n Pointer to a node of the document tree
      @param poll_response Pointer to a poll response
      */
      void fill_poll_response(xml::node *n, PollResponse *poll_response);

      /// Fills a BrOrg Info response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a BrOrg Info response
      */
      void fill_brorg_info_response(xml::node *n, BrOrgInfoResponse *response);

      /// Fills a BrOrg Check response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a BrOrg Check response
      */
      void fill_brorg_check_response(xml::node *n, BrOrgCheckResponse *response);

      /// Fills a BrOrg PanData response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a BrOrgPanData response
      */
      void fill_brorg_pandata_response(xml::node *n, BrOrgPanDataResponse *response);

      /// Fills a BrOrgCreate response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a BrOrgCreate response
      */
      void fill_brorg_create_response(xml::node *n, BrOrgCreateResponse *response);

      /// Fills a BrDomain check response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a BrDomain check response
      */
      void fill_brdomain_check_response(xml::node *n, BrDomainCheckResponse *response);

      /// Fills a BrDomain info response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a domain info response
      */
      void fill_brdomain_info_response(xml::node *n, BrDomainInfoResponse *response);

      /// Fills a BrDomain create response object
      /**
      @param n Pointer to a node of the document tree
      @param d_response Pointer to a BrDomain create response
      */
      void fill_brdomain_create_response(xml::node *n, BrDomainCreateResponse *response);

      /// Fills a BrDomain renew response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a domain renew response
      */
      void fill_brdomain_renew_response(xml::node *n, BrDomainRenewResponse *response);

      /// Fills a BrDomain update response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a BrDomain update response
      */
      void fill_brdomain_update_response(xml::node *n, BrDomainUpdateResponse *response);

      /// Fills a BrDomain PanData response object
      /**
      @param n Pointer to a node of the document tree
      @param response Pointer to a BrDomainPanData response
      */
      void fill_brdomain_pandata_response(xml::node *n, BrDomainPanDataResponse *response);
   };

} // namespace libepp
