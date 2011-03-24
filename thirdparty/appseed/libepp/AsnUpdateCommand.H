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
/* $Id: AsnUpdateCommand.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file AsnUpdateCommand.H
*  @brief EPP AsnUpdateCommand Class
*/

#pragma once

namespace libepp
{

   /// EPP AsnUpdate Class
   class AsnUpdateCommand : public Command
   {
   public:
      /// Default constructor
      AsnUpdateCommand(bool reset = true) : Command(false)
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

      /// Inserts a contact to be added
      /**
      @param type             contact type
      @param identification   contact identification
      */
      void insert_contact_add(const char *type, const char *identification)
      {
         _contacts_add[type] = identification;
      }

      /// Returns map of other contacts to be added
      /**
      @return map of other contacts
      */
      string_to_string_map get_contacts_add() const
      {
         return _contacts_add;
      }

      /// Inserts a contact to be removed
      /**
      @param type             contact type
      @param identification   contact identification
      */
      void insert_contact_rem(const char *type, const char *identification)
      {
         _contacts_rem[type] = identification;
      }

      /// Returns map of other contacts to be removed
      /**
      @return map of other contacts
      */
      string_to_string_map get_contacts_rem() const
      {
         return _contacts_rem;
      }

      void reset()
      {
         Command::reset();
         _asn = 0;
         _organization = "";
         _contacts_add.remove_all();
         _contacts_rem.remove_all();
      }

   protected:
      /// autonomous system number
      int _asn;

      /// organization associated with the asn
      string _organization;

      /// contacts to be added
      string_to_string_map _contacts_add;

      /// contacts to be removed
      string_to_string_map _contacts_rem;
   };

} // namespace libepp
