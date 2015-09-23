#pragma once


#ifdef OSBIT == 64


#define int_ptr         int64_t
#define pint_ptr        int64_t *
#define uint_ptr        uint64_t
#define puint_ptr       uint64_t *
#define ssize_t         int_ptr


#else


#define int_ptr         int32_t
#define pint_ptr        int32_t *
#define uint_ptr        uin32_t
#define puint_ptr       uin32_t *
#define ssize_t         int_ptr


#endif
