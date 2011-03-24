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
/* $Id: ContactUpdateCommand.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file ContactUpdateCommand.H
*  @brief EPP ContactUpdateCommand Class
*/
#pragma once


namespace libepp
{

   /// EPP ContactUpdateCommand Class
   class ContactUpdateCommand : public Command
   {
   public:

      /// Default constructor
      ContactUpdateCommand(bool reset = true) : Command(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Inserts a status to the object
      /**
      @param status_add status to be added to the object
      */
      void insert_status_list_add(const char *status_add) 
      { 
         _status_list_add.add(status_add); 
      }

      /// Removes a status from the object
      /**
      @param status_rem status to be removed to the object
      */
      void insert_status_list_rem(const char *status_rem) 
      { 
         _status_list_rem.add(status_rem); 
      }

      /// Returns the list of status to be added to the object
      /**
      @return status list to be added to the object
      */
      stringa get_status_list_add() const { return _status_list_add; }

      /// Returns the list of status to be removed from the object
      /**
      @return status list to be removed to the object
      */
      stringa get_status_list_rem() const { return _status_list_rem; }

      /// Sets the common data object
      /**
      @param common common data object
      */
      void set_common_data(const CommonData &common) 
      {
         _common = common;
      }

      /// Returns the common data object
      /**
      @return a common data object raw pointer
      */
      CommonData get_common_data() const { return _common; }

      /// Resets the data in the object
      void reset() 
      { 
         Command::reset();
         _status_list_add.remove_all();
         _status_list_rem.remove_all();
         _common.reset();
         _authInfo.reset();
      }

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

   protected:
      /// Status List to be added to the object
      stringa _status_list_add;

      /// Status list to be removed to the object
      stringa _status_list_rem;

      /// Common data object
      CommonData _common;

      /// authorization information
      AuthInfo _authInfo;
   };

} // namespace libepp
