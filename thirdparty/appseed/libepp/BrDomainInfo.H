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
/* $Id: BrDomainInfo.H 543 2006-03-07 12:31:53Z cesar $ */
/** @file BrDomainInfo.H
*  @brief EPP BrDomainInfo extension Class
*/
#pragma once


namespace libepp
{

   /// EPP BrDomainInfo extension Class
   class BrDomainInfo : public DomainInfo
   {
   public:

      /// Constructor
      BrDomainInfo(::ca::application * papp, const ActionType type = BR_DOMAIN_INFO) : DomainInfo(papp, type)
      {
         if (type == BR_DOMAIN_INFO) {
            _command = new BrDomainInfoCommand();
            _response = new BrDomainInfoResponse();
         }
      }

      /// Sets XML template
      /**
      @param xml_template   XML command template
      */
      void set_xml_template(DomParser * pparser, const char * xml_template);

      /// Returns raw pointer to the command
      /**
      @return raw pointer to the command
      */
      BrDomainInfoCommand* get_command()
      {
         return (BrDomainInfoCommand *) _command.get_p();
      }

      /// Returns raw pointer to the response
      /**
      @return raw pointer to the response
      */
      BrDomainInfoResponse* get_response()
      {
         return (BrDomainInfoResponse *) _response.get_p();
      }
   };

} // namespace libepp
