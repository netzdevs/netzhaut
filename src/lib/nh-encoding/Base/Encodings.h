#ifndef NH_ENCODING_ENCODINGS_H
#define NH_ENCODING_ENCODINGS_H

// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

// INCLUDES ========================================================================================

#include "../Common/Includes.h"

// ENUMS ===========================================================================================

typedef enum NH_ENCODING_NAME { 
     NH_ENCODING_NAME_UNDEFINED, 
     NH_ENCODING_NAME_UTF_8, 
     NH_ENCODING_NAME_IBM866, 
     NH_ENCODING_NAME_ISO_8859_2, 
     NH_ENCODING_NAME_ISO_8859_3, 
     NH_ENCODING_NAME_ISO_8859_4, 
     NH_ENCODING_NAME_ISO_8859_5, 
     NH_ENCODING_NAME_ISO_8859_6, 
     NH_ENCODING_NAME_ISO_8859_7, 
     NH_ENCODING_NAME_ISO_8859_8, 
     NH_ENCODING_NAME_ISO_8859_8_I, 
     NH_ENCODING_NAME_ISO_8859_10, 
     NH_ENCODING_NAME_ISO_8859_13, 
     NH_ENCODING_NAME_ISO_8859_14, 
     NH_ENCODING_NAME_ISO_8859_15, 
     NH_ENCODING_NAME_ISO_8859_16, 
     NH_ENCODING_NAME_KOI8_R, 
     NH_ENCODING_NAME_KOI8_U, 
     NH_ENCODING_NAME_MACINTOSH, 
     NH_ENCODING_NAME_WINDOWS_874, 
     NH_ENCODING_NAME_WINDOWS_1250, 
     NH_ENCODING_NAME_WINDOWS_1251, 
     NH_ENCODING_NAME_WINDOWS_1252, 
     NH_ENCODING_NAME_WINDOWS_1253, 
     NH_ENCODING_NAME_WINDOWS_1254, 
     NH_ENCODING_NAME_WINDOWS_1255, 
     NH_ENCODING_NAME_WINDOWS_1256, 
     NH_ENCODING_NAME_WINDOWS_1257, 
     NH_ENCODING_NAME_WINDOWS_1258, 
     NH_ENCODING_NAME_X_MAC_CYRILLIC, 
     NH_ENCODING_NAME_GBK, 
     NH_ENCODING_NAME_GB18030, 
     NH_ENCODING_NAME_BIG5, 
     NH_ENCODING_NAME_EUC_JP, 
     NH_ENCODING_NAME_ISO_2022_JP, 
     NH_ENCODING_NAME_SHIFT_JIS, 
     NH_ENCODING_NAME_EUC_KR, 
     NH_ENCODING_NAME_REPLACEMENT, 
     NH_ENCODING_NAME_UTF_16BE, 
     NH_ENCODING_NAME_UTF_16LE, 
     NH_ENCODING_NAME_X_USER_DEFINED, 
 } NH_ENCODING_NAME; 

typedef enum NH_ENCODING_LABEL {
    NH_ENCODING_LABEL_UNICODE_1_1_UTF_8,
    NH_ENCODING_LABEL_UNICODE11UTF8,
    NH_ENCODING_LABEL_UNICODE20UTF8,
    NH_ENCODING_LABEL_UTF_8,
    NH_ENCODING_LABEL_UTF8,
    NH_ENCODING_LABEL_X_UNICODE20UTF8,
    NH_ENCODING_LABEL_866,
    NH_ENCODING_LABEL_CP866,
    NH_ENCODING_LABEL_CSIBM866,
    NH_ENCODING_LABEL_IBM866,
    NH_ENCODING_LABEL_CSISOLATIN2,
    NH_ENCODING_LABEL_ISO_8859_2,
    NH_ENCODING_LABEL_ISO_IR_101,
    NH_ENCODING_LABEL_ISO8859_2,
    NH_ENCODING_LABEL_ISO88592,
    NH_ENCODING_LABEL_ISO_8859_2_,
    NH_ENCODING_LABEL_ISO_8859_2_1987,
    NH_ENCODING_LABEL_L2,
    NH_ENCODING_LABEL_LATIN2,
    NH_ENCODING_LABEL_CSISOLATIN3,
    NH_ENCODING_LABEL_ISO_8859_3,
    NH_ENCODING_LABEL_ISO_IR_109,
    NH_ENCODING_LABEL_ISO8859_3,
    NH_ENCODING_LABEL_ISO88593,
    NH_ENCODING_LABEL_ISO_8859_3_,
    NH_ENCODING_LABEL_ISO_8859_3_1988,
    NH_ENCODING_LABEL_L3,
    NH_ENCODING_LABEL_LATIN3,
    NH_ENCODING_LABEL_CSISOLATIN4,
    NH_ENCODING_LABEL_ISO_8859_4,
    NH_ENCODING_LABEL_ISO_IR_110,
    NH_ENCODING_LABEL_ISO8859_4,
    NH_ENCODING_LABEL_ISO88594,
    NH_ENCODING_LABEL_ISO_8859_4_,
    NH_ENCODING_LABEL_ISO_8859_4_1988,
    NH_ENCODING_LABEL_L4,
    NH_ENCODING_LABEL_LATIN4,
    NH_ENCODING_LABEL_CSISOLATINCYRILLIC,
    NH_ENCODING_LABEL_CYRILLIC,
    NH_ENCODING_LABEL_ISO_8859_5,
    NH_ENCODING_LABEL_ISO_IR_144,
    NH_ENCODING_LABEL_ISO8859_5,
    NH_ENCODING_LABEL_ISO88595,
    NH_ENCODING_LABEL_ISO_8859_5_,
    NH_ENCODING_LABEL_ISO_8859_5_1988,
    NH_ENCODING_LABEL_ARABIC,
    NH_ENCODING_LABEL_ASMO_708,
    NH_ENCODING_LABEL_CSISO88596E,
    NH_ENCODING_LABEL_CSISO88596I,
    NH_ENCODING_LABEL_CSISOLATINARABIC,
    NH_ENCODING_LABEL_ECMA_114,
    NH_ENCODING_LABEL_ISO_8859_6,
    NH_ENCODING_LABEL_ISO_8859_6_E,
    NH_ENCODING_LABEL_ISO_8859_6_I,
    NH_ENCODING_LABEL_ISO_IR_127,
    NH_ENCODING_LABEL_ISO8859_6,
    NH_ENCODING_LABEL_ISO88596,
    NH_ENCODING_LABEL_ISO_8859_6_,
    NH_ENCODING_LABEL_ISO_8859_6_1987,
    NH_ENCODING_LABEL_CSISOLATINGREEK,
    NH_ENCODING_LABEL_ECMA_118,
    NH_ENCODING_LABEL_ELOT_928,
    NH_ENCODING_LABEL_GREEK,
    NH_ENCODING_LABEL_GREEK8,
    NH_ENCODING_LABEL_ISO_8859_7,
    NH_ENCODING_LABEL_ISO_IR_126,
    NH_ENCODING_LABEL_ISO8859_7,
    NH_ENCODING_LABEL_ISO88597,
    NH_ENCODING_LABEL_ISO_8859_7_,
    NH_ENCODING_LABEL_ISO_8859_7_1987,
    NH_ENCODING_LABEL_SUN_EU_GREEK,
    NH_ENCODING_LABEL_CSISO88598E,
    NH_ENCODING_LABEL_CSISOLATINHEBREW,
    NH_ENCODING_LABEL_HEBREW,
    NH_ENCODING_LABEL_ISO_8859_8,
    NH_ENCODING_LABEL_ISO_8859_8_E,
    NH_ENCODING_LABEL_ISO_IR_138,
    NH_ENCODING_LABEL_ISO8859_8,
    NH_ENCODING_LABEL_ISO88598,
    NH_ENCODING_LABEL_ISO_8859_8_,
    NH_ENCODING_LABEL_ISO_8859_8_1988,
    NH_ENCODING_LABEL_VISUAL,
    NH_ENCODING_LABEL_CSISO88598I,
    NH_ENCODING_LABEL_ISO_8859_8_I,
    NH_ENCODING_LABEL_LOGICAL,
    NH_ENCODING_LABEL_CSISOLATIN6,
    NH_ENCODING_LABEL_ISO_8859_10,
    NH_ENCODING_LABEL_ISO_IR_157,
    NH_ENCODING_LABEL_ISO8859_10,
    NH_ENCODING_LABEL_ISO885910,
    NH_ENCODING_LABEL_L6,
    NH_ENCODING_LABEL_LATIN6,
    NH_ENCODING_LABEL_ISO_8859_13,
    NH_ENCODING_LABEL_ISO8859_13,
    NH_ENCODING_LABEL_ISO885913,
    NH_ENCODING_LABEL_ISO_8859_14,
    NH_ENCODING_LABEL_ISO8859_14,
    NH_ENCODING_LABEL_ISO885914,
    NH_ENCODING_LABEL_CSISOLATIN9,
    NH_ENCODING_LABEL_ISO_8859_15,
    NH_ENCODING_LABEL_ISO8859_15,
    NH_ENCODING_LABEL_ISO885915,
    NH_ENCODING_LABEL_ISO_8859_15_,
    NH_ENCODING_LABEL_L9,
    NH_ENCODING_LABEL_ISO_8859_16,
    NH_ENCODING_LABEL_CSKOI8R,
    NH_ENCODING_LABEL_KOI,
    NH_ENCODING_LABEL_KOI8,
    NH_ENCODING_LABEL_KOI8_R,
    NH_ENCODING_LABEL_KOI8_R_,
    NH_ENCODING_LABEL_KOI8_RU,
    NH_ENCODING_LABEL_KOI8_U,
    NH_ENCODING_LABEL_CSMACINTOSH,
    NH_ENCODING_LABEL_MAC,
    NH_ENCODING_LABEL_MACINTOSH,
    NH_ENCODING_LABEL_X_MAC_ROMAN,
    NH_ENCODING_LABEL_DOS_874,
    NH_ENCODING_LABEL_ISO_8859_11,
    NH_ENCODING_LABEL_ISO8859_11,
    NH_ENCODING_LABEL_ISO885911,
    NH_ENCODING_LABEL_TIS_620,
    NH_ENCODING_LABEL_WINDOWS_874,
    NH_ENCODING_LABEL_CP1250,
    NH_ENCODING_LABEL_WINDOWS_1250,
    NH_ENCODING_LABEL_X_CP1250,
    NH_ENCODING_LABEL_CP1251,
    NH_ENCODING_LABEL_WINDOWS_1251,
    NH_ENCODING_LABEL_X_CP1251,
    NH_ENCODING_LABEL_ANSI_X3_4_1968,
    NH_ENCODING_LABEL_ASCII,
    NH_ENCODING_LABEL_CP1252,
    NH_ENCODING_LABEL_CP819,
    NH_ENCODING_LABEL_CSISOLATIN1,
    NH_ENCODING_LABEL_IBM819,
    NH_ENCODING_LABEL_ISO_8859_1,
    NH_ENCODING_LABEL_ISO_IR_100,
    NH_ENCODING_LABEL_ISO8859_1,
    NH_ENCODING_LABEL_ISO88591,
    NH_ENCODING_LABEL_ISO_8859_1_,
    NH_ENCODING_LABEL_ISO_8859_1_1987,
    NH_ENCODING_LABEL_L1,
    NH_ENCODING_LABEL_LATIN1,
    NH_ENCODING_LABEL_US_ASCII,
    NH_ENCODING_LABEL_WINDOWS_1252,
    NH_ENCODING_LABEL_X_CP1252,
    NH_ENCODING_LABEL_CP1253,
    NH_ENCODING_LABEL_WINDOWS_1253,
    NH_ENCODING_LABEL_X_CP1253,
    NH_ENCODING_LABEL_CP1254,
    NH_ENCODING_LABEL_CSISOLATIN5,
    NH_ENCODING_LABEL_ISO_8859_9,
    NH_ENCODING_LABEL_ISO_IR_148,
    NH_ENCODING_LABEL_ISO8859_9,
    NH_ENCODING_LABEL_ISO88599,
    NH_ENCODING_LABEL_ISO_8859_9_,
    NH_ENCODING_LABEL_ISO_8859_9_1989,
    NH_ENCODING_LABEL_L5,
    NH_ENCODING_LABEL_LATIN5,
    NH_ENCODING_LABEL_WINDOWS_1254,
    NH_ENCODING_LABEL_X_CP1254,
    NH_ENCODING_LABEL_CP1255,
    NH_ENCODING_LABEL_WINDOWS_1255,
    NH_ENCODING_LABEL_X_CP1255,
    NH_ENCODING_LABEL_CP1256,
    NH_ENCODING_LABEL_WINDOWS_1256,
    NH_ENCODING_LABEL_X_CP1256,
    NH_ENCODING_LABEL_CP1257,
    NH_ENCODING_LABEL_WINDOWS_1257,
    NH_ENCODING_LABEL_X_CP1257,
    NH_ENCODING_LABEL_CP1258,
    NH_ENCODING_LABEL_WINDOWS_1258,
    NH_ENCODING_LABEL_X_CP1258,
    NH_ENCODING_LABEL_X_MAC_CYRILLIC,
    NH_ENCODING_LABEL_X_MAC_UKRAINIAN,
    NH_ENCODING_LABEL_CHINESE,
    NH_ENCODING_LABEL_CSGB2312,
    NH_ENCODING_LABEL_CSISO58GB231280,
    NH_ENCODING_LABEL_GB2312,
    NH_ENCODING_LABEL_GB_2312,
    NH_ENCODING_LABEL_GB_2312_80,
    NH_ENCODING_LABEL_GBK,
    NH_ENCODING_LABEL_ISO_IR_58,
    NH_ENCODING_LABEL_X_GBK,
    NH_ENCODING_LABEL_GB18030,
    NH_ENCODING_LABEL_BIG5,
    NH_ENCODING_LABEL_BIG5_HKSCS,
    NH_ENCODING_LABEL_CN_BIG5,
    NH_ENCODING_LABEL_CSBIG5,
    NH_ENCODING_LABEL_X_X_BIG5,
    NH_ENCODING_LABEL_CSEUCPKDFMTJAPANESE,
    NH_ENCODING_LABEL_EUC_JP,
    NH_ENCODING_LABEL_X_EUC_JP,
    NH_ENCODING_LABEL_CSISO2022JP,
    NH_ENCODING_LABEL_ISO_2022_JP,
    NH_ENCODING_LABEL_CSSHIFTJIS,
    NH_ENCODING_LABEL_MS932,
    NH_ENCODING_LABEL_MS_KANJI,
    NH_ENCODING_LABEL_SHIFT_JIS,
    NH_ENCODING_LABEL_SHIFT_JIS_,
    NH_ENCODING_LABEL_SJIS,
    NH_ENCODING_LABEL_WINDOWS_31J,
    NH_ENCODING_LABEL_X_SJIS,
    NH_ENCODING_LABEL_CSEUCKR,
    NH_ENCODING_LABEL_CSKSC56011987,
    NH_ENCODING_LABEL_EUC_KR,
    NH_ENCODING_LABEL_ISO_IR_149,
    NH_ENCODING_LABEL_KOREAN,
    NH_ENCODING_LABEL_KS_C_5601_1987,
    NH_ENCODING_LABEL_KS_C_5601_1989,
    NH_ENCODING_LABEL_KSC5601,
    NH_ENCODING_LABEL_KSC_5601,
    NH_ENCODING_LABEL_WINDOWS_949,
    NH_ENCODING_LABEL_CSISO2022KR,
    NH_ENCODING_LABEL_HZ_GB_2312,
    NH_ENCODING_LABEL_ISO_2022_CN,
    NH_ENCODING_LABEL_ISO_2022_CN_EXT,
    NH_ENCODING_LABEL_ISO_2022_KR,
    NH_ENCODING_LABEL_REPLACEMENT,
    NH_ENCODING_LABEL_UNICODEFFFE,
    NH_ENCODING_LABEL_UTF_16BE,
    NH_ENCODING_LABEL_CSUNICODE,
    NH_ENCODING_LABEL_ISO_10646_UCS_2,
    NH_ENCODING_LABEL_UCS_2,
    NH_ENCODING_LABEL_UNICODE,
    NH_ENCODING_LABEL_UNICODEFEFF,
    NH_ENCODING_LABEL_UTF_16,
    NH_ENCODING_LABEL_UTF_16LE,
    NH_ENCODING_LABEL_X_USER_DEFINED,
} NH_ENCODING_LABEL;

// DATA ============================================================================================

extern const char *NH_ENCODING_LABELS_PP[];
extern int NH_ENCODING_LABELS_PP_COUNT;

// FUNCTIONS =======================================================================================

NH_ENCODING_NAME nh_encoding_getEncoding(
    char *label_p
);

NH_ENCODING_NAME nh_encoding_getOutputEncoding(
    NH_ENCODING_NAME encoding
);

#endif
