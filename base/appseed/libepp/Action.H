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
/* $Id: Action.H 895 2007-03-08 20:27:11Z eduardo $ */
/** @file Action.H
*  @brief EPP Action Class
*/

#pragma once

namespace libepp
{

   class DomParser;

   /// EPP Action Class
   class Action :
      virtual public ::radix::object
   {
   public:
      /// virtual destructor
      virtual ~Action() {}  


      /// Sets the xml template and parses the tags (pure virtual)
      /**
      @param xml_template XML template     
      */
      virtual void set_xml_template(DomParser * pparser, const char *xml_template) = 0;

      /// Returns XML
      /**
      @return XML
      */
      string get_xml() { return _xml; }

      /// Returns Action type
      /**
      @return Action type
      */
      ActionType who_am_i() { return _type; }

      /// Pure virtual method to comparable_array response from a XML document
      /**
      @param xml_payload   XML document
      @param parser        reference to the XML parser
      */
      virtual void set_response(const char *xml_payload, DomParser *parser) = 0;

      /// Returns raw pointer to the response
      /**
      @return raw pointer to the response
      */
      Response* get_response()
      {
         return _response; 
      }

      /// Returns raw pointer to the command
      /**
      @return raw pointer to the command
      */
      Command* get_command()
      {
         return _command; 
      }

   protected:
      /// Generic command
      gen::scoped_ptr < Command > _command;

      /// Generic response
      gen::scoped_ptr < Response > _response;

      /// Action type
      ActionType _type;

      /// XML command
      string _xml;

      /// Constructor that forces childs to comparable_array their types
      /**
      @param type Action type
      */
      Action(const ActionType &type) : _type(type) {}

      /// Sets the xml template and parses the tags (protected)
      /**
      @param xml_template XML template     
      */
      void set_xml_template_common(const char *xml_template)
      {
         StrUtil su(get_app());
         string clTRID = _command->get_clTRID();
         string_to_string_map to_parse;
         if (clTRID != "") 
         {
            to_parse["clTRID"] = "<clTRID>" + su.esc_xml_markup(clTRID) + "</clTRID>";
         } 
         else
         {
            to_parse["clTRID"] = "";
         }

         // Response specific attributes
         to_parse["svTRID"] = su.esc_xml_markup(_response->get_svTRID());

         string lang = "";
         if (_response->get_result_lang() != "en")
         {
            lang = " lang=\"" + su.esc_xml_markup(_response->get_result_lang()) + "\"";
         }

         Response::result_list result;
         Response::ResultCode resultcode;
         Response::ResultInfo resultinfo;

         result = _response->get_result_list();
         
         to_parse["result"] = "";

         for(POSITION pos = result.get_start_position(); pos != NULL; )
         {
            result.get_next_assoc(pos, resultcode, resultinfo);
            to_parse["result"] += "<result code=\"" + gen::str::itoa(resultcode) + "\">" + "<msg" + lang + ">" + su.esc_xml_markup(resultinfo.msg) + "</msg>";
            for(POSITION pos_ev_it = resultinfo.ext_values.get_head_position(); pos_ev_it != NULL;)
            {
               Response::ResultExtValue & ev_it = resultinfo.ext_values.get_next(pos_ev_it);
               // Contents of the value element must be escaped by the
               // application as it can be an XML string
               if (ev_it.reason == "")
               {
                  to_parse["result"] += "<value " + ev_it.xmlns + ">" + ev_it.value + "</value>";
               } 
               else
               {
                  to_parse["result"] += "<extValue><value " + ev_it.xmlns + ">" + ev_it.value + "</value><reason" + lang + ">" +  su.esc_xml_markup(ev_it.reason) + "</reason></extValue>";
               }
            }
            to_parse["result"] += "</result>";
         }
         _xml = su.parse(xml_template, to_parse, "$(", ")$");
      }

   private:
      Action();

   };

} // namespace libepp
