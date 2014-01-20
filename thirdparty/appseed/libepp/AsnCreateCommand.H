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
/* $Id: AsnCreateCommand.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file AsnCreateCommand.H
*  @brief EPP AsnCreateCommand Class
*/

#pragma once

namespace libepp
{

   /// EPP AsnCreate Class
   class AsnCreateCommand : public Command
   {
   public:
      /// Default constructor
      AsnCreateCommand(bool reset = true) : Command(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Sets asn
      /**
      @param asn   autonomous system number
      */
      void set_asn(const int asn)
      {
         _asn = asn;
      }

      /// Returns asn
      /**
      @return autonomous system number
      */
      int get_asn() const
      {
         return _asn;
      }

      /// Sets organization
      /**
      @param organization   organization to be associated with the asn
      */
      void set_organization(const char *organization)
      {
         _organization = organization;
      }

      /// Returns organization associated with the asn
      /**
      @return organization owner of the asn
      */
      string get_organization() const
      {
         return _organization;
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

      void reset()
      {
         Command::reset();
         _asn = 0;
         _organization = "";
         _contacts.remove_all();
      }

   protected:
      /// autonomous system number
      int _asn;

      /// organization associated with the asn
      string _organization;

      /// other contact objects
      string_to_string_map _contacts;

   };

} // namespace libepp

