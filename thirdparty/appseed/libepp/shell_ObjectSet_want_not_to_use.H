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
/* $Id: ObjectSet.H 1064 2010-07-07 22:32:51Z eduardo $ */
/** @file ObjectSet.H
*  @brief shepp specific objects information setting class
*/
#pragma once


namespace libepp
{

   namespace shell
   {

      /// shepp specific objects information setting class
      class ObjectSet
      {
      public:

         //used by both contact and domain

         /// fills an AuthInfo based on input command line
         /**
         @param auth    reference to an AuthInfo object to be comparable_array
         @param words   comparable_array with command-line arguments
         @return 0 if ok, -1 otherwise
         */
         static int authInfo(libepp::AuthInfo &auth, stringa &words)
         {
            words.remove_at(0);

            if(words.is_empty())
            {
               return -1;
            }

            string pw;
            string roid;
            if(StrUtil::split(words[0], pw, roid, ":", true) != 0)
            {
               return -1;
            }

            auth.set_pw(pw);
            auth.set_roid(roid);

            words.remove_at(0); 

            return 0;
         }

         //domain specific

         /// fills a NameServer based on input command line
         /**
         @param ns      reference to a NameServer object to be comparable_array
         @param words   comparable_array with command-line arguments
         @return 0 if ok, -1 otherwise
         */
         static int nameServer(libepp::NameServer &ns, stringa &words)
         {
            words.remove_at(0);
            if(words.is_empty())
            {
               return -1;
            }

            string ips;
            StrUtil::split(words[0], ns.name, ips, ",", true);

            if (ips != "") 
            {
               string this_ip;
               do
               {
                  if(StrUtil::split(ips, this_ip, ips, ",", true) != 0)
                  {
                     return -1;
                  }

                  NSIPAddr ip;
                  if(StrUtil::split(this_ip, ip.version, ip.addr, ":", false) != 0) 
                  {
                     return -1;
                  }

                  ns.ips.add(ip);
               } while (ips != "");
            }

            words.remove_at(0);

            return 0;
         }

         /// fills a Status based on input command line
         /**
         @param status      reference to a Status object to be comparable_array
         @param words       comparable_array with command-line arguments
         @return 0 if ok, -1 otherwise
         */
         static int status(libepp::DomainUpdateCommand::Status &st, stringa &words)
         {
            string status;
            string lang;
            string description;

            if(StrUtil::split(words[0], status, lang, ":", false) != 0) 
            {
               return -1;
            }
            words.remove_at(0);

            if(StrUtil::split(lang, lang, description, ":", false) != 0) 
            {
               return -1;
            }

            StrUtil::quote_gathering(words, description);

            st.s = status;
            st.lang = lang;
            st.msg = description;

            return 0;
         }

         /// fills a DSInfo based on input command line
         /**
         @param ds      reference to a DSInfo object to be comparable_array
         @param words   comparable_array with command-line arguments
         @return 0 if ok, -1 otherwise
         */
         static int dsInfo(libepp::DSInfo &ds, stringa &words, string &error_msg)
         {
            words.remove_at(0); // -ds

            // must have at least 4 elements: keytag, algorithm, digtype and digest
            if(words.is_empty(4))
            {
               error_msg = "not enough arguments for DS";
               return -1;
            }

            // parse the key tag: check if it has only numbers
            if(!gen::str::is_simple_natural(words[0]))
            {
               error_msg = "keyTag must be a non-negative number";
               return -1;
            }

            int key_tag = atoi(words[0]);
            ds.set_key_tag(key_tag);

            int alg = atoi(words[1]);
            if (alg < 0)
            {
               error_msg = "alg cannot be a negative number";
               return -1;
            }
            ds.set_algo(alg);

            int dig_type = atoi(words[2]);
            if (dig_type < 0)
            {
               error_msg = "digestType cannot be a negative number";
               return -1;
            }
            ds.set_digest_type(dig_type);
            ds.set_digest(words[3]);

            words.remove_at(0, 4);

            //optional parameters
            while(words.has_elements())
            {
               if(words[0] == "-maxlife")
               {
                  if(words.is_empty(2))
                  {
                     error_msg = "maxSigLife value missing";
                     return -1;
                  }
                  words.remove_at(0); // -maxlife
                  int maxlife = atoi(words[0]);
                  if(maxlife < 0)
                  {
                     error_msg = "maxSigLife cannot be a negative number";
                     return -1;
                  }
                  ds.set_max_sig_life(maxlife);
                  words.remove_at(0); // maxlife value
               }
               else if (words[0] == "-keyData") 
               {
                  KeyData dnskey;
                  if (ObjectSet::keyData(dnskey, words, error_msg) != 0) 
                  {
                     return -1;
                  }
                  ds.set_key_data(dnskey);
               } 
               else 
               {
                  break;
               }
            }
            return 0;
         }

         /// fills a KeyData based on input command line
         /**
         @param dnskey  reference to a KeyData object to be comparable_array
         @param words   comparable_array with command-line arguments
         @return 0 if ok, -1 otherwise
         */
         static int keyData(libepp::KeyData &dnskey, stringa &words, string &error_msg)
         {
            if (words.is_empty(5))
            {
               error_msg = "not enough arguments for keyData";
               return -1;
            }

            dnskey.set_flags(atoi(words[1]));
            dnskey.set_protocol(atoi(words[2]));
            dnskey.set_algorithm(atoi(words[3]));
            dnskey.set_pub_key(words[4]);

            if (dnskey.get_flags() < 0 || dnskey.get_protocol() < 0 ||
               dnskey.get_algorithm() < 0) {
                  error_msg =
                     "keyData flags, protocol and alg cannot be negative numbers";
                  return -1;
            }
            words.remove_at(0, 5); 

            return 0;
         }

         //contact specific

         /// fills a PostalInfo based on input command line
         /**
         @param postal      reference to a PostalInfo object to be comparable_array
         @param words       comparable_array with command-line arguments
         @param error_msg   string to hold error msg on return -1
         @param relaxed     true for update, false for create
         @return 0 if ok, -1 otherwise
         */
         static int postalInfo(libepp::PostalInfo &postal, stringa &words, string &error_msg, bool relaxed)
         {
            //type
            string postal_type = words[0];
            words.remove_at(0);
            if(StrUtil::quote_gathering(words, postal_type) != 0) 
            {
               error_msg = "error setting postalInfo type";
               return -1;
            }
            postal.set_type(postal_type);

            while(words.has_elements())
            {
               if (words[0] == "-name")
               {
                  //name
                  words.remove_at(0);
                  if (words.is_empty()) 
                  {
                     error_msg = "unspecified contact name";
                     return -1;
                  }
                  string postal_name = words[0];
                  words.remove_at(0);
                  if(StrUtil::quote_gathering(words, postal_name) != 0) 
                  {
                     error_msg = "error setting contact name";
                     return -1;
                  }
                  postal.set_name(postal_name);
               }
               else if (words[0] == "-org") 
               {
                  //org
                  words.remove_at(0);
                  if (words.is_empty())
                  {
                     error_msg = "unspecified organization";
                     return -1;
                  }
                  string postal_org = words[0];
                  words.remove_at(0);
                  if(StrUtil::quote_gathering(words, postal_org) != 0) 
                  {
                     error_msg = "error setting organization";
                     return -1;
                  }
                  postal.set_org(postal_org);
               } 
               else if (words[0] == "-street1") 
               {
                  //street1
                  words.remove_at(0);
                  if (words.is_empty()) 
                  {
                     error_msg = "unspecified address street/line 1";
                     return -1;
                  }
                  string postal_str1 = words[0];
                  words.remove_at(0);
                  if(StrUtil::quote_gathering(words, postal_str1) != 0) 
                  {
                     error_msg = "error setting address street/line 1";
                     return -1;
                  }
                  postal.set_str1(postal_str1);
               }
               else if (words[0] == "-street2") 
               {
                  //street2
                  words.remove_at(0);
                  if (words.is_empty()) 
                  {
                     error_msg = "unspecified address number/line 2";
                     return -1;
                  }
                  string postal_str2 = words[0];
                  words.remove_at(0);
                  if(StrUtil::quote_gathering(words, postal_str2) != 0) {
                     error_msg = "error setting address number/line 2";
                     return -1;
                  }
                  postal.set_str2(postal_str2);
               }
               else if (words[0] == "-street3")
               {
                  //street3
                  words.remove_at(0);
                  if (words.is_empty())
                  {
                     error_msg = "unspecified street3";
                     return -1;
                  }
                  string postal_str3 = words[0];
                  words.remove_at(0);
                  if(StrUtil::quote_gathering(words, postal_str3) != 0) 
                  {
                     error_msg = "error setting address line 3";
                     return -1;
                  }
                  postal.set_str3(postal_str3);
               } 
               else if (words[0] == "-city") 
               {
                  //city
                  words.remove_at(0);
                  if (words.is_empty()) 
                  {
                     error_msg = "unspecified city";
                     return -1;
                  }
                  string postal_city = words[0];
                  words.remove_at(0);
                  if(StrUtil::quote_gathering(words, postal_city) != 0) 
                  {
                     error_msg = "error setting city";
                     return -1;
                  }
                  postal.set_city(postal_city);
               } 
               else if (words[0] == "-state") 
               {
                  //state
                  words.remove_at(0);
                  if (words.is_empty()) 
                  {
                     error_msg = "unspecified state";
                     return -1;
                  }
                  string postal_sp = words[0];
                  words.remove_at(0);
                  if(StrUtil::quote_gathering(words, postal_sp) != 0) 
                  {
                     error_msg = "error setting state/province";
                     return -1;
                  }
                  postal.set_sp(postal_sp);
               } 
               else if (words[0] == "-pc") 
               {
                  //pc
                  words.remove_at(0);
                  if (words.is_empty()) 
                  {
                     error_msg = "unspecified postal code";
                     return -1;
                  }
                  string postal_pc = words[0];
                  words.remove_at(0);
                  if(StrUtil::quote_gathering(words, postal_pc) != 0) 
                  {
                     error_msg = "error setting postal code";
                     return -1;
                  }
                  postal.set_pc(postal_pc);
               } 
               else if (words[0] == "-cc") 
               {
                  //cc
                  words.remove_at(0);
                  if (words.is_empty())
                  {
                     error_msg = "unspecified country code";
                     return -1;
                  }
                  string postal_cc = words[0];
                  words.remove_at(0);
                  if(StrUtil::quote_gathering(words, postal_cc) != 0) 
                  {
                     error_msg = "error setting country code";
                     return -1;
                  }
                  postal.set_cc(postal_cc);
               } 
               else 
               {
                  break;
               }
            }

            //relaxed: update; !relaxed: create
            if(!relaxed) 
            {
               if (postal.get_name() == "")
               {
                  error_msg = "name is mandatory";
                  return -1;
               }

               if (postal.get_str1() == "") 
               {
                  error_msg = "address street/line 1 is mandatory";
                  return -1;
               }

               if (postal.get_city() == "")
               {
                  error_msg = "city is mandatory";
                  return -1;
               }

               if (postal.get_cc() == "")
               {
                  error_msg = "country code is mandatory";
                  return -1;
               }
            } 
            else 
            {
               if (postal.get_name() == "" &&
                  postal.get_org() == "" &&
                  postal.get_str1() == "" &&
                  postal.get_str2() == "" &&
                  postal.get_str3() == "" &&
                  postal.get_city() == "" &&
                  postal.get_sp() == "" &&
                  postal.get_pc() == "" &&
                  postal.get_cc() == "") 
               {
                  error_msg = "is_empty() postal info";
                  return -1;
               }
            }   

            return 0;
         }

         /// fills a Phone based on input command line
         /**
         @param phone   reference to a Phone object to be comparable_array
         @param words   comparable_array with command-line arguments
         @return 0 if ok, -1 otherwise
         */
         static int phone(libepp::CommonData::Phone &phone, stringa &words)
         {
            if (words.is_empty() || StrUtil::split(words[0], phone.number, phone.ext, ":", true) != 0) 
            {
               return -1;
            }
            words.remove_at(0);
            return 0;
         }

         /// fills a Disclose based on input command line
         /**
         @param disclose   reference to a Disclose object to be comparable_array
         @param word       input string with disclose info
         @return 0 if ok, -1 otherwise
         */
         static int disclose(CommonData::Disclose &disclose, string word)
         {
            string opt1 = word;
            string opt2;
            while (opt1 != "" && StrUtil::split(opt1, opt1, opt2, ",", true) == 0) 
            {
                  if (opt1 == "name_int") {
                     disclose.name_int = true;
                  } else if (opt1 == "name_loc") {
                     disclose.name_loc = true;
                  } else if (opt1 == "org_int") {
                     disclose.org_int = true;
                  } else if (opt1 == "org_loc") {
                     disclose.org_loc = true;
                  } else if (opt1 == "addr_int") {
                     disclose.addr_int = true;
                  } else if (opt1 == "addr_loc") {
                     disclose.addr_loc = true;
                  } else if (opt1 == "voice") {
                     disclose.voice = true;
                  } else if (opt1 == "fax") {
                     disclose.fax = true;
                  } else if (opt1 == "email") {
                     disclose.email = true;
                  } else {
                     return -1;
                  }
                  opt1 = opt2;
            }
            return 0;
         }

         // brorg specific

         /// fills a map of contacts based on input command line
         /**
         @param contacts    reference to the map of contacts to be filled
         @param args        input string with contacts info
         @param error_msg   string to hold error msg on return -1
         @return 0 if ok, -1 otherwise
         */
         static int contacts(string_to_string_map &contacts,
            string args, string &error_msg)
         {
            string one = args;
            string rest;

            do
            {
               if (StrUtil::split(one, one, rest, ",", true) != 0) 
               {
                  error_msg = "invalid contact";
                  return -1;
               }

               string key;
               string value;
               if(StrUtil::split(one, key, value, "=", false) != 0) 
               {
                  error_msg = "invalid contact";
                  return -1;
               }

               contacts[key] = value;

               one = rest;
            } while (one != "");

            return 0;
         }
      };

   } // namespace shell

} // namespace libepp
