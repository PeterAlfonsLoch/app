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
/* $Id: SheppCommandFunctions.H 1067 2010-07-08 19:13:45Z eduardo $ */
/** @file SheppCommandFunctions.H
*  @brief EPP command-line shell client command functions include file
*/
#pragma once


namespace libepp
{

   namespace shell
   {

      //#include <unistd.h>   //alarm

      //used by getpasswd
      //#include <termios.h>
      //#include <iostream>


      // Functions for eppsh commands
      int cmd_source(stringa &);
      int cmd_login(stringa &);
      int cmd_logout(stringa &);
      int cmd_hello(stringa &);
      int cmd_poll(stringa &);
      int cmd_domain(stringa &);
      int cmd_contact(stringa &);
      int cmd_brorg(stringa &);
      int cmd_asn(stringa &);
      int cmd_ipnetwork(stringa &);

      int cmd_xmlcmd(stringa &);
      int cmd_xmlresponse(stringa &);
      int cmd_runxml(stringa &);

      int cmd_server(stringa &);
      int cmd_port(stringa &);
      int cmd_client_pem(stringa &);
      int cmd_root_pem(stringa &);
      int cmd_pass(stringa &);
      int cmd_user(stringa &);
      int cmd_login_pw(stringa &);
      int cmd_login_new_pw(stringa &);
      int cmd_lang(stringa &);
      int cmd_connect(stringa &);
      int cmd_disconnect(stringa &);

      int cmd_help(stringa &);
      int cmd_about(stringa &);
      int cmd_quit(stringa &);

      int cmd_beauty(stringa &);
      int cmd_debug(stringa &);
      int cmd_autoresponse(stringa &);
      int cmd_keepalive(stringa &);
      int cmd_peer_crt_check(stringa &);

      string getpasswd(string prompt);

      /// Populates comparable_array of available commands
      void init_commands()
      {
         command cmd;

         //non-EPP commands
         cmd.reset("?", cmd_help, "This help screen");
         _commands.add_tail(cmd);
         cmd.reset("help", cmd_help, "This help screen");
         _commands.add_tail(cmd);
         cmd.reset("about", cmd_about, "shepp version information");
         _commands.add_tail(cmd);
         cmd.reset("exit", cmd_quit, "Exit shepp\n");
         _commands.add_tail(cmd);

         //runtime flags
         cmd.reset("beauty", cmd_beauty, "Turn XML beautifier on/off");
         _commands.add_tail(cmd);
         cmd.reset("debug", cmd_debug, "Turn debug messages on/off");
         _commands.add_tail(cmd);
         cmd.reset("autoresponse", cmd_autoresponse, "Turn auto-show response on/off");
         _commands.add_tail(cmd);
         cmd.reset("keepalive", cmd_keepalive, "Turn keep-alive on/off");
         _commands.add_tail(cmd);
         cmd.reset("peer-crt-check", cmd_peer_crt_check,
            "Turn peer's certificate check on/off\n");
         _commands.add_tail(cmd);

         //connection related commands
         cmd.reset("source", cmd_source, "Read and execute file with shepp commands");
         _commands.add_tail(cmd);
         cmd.reset("server", cmd_server, "Sets server address");
         _commands.add_tail(cmd);
         cmd.reset("port", cmd_port, "Sets server port");
         _commands.add_tail(cmd);
         cmd.reset("client-pem", cmd_client_pem,
            "Sets client.pem certificate file location");
         _commands.add_tail(cmd);
         cmd.reset("root-pem", cmd_root_pem,
            "Sets root.pem certificate file location");
         _commands.add_tail(cmd);
         cmd.reset("pass", cmd_pass, "Sets SSL certificate passphrase");
         _commands.add_tail(cmd);  
         cmd.reset("user", cmd_user, "Sets EPP Login username");
         _commands.add_tail(cmd);
         cmd.reset("pw", cmd_login_pw, "Sets EPP Login password");
         _commands.add_tail(cmd);
         cmd.reset("newpw", cmd_login_new_pw, "Sets new EPP Login password");
         _commands.add_tail(cmd);
         cmd.reset("lang", cmd_lang, "Sets text language");
         _commands.add_tail(cmd);
         cmd.reset("connect", cmd_connect, "Establishes connection");
         _commands.add_tail(cmd);
         cmd.reset("disconnect", cmd_disconnect, "Closes connection\n");
         _commands.add_tail(cmd);

         //EPP commands
         cmd.reset("login", cmd_login, "EPP Login");
         _commands.add_tail(cmd);
         cmd.reset("logout", cmd_logout, "EPP Logout");
         _commands.add_tail(cmd);
         cmd.reset("hello", cmd_hello, "EPP Hello");
         _commands.add_tail(cmd);
         cmd.reset("poll", cmd_poll, "EPP Poll related actions");
         _commands.add_tail(cmd);
         cmd.reset("domain", cmd_domain, "EPP Domain related actions");
         _commands.add_tail(cmd);
         cmd.reset("contact", cmd_contact, "EPP Contact related actions");
         _commands.add_tail(cmd);
         cmd.reset("asn", cmd_asn, "Autonomous System related actions");
         _commands.add_tail(cmd);
         cmd.reset("ipnetwork", cmd_ipnetwork, "IP network related actions");
         _commands.add_tail(cmd);
         cmd.reset("brorg", cmd_brorg, "EPP BrOrg related actions\n");
         _commands.add_tail(cmd);

         //XML related commands
         cmd.reset("xmlcmd", cmd_xmlcmd, "Show last command XML");
         _commands.add_tail(cmd);
         cmd.reset("xmlresponse", cmd_xmlresponse, "Show last response XML");
         _commands.add_tail(cmd);
         cmd.reset("runxml", cmd_runxml, "Run XML input (good for debugging)");
         _commands.add_tail(cmd);
      }

      /// Given a word check if it's a valid command
      /**
      @param   name of command check validity
      @return pointer to a command if found, NULL pointer if not found
      */
      const command* find_command(string name)
      {
         
         for(POSITION pos = _commands.get_head_position(); pos != NULL; ) 
         {
            command * pcommand = &_commands.get_next(pos);
            if(pcommand->name == name)
            {
               return pcommand;
            }
         }

         return ((const command *) NULL);
      }

      /// Given a input file, read and execute all shepp commands in this
      /// file
      /**
      @param inputFile   input file with shepp commands
      @return 0 if ok, -1 otherwise
      */
      int executeInputFile(const char *file)
      {
         ex1::text_file_sp inputFile(get_app());
         if(!inputFile->open(file, ex1::file::type_text | ex1::file::mode_read))
         {
               printf("error reading input file.\n");
               return -1;
         }

         init_commands();

         string cmdLine;
         while(inputFile->read_string(cmdLine))
         {
            cmdLine.trim();
            if(cmdLine.is_empty())
            {
               continue;
            }

            // Comments symbols
            if(cmdLine[0] == '#' || cmdLine[0] == ';')
            {
               continue;
            }

            // get the first word (command name)
            stringa command_args = shell::StrUtil::parse_line((char *) (const char *) cmdLine);

            // args will be is_empty() if any word exceed MAX_WORD_LENGTH
            if(command_args.is_empty())
            {
               continue;
            }

            const command* cmd = find_command(command_args[0]);

            if (cmd == NULL) {
               fprintf(stderr, "Unknown command: %s\n", command_args[0]);
               continue;
            }

            // commands that require raw command-line input
            if (command_args[0] == "runxml") {
               string rawcmd(cmdLine);
               rawcmd = rawcmd.substr(command_args[0].get_length());
               while (whitespace(rawcmd[0])) {
                  rawcmd = rawcmd.substr(1);
               }

               if (rawcmd == "") {
                  // read input
                  printf("Enter XML code. Escape character is '^]'.\n");

                  string unit;
                  getline(cin, unit, (char)29);
                  rawcmd += unit;
               }

               command_args.clear();
               command_args.add(rawcmd);
            } else {
               command_args.remove_at(command_args.begin());
            }

            (*(cmd->function))(command_args);
         }

         inputFile.close();

         return 0;
      }

      /// Given a input file, read and execute all shepp commands in this
      /// file
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_source(stringa &args)
      {
         if (args.size() != 0) {
            return executeInputFile(args[0]);
         }

         return 0;
      }

      /// Sets server address [and port] based on input command-line
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_server(stringa &args)
      {
         if (args.size() != 0) {
            string new_port;
            string new_server;
            SheppStrUtil::split(args[0], new_server, new_port, ":", true);
            if (new_server != _server) {
               _server = new_server;
            }
            if (new_port != "" && _port != atoi(new_port)) {
               _port = atoi(new_port);
            }
         }

         if (_server != "") {
            printf("server %s:%d\n", _server, _port);
         } else {
            printf("no server address given.\n");
         }

         return 0;
      }

      /// Sets server port based on input command-line
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_port(stringa &args)
      {
         if (args.size() == 1) {
            if (_port != atoi(args[0])) {
               _port = atoi(args[0]);
            }
         }

         printf("port %d\n", _port);

         return 0;
      }

      /// Sets client.pem certificate file location
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_client_pem(stringa &args)
      {
         if (args.size() == 1) {
            if (_client_pem != args[0]) {
               _client_pem = args[0];
               printf("Warning: changing cetificates requires you to reconnect.\n");
            }
         } else if (args.size() > 1) {
            printf("usage: client-pem <file>\n");
            return -1;
         }

         printf("Current client.pem is %s\n", _client_pem);
         return 0;
      }

      /// Sets root.pem certificate file location
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_root_pem(stringa &args)
      {
         if (args.size() == 1) {
            if (_root_pem != args[0]) {
               _root_pem = args[0];
               printf("Warning: changing cetificates requires you to reconnect.\n");
            }
         } else if (args.size() > 1) {
            printf("usage: root-pem <file>\n");
            return -1;
         }

         printf("Current root.pem is %s\n", _root_pem);
         return 0;
      }

      /// Sets SSL certificate passphrase based on input command-line
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_pass(stringa &args)
      {
         if (!args.is_empty()) {
            _passphrase = args[0];
         } else {
            _passphrase = getpasswd("Passphrase");
         }

         return 0;
      }

      /// Sets login user based on input command-line
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_user(stringa &args)
      {
         if (args.size() == 0) {
            if (_user != "") {
               printf("username: %s\n", _user);
               return 0;
            } else {
               printf("no username given.\n");
               return -1;
            }
         }

         _user = args[0];

         return 0;
      }

      /// Sets EPP login password based on input command-line
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_login_pw(stringa &args)
      {
         if (!args.is_empty()) {
            _login_pw = args[0];
         } else {
            _login_pw = getpasswd("Password");
         }

         return 0;
      }

      /// Sets new EPP login password based on input command-line
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_login_new_pw(stringa &args)
      {
         if (!args.is_empty()) {
            _login_new_pw = args[0];
         } else {
            _login_new_pw = getpasswd("New Password");
         }

         _new_pw = true;
         return 0;
      }

      /// Sets text language based on input command-line
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_lang(stringa &args)
      {
         if (args.is_empty()) {
            printf("usage: lang [en|pt]\n");
            return -1;
         } else {
            _lang = args[0];
         }

         return 0;
      }

      /// Connects to previously specified server and port
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_connect(stringa &args)
      {
         if (cmd_server(args) != 0) {
            return -1;
         }

         bool exception = false;

         // Session code goes here
         try {
            _session = pointer_object<Session>(new Session(_server, _port));
            if (_peer_crt_check) {
               _session->enable_cert_common_name_check();
            } else {
               _session->disable_cert_common_name_check();
            }
            _session->connect(_client_pem, _root_pem, _passphrase);
            printf("Connected to %s\n", _server);

            Greeting *greeting = _session->get_greeting();

            // attempt to verify secDNS extension version supported by server
            stringa extensions = greeting->get_extURI();
            stringa::iterator it;
            for (it = extensions.begin(); it != extensions.end(); it++) {
               if (*it == "urn:ietf:params:xml:ns:secDNS-1.0") {
                  _serverSecDnsVersion = "1.0";
               } else if (*it == "urn:ietf:params:xml:ns:secDNS-1.1") {
                  _serverSecDnsVersion = "1.1";
               }
            }

            if (_debug) {
               if (greeting) {
                  printf("Greeting received\n");
               }
            } //_debug

            _xmlresponse = _session->get_last_response();
            _xmlcmd = _session->get_last_command();

            _connected = true;

         } catch (const IoException &e) {
            printf("ERROR! IO Exception [%d]:\n[%s]\n", 
               e.get_code(), e.get_msg());
            exception = true;
         } catch (const TransportException &e) {
            printf("ERROR! Transport Exception [%d]:\n[%s]\n[%s]\n",
               e.get_code(), e.get_msg(), e.get_low_level_msg());
            exception = true;
         } catch (const GeneralException &e) {
            printf("ERROR! General Exception [%d]:\n[%s]\n", 
               e.get_code(), e.get_msg());
            exception = true;
         }

         if (exception) {
            return -1;
         }

         // print greeting
         stringa dummy;
         cmd_xmlresponse(dummy);

         return 0;
      }

      /// Closes connection
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_disconnect(stringa &args)
      {
         if (_connected) {
            bool exception = false;

            // Session code goes here
            try {
               _session->disconnect();
               printf("disconnected from %s\n", _server);
               _connected = false;
            } catch (const TransportException &e) {
               printf("ERROR! Transport Exception [%d]:\n[%s]\n[%s]\n",
                  e.get_code(), e.get_msg(), e.get_low_level_msg());
               exception = true;
            } catch (const GeneralException &e) {
               printf("ERROR! General Exception [%d]:\n[%s]\n", 
                  e.get_code(), e.get_msg());
               exception = true;
            }

            if (exception) {
               return -1;
            }
         } else {
            printf("not connected\n");
         }

         return 0;
      }

      /// Turns XML beautifier ON and OFF
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_beauty(stringa &args)
      {
         if (args.is_empty()) {
            if (_beauty) {
               printf("XML beautifier is ON\n");
            } else {
               printf("XML beautifier is OFF\n");
            }
            return 0;
         } else if (args.size() > 1) {
            printf("usage: beauty [on|off]\n");
            return -1;
         }

         if (args[0] == "on") {
            _beauty = true;
            printf("XML beautifier now ON\n");
         } else if (args[0] == "off") {
            _beauty = false;
            printf("XML beautifier now OFF\n");
         } else {
            printf("usage: beauty [on|off]\n");
            return -1;
         }

         return 0;
      }

      /// Turns debug messages ON and OFF
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_debug(stringa &args)
      {
         if (args.is_empty()) {
            if (_debug) {
               printf("Debug is ON\n");
            } else {
               printf("Debug is OFF\n");
            }
            return 0;
         } else if (args.size() > 1) {
            printf("usage: debug [on|off]\n");
            return -1;
         }

         if (args[0] == "on") {
            _debug = true;
            printf("Debug now ON\n");
         } else if (args[0] == "off") {
            _debug = false;
            printf("Debug now OFF\n");
         } else {
            printf("usage: beauty [on|off]\n");
            return -1;
         }

         return 0;
      }

      /// Turns auto-show response ON and OFF
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_autoresponse(stringa &args)
      {
         if (args.is_empty()) {
            if (_autoresponse) {
               printf("autoresponse is ON\n");
            } else {
               printf("autoresponse is OFF\n");
            }
            return 0;
         } else if (args.size() > 1) {
            printf("usage: autoresponse [on|off]\n");
            return -1;
         }

         if (args[0] == "on") {
            _autoresponse = true;
            printf("autoresponse now ON\n");
         } else if (args[0] == "off") {
            _autoresponse = false;
            printf("autoresponse now OFF\n");
         } else {
            printf("usage: autoresponse [on|off]\n");
            return -1;
         }

         return 0;
      }

      /// Turns keep-alive ON and OFF
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_keepalive(stringa &args)
      {
         if (args.is_empty()) {
            if (_keepalive) {
               printf("Keep-alive is ON\n");
            } else {
               printf("Keep-alive is OFF\n");
            }
            return 0;
         } else if (args.size() > 1) {
            printf("usage: keepalive [on|off]\n");
            return -1;
         }

         if (args[0] == "on") {
            _keepalive = true;
            printf("Keep-alive now ON\n");
         } else if (args[0] == "off") {
            _keepalive = false;
            printf("Keep-alive now OFF\n");
         } else {
            printf("usage: keepalive [on|off]\n");
            return -1;
         }

         if (_keepalive) {
            alarm(_keepalive_timer);
         } else {
            alarm(0);
         }

         return 0;
      }

      /// Turn peer's certificate check ON and OFF
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_peer_crt_check(stringa &args)
      {
         if (args.is_empty()) {
            if (_peer_crt_check) {
               printf("Peer's certificate check is ON\n");
            } else {
               printf("Peer's certificate check is OFF\n");
            }
            return 0;
         } else if (args.size() > 1) {
            printf("usage: peer-crt-check [on|off]\n");
            return -1;
         }

         if (args[0] == "on") {
            _peer_crt_check = true;
            printf("Peer's certificate check now ON\n");
         } else if (args[0] == "off") {
            _peer_crt_check = false;
            printf("Peer's certificate check now OFF\n");
         } else {
            printf("usage: peer-crt-check [on|off]\n");
            return -1;
         }

         return 0;
      }

      /// SIGALRM signal handler for keepalive command
      static void sig_alrm(int signo)
      {
         if (_connected && !_cmd_running) {
            _ka_running = true;
            stringa args;
            args.add((string) "keepalive");
            cmd_hello(args);
            _ka_running = false;
         }
         alarm(_keepalive_timer);
      }

      /// Shows last XML command
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_xmlcmd(stringa &args)
      {
         if (!_connected) {
            printf("not connected\n");
            return -1;
         }

         if (_beauty) {
            // Convert to UTF8
            string last_command("");
            StrUtil::iso88591_to_utf8(_xmlcmd, last_command);

            if (_session->get_last_command() == "") {
               printf("\n");
               return 0;
            }
            try {
               StrUtil str_util;
               printf("%s\n", str_util.xml_beautifier(last_command));
            } catch (const XmlException &e) {
               printf("ERROR! XML Exception [%d]:\n[%s]\n", e.get_code(),
                  e.get_msg());
            }
         } else {
            printf("%s\n", _session->get_last_command());
         }
         return 0;
      }

      /// Shows last XML response
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_xmlresponse(stringa &args)
      {
         if (!_connected) {
            printf("not connected\n");
            return -1;
         }

         if (_beauty) {
            // No need to convert to UTF8
            if (_xmlresponse == "") {
               printf("\n");
               return 0;
            }
            try {
               StrUtil str_util;
               printf("%s\n", str_util.xml_beautifier(_xmlresponse));
            } catch (const XmlException &e) {
               printf("ERROR! XML Exception [%d]:\n[%s]\n", e.get_code(),
                  e.get_msg());
            }
         } else {
            printf("%s\n", _xmlresponse);
         }
         return 0;
      }

      // EPP action processing functions

      /// Prints "command sent ok" message
      void print_cmd_sent_ok()
      {
         if (!_autoresponse) {
            printf("Ok! Use 'xmlcmd' and 'xmlresponse' to view command/response "
               "XML code.\n");
         } else {
            stringa dummy;
            cmd_xmlresponse(dummy);
         }
      }

      /// Send and EPP Action
      /**
      @return 0 if ok, -1 otherwise
      */
      int process_action(Action &act)
      {
         if (!_connected) {
            printf("not connected\n");
            return -1;
         }

         bool exception = false;

         // prevents concurrency with keep-alive
         if (!_ka_running) {
            _cmd_running = true;
         } else {
            printf("ERROR! Keep-alive is running. Please try again.\n");
            return -1;
         }

         try {
            _session->process_action(&act);
            _xmlresponse = _session->get_last_response();
            _xmlcmd = _session->get_last_command();
         } catch (const EppException &e) {
            printf("ERROR! EPP Exception [%d]:\n[%s]\n", e.get_code(),
               e.get_msg());  
            exception = true;
         } catch (const IoException &e) {
            printf("ERROR! IO Exception [%d]:\n[%s]\n", 
               e.get_code(), e.get_msg());
            exception = true;
            _connected = false;
         } catch (const TransportException &e) {
            printf("ERROR! Transport Exception [%d]:\n[%s]\n[%s]\n",
               e.get_code(), e.get_msg(), e.get_low_level_msg());
            exception = true;
            _connected = false;
         } catch (const GeneralException &e) {
            printf("ERROR! General Exception [%d]:\n[%s]\n", 
               e.get_code(), e.get_msg());
            exception = true;
         }

         if (exception) {
            _cmd_running = false;
            return -1;
         }

         print_cmd_sent_ok();

         // a command was just run; postpone keepalive alarm
         if (_keepalive) {
            alarm(_keepalive_timer);
         }

         _cmd_running = false;
         return 0;
      }

      /// Run XML input command
      /**
      @return 0 if ok, -1 otherwise
      */
      int cmd_runxml(stringa &args)
      {
         if (!_connected) {
            printf("not connected\n");
            return -1;
         }

         bool exception = false;

         // prevents concurrency with keep-alive
         if (!_ka_running) {
            _cmd_running = true;
         } else {
            printf("ERROR! Keep-alive is running. Please try again.\n");
            return -1;
         }

         try {
            _session->runXML(args[0]);
            _xmlresponse = _session->get_last_response();
            _xmlcmd = _session->get_last_command();
         } catch (const EppException &e) {
            printf("ERROR! EPP Exception [%d]:\n[%s]\n", e.get_code(),
               e.get_msg());  
            exception = true;
         } catch (const IoException &e) {
            printf("ERROR! IO Exception [%d]:\n[%s]\n", 
               e.get_code(), e.get_msg());
            exception = true;
            _connected = false;
         } catch (const TransportException &e) {
            printf("ERROR! Transport Exception [%d]:\n[%s]\n[%s]\n",
               e.get_code(), e.get_msg(), e.get_low_level_msg());
            exception = true;
            _connected = false;
         } catch (const GeneralException &e) {
            printf("ERROR! General Exception [%d]:\n[%s]\n", 
               e.get_code(), e.get_msg());
            exception = true;
         }

         if (exception) {
            _cmd_running = false;
            return -1;
         }

         print_cmd_sent_ok();

         // a command was just run; postpone keepalive alarm
         if (_keepalive) {
            alarm(_keepalive_timer);
         }

         _cmd_running = false;
         return 0;
      }

      /// Send an EPP Login
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_login(stringa &args)
      {
         if (!_connected) {
            printf("not connected\n");
            return -1;
         }

         if (_user == "") {
            printf("no username given.\n");
            return -1;
         }

         Login act;
         LoginCommand *cmd = act.get_command();

         // add extensions supported by client
         cmd->add_extURI("urn:ietf:params:xml:ns:brorg-1.0");
         cmd->add_extURI("urn:ietf:params:xml:ns:brdomain-1.0");
         cmd->add_extURI("urn:ietf:params:xml:ns:ipnetwork-1.0");
         cmd->add_extURI("urn:ietf:params:xml:ns:asn-1.0");
         cmd->add_extURI("urn:ietf:params:xml:ns:secDNS-1.0");
         cmd->add_extURI("urn:ietf:params:xml:ns:secDNS-1.1");

         cmd->set_clID(_user);
         cmd->set_pw(_login_pw);

         if (_new_pw) {
            _new_pw = false;
            cmd->set_new_pw(_login_new_pw);
         }

         if (_lang != "" && _lang != "en") {
            cmd->set_lang(_lang);
         }

         if (process_action(act) != 0) {
            return -1;
         }

         return 0;
      }

      /// Send an EPP Logout
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_logout(stringa &args)
      {
         if (!_connected) {
            printf("not connected\n");
            return -1;
         }

         Logout act;

         if (process_action(act) != 0) {
            return -1;
         }  

         return 0;
      }

      /// Send an EPP HELLO
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_hello(stringa &args)
      {
         if (!_connected) {
            printf("not connected\n");
            return -1;
         }

         if (_ka_running &&
            !(args.size() == 1 && args[0] == "keepalive")) {
               printf("ERROR! Keep-alive is running. Please try again.\n");
               return -1;
         }

         bool exception = false;

         // prevents concurrency with keep-alive
         if (!_ka_running) {
            _cmd_running = true;
         }

         try {
            if (_debug) {
               printf("Sending EPP Hello\n");
            }
            _session->send_hello();
            // updates _xmlcmd and _xmlresponse only if it's not a keep-alive run
            if (!_ka_running) {
               _xmlresponse = _session->get_last_response();
               _xmlcmd = _session->get_last_command();
            }
         } catch (const EppException &e) {
            printf("ERROR! EPP Exception [%d]:\n[%s]\n", e.get_code(),
               e.get_msg());  
            exception = true;
         } catch (const IoException &e) {
            printf("ERROR! IO Exception [%d]:\n[%s]\n", 
               e.get_code(), e.get_msg());
            exception = true;
            _connected = false;
         } catch (const TransportException &e) {
            printf("ERROR! Transport Exception [%d]:\n[%s]\n[%s]\n",
               e.get_code(), e.get_msg(), e.get_low_level_msg());
            exception = true;
            _connected = false;
         } catch (const GeneralException &e) {
            printf("ERROR! General Exception [%d]:\n[%s]\n", 
               e.get_code(), e.get_msg());
            exception = true;
         }

         if (exception) {
            if (_cmd_running) {
               _cmd_running = false;
            }
            return -1;
         }

         if (!_ka_running) {
            print_cmd_sent_ok();
         }

         if (_cmd_running) {
            // a command was just run; postpone keepalive alarm
            if (_keepalive) {
               alarm(_keepalive_timer);
            }
            _cmd_running = false;
         }
         return 0;
      }

      // non-EPP commands

      /// Leaves shepp
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_quit(stringa &args)
      {
         if (_connected) {
            _session->disconnect();
         }
         printf("Bye\n");
         exit(0);
      }

      /// Prints help
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_help(stringa &args)
      {
         list<command>::const_iterator it;
         for (it = _commands.begin(); it != _commands.end(); it++) {
            printf("%-16s %s\n", (*it).name, (*it).brief);
         }

         return 0;
      }

      /// Prints version information
      /**
      @param args   input command-line
      @return 0 if ok, -1 otherwise
      */
      int cmd_about(stringa &args)
      {
         about();
         return 0;
      }

      /// Function to read from stdin without echoing
      /**
      @param prompt   prompt to be echoed
      @return content read from stdin
      */
      string getpasswd(string prompt) {
         printf("%s:", prompt);

         string passwd("");
         struct termios old_opts;
         struct termios new_opts;

         int res = 0;

         // store old settings
         res = tcgetattr(STDIN_FILENO, &old_opts);
         assert(res == 0);

         // comparable_array new terminal parms
         memcpy(&new_opts, &old_opts, sizeof(new_opts));
         new_opts.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
         new_opts.c_lflag |= ICANON;
         tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);

         // read password
         getline(cin, passwd);
         cout << endl;

         // restore old settings
         res = tcsetattr(STDIN_FILENO, TCSANOW, &old_opts);
         assert(res == 0);

         return passwd;
      }

   } // namespace shell

} // namespace libepp
