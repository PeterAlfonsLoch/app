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
/* $Id: BrOrgCreateCommand.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file BrOrgCreateCommand.H
*  @brief EPP BrOrgCreateCommand Class
*/
#pragma once


namespace libepp
{

   /// EPP BrOrgCreateCommand Class
   class BrOrgCreateCommand : public ContactCreateCommand
   {
   public:
      /// Default constructor
      BrOrgCreateCommand(bool reset = true) : ContactCreateCommand(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Sets Organization attribute
      /**
      @param organization   Organization Identifier
      */
      void set_organization(const char *organization)
      {
         _organization = organization;
      }

      /// Returns the Organization
      /**
      @return organization attribute
      */
      string get_organization() const
      {
         return _organization;
      }

      /// Sets the responsible for the organization
      /**
      @param responsible   Person responsible
      */
      void set_responsible(const char *responsible)
      {
         _responsible = responsible;
         _responsible_f = true;
      }

      /// Returns the responsible for the organization
      /**
      @return Person responsible
      */
      string get_responsible() const
      {
         return _responsible;
      }

      /// Sets the responsible change flag
      /**
      @param responsible_f responsible change flag
      */
      void set_responsible_f(const bool responsible_f) 
      {
         _responsible_f = responsible_f;
      }

      /// Returns the responsible change flag
      /**
      @return The responsible change flag
      */
      bool get_responsible_f() const
      {
         return _responsible_f;
      }

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
      string_to_string_map get_contact_list() const
      {
         return _contact_list;
      }

      /// reset attributes
      void reset()
      {
         ContactCreateCommand::reset();
         _organization = "";
         _responsible = "";
         _responsible_f = false;
         _contact_list.remove_all();
      }

   protected:
      /// map with organization attribute
      string _organization;

      /// Person responsible for the organization
      string _responsible;

      /// Responsible change flag
      bool _responsible_f;

      /// Human Contacts
      string_to_string_map _contact_list;
   };

} // namespace libepp
