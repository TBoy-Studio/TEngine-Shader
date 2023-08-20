/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef cglm_types_h
#define cglm_types_h

#if defined(_MSC_VER)
/* do not use alignment for older visual studio versions */
#  if _MSC_VER < 1913 /*  Visual Studio 2017 version 15.6  */
#    define CGLM_ALL_UNALIGNED
#    define CGLM_ALIGN(X) /* no alignment */
#  else
#    define CGLM_ALIGN(X) __declspec(align(X))
#  endif
#else
#  define CGLM_ALIGN(X) __attribute((aligned(X)))
#endif

#ifndef CGLM_ALL_UNALIGNED
#  define CGLM_ALIGN_IF(X) CGLM_ALIGN(X)
#else
#  define CGLM_ALIGN_IF(X) /* no alignment */
#endif

#ifdef __AVX__
#  define CGLM_ALIGN_MAT CGLM_ALIGN(32)
#else
#  define CGLM_ALIGN_MAT CGLM_ALIGN(16)
#endif

#ifndef CGLM_HAVE_BUILTIN_ASSUME_ALIGNED

#  if defined(__has_builtin)
#    if __has_builtin(__builtin_assume_aligned)
#      define CGLM_HAVE_BUILTIN_ASSUME_ALIGNED 1
#    endif
#  elif defined(__GNUC__) && defined(__GNUC_MINOR__)
#    if __GNUC__ >= 4 && __GNUC_MINOR__ >= 7
#      define CGLM_HAVE_BUILTIN_ASSUME_ALIGNED 1
#    endif
#  endif

#  ifndef CGLM_HAVE_BUILTIN_ASSUME_ALIGNED
#    define CGLM_HAVE_BUILTIN_ASSUME_ALIGNED 0
#  endif

#endif

#if CGLM_HAVE_BUILTIN_ASSUME_ALIGNED
#  define CGLM_ASSUME_ALIGNED(expr, alignment) \
     __builtin_assume_aligned((expr), (alignment))
#else
#  define CGLM_ASSUME_ALIGNED(expr, alignment) (expr)
#endif

#define CGLM_CASTPTR_ASSUME_ALIGNED(expr, type) \
  ((type*)CGLM_ASSUME_ALIGNED((expr), __alignof__(type)))

typedef int                     ivec2[2];
typedef int                     ivec3[3];
typedef int                     ivec4[4];

typedef float                   vec2[2];
typedef float                   vec3[3];
typedef CGLM_ALIGN_IF(16) float vec4[4];
typedef vec4                    versor;     /* |x, y, z, w| -> w is the last */
typedef vec3                    mat3[3];
typedef vec2                    mat3x2[3];  /* [col (3), row (2)] */
typedef vec4                    mat3x4[3];  /* [col (3), row (4)] */
typedef CGLM_ALIGN_IF(16) vec2  mat2[2];
typedef vec3                    mat2x3[2];  /* [col (2), row (3)] */
typedef vec4                    mat2x4[2];  /* [col (2), row (4)] */
typedef CGLM_ALIGN_MAT    vec4  mat4[4];
typedef vec2                    mat4x2[4];  /* [col (4), row (2)] */
typedef vec3                    mat4x3[4];  /* [col (4), row (3)] */

/*
  Important: cglm stores quaternion as [x, y, z, w] in memory since v0.4.0 
  it was [w, x, y, z] before v0.4.0 ( v0.3.5 and earlier ). w is real part.
*/

#endif /* cglm_types_h */
