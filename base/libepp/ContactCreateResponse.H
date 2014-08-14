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
/* $Id: ContactCreateResponse.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file ContactCreateResponse.H
*  @brief EPP ContactCreateResponse Class
*/
#pragma once


namespace libepp
{

   /// EPP ContactCreateResponse Class
   class ContactCreateResponse : public Response
   {
   public:
      /// Default constructor
      ContactCreateResponse(bool reset = true) : Response(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Sets the contact's id
      /**
      @param id contact id
      */
      void set_id(const char *id) { _id = id; }

      /// Sets the contact's creation date
      /**
      @param crDate contact creation date
      */
      void set_crDate(const char *crDate) { _crDate = crDate; }

      /// Returns the contact's id
      /**
      @return contact id
      */
      string get_id() const { return _id; }

      /// Returns the contact's creation date
      /**
      @return contact creation date
      */
      string get_crDate() const { return _crDate; }

      /// Resets object attributes
      void reset()
      {
         Response::reset();
         _id = "";
         _crDate = "";
      }

   protected:
      /// Contact id
      string _id;

      /// Date and Time of contact creation
      string _crDate;

   };

} // namespace libepp
