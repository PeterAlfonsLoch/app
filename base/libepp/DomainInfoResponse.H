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
/* $Id: DomainInfoResponse.H 1070 2010-07-15 19:00:39Z eduardo $ */
/** @file  DomainInfoResponse.H
*  @brief EPP DomainInfoResponse Class
*/
#pragma once


namespace libepp
{

   /// EPP DomainInfoResponse Class
   class DomainInfoResponse : public Response
   {
   public:

      /// Default constructor
      DomainInfoResponse(::ca::application * papp, bool reset = true) : Response(false), _ds_list(papp)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Sets domain name
      /**
      @param name   fully qualified domain name
      */
      void set_name(const string& name) { _name = name; }

      /// Returns domain name
      /**
      @return fully qualified domain name
      */
      string get_name() const { return _name; }

      /// Sets domain repository object identification
      /**
      @param roid   domain repository object identification
      */
      void set_roid(const string& roid) { _roid = roid; }

      /// Returns domain repository object identification
      /**
      @return domain repository object identification
      */
      string get_roid() const { return _roid; }

      /// Inserts a new status in _status_set
      /**
      @param status   the status to be inserted
      */
      void insert_status(const string& status) { _status_set.add(status); }

      /// Returns comparable_array of domain status
      /**
      @return comparable_array of domain status
      */
      stringa get_status_set() const { return _status_set; }

      /// Sets registrant
      /**
      @param registrant   registrant identification
      */
      void set_registrant(const string& registrant) { _registrant = registrant; }

      /// Returns registrant
      /**
      @return registrant identification
      */
      string get_registrant() const { return _registrant; }

      /// Inserts a contact in the map of other contacts
      /**
      @param type             contact type
      @param identification   contact identification
      */
      void insert_contact(const string& type, const string& identification)
      {
         _contacts[type] = identification;
      }

      /// Returns map of other contacts
      /**
      @return map of other contacts
      */
      string_to_string_map get_contacts() const { return _contacts; }

      /// Inserts a nameserver to the list of nameservers
      /**
      @param nameserver   fully qualified domain name
      */
      void insert_nameserver(const NameServer &nameserver)
      {
         _nameservers.add(nameserver);
      }

      /// Returns a list of nameservers
      /**
      @return list of nameservers associated with domain object
      */
      NameServerArray get_nameservers() const { return _nameservers; }

      /// Sets the sponsoring client
      /**
      @param clID   sponsoring client
      */
      void set_clID(const string& clID)
      {
         _clID = clID;
      }

      /// Returns sponsoring client
      /**
      @return sponsoring client
      */
      string get_clID() const { return _clID; }

      /// Sets the identifier of the client that created the domain object
      /**
      @param crID   id of the client that created the object
      */
      void set_crID(const string& crID) { _crID = crID; }

      /// Returns the identifier of the client that created the domain object
      /**
      @return client identification
      */
      string get_crID() const { return _crID; }

      /// Sets creation date
      /**
      @param crDate   object creation date
      */
      void set_crDate(const string& crDate) { _crDate = crDate; }

      /// Returns creation date
      /**
      @return creation date
      */
      string get_crDate() const { return _crDate; }

      /// Sets the identifier of the client that last updated the domain object
      /**
      @param upID   id of the client that created the object
      */
      void set_upID(const string& upID) { _upID = upID; }

      /// Returns the identifier of the client that last updated the domain object
      /**
      @return id of client that last updated the domain object
      */
      string get_upID() const { return _upID; }

      /// Sets expiration date
      /**
      @param exDate   expiration date
      */
      void set_exDate(const string& exDate) { _exDate = exDate; }

      /// Returns expiration date
      /**
      @return expiration date
      */
      string get_exDate() const { return _exDate; }

      /// Sets last modification date
      /**
      @param upDate   last modification date
      */
      void set_upDate(const string& upDate) { _upDate = upDate; }

      /// Returns last modification date
      /**
      @return last modification date
      */
      string get_upDate() const { return _upDate; }

      /// Sets last successfull transfer date
      /**
      @param trDate   last successfull transfer date
      */
      void set_trDate(const string& trDate) { _trDate = trDate; }

      /// Returns last successfull transfer date
      /**
      @return last successfull transfer date
      */
      string get_trDate() const { return _trDate; }

      /// Sets authorization information
      /**
      @param authInfo   domain authorization information
      */
      void set_authInfo(const AuthInfo &authInfo)
      {
         _authInfo = authInfo;
      }

      /// Returns authorization information
      /**
      @return authorization information
      */
      AuthInfo get_authInfo() const { return _authInfo; }

      //******************** RFC 4310/5910 BEGIN ********************
      /// Adds a DSInfo object to the list
      /**
      @param DSInfo object
      */
      void add_dsInfo(const DSInfo &dsInfo)
      {
         _ds_list.add(dsInfo);
      }

      /// Returns list of DSInfo objects
      /**
      @return list of DSInfo objects
      */
      ds_info_array get_dsInfo() const
      {
         return _ds_list;
      }

      ///  Adds DNSKEY information
      /**
      @param DNSKEY information
      */
      void add_keyData(const KeyData &dnskey_data)
      {
         _dnskey_list.add_tail(dnskey_data);
      }

      /// Returns DNSKEY information list
      /**
      @return DNSKEY information list
      */
      collection::list < KeyData > get_keyDataList() const
      {
         return _dnskey_list;
      }

      /// Sets secDNS extension version
      /**
      @param secDNS extension version
      */
      void set_secDnsVersion(string secDnsVersion)
      {
         _secDnsVersion = secDnsVersion;
      }

      /// Returns secDNS extension version
      /**
      @return secDNS extension version
      */
      string get_secDnsVersion() const
      {
         return _secDnsVersion;
      }
      //******************** RFC 4310/5910 END ********************

      /// Reset object attributes
      void reset()
      {
         Response::reset();
         _name = "";
         _roid = "";
         _status_set.remove_all();
         _registrant = "";
         _contacts.remove_all();
         _nameservers.remove_all();
         _clID = "";
         _crID = "";
         _crDate = "";
         _upID = "";
         _exDate = "";
         _upDate = "";
         _trDate = "";
         _authInfo.reset();
         _ds_list.remove_all();
         _dnskey_list.remove_all();
         _secDnsVersion = "0";
      }

   protected:
      /// fully qualified domain name
      string _name;

      /// element that contains the Repository Object IDentifier assigned
      /// to the domain object when the object was created
      string _roid;

      /// comparable_array of domain status
      stringa _status_set;

      /// registrant
      string _registrant;

      /// other contact objects
      string_to_string_map _contacts;

      /// name servers associated with domain object
      NameServerArray _nameservers;

      /// sponsoring client id
      string _clID;

      /// client that created object
      string _crID;

      /// creation date
      string _crDate;

      /// client that last updated object
      string _upID;

      /// expiration date
      string _exDate;

      /// last modification date
      string _upDate;

      /// last successfull transfer date
      string _trDate;

      /// authorization information
      AuthInfo _authInfo;

      /// DS info
      ds_info_array _ds_list;

      /// KeyData
      collection::list < KeyData > _dnskey_list;

      /// secDNS extension version
      string _secDnsVersion;
   };

} // namespace libeep
