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
/* $Id: DSInfo.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file DSInfo.H
*  @brief EPP/DNSSEC DS information class
*/
#pragma once


namespace libepp
{

   class KeyData :
      virtual public ::radix::object
   {
   public:
      unsigned int get_flags() const
      {
         return _flags;
      }

      unsigned int get_protocol() const
      {
         return _protocol;
      }

      unsigned int get_algorithm() const
      {
         return _algorithm;
      }

      string get_pub_key() const
      {
         return _pub_key;
      }

      void set_flags(unsigned int flags)
      {
         _flags = flags;
      }

      void set_protocol(unsigned int protocol)
      {
         _protocol = protocol;
      }

      void set_algorithm(unsigned int algorithm)
      {
         _algorithm = algorithm;
      }

      void set_pub_key(string pub_key)
      {
         _pub_key = pub_key;
      }

      KeyData& operator=(const KeyData &key_data) {
         _flags = key_data._flags;
         _protocol = key_data._protocol;
         _algorithm = key_data._algorithm;
         _pub_key = key_data._pub_key;

         return *this;
      }

      KeyData() {
         this->reset();
      }

      bool is_set() {      
         return (_flags != 0 && _protocol != 0 && _algorithm != 0 && 
            _pub_key != "");
      }

      void reset() {
         _flags = 0;
         _protocol = 0;
         _algorithm = 0;
         _pub_key = "";
      }

      string get_xml_format() const
      {
         return "<secDNS:keyData>"
            "<secDNS:flags>" + gen::str::itoa(_flags) +
            "</secDNS:flags>"
            "<secDNS:protocol>" + gen::str::itoa(_protocol) +
            "</secDNS:protocol>"
            "<secDNS:alg>"  + gen::str::itoa(_algorithm) +
            "</secDNS:alg>"
            "<secDNS:pubKey>" + _pub_key +
            "</secDNS:pubKey>" +
            "</secDNS:keyData>";
      }

   private:
      uint16_t    _flags;
      uint8_t     _protocol;
      uint8_t     _algorithm;
      string      _pub_key;

   };

} // namespace libepp

