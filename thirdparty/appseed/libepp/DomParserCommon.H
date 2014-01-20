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
/* $Id: DomParserCommon.H 1068 2010-07-12 13:58:26Z eduardo $ */
/** @file DomParser.H
 *  @brief EPP DomParser Class
 */
#pragma once


namespace libepp
{

   /// EPP DomParser Class
   class DomParserCommon :
      virtual public ::radix::object
   {
   public:
     /// Constructor
     DomParserCommon(::ca::application * papp);

     /// Destructor
     ~DomParserCommon();

     /// Enable Validation
     /**
        @param schemas_dir Path to the schemas directory
      */
     void enable_validation(const string& schemas_dir = SCHEMASDIR);

     /// Disable Validation
     void disable_validation();

     /// Transcodes a XMLCh to string
     /**
        @param to_transcode String to be transcoded
        @return Transcoded string
      */
     static string str_transcode(const char * to_transcode);

     static string get_xmlns(xml::node * pnode);

   protected:
     /// Do the actual parsing of the XML document
     /**
        @param xml_payload XML to be parsed
        @return Pointer to the root of the document tree
      */
     xml::node *parse(const char *xml_payload);

     /// Fills a Postal Info struct
     /**
        @param n Pointer to a node of the document tree
        @param postal_info Pointer to a postal info struct
     */
     void fill_postal_info(xml::node *n, PostalInfo *postal_info);
  
     /// Fills a DSInfo object
     /**
        @param n reference to a node of the document tree
        @param ds_info reference to a DSInfo object
     */
     void fill_ds_info(xml::node *n, DSInfo *ds_info);
  
     /// Fills a KeyData object
     /**
        @param n reference to a node of the document tree
        @param keyData reference to a KeyData object
     */
     void fill_key_data(xml::node *n, KeyData *keyData);
  
     /// Load IP Range object
     /**
        @param n Pointer to a node of the document tree
     */
     IpRange fill_ipRange(xml::node *n);

     /// Load reverse DNS object
     /**
        @param n Pointer to a node of the document tree
     */
     ReverseDns fill_reverseDns(xml::node *n);

     /// Load IP Range object for Organization
     /**
        @param n Pointer to a node of the document tree
     */
     IpRange fill_brorg_ipRange(xml::node *n);

     /// Fills a map of children names with associated content text
     /**
        @param n   Pointer to a node of the document tree
        @return    map of children names with associated content text
      */
     //string_to_string_map get_children_simple(xml::node *n);

     /// Fills a map of attributes and associated values
     /**
        @param n   Pointer to a node of the document tree
        @return    map of attributes and associated values
     */
     //string_to_string_map get_attributes(xml::node *n);

     /// Object for parsing XML documents
     xml::document _parser;

     /// DOM error handler
     DomErrorHandler _error_handler;
   };

} // namespace libepp
