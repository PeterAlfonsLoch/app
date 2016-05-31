#pragma once


CLASS_DECL_ACE void srand_dup(uint32_t seed);
CLASS_DECL_ACE int32_t  rand_dup();

CLASS_DECL_ACE int32_t abs_dup(int32_t i);
CLASS_DECL_ACE double fabs_dup(double d);

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_ACE double atan_dup(double d);
CLASS_DECL_ACE double asin_dup(double d);
CLASS_DECL_ACE double acos_dup(double d);
CLASS_DECL_ACE double sqrt_dup(double d);
CLASS_DECL_ACE double pow_dup(double ace, double e);
CLASS_DECL_ACE double exp_dup(double d);
CLASS_DECL_ACE double log_dup(double d);
CLASS_DECL_ACE double tan_dup(double d);
CLASS_DECL_ACE double sin_dup(double d);
CLASS_DECL_ACE double cos_dup(double d);
CLASS_DECL_ACE double fmod_dup(double x, double y);
#endif



CLASS_DECL_ACE int64_t ftoi64(double d);
CLASS_DECL_ACE int32_t ftol(double d);
