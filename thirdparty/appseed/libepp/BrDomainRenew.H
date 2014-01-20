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
/* $Id: BrDomainRenew.H 696 2006-04-26 21:40:45Z koji $ */
/** @file BrDomainRenew.H
*  @brief EPP BrDomainRenew extension Class
*/
#pragma once


namespace libepp
{

   /// EPP BrDomainRenew extension Class
   class BrDomainRenew : public DomainRenew
   {
   public:

      /// Constructor
      BrDomainRenew(const ActionType type = BR_DOMAIN_RENEW)
         : DomainRenew(type)
      {
         if (type == BR_DOMAIN_RENEW) {
            _command = new DomainRenewCommand();
            _response = new BrDomainRenewResponse();
         }
      }

      /// Returns raw pointer to the command
      /**
      @return raw pointer to the command
      */
      DomainRenewCommand* get_command()
      {
         return (DomainRenewCommand *) _command.get_p();
      }

      /// Returns raw pointer to the response
      /**
      @return raw pointer to the response
      */
      BrDomainRenewResponse* get_response()
      {
         return (BrDomainRenewResponse *) _response.get_p();
      }
   };

} // namespace libepp
