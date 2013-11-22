#pragma once


CLASS_DECL_BOOT void srand_dup(uint32_t seed);
CLASS_DECL_BOOT int32_t  rand_dup();

CLASS_DECL_BOOT int32_t abs_dup(int32_t i);
CLASS_DECL_BOOT double fabs_dup(double d);

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_BOOT double atan_dup(double d);
CLASS_DECL_BOOT double asin_dup(double d);
CLASS_DECL_BOOT double acos_dup(double d);
CLASS_DECL_BOOT double sqrt_dup(double d);
CLASS_DECL_BOOT double pow_dup(double base, double e);
CLASS_DECL_BOOT double exp_dup(double d);
CLASS_DECL_BOOT double log_dup(double d);
CLASS_DECL_BOOT double tan_dup(double d);
CLASS_DECL_BOOT double sin_dup(double d);
CLASS_DECL_BOOT double cos_dup(double d);
CLASS_DECL_BOOT double fmod_dup(double x, double y);
#endif



CLASS_DECL_BOOT int64_t ftoi64(double d);
CLASS_DECL_BOOT int32_t ftol(double d);
