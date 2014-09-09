/**
 * WinPR: Windows Portable Runtime
 * Windows HTTP (WinHTTP)
 *
 * Copyright 2012 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <winpr/winhttp.h>

/**
 * winhttp.dll:
 *
 * WinHttpAddRequestHeaders
 * WinHttpAutoProxySvcMain
 * WinHttpCheckPlatform
 * WinHttpCloseHandle
 * WinHttpConnect
 * WinHttpCrackUrl
 * WinHttpCreateProxyResolver
 * WinHttpCreateUrl
 * WinHttpDetectAutoProxyConfigUrl
 * WinHttpFreeProxyResult
 * WinHttpGetDefaultProxyConfiguration
 * WinHttpGetIEProxyConfigForCurrentUser
 * WinHttpGetProxyForUrl
 * WinHttpGetProxyForUrlEx
 * WinHttpGetProxyResult
 * WinHttpOpen
 * WinHttpOpenRequest
 * WinHttpQueryAuthSchemes
 * WinHttpQueryDataAvailable
 * WinHttpQueryHeaders
 * WinHttpQueryOption
 * WinHttpReadData
 * WinHttpReceiveResponse
 * WinHttpResetAutoProxy
 * WinHttpSendRequest
 * WinHttpSetCredentials
 * WinHttpSetDefaultProxyConfiguration
 * WinHttpSetOption
 * WinHttpSetStatusCallback
 * WinHttpSetTimeouts
 * WinHttpTimeFromSystemTime
 * WinHttpTimeToSystemTime
 * WinHttpWebSocketClose
 * WinHttpWebSocketCompleteUpgrade
 * WinHttpWebSocketQueryCloseStatus
 * WinHttpWebSocketReceive
 * WinHttpWebSocketSend
 * WinHttpWebSocketShutdown
 * WinHttpWriteData
 */

#ifndef _WIN32

WINBOOL WinHttpTimeFromSystemTime(const SYSTEMTIME* pst, LPWSTR pwszTime)
{
	return TRUE;
}

WINBOOL WinHttpTimeToSystemTime(LPCWSTR pwszTime, SYSTEMTIME* pst)
{
	return TRUE;
}

WINBOOL WinHttpCrackUrl(LPCWSTR pwszUrl, DWORD dwUrlLength, DWORD dwFlags, LPURL_COMPONENTS lpUrlComponents)
{
	return TRUE;
}

WINBOOL WinHttpCreateUrl(LPURL_COMPONENTS lpUrlComponents, DWORD dwFlags, LPWSTR pwszUrl, LPDWORD pdwUrlLength)
{
	return TRUE;
}

WINBOOL WinHttpCheckPlatform(void)
{
	return TRUE;
}

WINBOOL WinHttpGetDefaultProxyConfiguration(WINHTTP_PROXY_INFO* pProxyInfo)
{
	return TRUE;
}

WINBOOL WinHttpSetDefaultProxyConfiguration(WINHTTP_PROXY_INFO* pProxyInfo)
{
	return TRUE;
}

HINTERNET WinHttpOpen(LPCWSTR pszAgentW, DWORD dwAccessType, LPCWSTR pszProxyW, LPCWSTR pszProxyBypassW, DWORD dwFlags)
{
	return NULL;
}

WINBOOL WinHttpCloseHandle(HINTERNET hInternet)
{
	return TRUE;
}

HINTERNET WinHttpConnect(HINTERNET hSession, LPCWSTR pswzServerName, INTERNET_PORT nServerPort, DWORD dwReserved)
{
	return NULL;
}

WINBOOL WinHttpReadData(HINTERNET hRequest, LPVOID lpBuffer, DWORD dwNumberOfBytesToRead, LPDWORD lpdwNumberOfBytesRead)
{
	return TRUE;
}

WINBOOL WinHttpWriteData(HINTERNET hRequest, LPCVOID lpBuffer, DWORD dwNumberOfBytesToWrite, LPDWORD lpdwNumberOfBytesWritten)
{
	return TRUE;
}

WINBOOL WinHttpQueryDataAvailable(HINTERNET hRequest, LPDWORD lpdwNumberOfBytesAvailable)
{
	return TRUE;
}

WINBOOL WinHttpQueryOption(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer, LPDWORD lpdwBufferLength)
{
	return TRUE;
}

WINBOOL WinHttpSetOption(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer, DWORD dwBufferLength)
{
	return TRUE;
}

WINBOOL WinHttpSetTimeouts(HINTERNET hInternet, int nResolveTimeout, int nConnectTimeout, int nSendTimeout, int nReceiveTimeout)
{
	return TRUE;
}

DWORD WinHttpIsHostInProxyBypassList(const WINHTTP_PROXY_INFO* pProxyInfo, PCWSTR pwszHost,
		INTERNET_SCHEME tScheme, INTERNET_PORT nPort, WINBOOL* pfIsInBypassList)
{
	return 0;
}

WINHTTP_STATUS_CALLBACK WinHttpSetStatusCallback(HINTERNET hInternet,
		WINHTTP_STATUS_CALLBACK lpfnInternetCallback, DWORD dwNotificationFlags, DWORD_PTR dwReserved)
{
	return NULL;
}

HINTERNET WinHttpOpenRequest(HINTERNET hConnect, LPCWSTR pwszVerb, LPCWSTR pwszObjectName,
		LPCWSTR pwszVersion, LPCWSTR pwszReferrer, LPCWSTR* ppwszAcceptTypes, DWORD dwFlags)
{
	return NULL;
}

WINBOOL WinHttpAddRequestHeaders(HINTERNET hRequest, LPCWSTR pwszHeaders, DWORD dwHeadersLength, DWORD dwModifiers)
{
	return TRUE;
}

WINBOOL WinHttpSendRequest(HINTERNET hRequest, LPCWSTR lpszHeaders, DWORD dwHeadersLength,
		LPVOID lpOptional, DWORD dwOptionalLength, DWORD dwTotalLength, DWORD_PTR dwContext)
{
	return TRUE;
}

WINBOOL WinHttpSetCredentials(HINTERNET hRequest, DWORD AuthTargets, DWORD AuthScheme,
		LPCWSTR pwszUserName, LPCWSTR pwszPassword, LPVOID pAuthParams)
{
	return TRUE;
}

WINBOOL WinHttpQueryAuthSchemes(HINTERNET hRequest, LPDWORD lpdwSupportedSchemes, LPDWORD lpdwFirstScheme, LPDWORD pdwAuthTarget)
{
	return TRUE;
}

WINBOOL WinHttpQueryAuthParams(HINTERNET hRequest, DWORD AuthScheme, LPVOID* pAuthParams)
{
	return TRUE;
}

WINBOOL WinHttpReceiveResponse(HINTERNET hRequest, LPVOID lpReserved)
{
	return TRUE;
}

WINBOOL WinHttpQueryHeaders(HINTERNET hRequest, DWORD dwInfoLevel, LPCWSTR pwszName,
		LPVOID lpBuffer, LPDWORD lpdwBufferLength, LPDWORD lpdwIndex)
{
	return TRUE;
}

WINBOOL WinHttpDetectAutoProxyConfigUrl(DWORD dwAutoDetectFlags, LPWSTR* ppwstrAutoConfigUrl)
{
	return TRUE;
}

WINBOOL WinHttpGetProxyForUrl(HINTERNET hSession, LPCWSTR lpcwszUrl,
		WINHTTP_AUTOPROXY_OPTIONS* pAutoProxyOptions, WINHTTP_PROXY_INFO* pProxyInfo)
{
	return TRUE;
}

WINBOOL WinHttpGetIEProxyConfigForCurrentUser(WINHTTP_CURRENT_USER_IE_PROXY_CONFIG* pProxyConfig)
{
	return TRUE;
}

#endif
