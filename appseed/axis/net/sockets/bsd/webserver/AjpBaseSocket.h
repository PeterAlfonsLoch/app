/**
 **   \file AjpBaseSocket.h
 **   \date  2007-10-05
 **   \author grymse@alhem.net
**/
/*
Copyright (C) 2007  Anders Hedstrom

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#pragma once


namespace sockets
{


   class CLASS_DECL_AXIS AjpBaseSocket : public tcp_socket
   {
   public:

      class Initializer
      {
      public:
         Initializer();
         virtual ~Initializer() {}

         int_to_string Method;
         int_to_string header;
         int_to_string Attribute;
         string_map < int32_t > ResponseHeader;

      };

      AjpBaseSocket(base_socket_handler& h);

      void OnRawData(char *buf, primitive::memory_size sz);

      virtual void OnHeader( int16_t id, int16_t len ) = 0;
      virtual void OnPacket( const char *buf, primitive::memory_size sz ) = 0;

   protected:
      uchar get_byte(const char *buf, int32_t& ptr);
      bool get_boolean(const char *buf, int32_t& ptr);
      int16_t get_integer(const char *buf, int32_t& ptr);
      string get_string(const char *buf, int32_t& ptr);

      void put_byte(char *buf, int32_t& ptr, uchar zz);
      void put_boolean(char *buf, int32_t& ptr, bool zz);
      void put_integer(char *buf, int32_t& ptr, int16_t zz);
      void put_string(char *buf, int32_t& ptr, const char * psz);

   private:
      int32_t m_state;
      int32_t m_length;
      int32_t m_ptr;
      char m_message[8192];
   };


} // namespace sockets



