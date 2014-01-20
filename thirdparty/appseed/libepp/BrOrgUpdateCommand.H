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
/* $Id: BrOrgUpdateCommand.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file BrOrgUpdateCommand.H
*  @brief EPP BrOrgUpdateCommand Class
*/
#pragma once


namespace libepp 
{

   /// EPP BrOrgUpdateCommand Class
   class BrOrgUpdateCommand : public ContactUpdateCommand
   {
   public:
      /// Default constructor
      BrOrgUpdateCommand(bool reset = true) : ContactUpdateCommand(false)
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

      /// Sets Responsible for the organization
      /**
      @param responsible   Person Responsible
      */
      void set_responsible(const char *responsible) 
      {
         _responsible = responsible;
         _responsible_f = true;
      }

      /// Returns Responsible for the organization
      /**
      @return Person Responsible
      */
      string get_responsible() const { return _responsible; };

      /// Sets the responsible change flag
      /**
      @param responsible_f responsible change flag
      */
      void set_responsible_f(const bool responsible_f)
      {
         _responsible_f = responsible_f;
      };

      /// Returns the responsible change flag
      /**
      @return The responsible change flag
      */
      bool get_responsible_f() const
      {
         return _responsible_f;
      };

      /// Sets expiration date
      /**
      @param exDate   object expiration date
      */
      void set_exDate(const string& exDate) { _exDate = exDate; }

      /// Returns expiration date
      /**
      @return expiration date
      */
      string get_exDate() const { return _exDate; }

      /// Inserts a Contact into the list of additions
      /**
      @param id Contact Id
      @param type Contact Type
      */
      void insert_contact_add(const char *type, const char *id)
      {
         _contact_list_add[type] = id;
      }

      /// Returns the Contact List of additions
      /**
      @return Contact List
      */
      string_to_string_map get_contact_list_add() const
      {
         return _contact_list_add;
      }

      /// Inserts a Contact into the list of deletions
      /**
      @param id Contact Id
      @param type Contact Type
      */
      void insert_contact_rem(const char *type, const char *id)
      {
         _contact_list_rem[type] = id;
      }

      /// Returns the Contact List
      /**
      @return Contact List
      */
      string_to_string_map get_contact_list_rem() const
      {
         return _contact_list_rem;
      }

      /// reset attributes
      void reset()
      {
         ContactUpdateCommand::reset();
         _organization = "";
         _contact_list_add.remove_all();
         _contact_list_rem.remove_all();
         _responsible = "";
         _responsible_f = false;
         _exDate = "";
      }

   protected:
      /// map with organization attribute
      string _organization;

      /// Person responsible for the organization
      string _responsible;

      /// Responsible change flag
      bool _responsible_f;

      /// date and  time identifying the end of  the organization object's
      /// registration period
      string _exDate;

      /// Human Contacts to add
      string_to_string_map _contact_list_add;

      /// Human Contacts to remove
      string_to_string_map _contact_list_rem;
   };
 
} // namespace libepp
