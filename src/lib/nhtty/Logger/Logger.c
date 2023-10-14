// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

// INCLUDES ========================================================================================

#include "Logger.h"

#include "../Common/Macros.h"

#include "../../nhencoding/Common/Macros.h"
#include "../../nhencoding/Encodings/UTF32.h"

#include "../../nhcore/System/Memory.h"

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

// UPDATE LOGGER ===================================================================================

static NH_TTY_RESULT nh_tty_updateLoggerNode(
    nh_LoggerNode *LoggerNode_p, nh_tty_LoggerNode *InstanceNode_p)
{
NH_TTY_BEGIN()

    for (int i = 0; i < LoggerNode_p->Children.size; ++i) 
    {
        nh_LoggerNode *NextLoggerNode_p = LoggerNode_p->Children.pp[i];
        nh_tty_LoggerNode *NextInstanceNode_p = nh_core_getFromList(&InstanceNode_p->Children, i);

        if (NextInstanceNode_p == NULL) 
        {
            NextInstanceNode_p = nh_core_allocate(sizeof(nh_tty_LoggerNode));
            NH_TTY_CHECK_MEM(NextInstanceNode_p)

            NextInstanceNode_p->Children     = nh_core_initList(8);
            NextInstanceNode_p->LoggerNode_p = NextLoggerNode_p;
            NextInstanceNode_p->isOpen       = NH_FALSE;
            NextInstanceNode_p->isCurrent    = NH_FALSE;
            NextInstanceNode_p->isSelected   = NH_FALSE;
            NextInstanceNode_p->hasFocus     = NH_FALSE;
            NextInstanceNode_p->focusedRow   = 0;
            NextInstanceNode_p->offset       = 0;
            NextInstanceNode_p->peak         = 0;
            NextInstanceNode_p->Parent_p     = InstanceNode_p;

            nh_core_appendToList(&InstanceNode_p->Children, NextInstanceNode_p);
        }

        NH_TTY_CHECK(nh_tty_updateLoggerNode(NextLoggerNode_p, NextInstanceNode_p))
    }

NH_TTY_DIAGNOSTIC_END(NH_TTY_SUCCESS)
}

static void nh_tty_getLoggerNodes(
    nh_tty_LoggerNode *Node_p, nh_List *List_p)
{
NH_TTY_BEGIN()

    if (!Node_p->isOpen) {NH_TTY_SILENT_END()}

    for (int i = 0; i < Node_p->Children.size; ++i) 
    {
        nh_core_appendToList(List_p, Node_p->Children.pp[i]);
        nh_tty_getLoggerNodes(Node_p->Children.pp[i], List_p);
    }

NH_TTY_SILENT_END()
}

static int nh_tty_getLoggerNodeDepth(
    nh_tty_LoggerNode *Node_p)
{
NH_TTY_BEGIN()

    int depth = 0;
    nh_tty_LoggerNode *Parent_p = Node_p->Parent_p;
    while ((Parent_p = Parent_p->Parent_p) != NULL) {
        depth++;
    }

NH_TTY_END(depth)
}

static int nh_tty_getCategoryListingWidth(
    nh_tty_Logger *Logger_p)
{
NH_TTY_BEGIN()

    nh_List Nodes = nh_core_initList(16);
    nh_tty_getLoggerNodes(&Logger_p->Root, &Nodes);

    int maxWidth = 0;
    nh_tty_LoggerNode *Node_p = NULL;
    for (int i = 0; (Node_p = nh_core_getFromList(&Nodes, i)) != NULL; ++i) {
        int width = (nh_tty_getLoggerNodeDepth(Node_p) * 2) + strlen(Node_p->LoggerNode_p->name_p);
        if (width > maxWidth) {
            maxWidth = width;
        }
    }

    nh_core_freeList(&Nodes, NH_FALSE);

NH_TTY_END(maxWidth + 2)
}

static NH_TTY_RESULT nh_tty_updateLogger(
    nh_tty_Program *Program_p)
{
NH_TTY_BEGIN()

    nh_tty_Logger *Logger_p = Program_p->handle_p;

    nh_SystemTime Now = nh_core_getSystemTime();
    if (nh_core_getSystemTimeDiffInSeconds(Logger_p->LastUpdate, Now) < Logger_p->updateIntervalInSeconds) {
        NH_TTY_DIAGNOSTIC_END(NH_TTY_SUCCESS)
    }

    NH_BOOL init = Logger_p->Root.Children.size == 0;

    nh_tty_updateLoggerNode(&NH_LOGGER.Root, &Logger_p->Root);

    if (init && Logger_p->Root.Children.size > 0) {
        ((nh_tty_LoggerNode*)Logger_p->Root.Children.pp[0])->isCurrent = NH_TRUE;
    }

    Logger_p->listingWidth = nh_tty_getCategoryListingWidth(Logger_p);
    Logger_p->LastUpdate = Now;

    // force screen refresh
    Program_p->refresh = NH_TRUE;

NH_TTY_DIAGNOSTIC_END(NH_TTY_SUCCESS)
}

// INPUT ===========================================================================================

static nh_List nh_tty_getSelectedLoggerNodes(
    nh_tty_Logger *Logger_p)
{
NH_TTY_BEGIN()

    nh_List SelectedNodes = nh_core_initList(8);
    nh_List Nodes = nh_core_initList(32);
    nh_tty_getLoggerNodes(&Logger_p->Root, &Nodes);

    for (int i = 0; i < Nodes.size; ++i) {
        if (((nh_tty_LoggerNode*)Nodes.pp[i])->isSelected) {
            nh_core_appendToList(&SelectedNodes, Nodes.pp[i]);
        }
    }

    nh_core_freeList(&Nodes, NH_FALSE);

NH_TTY_END(SelectedNodes)
}

static void nh_tty_resetLoggerFocuses(
    nh_tty_Logger *Logger_p)
{
NH_TTY_BEGIN()

    nh_List SelectedNodes = nh_tty_getSelectedLoggerNodes(Logger_p);
    for (int i = 0; i < SelectedNodes.size; ++i) {
        ((nh_tty_LoggerNode*)SelectedNodes.pp[i])->hasFocus = NH_FALSE;
    }
    nh_core_freeList(&SelectedNodes, NH_FALSE);

NH_TTY_SILENT_END()
}

static nh_tty_LoggerNode *nh_tty_getFocusedLoggerNode(
    nh_tty_Logger *Logger_p)
{
NH_TTY_BEGIN()

    nh_List SelectedNodes = nh_tty_getSelectedLoggerNodes(Logger_p);
    if (SelectedNodes.size <= 0) {NH_TTY_END(NULL)}

    int focus;
    for (focus = 0; focus < SelectedNodes.size && !((nh_tty_LoggerNode*)SelectedNodes.pp[focus])->hasFocus; ++focus);
    nh_tty_LoggerNode *Node_p = SelectedNodes.pp[focus];

    nh_core_freeList(&SelectedNodes, NH_FALSE);

NH_TTY_END(Node_p)
}

static nh_tty_LoggerNode *nh_tty_getCurrentLoggerNode(
    nh_tty_LoggerNode *Node_p)
{
NH_TTY_BEGIN()

    if (Node_p->isCurrent) {
        NH_TTY_END(Node_p)
    }
    else
    {
        for (int i = 0; Node_p->isOpen && i < Node_p->Children.size; ++i) 
        {
            nh_tty_LoggerNode *Result_p = 
                nh_tty_getCurrentLoggerNode(Node_p->Children.pp[i]);
            if (Result_p != NULL) {NH_TTY_END(Result_p)}
        }
    }

NH_TTY_END(NULL)
}

static void nh_tty_moveCursorVertically(
    nh_tty_Program *Program_p, nh_tty_LoggerNode *Current_p, int key) 
{
NH_TTY_BEGIN()

    nh_tty_Logger *Logger_p = Program_p->handle_p;

    nh_List Nodes = nh_core_initList(16);
    nh_tty_getLoggerNodes(&Logger_p->Root, &Nodes);
    int index;
    for (index = 0; index < Nodes.size && Nodes.pp[index] != Current_p; ++index);

    switch (key) 
    {
        case 'w' :
            if (index > 0) 
            {
                Current_p->isCurrent = NH_FALSE;
                ((nh_tty_LoggerNode*)Nodes.pp[index - 1])->isCurrent = NH_TRUE;

                if (Logger_p->View.screenCursor == 0 && Logger_p->View.rowOffset > 0) {Logger_p->View.rowOffset--;}
                else if (Logger_p->View.screenCursor > 0) {Logger_p->View.screenCursor--;}
            }
            break;
        case 's' :
            if (Nodes.size > index + 1) 
            {
                Current_p->isCurrent = NH_FALSE;
                ((nh_tty_LoggerNode*)Nodes.pp[index + 1])->isCurrent = NH_TRUE;

                if (Logger_p->View.screenCursor < Logger_p->View.height - 1) {Logger_p->View.screenCursor++;}
                else {Logger_p->View.rowOffset++;}
            }
            break;
    }

    nh_core_freeList(&Nodes, NH_FALSE);

NH_TTY_SILENT_END()
}

static void nh_tty_unselectLoggerNode(
    nh_tty_Logger *Logger_p, nh_tty_LoggerNode *Selected_p)
{
NH_TTY_BEGIN()

    nh_List SelectedNodes = nh_tty_getSelectedLoggerNodes(Logger_p);
    
    if (SelectedNodes.size > 1 && Selected_p->hasFocus) 
    {
        int index;
        for (index = 0; index < SelectedNodes.size && SelectedNodes.pp[index] != Selected_p; ++index);

        if (index == 0) {((nh_tty_LoggerNode*)SelectedNodes.pp[SelectedNodes.size - 1])->hasFocus = NH_TRUE;}
        else if (index == SelectedNodes.size - 1) {
            ((nh_tty_LoggerNode*)SelectedNodes.pp[0])->hasFocus = NH_TRUE;
        }
        else {
            ((nh_tty_LoggerNode*)SelectedNodes.pp[index - 1])->hasFocus = NH_TRUE;
        }
    }

    Selected_p->isSelected = NH_FALSE;
    Selected_p->hasFocus = NH_FALSE;

    nh_core_freeList(&SelectedNodes, NH_FALSE);

NH_TTY_SILENT_END()
}

static void nh_tty_changeFocus(
    nh_tty_Logger *Logger_p, int c)
{
NH_TTY_BEGIN()

    nh_List SelectedNodes = nh_tty_getSelectedLoggerNodes(Logger_p);
    if (SelectedNodes.size <= 1) {NH_TTY_SILENT_END()}

    int focus;
    for (focus = 0; focus < SelectedNodes.size && !((nh_tty_LoggerNode*)SelectedNodes.pp[focus])->hasFocus; ++focus);

    switch (c) 
    {
        case 'f' :
            if (focus > 0) {
                ((nh_tty_LoggerNode*)SelectedNodes.pp[focus])->hasFocus = NH_FALSE;
                ((nh_tty_LoggerNode*)SelectedNodes.pp[focus - 1])->hasFocus = NH_TRUE;
            }
            break;
        case 'g' :
            if (focus < SelectedNodes.size - 1) {
                ((nh_tty_LoggerNode*)SelectedNodes.pp[focus])->hasFocus = NH_FALSE;
                ((nh_tty_LoggerNode*)SelectedNodes.pp[focus + 1])->hasFocus = NH_TRUE;
            }
            break;
    }

    nh_core_freeList(&SelectedNodes, NH_FALSE);

NH_TTY_SILENT_END()
}

static NH_TTY_RESULT nh_tty_handleLoggerInput(
    nh_tty_Program *Program_p, nh_wsi_Event Event)
{
NH_TTY_BEGIN()

    if (Event.type != NH_WSI_EVENT_KEYBOARD) {
        NH_TTY_END(NH_TTY_SUCCESS)
    }

    if (Event.Keyboard.trigger != NH_WSI_TRIGGER_PRESS) {NH_TTY_DIAGNOSTIC_END(NH_TTY_SUCCESS)}

    NH_ENCODING_UTF32 c = Event.Keyboard.codepoint;

    nh_tty_Logger *Logger_p = Program_p->handle_p;
    nh_tty_LoggerNode *Current_p = nh_tty_getCurrentLoggerNode(&Logger_p->Root);
    if (Current_p == NULL) {NH_TTY_DIAGNOSTIC_END(NH_TTY_SUCCESS)}

    nh_tty_LoggerNode *Node_p = nh_tty_getFocusedLoggerNode(Logger_p);

    switch (c)
    {
        case 'w' :
        case 's' :
            nh_tty_moveCursorVertically(Program_p, Current_p, c);
            break;

        case 'f' :
        case 'g' :
            nh_tty_changeFocus(Logger_p, c);
            break;

        case 'h' :
            if (Node_p != NULL && Node_p->peak > 0) {Node_p->peak--;}
            break;
        case 'l' :
            if (Node_p != NULL) {Node_p->peak++;}
            break;

        case 'j' :
            if (Node_p != NULL && Node_p->LoggerNode_p->Messages.size > Node_p->focusedRow + 1) {
                Node_p->focusedRow++;
                Node_p->peak = 0;
            }
            break;
        case 'k' :
            if (Node_p != NULL) {
                Node_p->focusedRow--;
                Node_p->peak = 0;
            }
            break;

        case 'a' :
            if (Current_p->isSelected) {
                nh_tty_unselectLoggerNode(Logger_p, Current_p);
            }
            else if (Current_p->Parent_p->Parent_p != NULL) 
            {
                for (int i = 0; i < Current_p->Parent_p->Children.size; ++i) 
                {
                    nh_tty_LoggerNode *Sibling_p = Current_p->Parent_p->Children.pp[i];
                    if (Sibling_p->isSelected) {
                        nh_tty_unselectLoggerNode(Logger_p, Sibling_p);
                    } 
                    Sibling_p->isCurrent = NH_FALSE;
                }
                Current_p->Parent_p->isOpen = NH_FALSE;
                Current_p->Parent_p->isCurrent = NH_TRUE;
            }
            break;

        case 'd' :

            Current_p->isOpen = NH_TRUE;

            if (Current_p->LoggerNode_p->Messages.size == 0) {
                Logger_p->listingWidth = nh_tty_getCategoryListingWidth(Logger_p);
            }
            else {
                nh_tty_resetLoggerFocuses(Logger_p);
                Current_p->isSelected = NH_TRUE;
                Current_p->hasFocus = NH_TRUE;
            }
            break;

        case CTRL_KEY('b') :
            Logger_p->showCategories = !Logger_p->showCategories; 
            break;
    }
 
    Program_p->refresh = NH_TRUE;

NH_TTY_END(NH_TTY_SUCCESS)
}

// DRAW ============================================================================================

static void nh_tty_setNextGlyph(
    nh_tty_Glyph **Glyphs_pp, NH_ENCODING_UTF32 codepoint)
{
NH_TTY_BEGIN()

    nh_tty_Glyph Glyph;
    memset(&Glyph, 0, sizeof(nh_tty_Glyph));
    Glyph.Attributes.reverse = NH_FALSE;
    Glyph.codepoint = codepoint;
 
    (*Glyphs_pp)[0] = Glyph;
    (*Glyphs_pp) = (*Glyphs_pp)+1;

NH_TTY_SILENT_END()
}

static const NH_BYTE *help_pp[] =
{
    "",
    "General Controls                             ",
    "---------------------------------------------",
    "[w][a][s][d] Navigate logging categories.    ",
    "[h][j][k][l] Navigate log entries.           ",
    "[f][g]       Jump to left/right selected log.",
    "[c]          Copy selected log entry.        ",
    "[b]          Toggle logging categories.      ",
    "",
};

static NH_TTY_RESULT nh_tty_drawHelp(
    nh_tty_Glyph **Glyphs_pp, int row, int cols, int rows)
{
NH_TTY_BEGIN()

    int entries = sizeof(help_pp) / sizeof(help_pp[0]);
    int begin = (rows / 2) - (entries / 2);

    if (row >= begin && row < begin + entries) {
        int sides = cols < strlen(help_pp[row-begin]) ? 0 
            : (cols - strlen(help_pp[row - begin])) / 2;
        for (int i = 0; i < sides; ++i) {
            nh_tty_setNextGlyph(Glyphs_pp, ' ');
        }
        for (int i = 0; i < strlen(help_pp[row - begin]) && i < cols; ++i) {
            nh_tty_setNextGlyph(Glyphs_pp, help_pp[row - begin][i]);
        }
    }
    else {
        for (int i = 0; i < cols; ++i) {
            nh_tty_setNextGlyph(Glyphs_pp, ' ');
        }
    }

NH_TTY_DIAGNOSTIC_END(NH_TTY_SUCCESS)
}

static NH_TTY_RESULT nh_tty_drawSelected(
    nh_tty_Logger *Logger_p, nh_tty_Glyph **Glyphs_pp, int row, int cols, int rows)
{
NH_TTY_BEGIN()

    nh_List SelectedNodes = nh_tty_getSelectedLoggerNodes(Logger_p);
    cols = SelectedNodes.size > 0 ? cols / SelectedNodes.size : cols;

    for (int i = 0; i < SelectedNodes.size; ++i)
    {
        nh_tty_LoggerNode *SelectedNode_p = SelectedNodes.pp[i]; 

        if (SelectedNode_p->focusedRow > rows - 1) {
            SelectedNode_p->offset++;
            SelectedNode_p->focusedRow = rows - 1;
        }
        else if (SelectedNode_p->focusedRow < 0) {
            if (SelectedNode_p->offset > 0) {SelectedNode_p->offset--;}
            SelectedNode_p->focusedRow = 0;
        }

        nh_List *Messages_p = &SelectedNode_p->LoggerNode_p->Messages;
        NH_BYTE *message_p = nh_core_getFromList(Messages_p, row + SelectedNode_p->offset);

        if (message_p != NULL) 
        {
            if (SelectedNode_p->hasFocus && SelectedNode_p->focusedRow == row && strlen(message_p) > cols) {
                for (int i = 0; i < SelectedNode_p->peak && strlen(message_p) > cols; ++i) {
                    message_p = message_p + (cols - 1);
                }
            }

            if (SelectedNode_p->hasFocus && SelectedNode_p->focusedRow == row) {
                nh_tty_setNextGlyph(Glyphs_pp, '>');
            }
            else {
                nh_tty_setNextGlyph(Glyphs_pp, ' ');
            }

            int length = strlen(message_p) + 1 > cols ? cols - 1: strlen(message_p);
            for (int i = 0; i < length; ++i) {
                nh_tty_setNextGlyph(Glyphs_pp, message_p[i]);
            }
 
            for (int j = 0; j < cols - (length + 1); ++j) {
                nh_tty_setNextGlyph(Glyphs_pp, ' ');
            }
        }
        else {
            for (int j = 0; j < cols; ++j) {nh_tty_setNextGlyph(Glyphs_pp, ' ');}
        }
    }

    if (SelectedNodes.size == 0) {nh_tty_drawHelp(Glyphs_pp, row, cols, rows);}

    nh_core_freeList(&SelectedNodes, NH_FALSE);

NH_TTY_DIAGNOSTIC_END(NH_TTY_SUCCESS)
}

static NH_TTY_RESULT nh_tty_drawLoggerRow(
    nh_tty_Program *Program_p, nh_tty_Glyph *Glyphs_p, int width, int height, int row)
{
NH_TTY_BEGIN()

    nh_tty_Logger *Logger_p = Program_p->handle_p;
    Logger_p->View.height = height;

    int tmp = -1;
    nh_List Nodes = nh_core_initList(16);
    nh_tty_getLoggerNodes(&Logger_p->Root, &Nodes);
    nh_tty_LoggerNode *Node_p = nh_core_getFromList(&Nodes, row + Logger_p->View.rowOffset);

    nh_tty_Glyph *Tmp_p = Glyphs_p;
    for (int i = 0; i < width; ++i) {
        nh_tty_setNextGlyph(&Glyphs_p, ' ');
    }
    Glyphs_p = Tmp_p;
 
    if (Logger_p->showCategories)
    {
        if (Node_p != NULL && row < Nodes.size) 
        {
            int offset = nh_tty_getLoggerNodeDepth(Node_p);
            for (int i = 0; i < offset; ++i) {
                nh_tty_setNextGlyph(&Glyphs_p, ' ');
                nh_tty_setNextGlyph(&Glyphs_p, ' ');
            }
            offset *= 2;
            offset += 1;

            if (Node_p->isCurrent) {nh_tty_setNextGlyph(&Glyphs_p, '>');}
            else if (Node_p->isSelected) {nh_tty_setNextGlyph(&Glyphs_p, '>');}
            else {nh_tty_setNextGlyph(&Glyphs_p, ' ');}

            for (int i = 0; i < strlen(Node_p->LoggerNode_p->name_p); ++i) {
                nh_tty_setNextGlyph(&Glyphs_p, Node_p->LoggerNode_p->name_p[i]);
            }

            for (int i = 0; i < Logger_p->listingWidth - (strlen(Node_p->LoggerNode_p->name_p) + offset); ++i) {
                nh_tty_setNextGlyph(&Glyphs_p, ' ');
            }
        }
        else {
            for (int i = 0; i < Logger_p->listingWidth; ++i) {
                nh_tty_setNextGlyph(&Glyphs_p, ' ');
            }
        }

        NH_TTY_CHECK(nh_tty_drawSelected(Logger_p, &Glyphs_p, row, width - (Logger_p->listingWidth), height))
    }
    else {NH_TTY_CHECK(nh_tty_drawSelected(Logger_p, &Glyphs_p, row, width, height))}

    nh_core_freeList(&Nodes, NH_FALSE);

NH_TTY_DIAGNOSTIC_END(NH_TTY_SUCCESS)
}

// INIT/DESTROY ====================================================================================

static void *nh_tty_initLogger(
    void *arg_p)
{
NH_TTY_BEGIN()

    nh_tty_Logger *Logger_p = nh_core_allocate(sizeof(nh_tty_Logger));
    NH_TTY_CHECK_MEM_2(NULL, Logger_p)

    memset(&Logger_p->View, 0, sizeof(nh_tty_LoggerView));

    Logger_p->showCategories = NH_TRUE;
    Logger_p->listingWidth   = 0;
    Logger_p->LastUpdate     = nh_core_getSystemTime();
    Logger_p->updateIntervalInSeconds = 1.0;

    Logger_p->Root.LoggerNode_p = &NH_LOGGER.Root;
    Logger_p->Root.isOpen       = NH_TRUE;
    Logger_p->Root.isCurrent    = NH_FALSE;
    Logger_p->Root.Children     = nh_core_initList(4);
    Logger_p->Root.Parent_p     = NULL;

NH_TTY_END(Logger_p)
}

static void nh_tty_destroyLogger(
    void *handle_p)
{
NH_TTY_BEGIN()

    nh_core_free(handle_p);

NH_TTY_SILENT_END()
}

// PROTOTYPE =======================================================================================

typedef enum NH_TTY_LOGGER_COMMAND_E {
    NH_TTY_LOGGER_COMMAND_E_COUNT = 0,
} NH_TTY_LOGGER_COMMAND_E;

static void nh_tty_destroyLoggerPrototype(
    nh_tty_ProgramPrototype *Prototype_p)
{
NH_TTY_BEGIN()

    nh_encoding_freeUTF32(&Prototype_p->Name);
    nh_core_free(Prototype_p);

NH_TTY_SILENT_END()
}

nh_tty_ProgramPrototype *nh_tty_createLoggerPrototype()
{
NH_TTY_BEGIN()

    nh_tty_ProgramPrototype *Prototype_p = nh_core_allocate(sizeof(nh_tty_ProgramPrototype));
    NH_TTY_CHECK_MEM_2(NULL, Prototype_p)

    memset(Prototype_p, 0, sizeof(nh_tty_ProgramPrototype));

    Prototype_p->Callbacks.init_f = nh_tty_initLogger;
    Prototype_p->Callbacks.draw_f = nh_tty_drawLoggerRow;
    Prototype_p->Callbacks.handleInput_f = nh_tty_handleLoggerInput;
    Prototype_p->Callbacks.update_f = nh_tty_updateLogger;
    Prototype_p->Callbacks.destroyPrototype_f = nh_tty_destroyLoggerPrototype;
    Prototype_p->Callbacks.destroy_f = nh_tty_destroyLogger;

    NH_ENCODING_UTF32 name_p[7] = {'l', 'o', 'g', 'g', 'e', 'r'};
    Prototype_p->Name = nh_encoding_initUTF32(6);
    NH_ENCODING_CHECK_2(NULL, nh_encoding_appendUTF32(&Prototype_p->Name, name_p, 6))

 //   nh_encoding_UTF32String *CommandNames_p =
 //       nh_core_allocate(sizeof(nh_encoding_UTF32String)*NH_TTY_LOGGER_COMMAND_E_COUNT);
 //   NH_TTY_CHECK_MEM_2(NULL, CommandNames_p)

 //   NH_ENCODING_UTF32 command1_p[7] = {'p', 'r', 'e', 'v', 'i', 'e', 'w'};
 //   NH_ENCODING_UTF32 command2_p[4] = {'t', 'r', 'e', 'e'};
 //   NH_ENCODING_UTF32 command3_p[3] = {'n', 'e', 'w'};

 //   CommandNames_p[NH_TTY_LOGGER_COMMAND_TAG] = nh_encoding_initUTF32(7);
 //   CommandNames_p[NH_TTY_LOGGER_COMMAND_UNTAG] = nh_encoding_initUTF32(4);
 //   CommandNames_p[NH_TTY_LOGGER_COMMAND_LOAD] = nh_encoding_initUTF32(3);

 //   NH_ENCODING_CHECK_2(NULL, nh_encoding_appendUTF32(&CommandNames_p[NH_TTY_LOGGER_COMMAND_TAG], command1_p, 7))
 //   NH_ENCODING_CHECK_2(NULL, nh_encoding_appendUTF32(&CommandNames_p[NH_TTY_LOGGER_COMMAND_UNTAG], command2_p, 4))
 //   NH_ENCODING_CHECK_2(NULL, nh_encoding_appendUTF32(&CommandNames_p[NH_TTY_LOGGER_COMMAND_LOAD], command3_p, 3))

    Prototype_p->CommandNames_p = NULL;
    Prototype_p->commands = NH_TTY_LOGGER_COMMAND_E_COUNT;

NH_TTY_END(Prototype_p)
}
