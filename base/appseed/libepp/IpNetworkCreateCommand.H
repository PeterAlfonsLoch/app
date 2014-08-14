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
/* $Id: IpNetworkCreateCommand.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file IpNetworkCreateCommand.H
*  @brief EPP IpNetworkCreateCommand Class
*/
#pragma once


namespace libepp 
{

   /// EPP IpNetworkCreateCommand Class
   class IpNetworkCreateCommand : public Command
   {
   public:
      /// Default constructor
      IpNetworkCreateCommand(bool reset = true) : Command(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Sets ip range
      /**
      @param ipRange  ip range
      */
      void set_ipRange(const IpRange &ipRange)
      {
         _ipRange = ipRange;
      }

      /// Returns ip range
      /**
      @return ip range
      */
      IpRange get_ipRange() const
      {
         return _ipRange;
      }

      /// Sets organization
      /**
      @param organization   organization to be associated with the ip range
      */
      void set_organization(const char *organization)
      {
         _organization = organization;
      }

      /// Returns organization associated with the ip range
      /**
      @return organization owner of the ip range
      */
      string get_organization() const
      {
         return _organization;
      }

      /// Sets asn
      /**
      @param asn   autonomous system number that is going to manage the ip range
      */
      void set_asn(const int asn)
      {
         _asn = asn;
      }

      /// Returns asn
      /**
      @return autonomous system number that manages the ip range
      */
      int get_asn() const
      {
         return _asn;
      }

      /// Sets allocation type
      /**
      @param allocType   ip range allocation type
      */
      void set_allocType(const char *allocType)
      {
         _allocType = allocType;
      }

      /// Returns allocation type
      /**
      @return ip range allocation type
      */
      string get_allocType() const
      {
         return _allocType;
      }

      /// Inserts a contact in the map of other contacts
      /**
      @param type             contact type
      @param identification   contact identification
      */
      void insert_contact(const char *type, const char *identification)
      {
         _contacts[type] = identification;
      }

      /// Returns map of other contacts
      /**
      @return map of other contacts
      */
      string_to_string_map get_contacts() const { return _contacts; }

      /// Sets reverse dns
      /**
      @param reverseDns   delegation information for the ip range
      */
      void insert_reverseDns(const ReverseDns &reverseDns)
      {
         _reversesDns.add(reverseDns);
      }

      /// Returns reverses dns
      /**
      @return all delegation information for the ip range
      */
      comparable_array<ReverseDns> get_reversesDns() const
      {
         return _reversesDns;
      }

      void reset()
      {
         Command::reset();
         _ipRange.reset();
         _organization = "";
         _asn = 0;
         _allocType = "";
         _contacts.remove_all();
         _reversesDns.remove_all();
      }

   protected:
      /// ip range
      IpRange _ipRange;

      /// organization associated with the ip range
      string _organization;

      /// autonomous system number that manages the ip range
      int _asn;

      /// allocation type
      string _allocType;

      /// other contact objects
      string_to_string_map _contacts;

      /// delegation information for the ip range
      comparable_array<struct ReverseDns> _reversesDns;
   };

} // namespace libepp
