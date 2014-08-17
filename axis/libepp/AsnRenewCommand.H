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
/* $Id: AsnRenewCommand.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file AsnRenewCommand.H
*  @brief EPP AsnRenewCommand Class
*/

#pragma once

namespace libepp
{

   /// EPP AsnRenew Class
   class AsnRenewCommand : public Command
   {
   public:
      /// Default constructor
      AsnRenewCommand(bool reset = true) : Command(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Sets asn
      /**
      @param asn   autonomous system number
      */
      void set_asn(const int asn)
      {
         _asn = asn;
      }

      /// Returns asn
      /**
      @return autonomous system number
      */
      int get_asn() const
      {
         return _asn;
      }

      /// Sets expiration date
      /**
      @param expDate   date on which the current validity period ends
      */
      void set_expDate(const char *expDate)
      {
         _expDate = expDate;
      }

      /// Returns expiration date
      /**
      @return date on which the current validity period ends
      */
      string get_expDate() const
      {
         return _expDate;
      }

      /// Sets period
      /**
      @param time   amount of time
      @param unit   measure unit
      */
      void set_period(const int time, const char *unit)
      {
         _period.time = time;
         _period.unit = unit;
      }

      /// Returns period
      /**
      @return number of units to be added to the registration period
      */
      RegistrationPeriod get_period() const
      {
         return _period;
      }

      void reset()
      {
         Command::reset();
         _asn = 0;
         _expDate = "";
         _period.time = 0;
         _period.unit = "";
      }

   protected:
      /// autonomous system number
      int _asn;

      /// date on which the current validity period ends
      string _expDate;

      /// number of units to be added to the registration period of the AS object
      RegistrationPeriod _period;
   };

} // namespace libepp
