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
/* $Id: ContactUpdate.H 543 2006-03-07 12:31:53Z cesar $ */
/** @file ContactUpdate.H
*  @brief EPP ContactUpdate Class
*/
#pragma once


namespace libepp
{

   /// EPP ContactUpdate Class
   class ContactUpdate : public Action
   {
   public:

      /// Constructor
      ContactUpdate(const ActionType type = CONTACT_UPDATE) : Action(type)
      {
         if (type == CONTACT_UPDATE) {
            _command = new ContactUpdateCommand();
            _response = new Response();
         }
      }

      /// Sets the xml template and parses the tags
      /**
      @param xml_template XML command template
      */
      void set_xml_template(DomParser * pparser, const char * xml_template);

      /// Sets the response attribute
      /**
      @param xml_payload   XML document
      @param parser        reference to the XML parser
      */
      void set_response(const char *xml_payload, DomParser *parser)
      {
         get_response()->reset();
         parser->parse_contact_update_response(xml_payload, get_response());
      }

      /// Returns raw pointer to the command
      /**
      @return raw pointer to the command
      */
      ContactUpdateCommand* get_command() 
      {
         return (ContactUpdateCommand*) _command.get_p(); 
      }

   };

} // namespace libepp
