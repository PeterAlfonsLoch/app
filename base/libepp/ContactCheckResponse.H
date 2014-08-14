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
/* $Id: ContactCheckResponse.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file ContactCheckResponse.H
*  @brief EPP ContactCheckResponse Class
*/
#pragma once


namespace libepp 
{

   /// EPP ContactCheckResponse Class
   class ContactCheckResponse : public Response
   {
   public:

      struct Availability {
         string available;
         string reason;
      };

      /// Default constructor
      ContactCheckResponse(bool reset = true) : Response(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Inserts availability information for a contact to the list
      /**
      @param id          contact id
      @param available   contact availability ["0" | "1"]
      @param reason      reason of unavailability
      */
      void insert_availability(const char *id, 
         const char *available,
         const char *reason);

      /// Returns the contact's availability list 
      /**
      @return contact availability list
      */
      collection::string_map < Availability > get_availability_list() const;

      /// reset attributes
      void reset() 
      { 
         Response::reset();
         _availability_list.remove_all();
      }

   protected:
      /// Contact availability list
      collection::string_map < Availability > _availability_list;

   };

} // namespace libepp
