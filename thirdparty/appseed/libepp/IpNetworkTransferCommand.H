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
/* $Id: IpNetworkTransferCommand.H 958 2008-12-11 14:36:22Z eduardo $ */
/** @file  IpNetworkTransferCommand.H
*  @brief EPP IpNetworkTransferCommand Class
*/
#pragma once


namespace libepp 
{

   /// EPP IpNetworkTransferCommand Class
   class IpNetworkTransferCommand : public Command
   {
   public:
      /// Default constructor
      IpNetworkTransferCommand(bool reset = true) : Command(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Sets operation
      /**
      @param op   identifies the transfer operation to be performed
      */
      void set_operation(const char *op)
      {
         _operation = op;
      }

      /// Returns operation
      /**
      @return transfer operation to be performed
      */
      string get_operation() const
      {
         return _operation;
      }

      /// Sets repository object ID
      /**
      @param roid   contains the server-unique id for the created IP network
      */
      void set_roid(const char *roid)
      {
         _roid = roid;
      }

      /// Returns repository object ID
      /**
      @return server-unique id for the created IP network
      */
      string get_roid() const
      {
         return _roid;
      }

      void reset()
      {
         Command::reset();
         _operation = "";
         _roid = "";
      }

   protected:
      /// identifies the transfer operation to be performed
      string _operation;
      /// server-unique id for the created IP network
      string _roid;
   };

} // namespace libepp
