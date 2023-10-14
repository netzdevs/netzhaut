// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

// INCLUDES ========================================================================================

#include "CommandBuffer.h"
#include "Commands.h"
#include "API.h"

#include "../Common/Macros.h"

#include "../../nhcore/Util/List.h"
#include "../../nhcore/System/Memory.h"

#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// COMMAND BUFFER ==================================================================================

nh_opengl_CommandBuffer nh_opengl_initCommandBuffer()
{
NH_GFX_BEGIN()

    nh_opengl_CommandBuffer CommandBuffer;
    CommandBuffer.Commands = nh_core_initList(64);

NH_GFX_END(CommandBuffer)
}

void nh_opengl_freeCommand(
    nh_opengl_Command *Command_p)
{
NH_GFX_BEGIN()

    if (!Command_p) {NH_GFX_SILENT_END()}

    for (int i = 0; i < Command_p->Arguments.size; ++i) {
        nh_opengl_Data *Data_p = Command_p->Arguments.pp[i];
        if (Data_p->autoFree) {
            nh_opengl_freeData(Data_p);
        }
    }

    nh_core_freeList(&Command_p->Arguments, NH_FALSE);
    nh_core_free(Command_p);

NH_GFX_SILENT_END()
}

nh_opengl_Command *nh_opengl_addCommand(
    nh_opengl_CommandBuffer *CommandBuffer_p, NH_BYTE *name_p, ...)
{
NH_GFX_BEGIN()

    nh_opengl_Command *Command_p = nh_core_allocate(sizeof(nh_opengl_Command));
    NH_GFX_CHECK_MEM_2(NULL, Command_p)

    NH_GFX_OPENGL_COMMAND_E type = nh_opengl_getCommandType(name_p);
    if (type == NH_GFX_OPENGL_COMMAND_UNDEFINED) {
        nh_core_free(Command_p);
        NH_GFX_END(NULL)
    }

    int arguments = nh_opengl_getCommandParameterCount(type);

    Command_p->type = type;
    Command_p->autoFree = NH_TRUE;
    Command_p->Arguments = nh_core_initList(arguments);
    Command_p->Result = nh_opengl_initData();

    va_list args_p;
    va_start(args_p, name_p);
    for(int i = 0; i < arguments; i++) {
        nh_opengl_Data *Data_p = va_arg(args_p, nh_opengl_Data*);
        nh_core_appendToList(&Command_p->Arguments, Data_p);
    }
    va_end(args_p);

    nh_core_appendToList(&CommandBuffer_p->Commands, Command_p);

NH_GFX_END(Command_p)
}

nh_opengl_Command *nh_opengl_disableCommandAutoFree(
    nh_opengl_Command *Command_p)
{
NH_GFX_BEGIN()

    Command_p->autoFree = NH_FALSE;
    Command_p->Result.autoFree = NH_FALSE;

NH_GFX_END(Command_p)
}

NH_GFX_RESULT nh_opengl_executeCommandBuffer(
    nh_opengl_CommandBuffer *CommandBuffer_p)
{
NH_GFX_BEGIN()

    for (int i = 0; i < CommandBuffer_p->Commands.size; ++i) {
        nh_opengl_executeCommand(CommandBuffer_p->Commands.pp[i]);
    }

NH_GFX_END(NH_GFX_SUCCESS)
}

NH_GFX_RESULT nh_opengl_freeCommandBuffer(
    nh_opengl_CommandBuffer *CommandBuffer_p)
{
NH_GFX_BEGIN()

    for (int i = 0; i < CommandBuffer_p->Commands.size; ++i) {
        if (((nh_opengl_Command*)CommandBuffer_p->Commands.pp[i])->autoFree) {
            nh_opengl_freeCommand(CommandBuffer_p->Commands.pp[i]);
        }
    }

    nh_core_freeList(&CommandBuffer_p->Commands, NH_FALSE);
    *CommandBuffer_p = nh_opengl_initCommandBuffer();

NH_GFX_END(NH_GFX_SUCCESS)
}

NH_GFX_RESULT nh_opengl_appendCommandBuffer(
    nh_opengl_CommandBuffer *CommandBuffer_p, nh_opengl_CommandBuffer *ToBeAppended_p)
{
NH_GFX_BEGIN()

    for (int i = 0; i < ToBeAppended_p->Commands.size; ++i) {
        nh_core_appendToList(&CommandBuffer_p->Commands, ToBeAppended_p->Commands.pp[i]);
    }

NH_GFX_END(NH_GFX_SUCCESS)
}

