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
/* $Id$ */
#pragma once


namespace libepp
{

   /// EPP ContactTransferResponse Class
   class ContactTransferResponse : public Response
   {
   public:

      /// Default constructor
      ContactTransferResponse(bool reset = true) : Response(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Sets contact ID
      /**
      @param id server-unique identifier for the queried contact
      */
      void set_id(const char *id)
      {
         _id = id;
      }

      /// Returns ID
      /**
      @return server-unique identifier for the queried contact
      */
      string get_id() const
      {
         return _id;
      }

      /// Sets state of the most recent transfer request
      /**
      @param trStatus transfer status
      */
      void set_trStatus(const char *trStatus)
      {
         _trStatus = trStatus;
      }

      /// Returns state of the most recent transfer request
      /**
      @return transfer status
      */
      string get_trStatus() const
      {
         return _trStatus;
      }

      /// Sets identifier of the client that requested the object transfer
      /**
      @param reID request ID
      */
      void set_reID(const char *reID)
      {
         _reID = reID;
      }

      /// Returns identifier of the client that requested the object
      /// transfer
      /**
      @return request ID
      */
      string get_reID() const
      {
         return _reID;
      }

      /// Sets date and time that the transfer was requested
      /**
      @param reDate transfer reqeust date
      */
      void set_reDate(const char *reDate)
      {
         _reDate = reDate;
      }

      /// Returns date and time that the transfer was requested
      /**
      @return transfer reqeust date
      */
      string get_reDate() const
      {
         return _reDate;
      }

      /// Sets identifier of the client that SHOULD act upon a PENDING transfer
      /// request
      /**
      @param acID identifier of the client
      */
      void set_acID(const char *acID)
      {
         _acID = acID;
      }

      /// Returns identifier of the client that SHOULD act upon a PENDING
      /// transfer request
      /**
      @return identifier of the client
      */
      string get_acID() const
      {
         return _acID;
      }

      /// Sets date and time of a required or completed response
      /**
      @param acDate date
      */
      void set_acDate(const char *acDate)
      {
         _acDate = acDate;
      }

      /// Returns date and time of a required or completed response
      /**
      @return date
      */
      string get_acDate() const
      {
         return _acDate;
      }

      /// reset attributes
      void reset() 
      { 
         Response::reset();
         _id = "";
         _trStatus = "";
         _reID = "";
         _reDate = "";
         _acID = "";
         _acDate = "";
      }

   protected:
      /// Server-unique identifier for the queried contact
      string _id;

      /// State of the most recent transfer request
      string _trStatus;

      /// Identifier of the client that requested the object transfer
      string _reID;

      /// Date and time that the transfer was requested
      string _reDate;

      /// Identifier of the client that SHOULD act upon a PENDING transfer
      /// request
      string _acID;

      /// date and time of a required or completed response
      string _acDate;
   };

} // namespace libepp
