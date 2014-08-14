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
/* $Id: DomainCreateCommand.H 1076 2010-08-03 18:55:45Z rafael $ */
/** @file  DomainCreateCommand.H
*  @brief EPP DomainCreateCommand Class
*/
#pragma once


namespace libepp
{

   /// EPP DomainCreateCommand Class
   class DomainCreateCommand : public Command
   {
   public:
      /// Default constructor
      DomainCreateCommand(::ca::application * papp, bool reset = true) : ca(papp), Command(false), _ds_list(papp)
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

      /// Sets domain registration period
      /**
      @param time   amount of time
      @param unit   measure unit
      */
      void set_period(const int time, const string& unit)
      {
         _period.time = time;
         _period.unit = unit;
      }

      /// Returns domain registration period
      /**
      @return domain registration period
      */
      RegistrationPeriod get_period() const { return _period; }

      /// Inserts a nameserver to the list of nameservers
      /**
      @param nameserver   a name server
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

      ///  Adds DS information
      /**
      @param DS information
      */
      void add_dsInfo(const DSInfo &ds_info)
      {
         _ds_list.add(ds_info);
      }

      /// Returns DS information list
      /**
      @return DS information list
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

      //******************** RFC 4310/5910 END ********************

      /// Check if there is any extension
      bool has_extension() const {
         return has_secdns_extension();
      }

      /// Check if there is secDNS extension
      bool has_secdns_extension() const 
      {
         bool hasSecDns10 = _secDnsVersion == "1.0" && !_ds_list.is_empty();

         bool hasSecDns11 = _secDnsVersion == "1.1" && !(_ds_list.is_empty() && _dnskey_list.is_empty());

         return (hasSecDns10 || hasSecDns11);
      }

      /// Reset object attributes
      void reset()
      {
         Command::reset();
         _name = "";
         _period.time = 0;
         _period.unit = "";
         _nameservers.remove_all();
         _registrant = "";
         _contacts.remove_all();
         _authInfo.reset();
         _secDnsVersion = "1.1";
         _max_sig_life = 0;
         _ds_list.remove_all(); 
         _dnskey_list.remove_all();
      }

   protected:
      /// fully qualified domain name
      string _name;

      /// initial registration period of the domain object
      RegistrationPeriod _period;

      /// name servers associated with domain object
      NameServerArray _nameservers;

      /// registrant
      string _registrant;

      /// other contact objects
      string_to_string_map _contacts;

      /// Authorization information
      AuthInfo _authInfo;

      /// RFC 4310/5910 secDNS extension version
      string _secDnsVersion;

      /// RRSIG max signature life
      unsigned int _max_sig_life;

      /// DS info
      ds_info_array _ds_list;

      /// KeyData
      collection::list < KeyData > _dnskey_list;
   };

} // namespace libepp

