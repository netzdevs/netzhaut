// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under MIT.
 */

// INCLUDE =========================================================================================

#include "UnicodeData.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// BUILD ===========================================================================================

static NH_BYTE *LICENSE_NOTICE =
    "/**\n * Netzhaut - Web Browser Engine\n * Copyright (C) 2022  Dajo Frey\n * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.\n *\n * This file was generated by nhmake\n */\n\n";

// http://unicode.org/Public/
static NH_MAKE_RESULT createUnicodeDataSource(
    NH_BYTE *bytes_p, FILE *File_p, int *count1_p, int *count2_p)
{
    fprintf(File_p, "// LICENSE NOTICE ==================================================================================\n\n");
    fprintf(File_p, LICENSE_NOTICE);

    fprintf(File_p, "// INCLUDE =========================================================================================\n\n");
    fprintf(File_p, "#include \"UnicodeData.h\"\n\n");

    long lines = 1;
    for (int i = 0; bytes_p[i] != '\0'; ++i) {
        if (bytes_p[i] == '\n') {++lines;}
    }

    fprintf(File_p, "// LOOKUP ==========================================================================================\n\n");
    fprintf(File_p, "const NH_BYTE NH_ENCODING_UNICODE_DATA_PP[%d][255] = \n{\n", lines);

    NH_BYTE *line_p = bytes_p;
    long expectedCodepoint = 0, currentEmpty = 0;
    long empty_pp[2048][2] = {0};

    for (int i = 0; bytes_p[i] != '\0'; ++i) 
    {
        if (bytes_p[i] == '\n') 
        {
            bytes_p[i] = '\0';
            long currentCodepoint = strtol(line_p, NULL, 16);
            if (currentCodepoint != expectedCodepoint) {
                empty_pp[currentEmpty][0] = expectedCodepoint;
                empty_pp[currentEmpty++][1] = currentCodepoint - 1;
                expectedCodepoint = currentCodepoint + 1;
            }
            else {expectedCodepoint++;}
            fprintf(File_p, "    \"%s\",\n", line_p);
            bytes_p[i] = '\n';
            line_p = &bytes_p[i + 1];
        }
    }

    fprintf(File_p, "};\n\n");
    fprintf(File_p, "// UNDEFINED RANGES ================================================================================\n\n");
    fprintf(File_p, "const long NH_ENCODING_UNICODE_DATA_UNDEFINED_RANGES_PP[%d][2] = \n{\n", currentEmpty);

    for (int i = 0; i < currentEmpty; ++i) {
        fprintf(File_p, "    {%d, %d}, \n", empty_pp[i][0], empty_pp[i][1]);
    }

    fprintf(File_p, "};\n\n");

    *count1_p = lines;
    *count2_p = currentEmpty;

    return NH_MAKE_SUCCESS;
}

static NH_MAKE_RESULT createUnicodeDataHeader(
    FILE *File_p, int count1, int count2)
{
    fprintf(File_p, "#ifndef NH_ENCODING_UNICODE_DATA_H\n");
    fprintf(File_p, "#define NH_ENCODING_UNICODE_DATA_H\n\n");
    fprintf(File_p, "#ifndef DOXYGEN_SHOULD_SKIP_THIS\n\n");

    fprintf(File_p, LICENSE_NOTICE);

    fprintf(File_p, "#include \"../Common/Includes.h\"\n\n");
    fprintf(File_p, "#endif\n\n");

    fprintf(File_p, "/** @addtogroup lib_nhcore_macros\n *  @{\n */\n\n");

    fprintf(File_p, "    #define NH_ENCODING_UNICODE_DATA_COUNT %d\n", count1);
    fprintf(File_p, "    #define NH_ENCODING_UNICODE_DATA_UNDEFINED_RANGES_COUNT %d\n\n", count2);

    fprintf(File_p, "/** @} */\n\n");
    fprintf(File_p, "/** @addtogroup lib_nhcore_vars\n *  @{\n */\n\n");

    fprintf(File_p, "    extern const NH_BYTE NH_ENCODING_UNICODE_DATA_PP[%d][255];\n", count1);
    fprintf(File_p, "    extern const long NH_ENCODING_UNICODE_DATA_UNDEFINED_RANGES_PP[%d][2];\n\n", count2);

    fprintf(File_p, "/** @} */\n\n#endif");

    return NH_MAKE_SUCCESS;
}

int createUnicodeData(
    nh_make_Runtime *Runtime_p) 
{
    nh_make_ValueArray ProjDir = nh_make_getVariableValues(Runtime_p, "PROJ_DIR");
    if (!ProjDir.length) {return 1;}

    // Get file data.
    NH_BYTE inPath_p[255] = {'\0'};
    sprintf(inPath_p, "%s/build/.misc/UnicodeData-14.0.0d3.txt", ProjDir.values_pp[0]);

    FILE *fh = fopen(inPath_p, "rb");
    if (fh == NULL) {return 1;}
    
    if (fseek(fh, 0, SEEK_END) != 0) {return 1;}
    long size = ftell(fh);
    rewind(fh);

    if(size <= 0) {
        fclose(fh);
        return 1;
    }

    NH_BYTE *data_p = malloc(size+1); 
    if (data_p == NULL) {return 1;}
    
    memset(data_p, 0, size+1);
    fread(data_p, 1, size, fh);
    fclose(fh);

    // Write.
    NH_BYTE outPath_p[255] = {'\0'};
    sprintf(outPath_p, "%s/src/lib/nhencoding/Base/UnicodeData.c", ProjDir.values_pp[0]);

    FILE *File_p = fopen(outPath_p, "w");
    if (!File_p) {return 1;}

    int count1, count2;
    if (createUnicodeDataSource(data_p, File_p, &count1, &count2)) {return 1;}

    free(data_p);
    fclose(File_p);

    outPath_p[strlen(outPath_p) - 1] = 'h';
    File_p = fopen(outPath_p, "w");
    if (!File_p) {return 1;}

    if (createUnicodeDataHeader(File_p, count1, count2)) {return 1;}
    fclose(File_p);

    return 0;
}

