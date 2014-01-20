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
/* $Id: BrOrgCreate.H 1021 2009-05-11 18:56:22Z eduardo $ */
/** @file BrOrgCreate.H
*  @brief EPP BrOrgCreate Class
*/
#pragma once


namespace libepp 
{

   /// EPP BrOrgCreate Class
   class BrOrgCreate : public ContactCreate
   {
   public:
      /// Constructor
      BrOrgCreate(const ActionType type = BR_ORG_CREATE) : ContactCreate(type)
      {
         if (type == BR_ORG_CREATE) {
            _command = new BrOrgCreateCommand();
            _response = new BrOrgCreateResponse();
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
      BrOrgCreateCommand* get_command() 
      { 
         return (BrOrgCreateCommand*) _command.get_p(); 
      }

      /// Returns raw pointer to the response
      /**
      @return raw pointer to the response
      */
      BrOrgCreateResponse* get_response()
      { 
         return (BrOrgCreateResponse*) _response.get_p(); 
      }
   };

} // namespace libepp
