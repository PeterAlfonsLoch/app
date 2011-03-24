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
/* $Id: PollCommand.H 1040 2009-10-01 17:49:12Z fneves $ */
/** @file PollCommand.H
*  @brief EPP PollCommand Class
*/
#pragma once


namespace libepp 
{

   /// EPP PollCommand Class
   class PollCommand : public Command
   {
   public:
      /// Default constructor
      PollCommand(bool reset = true) : Command(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Sets the operation of the poll command ("req" or "ack")
      /**
      @param op operation ("req" or "ack")
      */
      void set_op(const char *op) { _op = op; }

      /// Sets the msgID of the message being acknowledged
      /**
      @param msgID message id (just in "ack" operation)
      */
      void set_msgID(const char *msgID) { _msgID = msgID; }

      /// Returns the operation of the poll command
      /**
      @return operation
      */
      string get_op() const { return _op; }

      /// Returns the msgID of the message
      /**
      @return message id
      */
      string get_msgID() const { return _msgID; }

      /// reset attributes
      void reset() { 
         Command::reset();
         _op = "";
         _msgID = "";
      }

   protected:
      /// Operation
      string _op;

      /// Message id
      string _msgID;

   };

} // namespace libepp
