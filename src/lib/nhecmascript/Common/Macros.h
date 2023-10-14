#ifndef NH_ECMASCRIPT_COMMON_MACROS_H
#define NH_ECMASCRIPT_COMMON_MACROS_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

#ifdef NH_LOG_FLOW
    #include "Log.h"
#endif

#endif // DOXYGEN_SHOULD_SKIP_THIS

// FLOW LOGGING ====================================================================================

#ifdef NH_LOG_FLOW
    #define NH_ECMASCRIPT_BEGIN() {_nh_tty_logBegin(__FILE__, __func__);}
#else
    #define NH_ECMASCRIPT_BEGIN() 
#endif

#ifdef NH_LOG_FLOW
    #define NH_ECMASCRIPT_END(result) {_nh_tty_logEnd(__FILE__, __func__); return result;}
#else
    #define NH_ECMASCRIPT_END(result) {return result;} 
#endif

#ifdef NH_LOG_FLOW
    #define NH_ECMASCRIPT_SILENT_END() {_nh_tty_logEnd(__FILE__, __func__); return;}
#else
    #define NH_ECMASCRIPT_SILENT_END() {return;} 
#endif

#ifdef NH_LOG_FLOW
    #define NH_ECMASCRIPT_DIAGNOSTIC_END(result) {return _nh_tty_logDiagnosticEnd(__FILE__, __func__, result, __LINE__);}
#else
    #define NH_ECMASCRIPT_DIAGNOSTIC_END(result) {return result;} 
#endif

// ERROR LOGGING ===================================================================================

#define NH_ECMASCRIPT_CHECK(checkable)                                             \
{                                                                           \
    NH_ECMASCRIPT_RESULT checkResult = checkable;                                  \
    if (checkResult != NH_ECMASCRIPT_SUCCESS) {NH_ECMASCRIPT_DIAGNOSTIC_END(checkResult)} \
}

#define NH_ECMASCRIPT_CHECK_2(checkReturn, checkable)                   \
{                                                                \
    NH_ECMASCRIPT_RESULT checkResult = checkable;                       \
    if (checkResult != NH_ECMASCRIPT_SUCCESS) {NH_ECMASCRIPT_END(checkReturn)} \
}

#define NH_ECMASCRIPT_CHECK_NULL(checkable)                                              \
{                                                                                 \
    void *checkResult_p = checkable;                                              \
    if (checkResult_p == NULL) {NH_ECMASCRIPT_DIAGNOSTIC_END(NH_ECMASCRIPT_ERROR_NULL_POINTER)} \
}

#define NH_ECMASCRIPT_CHECK_NULL_2(checkReturn, checkable)      \
{                                                        \
    void *checkResult_p = checkable;                     \
    if (checkResult_p == NULL) {NH_ECMASCRIPT_END(checkReturn)} \
}

#define NH_ECMASCRIPT_CHECK_MEM(checkable)                                                    \
{                                                                                      \
    void *checkResult_p = checkable;                                                   \
    if (checkResult_p == NULL) {NH_ECMASCRIPT_DIAGNOSTIC_END(NH_ECMASCRIPT_ERROR_MEMORY_ALLOCATION)} \
}

#define NH_ECMASCRIPT_CHECK_MEM_2(checkReturn, checkable)       \
{                                                        \
    void *checkResult_p = checkable;                     \
    if (checkResult_p == NULL) {NH_ECMASCRIPT_END(checkReturn)} \
}

#endif // NH_ECMASCRIPT_COMMON_MACROS_H
