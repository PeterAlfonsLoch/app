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
/* $Id: AsnCheckResponse.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file  AsnCheckResponse.H
 *  @brief EPP AsnCheckResponse Class
 */

#pragma once


namespace libepp
{

   /// EPP AsnCheckResponse Class
   class AsnCheckResponse : public Response
   {
   public:
     struct CheckData {
       int asn;
       bool available;
       string reason;
       string reason_lang;
     };

     /// Default constructor
     AsnCheckResponse(bool reset = true) : Response(false)
     {
       if (reset) {
         this->reset();
       }
     }

      /// Inserts availability information for an asn to the list
     /**
        @param asn         autonomous system number that manages the ip range
        @param available   true if asn is available or false otherwise
        @param reason      reason of unavailability
        @param reason_lang language used in reason
     */
     void insert_availability(const int asn, const bool available, 
			      const char *reason, 
			      const char *reason_lang = "")
     {
       CheckData cd;
       cd.asn = asn;
       cd.available = available;
       cd.reason = reason;
       cd.reason_lang = reason_lang;
       _availability_list.add(cd);
     }

     /// Returns the ip range availability list
     /**
        @return ip range availability list
     */
     base_array<CheckData> get_availability_list() const
     {
       return _availability_list;
     }
  
     void reset()
     {
       Response::reset();
       _availability_list.remove_all();
     }

   protected:
     /// Asn response list
     base_array<CheckData> _availability_list;
   };

} // namespace libepp

