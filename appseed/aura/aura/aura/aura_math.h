#pragma once


CLASS_DECL_AURA void srand_dup(uint32_t seed);
CLASS_DECL_AURA int32_t  rand_dup();

CLASS_DECL_AURA int32_t abs_dup(int32_t i);
CLASS_DECL_AURA double fabs_dup(double d);

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_AURA double atan_dup(double d);
CLASS_DECL_AURA double asin_dup(double d);
CLASS_DECL_AURA double acos_dup(double d);
CLASS_DECL_AURA double sqrt_dup(double d);
CLASS_DECL_AURA double pow_dup(double aura, double e);
CLASS_DECL_AURA double exp_dup(double d);
CLASS_DECL_AURA double log_dup(double d);
CLASS_DECL_AURA double tan_dup(double d);
CLASS_DECL_AURA double sin_dup(double d);
CLASS_DECL_AURA double cos_dup(double d);
CLASS_DECL_AURA double fmod_dup(double x, double y);
#endif



CLASS_DECL_AURA int64_t ftoi64(double d);
CLASS_DECL_AURA int32_t ftol(double d);
