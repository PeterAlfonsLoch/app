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
/* $Id: Greeting.H 1062 2010-07-07 22:26:12Z eduardo $ */
/** @file Greeting.H
*  @brief EPP Greeting Class
*/
#pragma once


namespace libepp
{

   /// EPP Greeting Class
   class Greeting :
      virtual public ::radix::object
   {
   public:

      /// For details about the following codes, see RFC 3730 - Session 2.4
      enum Access {
         UNSET_AC = -1,
         ALL = 0,
         NONE_AC,
         NULL_AC,
         PERSONAL,
         PERSONAL_AND_OTHER,
         OTHER_AC
      };

      /// For details about the following codes, see RFC 3730 - Session 2.4
      enum Purpose {
         ADMIN = 0,
         CONTACT,
         PROV,
         OTHER_PR
      };

      /// For details about the following codes, see RFC 3730 - Session 2.4
      enum Recipient {
         OTHER_RC = 0,
         OURS,
         PUBLIC,
         SAME,
         UNRELATED
      };

      /// For details about the following codes, see RFC 3730 - Session 2.4 
      enum Retention {
         UNSET_RT = -1,
         BUSINESS = 0,
         INDEFINITE,
         LEGAL,
         NONE_RT,
         STATED
      };

      /// Sets the svID
      /**
      @param svID Server Name
      */
      void set_svID(const char *svID);

      /// Sets the server's current date and time
      /**
      @param svDate Server Current Date and Time (UTC)
      */
      void set_svDate(const char *svDate);

      /// Sets the protocol version
      /**
      @param version Protocol versions supported by the server
      */
      void set_version(const char *version);

      /// Sets the language supported by the server
      /**
      @param lang Languages known by the server (format defined by RFC3066)
      */
      void set_lang(const char *lang);

      /// Sets the object the server supports
      /**
      @param objURI Objects that the server is capable of managing
      */
      void set_objURI(const char *objURI);

      /// Sets object extensions the server supports
      /**
      @param extURI Object extensions supported by the server 
      */
      void set_extURI(const char *extURI); 

      /// Sets the server's Access parameter
      /**
      @param access Access provided by the server
      */
      void set_access(const Access &access);

      /// Sets the server's Purpose parameter
      /**
      @param purpose Data collection purposes 
      */
      void set_purpose(const Purpose &purpose); 

      /// Sets the server's Recipient parameter
      /**
      @param recipient Data recipients 
      */
      void set_recipient(const Recipient &recipient); 

      /// Sets the server's Recipient description
      /**
      @param recDesc Recipient description
      */
      void set_recDesc(const char *recDesc);

      /// Sets the server's Retention parameter
      /**
      @param retention Data retention
      */
      void set_retention(const Retention &retention);

      /// Sets the server's policy expiry
      /**
      @param type 0 = absolute, 1 = relative
      @param expiry Policy lifetime 
      */
      void set_expiry(const int &type, const char *expiry);

      /// Returns the svID
      /**
      @return svID
      */
      string get_svID() const;

      /// Returns the server's current date and time
      /**
      @return svDate
      */
      string get_svDate() const;

      /// Returns the protocol version
      /**
      @return version 
      */
      stringa get_version() const;

      /// Returns the language supported by the server
      /**
      @return lang 
      */
      stringa get_lang() const;

      /// Returns the object the server supports
      /**
      @return objURI
      */
      stringa get_objURI() const; 

      /// Returns the object extensions the server supports
      /**
      @return extURI
      */
      stringa get_extURI() const; 

      /// Returns the server's Access parameter
      /**
      @return access 
      */
      Access get_access() const;

      /// Returns the server's Purpose parameter
      /**
      @return purpose 
      */
      comparable_array < Purpose > get_purpose() const; 

      /// Returns the server's Recipient parameter
      /**
      @return recipient
      */
      comparable_array < Recipient > get_recipient() const;

      /// Returns the server's Recipient description
      /**
      @return recDesc
      */
      string get_recDesc() const;

      /// Returns the server's Retention parameter
      /**
      @return retention 
      */
      Retention get_retention() const;

      /// Returns the server's policy expiry type
      /**
      @return expiry type (absolute = 0, relative = 1) 
      */
      int get_type_expiry() const;

      /// Returns the server's policy expiry
      /**
      @return expiry 
      */
      string get_expiry() const;

      /// reset attributes
      void reset() 
      { 
         _svID = "";
         _svDate = "";
         _version.remove_all();
         _lang.remove_all();
         _objURI.remove_all();
         _extURI.remove_all();
         _access = UNSET_AC;
         _purpose.remove_all();
         _recipient.remove_all();
         _recDesc = "";
         _retention = UNSET_RT;
         _type_expiry = -1;
         _expiry = "";
      }

   protected:
      /// Server Name
      string _svID;  

      /// Server Current Date and Time (UTC)
      string _svDate;

      /// Protocol versions supported by the server
      stringa _version;

      /// Languages known by the server
      stringa _lang;

      /// Objects that the server is capable of managing
      stringa _objURI;

      /// Object extensions supported by the server (optional)
      stringa _extURI;

      /// Access provided by the server (optional)
      Access _access;

      /// Data collection purposes (optional)
      comparable_array < Purpose > _purpose;

      /// Data recipients (optional)
      comparable_array < Recipient > _recipient;

      /// Recipient description (optional)
      string _recDesc;

      /// Data retention (optional)
      Retention _retention;

      /// Expiry type (absolute = 0, relative = 1) (optional)
      int _type_expiry;

      /// Policy lifetime (optional)
      string _expiry;
   };

} // namespace libepp
