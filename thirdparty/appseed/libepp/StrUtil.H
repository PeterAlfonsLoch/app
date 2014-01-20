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
/* $Id: StrUtil.H 1033 2009-09-28 18:59:07Z fneves $ */
/** @file StrUtil.H
 *  @brief String Manipulation Utilities
 */

#pragma once

namespace libepp
{

   /// StrUtil Class: String Manipulation Utilities
   class StrUtil :
      virtual public ::radix::object
   {
   public:


      StrUtil(::ca::application * papp);
      virtual ~StrUtil();

     /// Used for parsing XML Templates 
     /**
        @param text      XML template to be parsed
        @param to_parse  Mapping tags into values
        @param tag_begin Symbol for begin tag
        @param tag_end   Symbol for end tag
        @return          Parsed string
     */
     string parse(const char *text,
		         string_to_string_map &to_parse,
		         string tag_begin, string tag_end);

     /// Used for substitution of pat for drp within buffer
     /**
        @param buffer Text to be scanned   
        @param pat    Pattern to be substituted
        @param drp    Substitute for the pattern indicated by pat
        @return       Number of matches       
     */
     // similar to string::replace
     //int gsub(string &buffer, const char *pat, const char *drp);

     /// Convert number to string where the format string looks like printf format.
     /** 
         @param format the format string in the printf format
         @param number the number to be converted
         @return the string containing the number
     */
     template<class kind>
     inline string to_string(const char* format, const kind &number)
     {
        string str;
        str.Format(format, number);
        return str;
     }

     /**
        Encodes an ISO-8859-1 string to UTF-8. ISO-8859-1 non-printable
        characters are substituted by spaces (ASCII 0x20).
        @param iso88591 ISO-8859-1 string to be encoded to UTF-8
        @param utf8 UTF-8 encodeded string
        @return number of characters substituted by spaces
      */
     int iso88591_to_utf8(const char *iso88591, string &utf8);

     /**
        Decodes a UTF-8 string to ISO-8859-1. ISO-8859-1 non-printable
        characters and not ISO-8859-1 characters are substituted by
        spaces (ASCII 0x20).
        @param utf8 UTF-8 encoded string to be decoded
        @param iso88591 decoded ISO-8859-1 string
        @return number of characters substituted by spaces
      */
     int utf8_to_iso88591(const char *utf8, string &iso88591);

     /// XML Beautifier
     /**
        @param input_txt The text to be formatted (in UTF-8)
        @return The indented XML document 
      */
     string xml_beautifier(const char *input_txt);

     /// Escape &'><" characters 
     /**
        @param input_txt The text that will possibly have some characters
        escaped
        @return strings with &'><" characters escaped
      */
     string esc_xml_markup(const char *input_txt);
   };

} // namespace libepp
