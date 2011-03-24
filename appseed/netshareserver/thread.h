#pragma once

#include "listen_socket.h"

namespace netshareserver
{

class socket_thread;

class _declspec(dllexport) thread :
   public ::thread,
   public ca45::login_thread_callback
{
public:
	thread(::ca::application * papp);
	virtual ~thread(void);

   void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

   netshareserver_service * m_pservice;
	listen_socket * m_plistensocket;
	HANDLE m_hChildThreadId;
	PROCESS_INFORMATION m_pi;
	comparable_array < socket_thread *, socket_thread * > m_ptrathread;
	socket_thread * m_pthreadCurrent;

   ca45::login_thread m_loginthread;

	::CEvent m_evInitialized;
   ::CEvent m_evSent;

   CCriticalSection m_csSnapshot;

	bool m_bInitialized;
	thread * m_pnext;

   void register_server(const char * pszServer);


	virtual bool initialize_instance();
	DECL_GEN_SIGNAL(OnApp)

   BOOL PreTranslateMessage(LPMSG lpmsg);

	// DECLARE_MESSAGE_MAP();

   void on_login_thread_response(int iAuth, const char * pszResponse);

};


} // namespace netshareserver