/**
 * \file macros.h
 * A collection of useful macros.
 */

/*
 * Mesa 3-D graphics library
 *
 * Copyright (C) 1999-2006  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef MACROS_H
#define MACROS_H

#include "macros.h"
#include "u_math.h"
#include "rounding.h"
#include "compiler.h"
#include "glheader.h"
#include "mesa_private.h"

/* Compute the size of an array */
#ifndef ARRAY_SIZE
#  define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

/* For compatibility with Clang's __has_builtin() */
#ifndef __has_builtin
#  define __has_builtin(x) 0
#endif

/**
 * __builtin_expect macros
 */
#if !defined(HAVE___BUILTIN_EXPECT)
#  define __builtin_expect(x, y) (x)
#endif

#ifndef likely
#  ifdef HAVE___BUILTIN_EXPECT
#    define likely(x)   __builtin_expect(!!(x), 1)
#    define unlikely(x) __builtin_expect(!!(x), 0)
#  else
#    define likely(x)   (x)
#    define unlikely(x) (x)
#  endif
#endif


/**
 * Static (compile-time) assertion.
 * Basically, use COND to dimension an array.  If COND is false/zero the
 * array size will be -1 and we'll get a compilation error.
 */
#define STATIC_ASSERT(COND) \
   do { \
      (void) sizeof(char [1 - 2*!(COND)]); \
   } while (0)


/**
 * Unreachable macro. Useful for suppressing "control reaches end of non-void
 * function" warnings.
 */
#if defined(HAVE___BUILTIN_UNREACHABLE) || __has_builtin(__builtin_unreachable)
#define unreachable(str)    \
do {                        \
   assert(!str);            \
   __builtin_unreachable(); \
} while (0)
#elif defined (_MSC_VER)
#define unreachable(str)    \
do {                        \
   assert(!str);            \
   __assume(0);             \
} while (0)
#else
#define unreachable(str) assert(!str)
#endif

/**
 * Assume macro. Useful for expressing our assumptions to the compiler,
 * typically for purposes of silencing warnings.
 */
#if __has_builtin(__builtin_assume)
#define assume(expr)       \
do {                       \
   assert(expr);           \
   __builtin_assume(expr); \
} while (0)
#elif defined HAVE___BUILTIN_UNREACHABLE
#define assume(expr) ((expr) ? ((void) 0) \
                             : (assert(!"assumption failed"), \
                                __builtin_unreachable()))
#elif defined (_MSC_VER)
#define assume(expr) __assume(expr)
#else
#define assume(expr) assert(expr)
#endif

/* Attribute const is used for functions that have no effects other than their
 * return value, and only rely on the argument values to compute the return
 * value.  As a result, calls to it can be CSEed.  Note that using memory
 * pointed to by the arguments is not allowed for const functions.
 */
#ifdef HAVE_FUNC_ATTRIBUTE_CONST
#define ATTRIBUTE_CONST __attribute__((__const__))
#else
#define ATTRIBUTE_CONST
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_FLATTEN
#define FLATTEN __attribute__((__flatten__))
#else
#define FLATTEN
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_FORMAT
#define PRINTFLIKE(f, a) __attribute__ ((format(__printf__, f, a)))
#else
#define PRINTFLIKE(f, a)
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_MALLOC
#define MALLOCLIKE __attribute__((__malloc__))
#else
#define MALLOCLIKE
#endif

/* Forced function inlining */
/* Note: Clang also sets __GNUC__ (see other cases below) */
#ifndef ALWAYS_INLINE
#  if defined(__GNUC__)
#    define ALWAYS_INLINE inline __attribute__((always_inline))
#  elif defined(_MSC_VER)
#    define ALWAYS_INLINE __forceinline
#  else
#    define ALWAYS_INLINE inline
#  endif
#endif

/* Used to optionally mark structures with misaligned elements or size as
 * packed, to trade off performance for space.
 */
#ifdef HAVE_FUNC_ATTRIBUTE_PACKED
#define PACKED __attribute__((__packed__))
#else
#define PACKED
#endif

/* Attribute pure is used for functions that have no effects other than their
 * return value.  As a result, calls to it can be dead code eliminated.
 */
#ifdef HAVE_FUNC_ATTRIBUTE_PURE
#define ATTRIBUTE_PURE __attribute__((__pure__))
#else
#define ATTRIBUTE_PURE
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_RETURNS_NONNULL
#define ATTRIBUTE_RETURNS_NONNULL __attribute__((__returns_nonnull__))
#else
#define ATTRIBUTE_RETURNS_NONNULL
#endif

#ifndef NORETURN
#  ifdef _MSC_VER
#    define NORETURN __declspec(noreturn)
#  elif defined HAVE_FUNC_ATTRIBUTE_NORETURN
#    define NORETURN __attribute__((__noreturn__))
#  else
#    define NORETURN
#  endif
#endif

#ifdef __cplusplus
/**
 * Macro function that evaluates to true if T is a trivially
 * destructible type -- that is, if its (non-virtual) destructor
 * performs no action and all member variables and base classes are
 * trivially destructible themselves.
 */
#   if (defined(__clang__) && defined(__has_feature))
#      if __has_feature(has_trivial_destructor)
#         define HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#      endif
#   elif defined(__GNUC__)
#      if ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)))
#         define HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#      endif
#   elif defined(_MSC_VER) && !defined(__INTEL_COMPILER)
#      define HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#   endif
#   ifndef HAS_TRIVIAL_DESTRUCTOR
       /* It's always safe (if inefficient) to assume that a
        * destructor is non-trivial.
        */
#      define HAS_TRIVIAL_DESTRUCTOR(T) (false)
#   endif
#endif

/**
 * PUBLIC/USED macros
 *
 * If we build the library with gcc's -fvisibility=hidden flag, we'll
 * use the PUBLIC macro to mark functions that are to be exported.
 *
 * We also need to define a USED attribute, so the optimizer doesn't
 * inline a static function that we later use in an alias. - ajax
 */
#ifndef PUBLIC
#  if defined(__GNUC__)
#    define PUBLIC __attribute__((visibility("default")))
#    define USED __attribute__((used))
#  elif defined(_MSC_VER)
#    define PUBLIC __declspec(dllexport)
#    define USED
#  else
#    define PUBLIC
#    define USED
#  endif
#endif

/**
 * UNUSED marks variables (or sometimes functions) that have to be defined,
 * but are sometimes (or always) unused beyond that. A common case is for
 * a function parameter to be used in some build configurations but not others.
 * Another case is fallback vfuncs that don't do anything with their params.
 *
 * Note that this should not be used for identifiers used in `assert()`;
 * see ASSERTED below.
 */
#ifdef HAVE_FUNC_ATTRIBUTE_UNUSED
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

/**
 * Use ASSERTED to indicate that an identifier is unused outside of an `assert()`,
 * so that assert-free builds don't get "unused variable" warnings.
 */
#ifdef NDEBUG
#define ASSERTED UNUSED
#else
#define ASSERTED
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_WARN_UNUSED_RESULT
#define MUST_CHECK __attribute__((warn_unused_result))
#else
#define MUST_CHECK
#endif

#if defined(__GNUC__)
#define ATTRIBUTE_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define ATTRIBUTE_NOINLINE __declspec(noinline)
#else
#define ATTRIBUTE_NOINLINE
#endif


/**
 * Check that STRUCT::FIELD can hold MAXVAL.  We use a lot of bitfields
 * in Mesa/gallium.  We have to be sure they're of sufficient size to
 * hold the largest expected value.
 * Note that with MSVC, enums are signed and enum bitfields need one extra
 * high bit (always zero) to ensure the max value is handled correctly.
 * This macro will detect that with MSVC, but not GCC.
 */
#define ASSERT_BITFIELD_SIZE(STRUCT, FIELD, MAXVAL) \
   do { \
      ASSERTED STRUCT s; \
      s.FIELD = (MAXVAL); \
      assert((int) s.FIELD == (MAXVAL) && "Insufficient bitfield size!"); \
   } while (0)


/** Compute ceiling of integer quotient of A divided by B. */
#define DIV_ROUND_UP( A, B )  ( ((A) + (B) - 1) / (B) )

/** Clamp X to [MIN,MAX].  Turn NaN into MIN, arbitrarily. */
#define CLAMP( X, MIN, MAX )  ( (X)>(MIN) ? ((X)>(MAX) ? (MAX) : (X)) : (MIN) )

/* Syntax sugar occuring frequently in graphics code */
#define SATURATE( X ) CLAMP(X, 0.0f, 1.0f)

/** Minimum of two values: */
#define MIN2( A, B )   ( (A)<(B) ? (A) : (B) )

/** Maximum of two values: */
#define MAX2( A, B )   ( (A)>(B) ? (A) : (B) )

/** Minimum and maximum of three values: */
#define MIN3( A, B, C ) ((A) < (B) ? MIN2(A, C) : MIN2(B, C))
#define MAX3( A, B, C ) ((A) > (B) ? MAX2(A, C) : MAX2(B, C))

/** Align a value to a power of two */
#define ALIGN_POT(x, pot_align) (((x) + (pot_align) - 1) & ~((pot_align) - 1))

/**
 * Macro for declaring an explicit conversion operator.  Defaults to an
 * implicit conversion if C++11 is not supported.
 */
#if __cplusplus >= 201103L
#define EXPLICIT_CONVERSION explicit
#elif defined(__cplusplus)
#define EXPLICIT_CONVERSION
#endif

/** Set a single bit */
#define BITFIELD_BIT(b)      (1u << (b))
/** Set all bits up to excluding bit b */
#define BITFIELD_MASK(b)      \
   ((b) == 32 ? (~0u) : BITFIELD_BIT((b) % 32) - 1)
/** Set count bits starting from bit b  */
#define BITFIELD_RANGE(b, count) \
   (BITFIELD_MASK((b) + (count)) & ~BITFIELD_MASK(b))

/** Set a single bit */
#define BITFIELD64_BIT(b)      (1ull << (b))
/** Set all bits up to excluding bit b */
#define BITFIELD64_MASK(b)      \
   ((b) == 64 ? (~0ull) : BITFIELD64_BIT(b) - 1)
/** Set count bits starting from bit b  */
#define BITFIELD64_RANGE(b, count) \
   (BITFIELD64_MASK((b) + (count)) & ~BITFIELD64_MASK(b))

/* TODO: In future we should try to move this to u_debug.h once header
 * dependencies are reorganised to allow this.
 */
enum pipe_debug_type
{
   PIPE_DEBUG_TYPE_OUT_OF_MEMORY = 1,
   PIPE_DEBUG_TYPE_ERROR,
   PIPE_DEBUG_TYPE_SHADER_INFO,
   PIPE_DEBUG_TYPE_PERF_INFO,
   PIPE_DEBUG_TYPE_INFO,
   PIPE_DEBUG_TYPE_FALLBACK,
   PIPE_DEBUG_TYPE_CONFORMANCE,
};

#if !defined(alignof) && !defined(__cplusplus)
#if __STDC_VERSION__ >= 201112L
#define alignof(t) _Alignof(t)
#elif defined(_MSC_VER)
#define alignof(t) __alignof(t)
#else
#define alignof(t) __alignof__(t)
#endif
#endif



/**
 * \name Integer / float conversion for colors, normals, etc.
 */
/*@{*/

/** Convert GLubyte in [0,255] to GLfloat in [0.0,1.0] */
extern GLfloat _mesa_ubyte_to_float_color_tab[256];
#define UBYTE_TO_FLOAT(u) _mesa_ubyte_to_float_color_tab[(unsigned int)(u)]

/** Convert GLfloat in [0.0,1.0] to GLubyte in [0,255] */
#define FLOAT_TO_UBYTE(X)   ((GLubyte) (GLint) ((X) * 255.0F))


/** Convert GLbyte in [-128,127] to GLfloat in [-1.0,1.0] */
#define BYTE_TO_FLOAT(B)    ((2.0F * (B) + 1.0F) * (1.0F/255.0F))

/** Convert GLfloat in [-1.0,1.0] to GLbyte in [-128,127] */
#define FLOAT_TO_BYTE(X)    ( (((GLint) (255.0F * (X))) - 1) / 2 )


/** Convert GLbyte to GLfloat while preserving zero */
#define BYTE_TO_FLOATZ(B)   ((B) == 0 ? 0.0F : BYTE_TO_FLOAT(B))


/** Convert GLbyte in [-128,127] to GLfloat in [-1.0,1.0], texture/fb data */
#define BYTE_TO_FLOAT_TEX(B)    ((B) == -128 ? -1.0F : (B) * (1.0F/127.0F))

/** Convert GLfloat in [-1.0,1.0] to GLbyte in [-128,127], texture/fb data */
#define FLOAT_TO_BYTE_TEX(X)    CLAMP( (GLint) (127.0F * (X)), -128, 127 )

/** Convert GLushort in [0,65535] to GLfloat in [0.0,1.0] */
#define USHORT_TO_FLOAT(S)  ((GLfloat) (S) * (1.0F / 65535.0F))

/** Convert GLfloat in [0.0,1.0] to GLushort in [0, 65535] */
#define FLOAT_TO_USHORT(X)   ((GLuint) ((X) * 65535.0F))


/** Convert GLshort in [-32768,32767] to GLfloat in [-1.0,1.0] */
#define SHORT_TO_FLOAT(S)   ((2.0F * (S) + 1.0F) * (1.0F/65535.0F))

/** Convert GLfloat in [-1.0,1.0] to GLshort in [-32768,32767] */
#define FLOAT_TO_SHORT(X)   ( (((GLint) (65535.0F * (X))) - 1) / 2 )

/** Convert GLshort to GLfloat while preserving zero */
#define SHORT_TO_FLOATZ(S)   ((S) == 0 ? 0.0F : SHORT_TO_FLOAT(S))


/** Convert GLshort in [-32768,32767] to GLfloat in [-1.0,1.0], texture/fb data */
#define SHORT_TO_FLOAT_TEX(S)    ((S) == -32768 ? -1.0F : (S) * (1.0F/32767.0F))

/** Convert GLfloat in [-1.0,1.0] to GLshort in [-32768,32767], texture/fb data */
#define FLOAT_TO_SHORT_TEX(X)    ( (GLint) (32767.0F * (X)) )


/** Convert GLuint in [0,4294967295] to GLfloat in [0.0,1.0] */
#define UINT_TO_FLOAT(U)    ((GLfloat) ((U) * (1.0F / 4294967295.0)))

/** Convert GLfloat in [0.0,1.0] to GLuint in [0,4294967295] */
#define FLOAT_TO_UINT(X)    ((GLuint) ((X) * 4294967295.0))


/** Convert GLint in [-2147483648,2147483647] to GLfloat in [-1.0,1.0] */
#define INT_TO_FLOAT(I)     ((GLfloat) ((2.0F * (I) + 1.0F) * (1.0F/4294967294.0)))

/** Convert GLfloat in [-1.0,1.0] to GLint in [-2147483648,2147483647] */
/* causes overflow:
#define FLOAT_TO_INT(X)     ( (((GLint) (4294967294.0 * (X))) - 1) / 2 )
*/
/* a close approximation: */
#define FLOAT_TO_INT(X)     ( (GLint) (2147483647.0 * (X)) )

/** Convert GLfloat in [-1.0,1.0] to GLint64 in [-(1<<63),(1 << 63) -1] */
#define FLOAT_TO_INT64(X)     ( (GLint64) (9223372036854775807.0 * (double)(X)) )


/** Convert GLint in [-2147483648,2147483647] to GLfloat in [-1.0,1.0], texture/fb data */
#define INT_TO_FLOAT_TEX(I)    ((I) == -2147483648 ? -1.0F : (I) * (1.0F/2147483647.0))

/** Convert GLfloat in [-1.0,1.0] to GLint in [-2147483648,2147483647], texture/fb data */
#define FLOAT_TO_INT_TEX(X)    ( (GLint) (2147483647.0 * (X)) )


#define BYTE_TO_UBYTE(b)   ((GLubyte) ((b) < 0 ? 0 : (GLubyte) (b)))
#define SHORT_TO_UBYTE(s)  ((GLubyte) ((s) < 0 ? 0 : (GLubyte) ((s) >> 7)))
#define USHORT_TO_UBYTE(s) ((GLubyte) ((s) >> 8))
#define INT_TO_UBYTE(i)    ((GLubyte) ((i) < 0 ? 0 : (GLubyte) ((i) >> 23)))
#define UINT_TO_UBYTE(i)   ((GLubyte) ((i) >> 24))


#define BYTE_TO_USHORT(b)  ((b) < 0 ? 0 : ((GLushort) (((b) * 65535) / 255)))
#define UBYTE_TO_USHORT(b) (((GLushort) (b) << 8) | (GLushort) (b))
#define SHORT_TO_USHORT(s) ((s) < 0 ? 0 : ((GLushort) (((s) * 65535 / 32767))))
#define INT_TO_USHORT(i)   ((i) < 0 ? 0 : ((GLushort) ((i) >> 15)))
#define UINT_TO_USHORT(i)  ((i) < 0 ? 0 : ((GLushort) ((i) >> 16)))
#define UNCLAMPED_FLOAT_TO_USHORT(us, f)  \
        us = ( (GLushort) _mesa_lroundevenf( CLAMP((f), 0.0F, 1.0F) * 65535.0F) )
#define CLAMPED_FLOAT_TO_USHORT(us, f)  \
        us = ( (GLushort) _mesa_lroundevenf( (f) * 65535.0F) )

#define UNCLAMPED_FLOAT_TO_SHORT(s, f)  \
        s = ( (GLshort) _mesa_lroundevenf( CLAMP((f), -1.0F, 1.0F) * 32767.0F) )

/***
 *** UNCLAMPED_FLOAT_TO_UBYTE: clamp float to [0,1] and map to ubyte in [0,255]
 *** CLAMPED_FLOAT_TO_UBYTE: map float known to be in [0,1] to ubyte in [0,255]
 ***/
#ifndef DEBUG
/* This function/macro is sensitive to precision.  Test very carefully
 * if you change it!
 */
#define UNCLAMPED_FLOAT_TO_UBYTE(UB, FLT)				\
        do {								\
           fi_type __tmp;						\
           __tmp.f = (FLT);						\
           if (__tmp.i < 0)						\
              UB = (GLubyte) 0;						\
           else if (__tmp.i >= IEEE_ONE)				\
              UB = (GLubyte) 255;					\
           else {							\
              __tmp.f = __tmp.f * (255.0F/256.0F) + 32768.0F;		\
              UB = (GLubyte) __tmp.i;					\
           }								\
        } while (0)
#define CLAMPED_FLOAT_TO_UBYTE(UB, FLT)					\
        do {								\
           fi_type __tmp;						\
           __tmp.f = (FLT) * (255.0F/256.0F) + 32768.0F;		\
           UB = (GLubyte) __tmp.i;					\
        } while (0)
#else
#define UNCLAMPED_FLOAT_TO_UBYTE(ub, f) \
	ub = ((GLubyte) _mesa_lroundevenf(CLAMP((f), 0.0F, 1.0F) * 255.0F))
#define CLAMPED_FLOAT_TO_UBYTE(ub, f) \
	ub = ((GLubyte) _mesa_lroundevenf((f) * 255.0F))
#endif

static fi_type UINT_AS_UNION(GLuint u)
{
   fi_type tmp;
   tmp.u = u;
   return tmp;
}

static inline fi_type INT_AS_UNION(GLint i)
{
   fi_type tmp;
   tmp.i = i;
   return tmp;
}

static inline fi_type FLOAT_AS_UNION(GLfloat f)
{
   fi_type tmp;
   tmp.f = f;
   return tmp;
}

static inline uint64_t DOUBLE_AS_UINT64(double d)
{
   union {
      double d;
      uint64_t u64;
   } tmp;
   tmp.d = d;
   return tmp.u64;
}

static inline double UINT64_AS_DOUBLE(uint64_t u)
{
   union {
      double d;
      uint64_t u64;
   } tmp;
   tmp.u64 = u;
   return tmp.d;
}

/* First sign-extend x, then return uint32_t. */
#define INT_AS_UINT(x) ((uint32_t)((int32_t)(x)))
#define FLOAT_AS_UINT(x) (FLOAT_AS_UNION(x).u)

/**
 * Convert a floating point value to an unsigned fixed point value.
 *
 * \param frac_bits   The number of bits used to store the fractional part.
 */
static inline uint32_t
U_FIXED(float value, uint32_t frac_bits)
{
   value *= (1 << frac_bits);
   return value < 0.0f ? 0 : (uint32_t) value;
}

/**
 * Convert a floating point value to an signed fixed point value.
 *
 * \param frac_bits   The number of bits used to store the fractional part.
 */
static inline int32_t
S_FIXED(float value, uint32_t frac_bits)
{
   return (int32_t) (value * (1 << frac_bits));
}
/*@}*/


/** Stepping a GLfloat pointer by a byte stride */
#define STRIDE_F(p, i)  (p = (GLfloat *)((GLubyte *)p + i))
/** Stepping a GLuint pointer by a byte stride */
#define STRIDE_UI(p, i)  (p = (GLuint *)((GLubyte *)p + i))
/** Stepping a GLubyte[4] pointer by a byte stride */
#define STRIDE_4UB(p, i)  (p = (GLubyte (*)[4])((GLubyte *)p + i))
/** Stepping a GLfloat[4] pointer by a byte stride */
#define STRIDE_4F(p, i)  (p = (GLfloat (*)[4])((GLubyte *)p + i))
/** Stepping a \p t pointer by a byte stride */
#define STRIDE_T(p, t, i)  (p = (t)((GLubyte *)p + i))


/**********************************************************************/
/** \name 4-element vector operations */
/*@{*/

/** Zero */
#define ZERO_4V( DST )  (DST)[0] = (DST)[1] = (DST)[2] = (DST)[3] = 0

/** Test for equality */
#define TEST_EQ_4V(a,b)  ((a)[0] == (b)[0] &&   \
              (a)[1] == (b)[1] &&   \
              (a)[2] == (b)[2] &&   \
              (a)[3] == (b)[3])

/** Test for equality (unsigned bytes) */
static inline GLboolean
TEST_EQ_4UBV(const GLubyte a[4], const GLubyte b[4])
{
#if defined(__i386__)
   return *((const GLuint *) a) == *((const GLuint *) b);
#else
   return TEST_EQ_4V(a, b);
#endif
}


/** Copy a 4-element vector */
#define COPY_4V( DST, SRC )         \
do {                                \
   (DST)[0] = (SRC)[0];             \
   (DST)[1] = (SRC)[1];             \
   (DST)[2] = (SRC)[2];             \
   (DST)[3] = (SRC)[3];             \
} while (0)

/** Copy a 4-element unsigned byte vector */
static inline void
COPY_4UBV(GLubyte dst[4], const GLubyte src[4])
{
#if defined(__i386__)
   *((GLuint *) dst) = *((GLuint *) src);
#else
   /* The GLuint cast might fail if DST or SRC are not dword-aligned (RISC) */
   COPY_4V(dst, src);
#endif
}

/** Copy \p SZ elements into a 4-element vector */
#define COPY_SZ_4V(DST, SZ, SRC)                  \
do {                                              \
   switch (SZ) {                                  \
   case 4: (DST)[3] = (SRC)[3]; /* fallthrough */ \
   case 3: (DST)[2] = (SRC)[2]; /* fallthrough */ \
   case 2: (DST)[1] = (SRC)[1]; /* fallthrough */ \
   case 1: (DST)[0] = (SRC)[0]; /* fallthrough */ \
   }                                              \
} while(0)

/** Copy \p SZ elements into a homegeneous (4-element) vector, giving
 * default values to the remaining */
#define COPY_CLEAN_4V(DST, SZ, SRC)  \
do {                                 \
      ASSIGN_4V( DST, 0, 0, 0, 1 );  \
      COPY_SZ_4V( DST, SZ, SRC );    \
} while (0)

/** Subtraction */
#define SUB_4V( DST, SRCA, SRCB )           \
do {                                        \
      (DST)[0] = (SRCA)[0] - (SRCB)[0];     \
      (DST)[1] = (SRCA)[1] - (SRCB)[1];     \
      (DST)[2] = (SRCA)[2] - (SRCB)[2];     \
      (DST)[3] = (SRCA)[3] - (SRCB)[3];     \
} while (0)

/** Addition */
#define ADD_4V( DST, SRCA, SRCB )           \
do {                                        \
      (DST)[0] = (SRCA)[0] + (SRCB)[0];     \
      (DST)[1] = (SRCA)[1] + (SRCB)[1];     \
      (DST)[2] = (SRCA)[2] + (SRCB)[2];     \
      (DST)[3] = (SRCA)[3] + (SRCB)[3];     \
} while (0)

/** Element-wise multiplication */
#define SCALE_4V( DST, SRCA, SRCB )         \
do {                                        \
      (DST)[0] = (SRCA)[0] * (SRCB)[0];     \
      (DST)[1] = (SRCA)[1] * (SRCB)[1];     \
      (DST)[2] = (SRCA)[2] * (SRCB)[2];     \
      (DST)[3] = (SRCA)[3] * (SRCB)[3];     \
} while (0)

/** In-place addition */
#define ACC_4V( DST, SRC )          \
do {                                \
      (DST)[0] += (SRC)[0];         \
      (DST)[1] += (SRC)[1];         \
      (DST)[2] += (SRC)[2];         \
      (DST)[3] += (SRC)[3];         \
} while (0)

/** Element-wise multiplication and addition */
#define ACC_SCALE_4V( DST, SRCA, SRCB )     \
do {                                        \
      (DST)[0] += (SRCA)[0] * (SRCB)[0];    \
      (DST)[1] += (SRCA)[1] * (SRCB)[1];    \
      (DST)[2] += (SRCA)[2] * (SRCB)[2];    \
      (DST)[3] += (SRCA)[3] * (SRCB)[3];    \
} while (0)

/** In-place scalar multiplication and addition */
#define ACC_SCALE_SCALAR_4V( DST, S, SRCB ) \
do {                                        \
      (DST)[0] += S * (SRCB)[0];            \
      (DST)[1] += S * (SRCB)[1];            \
      (DST)[2] += S * (SRCB)[2];            \
      (DST)[3] += S * (SRCB)[3];            \
} while (0)

/** Scalar multiplication */
#define SCALE_SCALAR_4V( DST, S, SRCB ) \
do {                                    \
      (DST)[0] = S * (SRCB)[0];         \
      (DST)[1] = S * (SRCB)[1];         \
      (DST)[2] = S * (SRCB)[2];         \
      (DST)[3] = S * (SRCB)[3];         \
} while (0)

/** In-place scalar multiplication */
#define SELF_SCALE_SCALAR_4V( DST, S ) \
do {                                   \
      (DST)[0] *= S;                   \
      (DST)[1] *= S;                   \
      (DST)[2] *= S;                   \
      (DST)[3] *= S;                   \
} while (0)

/*@}*/


/**********************************************************************/
/** \name 3-element vector operations*/
/*@{*/

/** Zero */
#define ZERO_3V( DST )  (DST)[0] = (DST)[1] = (DST)[2] = 0

/** Test for equality */
#define TEST_EQ_3V(a,b)  \
   ((a)[0] == (b)[0] &&  \
    (a)[1] == (b)[1] &&  \
    (a)[2] == (b)[2])

/** Copy a 3-element vector */
#define COPY_3V( DST, SRC )         \
do {                                \
   (DST)[0] = (SRC)[0];             \
   (DST)[1] = (SRC)[1];             \
   (DST)[2] = (SRC)[2];             \
} while (0)

/** Copy a 3-element vector with cast */
#define COPY_3V_CAST( DST, SRC, CAST )  \
do {                                    \
   (DST)[0] = (CAST)(SRC)[0];           \
   (DST)[1] = (CAST)(SRC)[1];           \
   (DST)[2] = (CAST)(SRC)[2];           \
} while (0)

/** Copy a 3-element float vector */
#define COPY_3FV( DST, SRC )        \
do {                                \
   const GLfloat *_tmp = (SRC);     \
   (DST)[0] = _tmp[0];              \
   (DST)[1] = _tmp[1];              \
   (DST)[2] = _tmp[2];              \
} while (0)

/** Subtraction */
#define SUB_3V( DST, SRCA, SRCB )        \
do {                                     \
      (DST)[0] = (SRCA)[0] - (SRCB)[0];  \
      (DST)[1] = (SRCA)[1] - (SRCB)[1];  \
      (DST)[2] = (SRCA)[2] - (SRCB)[2];  \
} while (0)

/** Addition */
#define ADD_3V( DST, SRCA, SRCB )       \
do {                                    \
      (DST)[0] = (SRCA)[0] + (SRCB)[0]; \
      (DST)[1] = (SRCA)[1] + (SRCB)[1]; \
      (DST)[2] = (SRCA)[2] + (SRCB)[2]; \
} while (0)

/** In-place scalar multiplication */
#define SCALE_3V( DST, SRCA, SRCB )     \
do {                                    \
      (DST)[0] = (SRCA)[0] * (SRCB)[0]; \
      (DST)[1] = (SRCA)[1] * (SRCB)[1]; \
      (DST)[2] = (SRCA)[2] * (SRCB)[2]; \
} while (0)

/** In-place element-wise multiplication */
#define SELF_SCALE_3V( DST, SRC )   \
do {                                \
      (DST)[0] *= (SRC)[0];         \
      (DST)[1] *= (SRC)[1];         \
      (DST)[2] *= (SRC)[2];         \
} while (0)

/** In-place addition */
#define ACC_3V( DST, SRC )          \
do {                                \
      (DST)[0] += (SRC)[0];         \
      (DST)[1] += (SRC)[1];         \
      (DST)[2] += (SRC)[2];         \
} while (0)

/** Element-wise multiplication and addition */
#define ACC_SCALE_3V( DST, SRCA, SRCB )     \
do {                                        \
      (DST)[0] += (SRCA)[0] * (SRCB)[0];    \
      (DST)[1] += (SRCA)[1] * (SRCB)[1];    \
      (DST)[2] += (SRCA)[2] * (SRCB)[2];    \
} while (0)

/** Scalar multiplication */
#define SCALE_SCALAR_3V( DST, S, SRCB ) \
do {                                    \
      (DST)[0] = S * (SRCB)[0];         \
      (DST)[1] = S * (SRCB)[1];         \
      (DST)[2] = S * (SRCB)[2];         \
} while (0)

/** In-place scalar multiplication and addition */
#define ACC_SCALE_SCALAR_3V( DST, S, SRCB ) \
do {                                        \
      (DST)[0] += S * (SRCB)[0];            \
      (DST)[1] += S * (SRCB)[1];            \
      (DST)[2] += S * (SRCB)[2];            \
} while (0)

/** In-place scalar multiplication */
#define SELF_SCALE_SCALAR_3V( DST, S ) \
do {                                   \
      (DST)[0] *= S;                   \
      (DST)[1] *= S;                   \
      (DST)[2] *= S;                   \
} while (0)

/** In-place scalar addition */
#define ACC_SCALAR_3V( DST, S )     \
do {                                \
      (DST)[0] += S;                \
      (DST)[1] += S;                \
      (DST)[2] += S;                \
} while (0)

/** Assignment */
#define ASSIGN_3V( V, V0, V1, V2 )  \
do {                                \
    V[0] = V0;                      \
    V[1] = V1;                      \
    V[2] = V2;                      \
} while(0)

/*@}*/


/**********************************************************************/
/** \name 2-element vector operations*/
/*@{*/

/** Zero */
#define ZERO_2V( DST )  (DST)[0] = (DST)[1] = 0

/** Copy a 2-element vector */
#define COPY_2V( DST, SRC )         \
do {                        \
   (DST)[0] = (SRC)[0];             \
   (DST)[1] = (SRC)[1];             \
} while (0)

/** Copy a 2-element vector with cast */
#define COPY_2V_CAST( DST, SRC, CAST )      \
do {                        \
   (DST)[0] = (CAST)(SRC)[0];           \
   (DST)[1] = (CAST)(SRC)[1];           \
} while (0)

/** Copy a 2-element float vector */
#define COPY_2FV( DST, SRC )            \
do {                        \
   const GLfloat *_tmp = (SRC);         \
   (DST)[0] = _tmp[0];              \
   (DST)[1] = _tmp[1];              \
} while (0)

/** Subtraction */
#define SUB_2V( DST, SRCA, SRCB )       \
do {                        \
      (DST)[0] = (SRCA)[0] - (SRCB)[0];     \
      (DST)[1] = (SRCA)[1] - (SRCB)[1];     \
} while (0)

/** Addition */
#define ADD_2V( DST, SRCA, SRCB )       \
do {                        \
      (DST)[0] = (SRCA)[0] + (SRCB)[0];     \
      (DST)[1] = (SRCA)[1] + (SRCB)[1];     \
} while (0)

/** In-place scalar multiplication */
#define SCALE_2V( DST, SRCA, SRCB )     \
do {                        \
      (DST)[0] = (SRCA)[0] * (SRCB)[0];     \
      (DST)[1] = (SRCA)[1] * (SRCB)[1];     \
} while (0)

/** In-place addition */
#define ACC_2V( DST, SRC )          \
do {                        \
      (DST)[0] += (SRC)[0];         \
      (DST)[1] += (SRC)[1];         \
} while (0)

/** Element-wise multiplication and addition */
#define ACC_SCALE_2V( DST, SRCA, SRCB )     \
do {                        \
      (DST)[0] += (SRCA)[0] * (SRCB)[0];    \
      (DST)[1] += (SRCA)[1] * (SRCB)[1];    \
} while (0)

/** Scalar multiplication */
#define SCALE_SCALAR_2V( DST, S, SRCB )     \
do {                        \
      (DST)[0] = S * (SRCB)[0];         \
      (DST)[1] = S * (SRCB)[1];         \
} while (0)

/** In-place scalar multiplication and addition */
#define ACC_SCALE_SCALAR_2V( DST, S, SRCB ) \
do {                        \
      (DST)[0] += S * (SRCB)[0];        \
      (DST)[1] += S * (SRCB)[1];        \
} while (0)

/** In-place scalar multiplication */
#define SELF_SCALE_SCALAR_2V( DST, S )      \
do {                        \
      (DST)[0] *= S;                \
      (DST)[1] *= S;                \
} while (0)

/** In-place scalar addition */
#define ACC_SCALAR_2V( DST, S )         \
do {                        \
      (DST)[0] += S;                \
      (DST)[1] += S;                \
} while (0)

/** Assign scalers to short vectors */
#define ASSIGN_2V( V, V0, V1 )	\
do {				\
    V[0] = V0;			\
    V[1] = V1;			\
} while(0)

/*@}*/

/** Copy \p sz elements into a homegeneous (4-element) vector, giving
 * default values to the remaining components.
 * The default values are chosen based on \p type.
 */
static inline void
COPY_CLEAN_4V_TYPE_AS_UNION(fi_type dst[4], int sz, const fi_type src[4],
                            GLenum type)
{
   switch (type) {
   case GL_FLOAT:
      ASSIGN_4V(dst, FLOAT_AS_UNION(0), FLOAT_AS_UNION(0),
                FLOAT_AS_UNION(0), FLOAT_AS_UNION(1));
      break;
   case GL_INT:
      ASSIGN_4V(dst, INT_AS_UNION(0), INT_AS_UNION(0),
                INT_AS_UNION(0), INT_AS_UNION(1));
      break;
   case GL_UNSIGNED_INT:
      ASSIGN_4V(dst, UINT_AS_UNION(0), UINT_AS_UNION(0),
                UINT_AS_UNION(0), UINT_AS_UNION(1));
      break;
   default:
      ASSIGN_4V(dst, FLOAT_AS_UNION(0), FLOAT_AS_UNION(0),
                FLOAT_AS_UNION(0), FLOAT_AS_UNION(1)); /* silence warnings */
      assert(!"Unexpected type in COPY_CLEAN_4V_TYPE_AS_UNION macro");
   }
   COPY_SZ_4V(dst, sz, src);
}

/** \name Linear interpolation functions */
/*@{*/

static inline GLfloat
LINTERP(GLfloat t, GLfloat out, GLfloat in)
{
   return out + t * (in - out);
}

static inline void
INTERP_3F(GLfloat t, GLfloat dst[3], const GLfloat out[3], const GLfloat in[3])
{
   dst[0] = LINTERP( t, out[0], in[0] );
   dst[1] = LINTERP( t, out[1], in[1] );
   dst[2] = LINTERP( t, out[2], in[2] );
}

static inline void
INTERP_4F(GLfloat t, GLfloat dst[4], const GLfloat out[4], const GLfloat in[4])
{
   dst[0] = LINTERP( t, out[0], in[0] );
   dst[1] = LINTERP( t, out[1], in[1] );
   dst[2] = LINTERP( t, out[2], in[2] );
   dst[3] = LINTERP( t, out[3], in[3] );
}

/*@}*/



static inline unsigned
minify(unsigned value, unsigned levels)
{
    return MAX2(1, value >> levels);
}


/** Cross product of two 3-element vectors */
static inline void
CROSS3(GLfloat n[3], const GLfloat u[3], const GLfloat v[3])
{
   n[0] = u[1] * v[2] - u[2] * v[1];
   n[1] = u[2] * v[0] - u[0] * v[2];
   n[2] = u[0] * v[1] - u[1] * v[0];
}


/** Dot product of two 2-element vectors */
static inline GLfloat
DOT2(const GLfloat a[2], const GLfloat b[2])
{
   return a[0] * b[0] + a[1] * b[1];
}

static inline GLfloat
DOT3(const GLfloat a[3], const GLfloat b[3])
{
   return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

static inline GLfloat
DOT4(const GLfloat a[4], const GLfloat b[4])
{
   return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}


static inline GLfloat
LEN_SQUARED_3FV(const GLfloat v[3])
{
   return DOT3(v, v);
}

static inline GLfloat
LEN_SQUARED_2FV(const GLfloat v[2])
{
   return DOT2(v, v);
}


static inline GLfloat
LEN_3FV(const GLfloat v[3])
{
   return sqrtf(LEN_SQUARED_3FV(v));
}

static inline GLfloat
LEN_2FV(const GLfloat v[2])
{
   return sqrtf(LEN_SQUARED_2FV(v));
}


/* Normalize a 3-element vector to unit length. */
static inline void
NORMALIZE_3FV(GLfloat v[3])
{
   GLfloat len = (GLfloat) LEN_SQUARED_3FV(v);
   if (len) {
      len = 1.0f / sqrtf(len);
      v[0] *= len;
      v[1] *= len;
      v[2] *= len;
   }
}


/** Test two floats have opposite signs */
static inline GLboolean
DIFFERENT_SIGNS(GLfloat x, GLfloat y)
{
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 6334 ) /* sizeof operator applied to an expression with an operator may yield unexpected results */
#endif
   return signbit(x) != signbit(y);
#ifdef _MSC_VER
#pragma warning( pop )
#endif
}


/** casts to silence warnings with some compilers */
#define ENUM_TO_INT(E)     ((GLint)(E))
#define ENUM_TO_FLOAT(E)   ((GLfloat)(GLint)(E))
#define ENUM_TO_DOUBLE(E)  ((GLdouble)(GLint)(E))
#define ENUM_TO_BOOLEAN(E) ((E) ? GL_TRUE : GL_FALSE)


/* Stringify */
#define STRINGIFY(x) #x

/*
 * For GL_ARB_vertex_buffer_object we need to treat vertex array pointers
 * as offsets into buffer stores.  Since the vertex array pointer and
 * buffer store pointer are both pointers and we need to add them, we use
 * this macro.
 * Both pointers/offsets are expressed in bytes.
 */
#define ADD_POINTERS(A, B)  ( (GLubyte *) (A) + (uintptr_t) (B) )

#endif
