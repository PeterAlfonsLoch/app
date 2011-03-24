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
/* $Id: SheppStrUtil.H 910 2007-03-19 21:29:33Z eduardo $ */
/** @file SheppStrUtil.H
*  @brief EPP command-line shell client string manipulation routines class
*/
#pragma once


namespace libepp
{

   namespace shell
   {
      /// Useful string manipulation routines used by shepp
      class StrUtil
      {
      public:
         /// Removes leading and ending white spaces from line (shepp)
         /**
         @param line   line to be trimmed
         @return trimmed line
         */
         /*static char *trim(char *line)
         {

            // remove leading white spaces by incrementing pointer to beginning
            // of line
            char *head;
            for (head = line; whitespace(*head); head++)
               ;

            // returns if head points to the end of line
            if (*head == '\0') {
               return head;
            }

            // remove ending white spaces
            char *tail;
            tail = head + strlen(head) - 1;
            while (tail > head && whitespace(*tail)) {
               tail--;
            }

            // ends the string at position where a white space was last seen
            *++tail = '\0';

            return head;
         }*/

         /// Given a line, split its words by white space into a string comparable_array (shepp)
         /**
         @param line   line to be parsed
         @param loop   boolean, default true, comparable_array to false to get only first word
         @return string comparable_array with all words found in line
         */
         static stringa parse_line(char *line)
         {
            gen::parse parse(line);

            stringa stra;
            while(true)
            {
               string strWord = parse.getword();
               stra.add(strWord);
            }

            return stra;
         }

         /**
         Splits input into first and second at first occurrence of splitter.
         If relaxed is true, it is acceptable for second to be is_empty().
         @param input     string to be divided
         @param first     left side goes here
         @param second    right side goes here
         @param splitter  division point
         @param relaxed   true means that second can be is_empty()
         */
         static int split(string input, string &first, string &second, string splitter, bool bSecondOptional = false)
         {
            int split_pos = input.find(splitter, 0);

            // first can never be is_empty()
            if (split_pos == 0)
            {
               return -1;
            }
            first = input.substr(0, split_pos);

            // second can be is_empty() if relaxed is true
            if (split_pos == -1 || split_pos == (int) (input.get_length() - 1)) 
            {
               if (bSecondOptional) 
               {
                  second = "";
               }
               else
               {
                     return -1;
               }
            }
            else 
            {
               second = input.substr(split_pos + 1);
            }

            return 0;  
         }

         /// Gathers command-line arguments bounded by quotes in a string
         /**
         @param words    reference to comparable_array with arguments
         @param gather   reference to return string
         @return 0 if OK, -1 if ERROR
         */
         static int quote_gathering(stringa &words, string &gather)
         {
            string tmp_str = gather.substr(0, 1);

            if (words.is_empty() && tmp_str == "\"")
            {
               return -1;
            }

            if (tmp_str == "\"") 
            {
               gather = gather.substr(1, gather.get_length() - 1);

               tmp_str = gather.substr(gather.get_length() - 1);
               while (tmp_str != "\"") 
               {
                  if (words.is_empty()) 
                  {
                     return -1;
                  }

                  gather += " " + words[0];

                  words.remove_at(0);
                  tmp_str = gather.substr(gather.get_length() - 1);
               }

               //remove starting and ending quotes
               gather = gather.substr(0, gather.get_length() - 1);
            }

            return 0;
         }

         /// Removes chars [./-] from document strings
         /**
         @param doc   a CPF or CNPJ document
         @return input doc with no [./-] characters
         */
         static string doc2id(const char *doc)
         {
            string numbers(doc);

            numbers.replace(".", "");
            numbers.replace("/", "");
            numbers.replace("-", "");

            return numbers;
         }
      };


   } // namespace shell

} // namespace libepp