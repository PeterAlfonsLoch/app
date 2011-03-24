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
/* $Id: SheppGlobal.H 1082 2010-08-12 15:10:41Z eduardo $ */
/** @file SheppGlobal.H
*  @brief shepp compiler definitions and global variables
*/
#pragma once

#define SHEPP_VERSION  "1.10"
#define DEFAULT_PORT   700
#define CLIENT_PEM     SSLCERTDIR "/client.pem"
#define ROOT_PEM       SSLCERTDIR "/root.pem"

// Limits readline input size if LIMITED_READLINE is defined
#define MAX_TERM_DEV_LINE_SIZE 4096

// Maximmum get_length a single input unit can have. This value is used by
// SheppStrUtil.H only to allocate a temporary buffer.
#define MAX_WORD_LENGTH        2048


namespace libepp
{
   
   namespace shell
   {


      collection::list<command> _commands;

      /// Global connection setup variables
      string _server     = "localhost";
      int    _port       = DEFAULT_PORT;
      string _user       = "test";
      string _passphrase = "client passphrase";
      string _client_pem = CLIENT_PEM;
      string _root_pem   = ROOT_PEM;      
      bool   _connected  = false;

      string _login_pw     = "";
      string _login_new_pw = "";
      bool   _new_pw       = false;
      string _lang         = "";

      bool   _beauty     = true;
      bool   _debug      = false;
      bool   _autoresponse    = true;

      bool   _keepalive  = false;
      bool   _ka_running = false;
      bool   _cmd_running= false;
      static int _keepalive_timer = 180;

      bool   _peer_crt_check = true;

      string _xmlresponse = "";
      string _xmlcmd = "";

      string _serverSecDnsVersion = "0";

      /// Reference to session
      pointer_object < libepp::Session > _session;

      /// shepp build info
      void about()
      {
         printf("shepp version " SHEPP_VERSION ", an EPP client shell!\n");
         printf("Copyright 2006-2009 Registro.br <libepp@registro.br>\n");
         printf("shepp is distributed with libepp-nicbr: "
            "http://registro.br/epp/index-EN.html\n");

         stringa extensions;

         extensions.add("brorg");
         extensions.add("brdomain");
         extensions.add("ipnetwork");
         extensions.add("asn");

         printf("extensions: ");
         if(extensions.has_elements())
         {
            for(int i = 0; i < extensions.get_count(); i++) 
            {
               string & ext = extensions[i];
               printf("%s ", ext);
            }
            printf("\n");
         } 
         else 
         {
            printf("(none)\n");
         }
      }

   } // namespace shell

} // namespace libepp