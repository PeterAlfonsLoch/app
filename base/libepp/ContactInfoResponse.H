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
/* $Id: ContactInfoResponse.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file ContactInfoResponse.H
*  @brief EPP ContactInfoResponse Class
*/
#pragma once


namespace libepp
{

   /// EPP ContactInfoResponse Class
   class ContactInfoResponse : public Response
   {
   public:
      /// Default constructor
      ContactInfoResponse(bool reset = true) : Response(false)
      {  
         if (reset) {
            this->reset();
         }
      }

      /// Sets the repository object id
      /**
      @param roid repository object id
      */
      void set_roid(const char *roid) { _roid = roid; }

      /// Inserts a status to the object
      /**
      @param status of contact object
      */
      void insert_status(const char *status) {  _status_set.add(status);  }

      /// Sets the client id
      /**
      @param clID sponsoring client id
      */
      void set_clID(const char *clID) { _clID = clID; }

      /// Sets the creator client id
      /**
      @param crID creator client id
      */
      void set_crID(const char *crID) { _crID = crID; }

      /// Sets the creation date
      /**
      @param crDate creation date and time
      */
      void set_crDate(const char *crDate) { _crDate = crDate; }

      /// Sets the last update client id
      /**
      @param upID client id that last updated the object
      */
      void set_upID(const char *upID) { _upID = upID; }

      /// Sets the last update
      /**
      @param upDate most recent date and time object modification
      */
      void set_upDate(const char *upDate) { _upDate = upDate; }

      /// Sets the last transfer date
      /**
      @param trDate most recent date and time object transfer
      */
      void set_trDate(const char *trDate) { _trDate = trDate; }

      /// Returns the repository object id
      /**
      @return roid
      */
      string get_roid() const { return _roid; }

      /// Returns the status list of the object
      /**
      @return status list 
      */
      stringa get_status_set() const { return _status_set; }

      /// Returns the client id
      /**
      @return clID 
      */
      string get_clID() const { return _clID; }

      /// Returns the creator client id
      /**
      @return crID 
      */
      string get_crID() const { return _crID; }

      /// Returns the creation date
      /**
      @return crDate 
      */
      string get_crDate() const { return _crDate; }

      /// Returns the last update client id
      /**
      @return upID 
      */
      string get_upID() const { return _upID; }

      /// Returns the last update
      /**
      @return upDate 
      */
      string get_upDate() const { return _upDate; }

      /// Returns the last transfer date
      /**
      @return trDate 
      */
      string get_trDate() const { return _trDate; }

      /// Sets the common data object
      /**
      @param common common data object
      */
      void set_common_data(const CommonData &common) 
      {
         _common = common;
      }

      /// Returns the common data of the object
      /**
      @return a common data object pointer
      */
      CommonData get_common_data() const { return _common; }

      /// Sets authorization information
      /**
      @param authInfo   domain authorization information
      */
      void set_authInfo(const AuthInfo &authInfo)
      {
         _authInfo = authInfo;
      }

      /// Returns authorization information
      /**
      @return authorization information
      */
      AuthInfo get_authInfo() const { return _authInfo; }

      /// reset attributes
      void reset() { 
         Response::reset();
         _roid = "";
         _status_set.remove_all();
         _clID = "";
         _crID = "";
         _crDate = "";
         _upID = "";
         _upDate = "";
         _trDate = "";
         _common.reset();
         _authInfo.reset();    
      }

   protected:
      /// Repository id
      string _roid;

      /// Status list
      stringa _status_set;

      /// Sponsoring client id
      string _clID;

      /// Creator client id
      string _crID;

      /// Creation date and time
      string _crDate;

      /// last client id that updated the object
      string _upID;

      /// Last modification date and time
      string _upDate;

      /// Last transfer date and time
      string _trDate;

      /// Common data object
      CommonData _common;

      /// authorization information
      AuthInfo _authInfo;
   };

} // namespace libepp
