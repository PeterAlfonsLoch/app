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
/* $Id: DomainUpdateCommand.H 1076 2010-08-03 18:55:45Z rafael $ */
/** @file  DomainUpdateCommand.H
*  @brief EPP DomainUpdateCommand Class
*/
#pragma once


namespace libepp 
{

   /// EPP DomainUpdateCommand Class
   class DomainUpdateCommand : public Command
   {
   public:

      struct Status {
         string s;
         string lang;
         string msg;
         bool operator<(const Status &st) const {
            return s < st.s;
         }
      };

      /// Default constructor
      DomainUpdateCommand(::ca::application * papp, bool reset = true) :
         ca(papp), 
         Command(false), 
         _ds_list_chg(papp),
         _ds_list_add(papp),
         _ds_list_rem(papp)
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

      /// Inserts a nameserver_add to the list of nameservers
      /**
      @param nameserver_add   fully qualified domain name
      */
      void insert_nameserver_add(const NameServer &nameserver_add)
      {
         _nameserver_add.add(nameserver_add);
      }

      /// Returns a list of nameserver_add
      /**
      @return list of nameserver_add associated with domain object
      */
      NameServerArray get_nameserver_add() const 
      { 
         return _nameserver_add;
      }

      /// Inserts a nameserver_rem to the list of nameservers
      /**
      @param nameserver_rem   fully qualified domain name
      */
      void insert_nameserver_rem(const NameServer &nameserver_rem)
      {
         _nameserver_rem.add(nameserver_rem);
      }

      /// Returns a list of nameserver_rem
      /**
      @return list of nameserver_rem associated with domain object
      */
      NameServerArray get_nameserver_rem() const 
      {
         return _nameserver_rem;
      }

      /// Inserts a contact_add in the map of contacts
      /**
      @param type_add             contact type
      @param identification_add   contact identification
      */
      void insert_contact_add(const string& type, const string& identification)
      {
         _contact_add[type] = identification;
      }

      /// Returns map of contacts
      /**
      @return map of contacts
      */
      string_to_string_map get_contact_add() const 
      { 
         return _contact_add; 
      }

      /// Inserts a contact_rem in the map of contacts
      /**
      @param type_rem             contact type
      @param identification_rem   contact identification
      */
      void insert_contact_rem(const string& type, const string& identification)
      {
         _contact_rem[type] = identification;
      }

      /// Returns map of contacts
      /**
      @return map of contacts
      */
      string_to_string_map get_contact_rem() const 
      { 
         return _contact_rem; 
      }

      /// Changes a status_add
      /**
      @param status_add status to be changed
      */
      void insert_status_add(const struct Status &status_add) 
      { 
         _status_add.add(status_add);
      }

      /// Returns comparable_array of domain status_add
      /**
      @return comparable_array of domain status_add
      */
      comparable_array<struct Status> get_status_add() const { return _status_add; }

      /// Changes a status_rem in _status_rem
      /**
      @param status_rem   the status_rem to be changed
      */
      void insert_status_rem(const struct Status &status_rem) 
      { 
         _status_rem.add(status_rem); 
      }

      /// Returns comparable_array of domain status_rem
      /**
      @return comparable_array of domain status_rem
      */
      comparable_array<struct Status> get_status_rem() const { return _status_rem; }

      /// Sets registrant
      /**
      @param registrant The domain registrant
      */
      void set_registrant(const char *registrant) 
      {
         _registrant = registrant; 
         _registrant_f = true;
      };

      /// Returns registrant
      /**
      @return registrant The domain registrant
      */
      string get_registrant() const { return _registrant; };

      /// Sets the registrant change flag
      /**
      @param registrant_f registrant change flag
      */
      void set_registrant_f(const bool registrant_f)
      {
         _registrant_f = registrant_f;
      };

      /// Returns the registrant change flag
      /**
      @return The registrant change flag
      */
      bool get_registrant_f() const
      {
         return _registrant_f;
      };

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

      /// Sets the maximum signature life
      /**
      @param max_sig_life the maximum signature life 
      */
      void set_max_sig_life(const unsigned int max_sig_life)
      { 
         _max_sig_life = max_sig_life;
      }

      /// Returns the maximum signature life
      /**
      @return maximum signature life
      */
      unsigned int get_max_sig_life() const 
      {
         return _max_sig_life;
      }

      /// Inserts one DNSKEY into the DNSKEY addition list 
      /**
      @param keydata   DNSKEY information
      */
      void insert_dnskey_add(const KeyData &keydata)
      {
         _dnskey_list_add.add_tail(keydata);
      }

      /// Returns the DNSKEY addition list
      /**
      @return list of DNSKEY records to be inserted into the domain object
      */
      collection::list < KeyData > get_dnskey_add() const
      {
         return _dnskey_list_add;
      }

      /// Inserts one DNSKEY into the DNSKEY removal list
      /**
      @param key_tag   key tag to identify the DNSKEY to be removed
      */
      void insert_dnskey_rem(const KeyData &keydata)
      {
         _dnskey_list_rem.add_tail(keydata);
      }

      /// Returns the DNSKEY removal list
      /**
      @return list of DNSKEY records to be removed from the domain object
      */
      collection::list < KeyData > get_dnskey_rem() const
      {
         return _dnskey_list_rem;
      }

      /// Inserts one ds into the ds addition list 
      /**
      @param ds_info   ds information
      */
      void insert_ds_add(const DSInfo &ds_info)
      {
         _ds_list_add.add(ds_info);
      }

      /// Returns the ds addition list
      /**
      @return list of ds records to be inserted into the domain object
      */
      ds_info_array get_ds_add() const
      {
         return _ds_list_add;
      }

      /// Inserts one ds into the ds removal list
      /**
      @param key_tag   DS RR to be removed
      */
      void insert_ds_rem_1_1(const DSInfo &ds_info)
      {
         _ds_list_rem.add(ds_info);
      }

      /// Inserts one ds into the ds removal list (RFC4310 - DEPRECATED!)
      /**
      @param key_tag   key tag to identify the DS RR to be removed
      */
      void insert_ds_rem(const unsigned int &keyTag)
      {
         _ds_list_rem_1_0.add(keyTag);
      }

      /// Returns the ds removal list
      /**
      @return list of ds records to be removed from the domain object
      */
      ds_info_array get_ds_rem_1_1() const
      {
         return _ds_list_rem;
      }

      /// Returns the ds removal list (RFC4310 - DEPRECATED!)
      /**
      @return list of ds records to be removed from the domain object
      */
      uint_array get_ds_rem() const
      {
         return _ds_list_rem_1_0;
      }

      /// Inserts one ds into the ds change list
      /**
      @param ds_info   ds information
      */
      void insert_ds_chg(const DSInfo &ds_info)
      {
         _ds_list_chg.add(ds_info);
      }

      /// Returns the ds change list
      /**
      @return list of ds records to be removed from the domain object
      */
      ds_info_array get_ds_chg() const
      {
         return _ds_list_chg;
      }

      /// Sets RFC4310 optional "urgent" attribute for domain:update
      /**
      @param urgentFlag domain:update urgent attribute value
      */
      void setUrgentFlag(const bool urgentFlag)
      {
         _urgentFlag = urgentFlag;
      }

      /// Getter for RFC4310 optional "urgent" attribute for domain:update
      /**
      @return RFC4310 optional "urgent" attribute for domain:update
      */
      bool isUrgent() const
      {
         return _urgentFlag;
      }

      /// Sets RFC5910 alternative "remove all" attribute for domain:update
      /**
      @param urgentFlag domain:update urgent attribute value
      */
      void setRemoveAll(const bool removeAll)
      {
         _removeAll = removeAll;
      }

      /// Getter for RFC5910 alternative "remove all" attribute for domain:update
      /**
      @return RFC5910 alternative "remove all" attribute for domain:update
      */
      bool getRemoveAll() const
      {
         return _removeAll;
      }

      //******************** RFC 4310/5910 END ********************

      /// Check if there is any extension
      bool has_extension() const {
         return has_secdns_extension();
      };

      /// Check if there is secDNS extension
      bool has_secdns_extension() const
      {
         bool hasSecDns10 = _secDnsVersion == "1.0" &&
            !(_ds_list_add.is_empty() && _ds_list_rem_1_0.is_empty() && _ds_list_chg.is_empty());

         bool hasSecDns11 = _secDnsVersion == "1.1" &&
            (!(_ds_list_add.is_empty() && _ds_list_rem.is_empty()) ||
            !(_dnskey_list_add.is_empty() && _dnskey_list_rem.is_empty()) ||
            _max_sig_life > 0 || _removeAll == true);

         return (hasSecDns10 || hasSecDns11);
      }

      /// Reset object attributes
      void reset()
      {
         Command::reset();
         _name = "";
         _nameserver_add.remove_all();
         _nameserver_rem.remove_all();
         _contact_add.remove_all();
         _contact_rem.remove_all();
         _status_add.remove_all();
         _status_rem.remove_all();
         _registrant = "";
         _registrant_f = false;

         // RFC 4310/5910
         _secDnsVersion = "1.1";
         _max_sig_life = 0;
         _ds_list_add.remove_all();
         _ds_list_rem.remove_all();
         _ds_list_rem_1_0.remove_all();
         _ds_list_chg.remove_all();
         _dnskey_list_rem.remove_all();
         _dnskey_list_add.remove_all();
         _urgentFlag = false;
         _removeAll = false;

         _authInfo.reset();
      }

   protected:
      /// fully qualified domain name
      string _name;

      /// name servers to be added to the domain object
      NameServerArray _nameserver_add;

      /// name servers to be removed from the domain object
      NameServerArray _nameserver_rem;

      /// contacts to be added to the domain object
      string_to_string_map _contact_add;

      /// contacts to be removed from the domain object
      string_to_string_map _contact_rem;

      /// comparable_array of status to be added to the domain object
      comparable_array<struct Status> _status_add;

      /// comparable_array of status to be removed from the domain object
      comparable_array<struct Status> _status_rem;

      /// registrant
      string _registrant;

      /// registrant change flag
      bool _registrant_f;

      /// authorization information
      AuthInfo _authInfo;

      /// RFC 4310/5910 secDNS extension version
      string _secDnsVersion;

      /// RRSIG max signature life
      unsigned int _max_sig_life;

      /// list of DS RR to be added to the domain object
      ds_info_array _ds_list_add;

      /// list of DS RR to be removed from the domain object
      ds_info_array _ds_list_rem;

      /// list of DS RR to be removed from the domain object (DEPRECATED,
      /// RFC 4310 only!)
      uint_array _ds_list_rem_1_0;

      /// list of DS to be changed in the domain object (RFC 4310 only!)
      ds_info_array _ds_list_chg;

      /// list of DNSKEY RR to be added to the domain object
      collection::list < KeyData > _dnskey_list_add;

      /// list of DNSKEY RR to be removed from the domain object
      collection::list < KeyData > _dnskey_list_rem;

      /// optinal domain:update urgent flag
      bool _urgentFlag;

      /// alternative secDNS:all for secDNS:rem
      bool _removeAll;
   };

} // namespace libepp
