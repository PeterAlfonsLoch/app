#pragma once


CLASS_DECL_c void srand_dup(unsigned int32_t seed);
CLASS_DECL_c int32_t  rand_dup();

CLASS_DECL_c int32_t abs_dup(int32_t i);
CLASS_DECL_c double fabs_dup(double d);

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_c double atan_dup(double d);
CLASS_DECL_c double asin_dup(double d);
CLASS_DECL_c double acos_dup(double d);
CLASS_DECL_c double sqrt_dup(double d);
CLASS_DECL_c double pow_dup(double base, double e);
CLASS_DECL_c double exp_dup(double d);
CLASS_DECL_c double log_dup(double d);
CLASS_DECL_c double tan_dup(double d);
CLASS_DECL_c double sin_dup(double d);
CLASS_DECL_c double cos_dup(double d);
CLASS_DECL_c double fmod_dup(double x, double y);
#endif



CLASS_DECL_c int64_t ftoi64(double d);
CLASS_DECL_c int32_t ftol(double d);
