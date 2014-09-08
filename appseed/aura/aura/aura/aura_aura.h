//
//  base_a_rid_file.h
//  aura
//
//  Created by Carlos Gustavo Cecyn Lundgren on 25/04/14.
//
//

#ifdef __OBJC__


// If saying OBJECTIVE that is an adjective, adjective is trash, so OBJECTIVE part of OBJC is trash!!


#define NON_CONVERGING_LANG_IS_TERMINAL_LANG


#if defined(__cplusplus)


// If saying OBJECTIVE that is an adjective, adjective is merdè (shit, sic., in portuguese-french), so OBJECTIVE part of C++ is double Merdè-Merdè what stills Merdè!!


#define __MM


#else


// If saying OBJECTIVE that is an adjective, adjective is merdè (shit, sic., in portuguese-french), so OBJECTIVE part of C++ is single Merdè what stills Merdè!!


#define __M


#endif


#endif


#ifdef __cplusplus_winrt


// If saying ADD-injective (adjective), add-ons are not the substantive all approved core, so it is trash, so _winrt part of cplusplus_winrt is trash!!


#define NON_CONVERGING_LANG_IS_TERMINAL_LANG


#endif


#ifndef NON_CONVERGING_LANG_IS_TERMINAL_LANG


#define AURA_LANGUAGE


#endif






#ifdef AURA_LANGUAGE


#ifdef __cplusplus


#define cplusplus


#else


#define cplus


#endif


#endif


#if defined(__cplusplus)


#define DECL_EXTERN_C	   extern "C"
#define BEGIN_EXTERN_C		extern "C" {
#define END_EXTERN_C		   }


#else


#define DECL_EXTERN_C
#define BEGIN_EXTERN_C
#define END_EXTERN_C


#endif





