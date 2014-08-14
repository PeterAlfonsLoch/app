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
/* $Id: BrOrgCheckResponse.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file BrOrgCheckResponse.H
*  @brief EPP BrOrgCheckResponse extension Class
*/
#pragma once


namespace libepp 
{

   /// EPP BrOrgCheckResponse extension Class
   class BrOrgCheckResponse : public ContactCheckResponse
   {
   public:

      struct Unavailability {
         int tkt_num;
         string tkt_fqdn;
      };

      /// Default constructor
      BrOrgCheckResponse(bool reset = true) : ContactCheckResponse(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Copies data from the parent
      void copy_parent_data(const ContactCheckResponse &parent) 
      {
         _availability_list = parent.get_availability_list();	
      }

      /// Inserts unavailability information for a organization
      /**
      @param organization Organization Identifier 
      @param unavail      Unavailability information
      */
      void insert_unavailability(const char *organization,
         const struct BrOrgCheckResponse::Unavailability&
         unavail);

      /// Returns the unavailable orgs list
      /**
      @return unavailable orgs list
      */
      collection::string_map < Unavailability > get_unavailability_list() const;

      /// Resets object attributes
      void reset() 
      {
         ContactCheckResponse::reset();
         _unavailability_list.remove_all();
      }

   protected:
      /// Unavailable orgs list
      collection::string_map < Unavailability > _unavailability_list;
   };

} // namespace libepp
