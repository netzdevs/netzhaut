// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

// INCLUDES =======================================================================================

#include "Surface.h"

#include "../Base/Surface.h"
#include "../Common/Macros.h"

#include "../../nhcore/System/Thread.h"
#include "../../nhcore/System/Memory.h"
#include "../../nhcore/Util/Array.h"

#include "../../nhwsi/Window/Window.h"
#include "../../nhwsi/Platforms/X11/Init.h"

#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <X11/extensions/Xrender.h>

// INIT ============================================================================================

nh_opengl_Surface nh_opengl_initSurface()
{
NH_GFX_BEGIN()

    nh_opengl_Surface Surface;
    Surface.Context_p = NULL;

NH_GFX_END(Surface)
}

// CREATE ==========================================================================================

/**
 * GLX_DRAWABLE_TYPE is probably a hack, i had serious perfomance issues with just the GLX_WINDOW_BIT
 * after resizing the window.
 */
static int VISUAL_DATA_P[] = {
    GLX_RENDER_TYPE, GLX_RGBA_BIT,
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT | GLX_PIXMAP_BIT | GLX_PBUFFER_BIT,
    GLX_DOUBLEBUFFER, True,
    GLX_RED_SIZE, 8,
    GLX_GREEN_SIZE, 8,
    GLX_BLUE_SIZE, 8,
    GLX_ALPHA_SIZE, 8,
    GLX_DEPTH_SIZE, 16,
    None
};

typedef GLXContext (*glXCreateContextAttribsARBProc)
    (Display*, GLXFBConfig, GLXContext, Bool, const int*);

static NH_GFX_RESULT nh_opengl_createOpenGLContext(
    nh_opengl_Surface *Surface_p, nh_wsi_Window *Window_p)
{
NH_GFX_BEGIN()

    int count = 0;
    GLXFBConfig *FrameBufferConfigurations_p = 
        glXChooseFBConfig(Window_p->X11.Common_p->Display_p, Window_p->X11.Common_p->screen, VISUAL_DATA_P, &count);

    GLXFBConfig FrameBufferConfiguration_p = NULL; 

    for (int i = 0; i < count; i++) {
        XVisualInfo *Info_p = (XVisualInfo*) 
            glXGetVisualFromFBConfig(Window_p->X11.Common_p->Display_p, FrameBufferConfigurations_p[i]);
        // We need to use the FBC that relates to the Visual that was used for window creation.
        if (Info_p->visualid == Window_p->X11.Info.visualid) {
            XFree(Info_p);
            FrameBufferConfiguration_p = FrameBufferConfigurations_p[i];
            break;
        }
        XFree(Info_p);
    }

    if (!FrameBufferConfiguration_p) {
        NH_GFX_DIAGNOSTIC_END(NH_GFX_ERROR_BAD_STATE)
    }
 
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB_f = 0;
    glXCreateContextAttribsARB_f = (glXCreateContextAttribsARBProc)
        glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");

    if (!glXCreateContextAttribsARB_f) {
        NH_GFX_DIAGNOSTIC_END(NH_GFX_ERROR_BAD_STATE)
    }

    /* Set desired minimum OpenGL version */
    static int contextAttributes_p[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 6,
        None
    };

    /* Create modern OpenGL context */
    Surface_p->Context_p = glXCreateContextAttribsARB_f(
        Window_p->X11.Common_p->Display_p, FrameBufferConfiguration_p, NULL, true, contextAttributes_p);

    if (!Surface_p->Context_p) {
        NH_GFX_DIAGNOSTIC_END(NH_GFX_ERROR_BAD_STATE)
    }

    XFree(FrameBufferConfigurations_p);

NH_GFX_DIAGNOSTIC_END(NH_GFX_SUCCESS)
}

NH_GFX_RESULT nh_opengl_createSurface(
    nh_opengl_Surface *Surface_p, nh_wsi_Window *Window_p)
{
NH_GFX_BEGIN()

    NH_GFX_CHECK(nh_opengl_createOpenGLContext(Surface_p, Window_p))

    int bufferCount = 3;

    Surface_p->CommandBuffers_p = nh_core_allocate(sizeof(nh_opengl_CommandBuffer)*bufferCount);
    NH_GFX_CHECK_MEM(Surface_p->CommandBuffers_p)

    Surface_p->bufferCount = bufferCount;
    Surface_p->currentBuffer = 0;

    for (int i = 0; i < Surface_p->bufferCount; ++i) {
         Surface_p->CommandBuffers_p[i] = nh_opengl_initCommandBuffer();
    }

NH_GFX_END(NH_GFX_SUCCESS)
}

// DESTROY =========================================================================================

NH_GFX_RESULT nh_opengl_destroySurface(
    nh_opengl_Surface *Surface_p, nh_wsi_Window *Window_p)
{
NH_GFX_BEGIN()

    glXDestroyContext(Window_p->X11.Common_p->Display_p, Surface_p->Context_p);
    nh_core_free(Surface_p->CommandBuffers_p);
    
NH_GFX_END(NH_GFX_SUCCESS)
}

// REQUIREMENTS ====================================================================================

NH_GFX_RESULT nh_opengl_createSurfaceRequirements(
    nh_opengl_SurfaceRequirements *Requirements_p)
{
NH_GFX_BEGIN()

    Requirements_p->Ids = nh_core_initArray(sizeof(VisualID), 8);

    Display *Display_p = XOpenDisplay(NULL);

    int count = 0;
    GLXFBConfig *FrameBufferConfigurations_p = 
        glXChooseFBConfig(Display_p, DefaultScreen(Display_p), VISUAL_DATA_P, &count);

    for (int i = 0; i < count; i++) {
        XVisualInfo *Visual_p = 
            (XVisualInfo*) glXGetVisualFromFBConfig(Display_p, FrameBufferConfigurations_p[i]);
        if (!Visual_p) {continue;}

        XRenderPictFormat *Format_p = XRenderFindVisualFormat(Display_p, Visual_p->visual);
        if (!Format_p) {
            XFree(Visual_p);
            continue;
        }

        // We need a framebuffer with alpha capabilities.
        if (Format_p->direct.alphaMask > 0) {
            nh_core_appendToArray(&Requirements_p->Ids, &Visual_p->visualid, 1);
        }

        XFree(Visual_p);
    }

    XFree(FrameBufferConfigurations_p);
    XCloseDisplay(Display_p);

NH_GFX_END(NH_GFX_SUCCESS)
}

NH_GFX_RESULT nh_opengl_freeSurfaceRequirements(
    nh_opengl_SurfaceRequirements *Requirements_p)
{
NH_GFX_BEGIN()

    nh_core_freeArray(&Requirements_p->Ids);

NH_GFX_END(NH_GFX_SUCCESS)
}

