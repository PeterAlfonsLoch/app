#pragma once


CLASS_DECL_____ void srand_dup(unsigned int seed);
CLASS_DECL_____ int  rand_dup();

CLASS_DECL_____ int abs_dup(int i);
CLASS_DECL_____ double fabs_dup(double d);

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_____ double atan_dup(double d);
CLASS_DECL_____ double asin_dup(double d);
CLASS_DECL_____ double acos_dup(double d);
CLASS_DECL_____ double sqrt_dup(double d);
CLASS_DECL_____ double pow_dup(double base, double e);
CLASS_DECL_____ double exp_dup(double d);
CLASS_DECL_____ double log_dup(double d);
CLASS_DECL_____ double tan_dup(double d);
CLASS_DECL_____ double sin_dup(double d);
CLASS_DECL_____ double cos_dup(double d);
CLASS_DECL_____ double fmod_dup(double x, double y);
#endif



CLASS_DECL_____ int64_t ftoi64(double d);
CLASS_DECL_____ int ftol(double d);
