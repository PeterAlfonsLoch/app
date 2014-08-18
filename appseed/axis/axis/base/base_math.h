#pragma once


CLASS_DECL_BASE void srand_dup(uint32_t seed);
CLASS_DECL_BASE int32_t  rand_dup();

CLASS_DECL_BASE int32_t abs_dup(int32_t i);
CLASS_DECL_BASE double fabs_dup(double d);

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_BASE double atan_dup(double d);
CLASS_DECL_BASE double asin_dup(double d);
CLASS_DECL_BASE double acos_dup(double d);
CLASS_DECL_BASE double sqrt_dup(double d);
CLASS_DECL_BASE double pow_dup(double base, double e);
CLASS_DECL_BASE double exp_dup(double d);
CLASS_DECL_BASE double log_dup(double d);
CLASS_DECL_BASE double tan_dup(double d);
CLASS_DECL_BASE double sin_dup(double d);
CLASS_DECL_BASE double cos_dup(double d);
CLASS_DECL_BASE double fmod_dup(double x, double y);
#endif



CLASS_DECL_BASE int64_t ftoi64(double d);
CLASS_DECL_BASE int32_t ftol(double d);
