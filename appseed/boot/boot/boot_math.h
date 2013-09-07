#pragma once


CLASS_DECL_ca void srand_dup(uint32_t seed);
CLASS_DECL_ca int32_t  rand_dup();

CLASS_DECL_ca int32_t abs_dup(int32_t i);
CLASS_DECL_ca double fabs_dup(double d);

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_ca double atan_dup(double d);
CLASS_DECL_ca double asin_dup(double d);
CLASS_DECL_ca double acos_dup(double d);
CLASS_DECL_ca double sqrt_dup(double d);
CLASS_DECL_ca double pow_dup(double base, double e);
CLASS_DECL_ca double exp_dup(double d);
CLASS_DECL_ca double log_dup(double d);
CLASS_DECL_ca double tan_dup(double d);
CLASS_DECL_ca double sin_dup(double d);
CLASS_DECL_ca double cos_dup(double d);
CLASS_DECL_ca double fmod_dup(double x, double y);
#endif



CLASS_DECL_ca int64_t ftoi64(double d);
CLASS_DECL_ca int32_t ftol(double d);
