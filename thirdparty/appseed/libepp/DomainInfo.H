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
/* $Id: DomainInfo.H 543 2006-03-07 12:31:53Z cesar $ */
/** @file  DomainInfo.H
*  @brief EPP DomainInfo Class
*/
#pragma once


namespace libepp 
{

   /// EPP DomainInfo Class
   class DomainInfo : public Action
   {
   public:

      /// Constructor
      DomainInfo(::ca::application * papp, const ActionType type = DOMAIN_INFO) : Action(type)
      {
         if (type == DOMAIN_INFO) {
            _command = new DomainInfoCommand();
            _response = new DomainInfoResponse(papp);
         }
      }

      /// Sets XML template
      /**
      @param xml_template   XML command template
      */
      void set_xml_template(DomParser * pparser, const char * xml_template);

      /// Pure virtual method to comparable_array response from a XML document
      /**
      @param xml_payload   XML document
      @param parser        reference to the XML parser
      */
      void set_response(const char *xml_payload, DomParser *parser) 
      {
         get_response()->reset();
         parser->parse_domain_info_response(xml_payload, get_response());
      }

      /// Returns raw pointer to the command
      /**
      @return raw pointer to the command
      */
      DomainInfoCommand* get_command() { return (DomainInfoCommand*) _command.get_p(); }

      /// Returns raw pointer to the response
      /**
      @return raw pointer to the response
      */
      DomainInfoResponse* get_response() { return (DomainInfoResponse*) _response.get_p(); }

   };

} // namespace libepp
