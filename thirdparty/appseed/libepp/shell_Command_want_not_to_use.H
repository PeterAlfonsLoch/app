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
/* $Id: command.H 804 2006-08-03 12:56:01Z eduardo $ */
/** @file command.H
*  @brief EPP command-line shell client Command class
*/
#pragma once


namespace libepp
{

   namespace shell
   {

      typedef int isfunc_t (stringa &);

      /// command class: command name, function and a brief description
      class command 
      {
      public:
         /// Operator necessary to create a comparable_array of SheppCommands
         bool operator<(const command &cmd) const {
            return name < cmd.name;
         }

         /// Constructor that initializes all object attributes to is_empty()
         command()
         {
            init();
         }

         /// Constructor that sets all object attributes
         command(string name, isfunc_t *function, string brief)
         {
            this->name = name;
            this->function = function;
            this->brief = brief;
         }

         /// Reinitializes all object attributes
         void reset(string name, isfunc_t *function, string brief)
         {
            this->name = name;
            this->function = function;
            this->brief = brief;
         }

         /// command name
         string name;

         /// Function to be called
         isfunc_t *function;

         /// command brief description
         string brief;
      protected:
         /// Initializes all object attributes to is_empty()
         void init()
         {
            name = "";
            function = NULL;
            brief = "";
         }   
      };

   } // namespace shell

} // namespace libepp