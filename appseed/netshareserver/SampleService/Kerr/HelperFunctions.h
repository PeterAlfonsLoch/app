//*****************************************************************************
//
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Helper functions used by this project.
//
//*****************************************************************************

#pragma once


namespace Kerr
{
    const std::wstring ToLower(const std::wstring&);

    const std::wstring GetMatchGroupValue(CAtlREMatchContext<>& match,
                                          int index);

    void Parse(CAtlRegExp<>& regex,
               const std::wstring& expression);

    DWORD Win32FromHResult(HRESULT);
}
