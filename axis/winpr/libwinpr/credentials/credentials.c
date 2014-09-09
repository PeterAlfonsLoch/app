/**
 * WinPR: Windows Portable Runtime
 * Credentials Management
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

#include <winpr/crt.h>

#include <winpr/credentials.h>

/*
 * Low-Level Credentials Management Functions:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa374731(v=vs.85).aspx#low_level_credentials_management_functions
 */

#ifndef _WIN32

WINBOOL CredWriteW(PCREDENTIALW Credential, DWORD Flags)
{
	return TRUE;
}

WINBOOL CredWriteA(PCREDENTIALA Credential, DWORD Flags)
{
	return TRUE;
}

WINBOOL CredReadW(LPCWSTR TargetName, DWORD Type, DWORD Flags, PCREDENTIALW* Credential)
{
	return TRUE;
}

WINBOOL CredReadA(LPCSTR TargetName, DWORD Type, DWORD Flags, PCREDENTIALA* Credential)
{
	return TRUE;
}

WINBOOL CredEnumerateW(LPCWSTR Filter, DWORD Flags, DWORD* Count, PCREDENTIALW** Credential)
{
	return TRUE;
}

WINBOOL CredEnumerateA(LPCSTR Filter, DWORD Flags, DWORD* Count, PCREDENTIALA** Credential)
{
	return TRUE;
}

WINBOOL CredWriteDomainCredentialsW(PCREDENTIAL_TARGET_INFORMATIONW TargetInfo, PCREDENTIALW Credential, DWORD Flags)
{
	return TRUE;
}

WINBOOL CredWriteDomainCredentialsA(PCREDENTIAL_TARGET_INFORMATIONA TargetInfo, PCREDENTIALA Credential, DWORD Flags)
{
	return TRUE;
}

WINBOOL CredReadDomainCredentialsW(PCREDENTIAL_TARGET_INFORMATIONW TargetInfo, DWORD Flags, DWORD* Count, PCREDENTIALW** Credential)
{
	return TRUE;
}

WINBOOL CredReadDomainCredentialsA(PCREDENTIAL_TARGET_INFORMATIONA TargetInfo, DWORD Flags, DWORD* Count, PCREDENTIALA** Credential)
{
	return TRUE;
}

WINBOOL CredDeleteW(LPCWSTR TargetName, DWORD Type, DWORD Flags)
{
	return TRUE;
}

WINBOOL CredDeleteA(LPCSTR TargetName, DWORD Type, DWORD Flags)
{
	return TRUE;
}

WINBOOL CredRenameW(LPCWSTR OldTargetName, LPCWSTR NewTargetName, DWORD Type, DWORD Flags)
{
	return TRUE;
}

WINBOOL CredRenameA(LPCSTR OldTargetName, LPCSTR NewTargetName, DWORD Type, DWORD Flags)
{
	return TRUE;
}

WINBOOL CredGetTargetInfoW(LPCWSTR TargetName, DWORD Flags, PCREDENTIAL_TARGET_INFORMATIONW* TargetInfo)
{
	return TRUE;
}

WINBOOL CredGetTargetInfoA(LPCSTR TargetName, DWORD Flags, PCREDENTIAL_TARGET_INFORMATIONA* TargetInfo)
{
	return TRUE;
}

WINBOOL CredMarshalCredentialW(CRED_MARSHAL_TYPE CredType, PVOID Credential, LPWSTR* MarshaledCredential)
{
	return TRUE;
}

WINBOOL CredMarshalCredentialA(CRED_MARSHAL_TYPE CredType, PVOID Credential, LPSTR* MarshaledCredential)
{
	return TRUE;
}

WINBOOL CredUnmarshalCredentialW(LPCWSTR MarshaledCredential, PCRED_MARSHAL_TYPE CredType, PVOID* Credential)
{
	return TRUE;
}

WINBOOL CredUnmarshalCredentialA(LPCSTR MarshaledCredential, PCRED_MARSHAL_TYPE CredType, PVOID* Credential)
{
	return TRUE;
}

WINBOOL CredIsMarshaledCredentialW(LPCWSTR MarshaledCredential)
{
	return TRUE;
}

WINBOOL CredIsMarshaledCredentialA(LPCSTR MarshaledCredential)
{
	return TRUE;
}

WINBOOL CredProtectW(WINBOOL fAsSelf, LPWSTR pszCredentials, DWORD cchCredentials,
		LPWSTR pszProtectedCredentials, DWORD* pcchMaxChars, CRED_PROTECTION_TYPE* ProtectionType)
{
	return TRUE;
}

WINBOOL CredProtectA(WINBOOL fAsSelf, LPSTR pszCredentials, DWORD cchCredentials,
		LPSTR pszProtectedCredentials, DWORD* pcchMaxChars, CRED_PROTECTION_TYPE* ProtectionType)
{
	return TRUE;
}

WINBOOL CredUnprotectW(WINBOOL fAsSelf, LPWSTR pszProtectedCredentials,
		DWORD cchCredentials, LPWSTR pszCredentials, DWORD* pcchMaxChars)
{
	return TRUE;
}

WINBOOL CredUnprotectA(WINBOOL fAsSelf, LPSTR pszProtectedCredentials,
		DWORD cchCredentials, LPSTR pszCredentials, DWORD* pcchMaxChars)
{
	return TRUE;
}

WINBOOL CredIsProtectedW(LPWSTR pszProtectedCredentials, CRED_PROTECTION_TYPE* pProtectionType)
{
	return TRUE;
}

WINBOOL CredIsProtectedA(LPSTR pszProtectedCredentials, CRED_PROTECTION_TYPE* pProtectionType)
{
	return TRUE;
}

WINBOOL CredFindBestCredentialW(LPCWSTR TargetName, DWORD Type, DWORD Flags, PCREDENTIALW* Credential)
{
	return TRUE;
}

WINBOOL CredFindBestCredentialA(LPCSTR TargetName, DWORD Type, DWORD Flags, PCREDENTIALA* Credential)
{
	return TRUE;
}

WINBOOL CredGetSessionTypes(DWORD MaximumPersistCount, LPDWORD MaximumPersist)
{
	return TRUE;
}

VOID CredFree(PVOID Buffer)
{

}

#endif
