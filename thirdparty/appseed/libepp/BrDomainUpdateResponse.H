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
/* $Id: BrDomainUpdateResponse.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file BrDomainUpdateResponse.H
*  @brief EPP BrDomainUpdateResponse extension Class
*/
#pragma once


namespace libepp
{

   /// EPP BrDomainUpdateResponse extension Class
   class BrDomainUpdateResponse : public Response
   {
   public:

      /// Default constructor
      BrDomainUpdateResponse(bool reset = true) : Response(false)
      {
         if (reset) {
            this->reset();
         }
      } 

      /// Sets the Ticket Number
      /**
      @param ticketNumber Ticket Number
      */
      void set_ticketNumber(const int ticketNumber)
      {
         _ticketNumber = ticketNumber;
      }

      /// Returns the Ticket Number
      /*
      @param Ticket Number 
      */
      int get_ticketNumber() const
      {
         return _ticketNumber;
      }

      /// Inserts a Doc Pending to the ticket
      /**
      @param p new Doc Pending
      */
      void insert_doc_pending(const struct PendingDoc& p)
      {
         _doc_pendings.add(p);
      }

      /// Returns the ticket's Doc Pendings
      /**
      @return Doc Pendings
      */
      comparable_array<struct PendingDoc> get_doc_pendings() const
      {
         return _doc_pendings;
      }

      /// Inserts a Dns Pending to the ticket
      /**
      @param p new Dns Pending
      */
      void insert_dns_pending(const struct PendingDns& p)
      {
         _dns_pendings.add(p);
      }

      /// Returns the ticket's Dns Pendings
      /**
      @return Dns Pendings
      */
      comparable_array<struct PendingDns> get_dns_pendings() const
      {
         return _dns_pendings;
      }

      /// Sets the ticket's Release Process Pending
      /**
      @param p Release Process Pending
      */
      void set_rel_pending(const struct PendingReleaseProc& p)
      {
         _rel_pending.status = p.status;
         _rel_pending.limit = p.limit;
      }

      /// Returns the ticket's Release Process Pending
      /**
      @return Release Process Pending
      */
      struct PendingReleaseProc get_rel_pending() const
      {
         return _rel_pending;
      }

      /// Insert a host status
      /**
      @param host     host name
      @param status   status
      */
      void insert_host_status(const struct HostStatus& hs)
      {
         _host_status.add(hs);
      }

      /// Returns list of host status
      /**
      @return   list of host status
      */
      comparable_array<struct HostStatus> get_host_status() const
      {
         return _host_status;
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
         Response::reset();
         _ticketNumber = 0;
         _doc_pendings.remove_all();
         _dns_pendings.remove_all();
         _rel_pending.status = "";
         _rel_pending.limit = "";
         _host_status.remove_all();
         _publicationFlag = "";
         _onhold_reasons.remove_all();
      }

   protected:
      /// ticket number
      int _ticketNumber;

      // Pendings
      /// doc
      comparable_array<struct PendingDoc> _doc_pendings;

      /// dns
      comparable_array<struct PendingDns> _dns_pendings;

      /// releaseProc
      struct PendingReleaseProc _rel_pending;

      /// host status
      comparable_array <struct HostStatus> _host_status;

      /// publicationFlag
      string _publicationFlag;

      /// onHoldReason
      stringa _onhold_reasons;
   };

} // namespace libepp
