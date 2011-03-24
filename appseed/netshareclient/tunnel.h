#pragma once

namespace netshareclient
{

   class thread;

   class tunnel :
      public ::sockets::http_tunnel
   {
   public:
      tunnel(::sockets::socket_handler_base & h);

      enum EAction
      {
         ActionEvent,
         ActionSetCursor,
         ActionSnapshot,
      };

      EAction                 m_eaction;
      point                   m_pt;
      stringa               m_straEvent;
      ::view *                m_pview;
      area *                  m_parea;


      thread *                m_pthread;
      int                     m_iFrame;
      int                     m_iFrameCount;
      string                  m_strImageType;
      rect                    m_rectClient;
      point                   m_ptCursor;


      virtual void OnFirst();
      virtual void OnHeader(const string &, const string &);
      virtual void OnHeaderComplete();
      virtual void OnData(const char * psz, size_t size);

      virtual void netshare_connect();
      virtual void netshare_request(const char * pszUrl, primitive::memory & storage);
      virtual void netshare_receive_body();
      virtual void netshare_receive(primitive::memory & storage);
      virtual void netshare_start();

      virtual void set_cursor(int x, int y);
      
      virtual void OnDataComplete();

   };
} // 