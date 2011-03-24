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
/* $Id: BrDomainRenewResponse.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file BrDomainRenewResponse.H
*  @brief EPP BrDomainRenewResponse extension Class
*/
#pragma once


namespace libepp
{

   /// EPP BrDomainRenewResponse extension Class
   class BrDomainRenewResponse : public DomainRenewResponse
   {
   public:

      /// Default constructor
      BrDomainRenewResponse(bool reset = true) : DomainRenewResponse(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Copies data from the parent
      void copy_parent_data(const DomainRenewResponse &parent) 
      {
         _name = parent.get_name();    
         _exDate = parent.get_exDate();
      }

      /// Sets publication flag attribute
      /**
      @param publication flag attribute
      */
      void set_publication_flag(const string& publicationFlag)
      {
         _publicationFlag = publicationFlag;
      }

      /// Returns publication flag attribute
      /**
      @return publication flag attribute
      */
      string get_publication_flag() const
      {
         return _publicationFlag;
      }

      /// Inserts a onHold Reason
      /**
      @param reason onHold Reason
      */

      void insert_onhold_reason(const string& reason)
      {
         _onhold_reasons.add(reason);
      }

      /// Returns the onHold Reasons
      /**
      @return onHold Reasons
      */
      stringa get_onhold_reasons() const
      {
         return _onhold_reasons;
      }

      /// Resets object attributes
      void reset()
      {
         DomainRenewResponse::reset();
         _publicationFlag = "";
         _onhold_reasons.remove_all();
      }

   protected:

      /// publicationFlag
      string _publicationFlag;

      /// onHoldReason
      stringa _onhold_reasons;
   };

} // namespace libepp

