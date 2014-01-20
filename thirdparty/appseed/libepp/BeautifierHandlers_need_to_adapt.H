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
/* $Id: BeautifierHandlers.H 1041 2009-10-16 19:05:48Z koji $ */
/** @file BeautifierHandlers.H
 *  @brief Beautifier Handlers Class
 */
#pragma once

#include "libepp.H"

#define HandlerBase ::radix::object
#define HandlerBase ::radix::object
#define SAXParseException simple_exception

namespace libepp {

/// User Data
struct UserData {
  string input_txt;
  string output_txt;
};

/// Beautifier Handlers Class
class BeautifierHandlers : public HandlerBase
{
public:  
  /// Constructor
  /**
     @param pretty_data The User Data Structure(input and output text) 
  */
  BeautifierHandlers(UserData *pretty_data);

  /// Destructor 
  ~BeautifierHandlers();

  /// Start Element Handler
  /**
     @param name The name of the starting element 
     @param attributes The list of attributes of the element
  */
  void startElement(const char * name, xml::attr::base_array& attributes);

  /// Characters Handler
  /**
     @param chars The text of some element 
     @param get_length The get_length of the text
  */
  void characters(const char * chars,
#if XERCES_VERSION_MAJOR == 2
		  const unsigned int get_length
#else
		  const size_t get_length
#endif
		  );

  /// End Element Handler
  /**
     @param chars The name of the ending element 
  */
  void endElement(const char * chars);

  /// Handle SAXParseException in case of warning
  /**
     @param SAXParseException The exception caught
   */
  void warning(const SAXParseException& exc);

  /// Handle SAXParseException in case of error
  /**
     @param SAXParseException The exception caught
   */
  void error(const SAXParseException& exc);

  /// Handle SAXParseException in case of fatal error
  /**
     @param SAXParseException The exception caught
   */
  void fatalError(const SAXParseException& exc);

private:
  /// Effective characters handling 
  /// The method is necessary because escaped characters generates 
  //  another character event so it is necessary to buffer the characters 
  //  until the end
  void chars_handler();

  /// Transcode XMLCh to string
  /**
     @param to_transcode XMLCh to be transcoded in string
     @return The transcoded string
   */
  string str_transcode(const char * to_transcode);

  /// Truncate the text based on the maximum line get_length
  /**
     @param line The text to be checked and formatted (if necessary)
     @return The formatted text
  */
  string truncate(const char *line);

  /// Remove leading, trailing and nested zeros
  /**
     @param buffer The text to be trimmed
  */  
  string alltrim(const string& buffer);

  /// Split one string into several strings separated by a given pattern
  /**
     @param buffer The original string
     @param words  The reference to the comparable_array to be fiiled
     @return The number of words found
  */
  int split(const string& buffer, stringa& words);

  /// Event Type
  enum eventType {
    NONE = 0,
    START = 1,
    CHARACTERS = 2,
    END = 3
  };

  /// The current depth in the XML Tree
  int _depth;

  /// The pointer to the user data(reference to the input and output)
  UserData *_user_data;

  /// Last event 
  eventType _last_event;

  /// Last non-characters event 
  eventType _last_non_chars_event;

  /// String to be printed
  string _to_be_printed;

  /// Number of whitespaces in the Left margin
  int _left_margin;

  /// Current Element Name
  string _element_name;

  /// Truncated text
  bool _truncated_txt;

  /// Tag Margin
  string _tag_margin;

  /// Buffered characters
  string _buffered_chars;
};

}
