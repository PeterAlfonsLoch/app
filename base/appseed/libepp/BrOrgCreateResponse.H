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
/* $Id: BrOrgCreateResponse.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file BrOrgCreateResponse.H
*  @brief EPP BrOrgCreateResponse Class
*/
#pragma once


namespace libepp 
{

   /// EPP BrOrgCreateResponse Class
   class BrOrgCreateResponse : public ContactCreateResponse
   {
   public:
      /// Default constructor
      BrOrgCreateResponse(bool reset = true) : ContactCreateResponse(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Resets object attributes
      void reset()
      {
         ContactCreateResponse::reset();
         _organization = "";
      }

      /// Sets organization identifier
      /**
      @param organization   organization identifier
      */
      void set_organization(const char *organization)
      {
         _organization = organization;
      }

      /// Returns the organization identifier
      /**
      @return organization attribute
      */
      string get_organization() const
      {
         return _organization;
      }

   protected:
      /// organization identifier
      string _organization;
   };

} // namespace liberpp
