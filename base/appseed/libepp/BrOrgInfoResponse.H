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
/* $Id: BrOrgInfoResponse.H 997 2009-01-22 12:35:13Z rafael $ */
/** @file BrOrgInfoResponse.H
*  @brief EPP BrOrgInfoResponse Class
*/
#pragma once


namespace libepp
{

   /// EPP BrOrgInfoResponse Class
   class BrOrgInfoResponse : public ContactInfoResponse
   {
   public:
      /// Default constructor
      BrOrgInfoResponse(bool reset = true) : ContactInfoResponse(false)
      {  
         if (reset) {
            this->reset();
         }
      } 

      /// Copies data from the parent
      void copy_parent_data(ContactInfoResponse &parent) 
      {
         _roid = parent.get_roid();
         _status_set = parent.get_status_set();
         _clID = parent.get_clID();
         _crID = parent.get_crID();
         _crDate = parent.get_crDate();
         _upID = parent.get_upID();
         _upDate = parent.get_upDate();
         _trDate = parent.get_trDate();
         _common = parent.get_common_data();
         _authInfo = parent.get_authInfo();
      }

      /// Sets the Organization
      /**
      @param organization Organization Identifier
      */
      void set_organization(const char *organization)
      {
         _organization = organization;
      }

      /// Returns the Organization
      /**
      @return Organization Identifier
      */
      string get_organization() 
      {
         return _organization;
      }


      /// Sets Responsible for the organization
      /**
      @param responsible   Person Responsible
      */
      void set_responsible(const char *responsible) 
      {
         _responsible = responsible;
      }

      /// Returns Responsible for the organization
      /**
      @return Person Responsible
      */
      string get_responsible() { return _responsible; };

      /// Inserts a Contact into the list
      /**
      @param id Contact Id
      @param type Contact Type
      */
      void insert_contact(const char *type, const char *id)
      {
         _contact_list[type] = id;
      }

      /// Returns the Contact List
      /**
      @return Contact List
      */
      string_to_string_map get_contact_list() 
      {
         return _contact_list;
      }

      /// Sets the Legal Representative
      /**
      @param proxy Local Legal Representative
      */
      void set_proxy(const char *proxy) 
      {
         _proxy = proxy;
      }

      /// Returns the Legal Representative
      /**
      @return Local Legal Representative
      */
      string get_proxy() 
      {
         return _proxy;
      }

      /// Inserts a domain name into the list
      /**
      @param fqdn fully qualified domain name
      */
      void insert_domainName(const char *fqdn)
      {
         _domain_list.add(fqdn);
      }

      /// Returns the domain name list
      /**
      @return domain name list
      */
      stringa get_domainName_list()
      {
         return _domain_list;
      }

      /// Sets  date and  time  identifying the  end  of the  organization
      /// object's registration period
      /**
      @param exDate expiration date
      */
      void set_exDate(const char *exDate)
      {
         _exDate = exDate;
      }

      /// Returns date  and time identifying  the end of  the organization
      /// object's registration period
      /**
      @return expiration date
      */
      string get_exDate() const
      {
         return _exDate;
      }

      /// Inserts   Autonomous   System   object  associated   with   this
      /// organization
      void insert_asn(const int &asn)
      {
         _asn_list.add(asn);
      }

      /// Returns   Autonomous   System   object  associated   with   this
      /// organization
      int_array get_asn_list() const
      {
         return _asn_list;
      }

      /// Inserts  IP addresses  of network  objects associated  with this
      /// organization
      void insert_ipRange(const IpRange &ipRange)
      {
         _ipRange_list.add(ipRange);
      }

      /// Returns  IP addresses  of network  objects associated  with this
      /// organization
      comparable_array<IpRange> get_ipRange_list() const
      {
         return _ipRange_list;
      }

      /// reset attributes
      void reset() { 
         ContactInfoResponse::reset();
         _organization = "";
         _responsible = "";
         _proxy = "";
         _contact_list.remove_all();
         _domain_list.remove_all();
         _exDate = "";
         _asn_list.remove_all();
         _ipRange_list.remove_all();
      }

   protected:
      /// Organization Identifier
      string _organization;

      /// Person responsible for the organization
      string _responsible;

      /// Human Contacts
      string_to_string_map _contact_list;

      /// Local Legal Representative
      string _proxy;

      /// Domain names
      stringa _domain_list;

      /// Expiration date
      string _exDate;

      /// ASNs
      int_array _asn_list;

      // IP Ranges
      comparable_array<IpRange> _ipRange_list;
   };

}
