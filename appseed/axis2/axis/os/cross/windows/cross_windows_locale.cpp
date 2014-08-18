#include "framework.h"

#undef WINAXISAPI
#define WINAXISAPI CLASS_DECL_AXIS

#define LOCALE_LOCALEINFOFLAGSMASK (LOCALE_NOUSEROVERRIDE|LOCALE_USE_CP_ACP|\
                                    LOCALE_RETURN_NUMBER|LOCALE_RETURN_GENITIVE_NAMES)



static LCID user_lcid, system_lcid;
//static LANGID user_ui_language, system_ui_language;
static LANGID system_ui_language;

UINT setup_unix_locales(void);
WINBOOL is_genitive_name_supported( LCTYPE lctype );
LCID convert_default_lcid( LCID lcid, LCTYPE lctype );
const WCHAR *get_locale_value_name( DWORD lctype );
INT get_registry_locale_info( LPCWSTR value, LPWSTR buffer, INT len );

/******************************************************************************
 *		GetLocaleInfoW (KERNEL32.@)
 *
 * See GetLocaleInfoA.
 */
#ifdef WINDOWS
WINAXISAPI
#endif
int32_t WINAPI GetLocaleInfoW( LCID lcid, LCTYPE lctype, LPWSTR buffer, int32_t len )
{
    LANGID lang_id;
    //HRSRC hrsrc;
    //HGLOBAL hmem;
    int32_t ret;
    uint32_t lcflags;
    const WCHAR *p;
    unsigned int i;

    if (len < 0 || (len && !buffer))
    {
        SetLastError( ERROR_INVALID_PARAMETER );
        return 0;
    }
    if (lctype & LOCALE_RETURN_GENITIVE_NAMES &&
       !is_genitive_name_supported( lctype ))
    {
        SetLastError( ERROR_INVALID_FLAGS );
        return 0;
    }

    if (!len) buffer = NULL;

    lcid = convert_default_lcid( lcid, lctype );

    lcflags = lctype & LOCALE_LOCALEINFOFLAGSMASK;
    lctype &= 0xffff;

    //TRACE( "(lcid=0x%x,lctype=0x%x,%p,%d)\n", lcid, lctype, buffer, len );

    /* first check for overrides in the registry */

    if (!(lcflags & LOCALE_NOUSEROVERRIDE) &&
        lcid == convert_default_lcid( LOCALE_USER_DEFAULT, lctype ))
    {
        const WCHAR *value = get_locale_value_name(lctype);

        if (value)
        {
            if (lcflags & LOCALE_RETURN_NUMBER)
            {
                WCHAR tmp[16];
                ret = get_registry_locale_info( value, tmp, sizeof(tmp)/sizeof(WCHAR) );
                if (ret > 0)
                {
                    const WCHAR *end;
                    uint32_t number = (uint32_t) wtoi64_dup(tmp, &end, 10 );
                    if (*end)  /* invalid number */
                    {
                        SetLastError( ERROR_INVALID_FLAGS );
                        return 0;
                    }
                    ret = sizeof(uint32_t)/sizeof(WCHAR);
                    if (!buffer) return ret;
                    if (ret > len)
                    {
                        SetLastError( ERROR_INSUFFICIENT_BUFFER );
                        return 0;
                    }
                    memcpy( buffer, &number, sizeof(number) );
                }
            }
            else ret = get_registry_locale_info( value, buffer, len );

            if (ret != -1) return ret;
        }
    }

    /* now load it from kernel resources */

    lang_id = LANGIDFROMLCID( lcid );

    /* replace SUBLANG_NEUTRAL by SUBLANG_DEFAULT */
    if (SUBLANGID(lang_id) == SUBLANG_NEUTRAL)
        lang_id = MAKELANGID(PRIMARYLANGID(lang_id), SUBLANG_DEFAULT);

/*    if (!(hrsrc = FindResourceExW( kernel32_handle, (LPWSTR)RT_STRING,
                                   ULongToPtr((lctype >> 4) + 1), lang_id )))
    {
        SetLastError( ERROR_INVALID_FLAGS );  /* no such lctype */
/*        return 0;
    }
    if (!(hmem = LoadResource( kernel32_handle, hrsrc )))
        return 0;

    p = LockResource( hmem );*/
   p = NULL;
    for (i = 0; i < (lctype & 0x0f); i++) p += *p + 1;

    if (lcflags & LOCALE_RETURN_NUMBER) ret = sizeof(uint32_t)/sizeof(WCHAR);
    else if (is_genitive_name_supported( lctype ) && *p)
    {
        /* genitive form's stored after a NULL separator from a nominative */
        for (i = 1; i <= *p; i++) if (!p[i]) break;

        if (i <= *p && (lcflags & LOCALE_RETURN_GENITIVE_NAMES))
        {
            ret = *p - i + 1;
            p += i;
        }
        else ret = i;
    }
    else
        ret = (lctype == LOCALE_FONTSIGNATURE) ? *p : *p + 1;

    if (!buffer) return ret;

    if (ret > len)
    {
        SetLastError( ERROR_INSUFFICIENT_BUFFER );
        return 0;
    }

    if (lcflags & LOCALE_RETURN_NUMBER)
    {
        uint32_t number;
//        WCHAR *end, *tmp = HeapAlloc( GetProcessHeap(), 0, (*p + 1) * sizeof(WCHAR) );
        const WCHAR *end;
        WCHAR * tmp = (WCHAR *) malloc((*p + 1) * sizeof(WCHAR) );
        if (!tmp) return 0;
        memcpy( tmp, p + 1, *p * sizeof(WCHAR) );
        tmp[*p] = 0;
        number = (uint32_t) wtoi64_dup( tmp, &end, 10 );
        if (!*end)
            memcpy( buffer, &number, sizeof(number) );
        else  /* invalid number */
        {
            SetLastError( ERROR_INVALID_FLAGS );
            ret = 0;
        }
//        HeapFree( GetProcessHeap(), 0, tmp );
         free(tmp);

        //TRACE( "(lcid=0x%x,lctype=0x%x,%p,%d) returning number %d\n", lcid, lctype, buffer, len, number );
    }
    else
    {
        memcpy( buffer, p + 1, ret * sizeof(WCHAR) );
        if (lctype != LOCALE_FONTSIGNATURE) buffer[ret-1] = 0;

        //TRACE( "(lcid=0x%x,lctype=0x%x,%p,%d) returning %d %s\n", lcid, lctype, buffer, len, ret, debugstr_w(buffer) );
    }
    return ret;
}











/***********************************************************************
 *           is_genitive_name_supported
 *
 * Determine could LCTYPE basically support genitive name form or not.
 */
WINBOOL is_genitive_name_supported( LCTYPE lctype )
{
    switch(lctype & 0xffff)
    {
    case LOCALE_SMONTHNAME1:
    case LOCALE_SMONTHNAME2:
    case LOCALE_SMONTHNAME3:
    case LOCALE_SMONTHNAME4:
    case LOCALE_SMONTHNAME5:
    case LOCALE_SMONTHNAME6:
    case LOCALE_SMONTHNAME7:
    case LOCALE_SMONTHNAME8:
    case LOCALE_SMONTHNAME9:
    case LOCALE_SMONTHNAME10:
    case LOCALE_SMONTHNAME11:
    case LOCALE_SMONTHNAME12:
    case LOCALE_SMONTHNAME13:
         return TRUE;
    default:
         return FALSE;
    }
}





/* locale ids corresponding to the various Unix locale parameters */
static LCID lcid_LC_COLLATE;
static LCID lcid_LC_CTYPE;
//static LCID lcid_LC_MESSAGES;
static LCID lcid_LC_MONETARY;
static LCID lcid_LC_NUMERIC;
static LCID lcid_LC_TIME;
static LCID lcid_LC_PAPER;
static LCID lcid_LC_MEASUREMENT;
static LCID lcid_LC_TELEPHONE;






/***********************************************************************
 *           convert_default_lcid
 *
 * Get the default LCID to use for a given lctype in GetLocaleInfo.
 */
LCID convert_default_lcid( LCID lcid, LCTYPE lctype )
{
    if (lcid == LOCALE_SYSTEM_DEFAULT ||
        lcid == LOCALE_USER_DEFAULT ||
        lcid == LOCALE_NEUTRAL)
    {
        LCID default_id = 0;

        switch(lctype & 0xffff)
        {
        case LOCALE_SSORTNAME:
            default_id = lcid_LC_COLLATE;
            break;

        case LOCALE_FONTSIGNATURE:
        case LOCALE_IDEFAULTANSICODEPAGE:
        case LOCALE_IDEFAULTCODEPAGE:
        case LOCALE_IDEFAULTEBCDICCODEPAGE:
        case LOCALE_IDEFAULTMACCODEPAGE:
#ifndef METROWIN
        case LOCALE_IDEFAULTUNIXCODEPAGE:
#endif
            default_id = lcid_LC_CTYPE;
            break;

        case LOCALE_ICURRDIGITS:
        case LOCALE_ICURRENCY:
        case LOCALE_IINTLCURRDIGITS:
        case LOCALE_INEGCURR:
        case LOCALE_INEGSEPBYSPACE:
        case LOCALE_INEGSIGNPOSN:
        case LOCALE_INEGSYMPRECEDES:
        case LOCALE_IPOSSEPBYSPACE:
        case LOCALE_IPOSSIGNPOSN:
        case LOCALE_IPOSSYMPRECEDES:
        case LOCALE_SCURRENCY:
        case LOCALE_SINTLSYMBOL:
        case LOCALE_SMONDECIMALSEP:
        case LOCALE_SMONGROUPING:
        case LOCALE_SMONTHOUSANDSEP:
        case LOCALE_SNATIVECURRNAME:
            default_id = lcid_LC_MONETARY;
            break;

        case LOCALE_IDIGITS:
        case LOCALE_IDIGITSUBSTITUTION:
        case LOCALE_ILZERO:
        case LOCALE_INEGNUMBER:
        case LOCALE_SDECIMAL:
        case LOCALE_SGROUPING:
        case LOCALE_SNAN:
        case LOCALE_SNATIVEDIGITS:
        case LOCALE_SNEGATIVESIGN:
        case LOCALE_SNEGINFINITY:
        case LOCALE_SPOSINFINITY:
        case LOCALE_SPOSITIVESIGN:
        case LOCALE_STHOUSAND:
            default_id = lcid_LC_NUMERIC;
            break;

        case LOCALE_ICALENDARTYPE:
        case LOCALE_ICENTURY:
        case LOCALE_IDATE:
        case LOCALE_IDAYLZERO:
        case LOCALE_IFIRSTDAYOFWEEK:
        case LOCALE_IFIRSTWEEKOFYEAR:
        case LOCALE_ILDATE:
        case LOCALE_IMONLZERO:
        case LOCALE_IOPTIONALCALENDAR:
        case LOCALE_ITIME:
        case LOCALE_ITIMEMARKPOSN:
        case LOCALE_ITLZERO:
        case LOCALE_S1159:
        case LOCALE_S2359:
        case LOCALE_SABBREVDAYNAME1:
        case LOCALE_SABBREVDAYNAME2:
        case LOCALE_SABBREVDAYNAME3:
        case LOCALE_SABBREVDAYNAME4:
        case LOCALE_SABBREVDAYNAME5:
        case LOCALE_SABBREVDAYNAME6:
        case LOCALE_SABBREVDAYNAME7:
        case LOCALE_SABBREVMONTHNAME1:
        case LOCALE_SABBREVMONTHNAME2:
        case LOCALE_SABBREVMONTHNAME3:
        case LOCALE_SABBREVMONTHNAME4:
        case LOCALE_SABBREVMONTHNAME5:
        case LOCALE_SABBREVMONTHNAME6:
        case LOCALE_SABBREVMONTHNAME7:
        case LOCALE_SABBREVMONTHNAME8:
        case LOCALE_SABBREVMONTHNAME9:
        case LOCALE_SABBREVMONTHNAME10:
        case LOCALE_SABBREVMONTHNAME11:
        case LOCALE_SABBREVMONTHNAME12:
        case LOCALE_SABBREVMONTHNAME13:
        case LOCALE_SDATE:
        case LOCALE_SDAYNAME1:
        case LOCALE_SDAYNAME2:
        case LOCALE_SDAYNAME3:
        case LOCALE_SDAYNAME4:
        case LOCALE_SDAYNAME5:
        case LOCALE_SDAYNAME6:
        case LOCALE_SDAYNAME7:
        case LOCALE_SDURATION:
        case LOCALE_SLONGDATE:
        case LOCALE_SMONTHNAME1:
        case LOCALE_SMONTHNAME2:
        case LOCALE_SMONTHNAME3:
        case LOCALE_SMONTHNAME4:
        case LOCALE_SMONTHNAME5:
        case LOCALE_SMONTHNAME6:
        case LOCALE_SMONTHNAME7:
        case LOCALE_SMONTHNAME8:
        case LOCALE_SMONTHNAME9:
        case LOCALE_SMONTHNAME10:
        case LOCALE_SMONTHNAME11:
        case LOCALE_SMONTHNAME12:
        case LOCALE_SMONTHNAME13:
        case LOCALE_SSHORTDATE:
        case LOCALE_SSHORTESTDAYNAME1:
        case LOCALE_SSHORTESTDAYNAME2:
        case LOCALE_SSHORTESTDAYNAME3:
        case LOCALE_SSHORTESTDAYNAME4:
        case LOCALE_SSHORTESTDAYNAME5:
        case LOCALE_SSHORTESTDAYNAME6:
        case LOCALE_SSHORTESTDAYNAME7:
        case LOCALE_STIME:
        case LOCALE_STIMEFORMAT:
        case LOCALE_SYEARMONTH:
            default_id = lcid_LC_TIME;
            break;

        case LOCALE_IPAPERSIZE:
            default_id = lcid_LC_PAPER;
            break;

        case LOCALE_IMEASURE:
            default_id = lcid_LC_MEASUREMENT;
            break;

        case LOCALE_ICOUNTRY:
            default_id = lcid_LC_TELEPHONE;
            break;
        }
        if (default_id) lcid = default_id;
    }
    return ConvertDefaultLocale( lcid );
}









/******************************************************************************
 *		get_locale_value_name
 *
 * Gets the registry value name for a given lctype.
 */
const WCHAR *get_locale_value_name( DWORD lctype )
{
    static const WCHAR iCalendarTypeW[] = {'i','C','a','l','e','n','d','a','r','T','y','p','e',0};
    static const WCHAR iCountryW[] = {'i','C','o','u','n','t','r','y',0};
    static const WCHAR iCurrDigitsW[] = {'i','C','u','r','r','D','i','g','i','t','s',0};
    static const WCHAR iCurrencyW[] = {'i','C','u','r','r','e','n','c','y',0};
    static const WCHAR iDateW[] = {'i','D','a','t','e',0};
    static const WCHAR iDigitsW[] = {'i','D','i','g','i','t','s',0};
    static const WCHAR iFirstDayOfWeekW[] = {'i','F','i','r','s','t','D','a','y','O','f','W','e','e','k',0};
    static const WCHAR iFirstWeekOfYearW[] = {'i','F','i','r','s','t','W','e','e','k','O','f','Y','e','a','r',0};
    static const WCHAR iLDateW[] = {'i','L','D','a','t','e',0};
    static const WCHAR iLZeroW[] = {'i','L','Z','e','r','o',0};
    static const WCHAR iMeasureW[] = {'i','M','e','a','s','u','r','e',0};
    static const WCHAR iNegCurrW[] = {'i','N','e','g','C','u','r','r',0};
    static const WCHAR iNegNumberW[] = {'i','N','e','g','N','u','m','b','e','r',0};
    static const WCHAR iPaperSizeW[] = {'i','P','a','p','e','r','S','i','z','e',0};
    static const WCHAR iTLZeroW[] = {'i','T','L','Z','e','r','o',0};
    static const WCHAR iTimePrefixW[] = {'i','T','i','m','e','P','r','e','f','i','x',0};
    static const WCHAR iTimeW[] = {'i','T','i','m','e',0};
    static const WCHAR s1159W[] = {'s','1','1','5','9',0};
    static const WCHAR s2359W[] = {'s','2','3','5','9',0};
    static const WCHAR sCountryW[] = {'s','C','o','u','n','t','r','y',0};
    static const WCHAR sCurrencyW[] = {'s','C','u','r','r','e','n','c','y',0};
    static const WCHAR sDateW[] = {'s','D','a','t','e',0};
    static const WCHAR sDecimalW[] = {'s','D','e','c','i','m','a','l',0};
    static const WCHAR sGroupingW[] = {'s','G','r','o','u','p','i','n','g',0};
    static const WCHAR sLanguageW[] = {'s','L','a','n','g','u','a','g','e',0};
    static const WCHAR sListW[] = {'s','L','i','s','t',0};
    static const WCHAR sLongDateW[] = {'s','L','o','n','g','D','a','t','e',0};
    static const WCHAR sMonDecimalSepW[] = {'s','M','o','n','D','e','c','i','m','a','l','S','e','p',0};
    static const WCHAR sMonGroupingW[] = {'s','M','o','n','G','r','o','u','p','i','n','g',0};
    static const WCHAR sMonThousandSepW[] = {'s','M','o','n','T','h','o','u','s','a','n','d','S','e','p',0};
    static const WCHAR sNativeDigitsW[] = {'s','N','a','t','i','v','e','D','i','g','i','t','s',0};
    static const WCHAR sNegativeSignW[] = {'s','N','e','g','a','t','i','v','e','S','i','g','n',0};
    static const WCHAR sPositiveSignW[] = {'s','P','o','s','i','t','i','v','e','S','i','g','n',0};
    static const WCHAR sShortDateW[] = {'s','S','h','o','r','t','D','a','t','e',0};
    static const WCHAR sThousandW[] = {'s','T','h','o','u','s','a','n','d',0};
    static const WCHAR sTimeFormatW[] = {'s','T','i','m','e','F','o','r','m','a','t',0};
    static const WCHAR sTimeW[] = {'s','T','i','m','e',0};
    static const WCHAR sYearMonthW[] = {'s','Y','e','a','r','M','o','n','t','h',0};
    static const WCHAR NumShapeW[] = {'N','u','m','s','h','a','p','e',0};

    switch (lctype)
    {
    /* These values are used by SetLocaleInfo and GetLocaleInfo, and
     * the values are stored in the registry, confirmed under Windows.
     */
    case LOCALE_ICALENDARTYPE:    return iCalendarTypeW;
    case LOCALE_ICURRDIGITS:      return iCurrDigitsW;
    case LOCALE_ICURRENCY:        return iCurrencyW;
    case LOCALE_IDIGITS:          return iDigitsW;
    case LOCALE_IFIRSTDAYOFWEEK:  return iFirstDayOfWeekW;
    case LOCALE_IFIRSTWEEKOFYEAR: return iFirstWeekOfYearW;
    case LOCALE_ILZERO:           return iLZeroW;
    case LOCALE_IMEASURE:         return iMeasureW;
    case LOCALE_INEGCURR:         return iNegCurrW;
    case LOCALE_INEGNUMBER:       return iNegNumberW;
    case LOCALE_IPAPERSIZE:       return iPaperSizeW;
    case LOCALE_ITIME:            return iTimeW;
    case LOCALE_S1159:            return s1159W;
    case LOCALE_S2359:            return s2359W;
    case LOCALE_SCURRENCY:        return sCurrencyW;
    case LOCALE_SDATE:            return sDateW;
    case LOCALE_SDECIMAL:         return sDecimalW;
    case LOCALE_SGROUPING:        return sGroupingW;
    case LOCALE_SLIST:            return sListW;
    case LOCALE_SLONGDATE:        return sLongDateW;
    case LOCALE_SMONDECIMALSEP:   return sMonDecimalSepW;
    case LOCALE_SMONGROUPING:     return sMonGroupingW;
    case LOCALE_SMONTHOUSANDSEP:  return sMonThousandSepW;
    case LOCALE_SNEGATIVESIGN:    return sNegativeSignW;
    case LOCALE_SPOSITIVESIGN:    return sPositiveSignW;
    case LOCALE_SSHORTDATE:       return sShortDateW;
    case LOCALE_STHOUSAND:        return sThousandW;
    case LOCALE_STIME:            return sTimeW;
    case LOCALE_STIMEFORMAT:      return sTimeFormatW;
    case LOCALE_SYEARMONTH:       return sYearMonthW;

    /* The following are not listed under MSDN as supported,
     * but seem to be used and also stored in the registry.
     */
    case LOCALE_ICOUNTRY:         return iCountryW;
    case LOCALE_IDATE:            return iDateW;
    case LOCALE_ILDATE:           return iLDateW;
    case LOCALE_ITLZERO:          return iTLZeroW;
    case LOCALE_SCOUNTRY:         return sCountryW;
    case LOCALE_SABBREVLANGNAME:  return sLanguageW;

    /* The following are used in XP and later */
    case LOCALE_IDIGITSUBSTITUTION: return NumShapeW;
    case LOCALE_SNATIVEDIGITS:      return sNativeDigitsW;
    case LOCALE_ITIMEMARKPOSN:      return iTimePrefixW;
    }
    return NULL;
}




/******************************************************************************
 *		get_registry_locale_info
 *
 * Retrieve user-modified locale info from the registry.
 * Return length, 0 on error, -1 if not found.
 */
//INT get_registry_locale_info( LPCWSTR value, LPWSTR buffer, INT len )
INT get_registry_locale_info(LPCWSTR, LPWSTR, INT)
{
   return 0;
/*    DWORD size;
    INT ret;
    HANDLE hkey;
    NTSTATUS status;
    UNICODE_STRING nameW;
    KEY_VALUE_PARTIAL_INFORMATION *info;
    static const int info_size = FIELD_OFFSET(KEY_VALUE_PARTIAL_INFORMATION, Data);

    if (!(hkey = create_registry_key())) return -1;

    RtlInitUnicodeString( &nameW, value );
    size = info_size + len * sizeof(WCHAR);

    if (!(info = HeapAlloc( GetProcessHeap(), 0, size )))
    {
        NtClose( hkey );
        SetLastError( ERROR_NOT_ENOUGH_MEMORY );
        return 0;
    }

    status = NtQueryValueKey( hkey, &nameW, KeyValuePartialInformation, info, size, &size );

    if (!status)
    {
        ret = (size - info_size) / sizeof(WCHAR);
        /* append terminating NULL if needed */
  /*      if (!ret || ((WCHAR *)info->Data)[ret-1])
        {
            if (ret < len || !buffer) ret++;
            else
            {
                SetLastError( ERROR_INSUFFICIENT_BUFFER );
                ret = 0;
            }
        }
        if (ret && buffer)
        {
            memcpy( buffer, info->Data, (ret-1) * sizeof(WCHAR) );
            buffer[ret-1] = 0;
        }
    }
    else if (status == STATUS_BUFFER_OVERFLOW && !buffer)
    {
        ret = (size - info_size) / sizeof(WCHAR) + 1;
    }
    else if (status == STATUS_OBJECT_NAME_NOT_FOUND)
    {
        ret = -1;
    }
    else
    {
        SetLastError( RtlNtStatusToDosError(status) );
        ret = 0;
    }
    NtClose( hkey );
    HeapFree( GetProcessHeap(), 0, info );
    return ret;*/
}




















/***********************************************************************
 *           setup_unix_locales
 */
UINT setup_unix_locales(void)
{
/*    struct locale_name locale_name;
    WCHAR buffer[128], ctype_buff[128];
    char *locale;
    UINT unix_cp = 0;

    if ((locale = setlocale( LC_CTYPE, NULL )))
    {
        strcpynAtoW( ctype_buff, locale, sizeof(ctype_buff)/sizeof(WCHAR) );
        parse_locale_name( ctype_buff, &locale_name );
        lcid_LC_CTYPE = locale_name.lcid;
        unix_cp = locale_name.codepage;
    }
    if (!lcid_LC_CTYPE)  /* this one needs a default value */
  /*      lcid_LC_CTYPE = MAKELCID( MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT), SORT_DEFAULT );

    TRACE( "got lcid %04x (%d matches) for LC_CTYPE=%s\n",
           locale_name.lcid, locale_name.matches, debugstr_a(locale) );

#define GET_UNIX_LOCALE(cat) do \
    if ((locale = setlocale( cat, NULL ))) \
    { \
        strcpynAtoW( buffer, locale, sizeof(buffer)/sizeof(WCHAR) ); \
        if (!strcmpW( buffer, ctype_buff )) lcid_##cat = lcid_LC_CTYPE; \
        else { \
            parse_locale_name( buffer, &locale_name );  \
            lcid_##cat = locale_name.lcid; \
            TRACE( "got lcid %04x (%d matches) for " #cat "=%s\n",        \
                   locale_name.lcid, locale_name.matches, debugstr_a(locale) ); \
        } \
    } while (0)

    GET_UNIX_LOCALE( LC_COLLATE );
    GET_UNIX_LOCALE( LC_MESSAGES );
    GET_UNIX_LOCALE( LC_MONETARY );
    GET_UNIX_LOCALE( LC_NUMERIC );
    GET_UNIX_LOCALE( LC_TIME );
#ifdef LC_PAPER
    GET_UNIX_LOCALE( LC_PAPER );
#endif
#ifdef LC_MEASUREMENT
    GET_UNIX_LOCALE( LC_MEASUREMENT );
#endif
#ifdef LC_TELEPHONE
    GET_UNIX_LOCALE( LC_TELEPHONE );
#endif

#undef GET_UNIX_LOCALE

    return unix_cp;*/
    return 0;
}


/***********************************************************************
 *		GetSystemDefaultLCID (KERNEL32.@)
 *
 * Get the default locale Id for the system.
 *
 * PARAMS
 *  None.
 *
 * RETURNS
 *  The current LCID of the default locale for the system.
 */
#ifdef WINDOWS
WINAXISAPI
#endif
LCID WINAPI GetSystemDefaultLCID(void)
{
    LCID lcid;
    NtQueryDefaultLocale( FALSE, &lcid );
    return lcid;
}


/******************************************************************************
 *		ConvertDefaultLocale (KERNEL32.@)
 *
 * Convert a default locale identifier into a real identifier.
 *
 * PARAMS
 *  lcid [I] LCID identifier of the locale to convert
 *
 * RETURNS
 *  lcid unchanged, if not a default locale or its sublanguage is
 *   not SUBLANG_NEUTRAL.
 *  GetSystemDefaultLCID(), if lcid == LOCALE_SYSTEM_DEFAULT.
 *  GetUserDefaultLCID(), if lcid == LOCALE_USER_DEFAULT or LOCALE_NEUTRAL.
 *  Otherwise, lcid with sublanguage changed to SUBLANG_DEFAULT.
 */
#ifdef WINDOWS
WINAXISAPI
#endif
LCID WINAPI ConvertDefaultLocale( LCID lcid )
{
    LANGID langid;

    switch (lcid)
    {
    case LOCALE_SYSTEM_DEFAULT:
        lcid = GetSystemDefaultLCID();
        break;
    case LOCALE_USER_DEFAULT:
    case LOCALE_NEUTRAL:
        lcid = GetUserDefaultLCID();
        break;
    default:
        /* Replace SUBLANG_NEUTRAL with SUBLANG_DEFAULT */
        langid = LANGIDFROMLCID(lcid);
        if (SUBLANGID(langid) == SUBLANG_NEUTRAL)
        {
          langid = MAKELANGID(PRIMARYLANGID(langid), SUBLANG_DEFAULT);
          lcid = MAKELCID(langid, SORTIDFROMLCID(lcid));
        }
    }
    return lcid;
}






/**********************************************************************
 *	NtQueryDefaultLocale  (NTDLL.@)
 */
NTSTATUS WINAPI NtQueryDefaultLocale( WINBOOL user, LCID *lcid )
{
    *lcid = user ? user_lcid : system_lcid;
    return STATUS_SUCCESS;
}


/**********************************************************************
 *	NtSetDefaultLocale  (NTDLL.@)
 */
NTSTATUS WINAPI NtSetDefaultLocale( WINBOOL user, LCID lcid )
{
    if (user) user_lcid = lcid;
    else
    {
        system_lcid = lcid;
        system_ui_language = LANGIDFROMLCID(lcid); /* there is no separate call to set it */
    }
    return STATUS_SUCCESS;
}



/***********************************************************************
 *		GetUserDefaultLCID (KERNEL32.@)
 *
 * Get the default locale Id for the current user.
 *
 * PARAMS
 *  None.
 *
 * RETURNS
 *  The current LCID of the default locale for the current user.
 */
#ifdef WINDOWS
WINAXISAPI
#endif
LCID WINAPI GetUserDefaultLCID(void)
{
    LCID lcid;
    NtQueryDefaultLocale( TRUE, &lcid );
    return lcid;
}
