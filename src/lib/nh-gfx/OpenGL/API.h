#ifndef NH_OPENGL_API_H
#define NH_OPENGL_API_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

#include "../Common/Includes.h"

#endif

/** @addtogroup lib_nh-gfx_vars
 *  @{
 */

    extern const char *NH_GFX_OPENGL_COMMAND_NAMES_PP[];
    extern size_t NH_GFX_OPENGL_COMMAND_NAMES_PP_COUNT;

    extern const int NH_GFX_OPENGL_COMMAND_PARAMETER_COUNTS_P[];
    extern size_t NH_GFX_OPENGL_COMMAND_PARAMETER_COUNTS_P_COUNT;
 
/** @} */

/** @addtogroup lib_nh-gfx_enums
 *  @{
 */

    typedef enum NH_GFX_OPENGL_COMMAND_E {
        NH_GFX_OPENGL_COMMAND_GLACCUM,
        NH_GFX_OPENGL_COMMAND_GLACTIVETEXTURE,
        NH_GFX_OPENGL_COMMAND_GLADDSWAPHINTRECTWIN,
        NH_GFX_OPENGL_COMMAND_GLALPHAFUNC,
        NH_GFX_OPENGL_COMMAND_GLARETEXTURESRESIDENT,
        NH_GFX_OPENGL_COMMAND_GLARRAYELEMENT,
        NH_GFX_OPENGL_COMMAND_GLATTACHSHADER,
        NH_GFX_OPENGL_COMMAND_GLBEGIN,
        NH_GFX_OPENGL_COMMAND_GLEND,
        NH_GFX_OPENGL_COMMAND_GLBINDBUFFER,
        NH_GFX_OPENGL_COMMAND_GLBINDTEXTURE,
        NH_GFX_OPENGL_COMMAND_GLBINDVERTEXARRAY,
        NH_GFX_OPENGL_COMMAND_GLBITMAP,
        NH_GFX_OPENGL_COMMAND_GLBLENDFUNC,
        NH_GFX_OPENGL_COMMAND_GLBUFFERDATA,
        NH_GFX_OPENGL_COMMAND_GLCALLLIST,
        NH_GFX_OPENGL_COMMAND_GLCALLLISTS,
        NH_GFX_OPENGL_COMMAND_GLCLEAR,
        NH_GFX_OPENGL_COMMAND_GLCLEARACCUM,
        NH_GFX_OPENGL_COMMAND_GLCLEARCOLOR,
        NH_GFX_OPENGL_COMMAND_GLCLEARDEPTH,
        NH_GFX_OPENGL_COMMAND_GLCLEARINDEX,
        NH_GFX_OPENGL_COMMAND_GLCLEARSTENCIL,
        NH_GFX_OPENGL_COMMAND_GLCLIPPLANE,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3B,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3D,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3F,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3I,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3S,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3UB,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3UI,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3US,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4B,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4D,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4F,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4I,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4S,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4UB,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4UI,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4US,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3BV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3DV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3FV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3IV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3SV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3UBV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3UIV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR3USV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4BV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4DV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4FV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4IV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4SV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4UBV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4UIV,
        NH_GFX_OPENGL_COMMAND_GLCOLOR4USV,
        NH_GFX_OPENGL_COMMAND_GLCOLORMASK,
        NH_GFX_OPENGL_COMMAND_GLCOLORMATERIAL,
        NH_GFX_OPENGL_COMMAND_GLCOLORPOINTER,
        NH_GFX_OPENGL_COMMAND_GLCOLORTABLEEXT,
        NH_GFX_OPENGL_COMMAND_GLCOLORSUBTABLEEXT,
        NH_GFX_OPENGL_COMMAND_GLCOMPILESHADER,
        NH_GFX_OPENGL_COMMAND_GLCOPYPIXELS,
        NH_GFX_OPENGL_COMMAND_GLCOPYTEXIMAGE1D,
        NH_GFX_OPENGL_COMMAND_GLCOPYTEXIMAGE2D,
        NH_GFX_OPENGL_COMMAND_GLCOPYTEXSUBIMAGE1D,
        NH_GFX_OPENGL_COMMAND_GLCOPYTEXSUBIMAGE2D,
        NH_GFX_OPENGL_COMMAND_GLCREATEPROGRAM,
        NH_GFX_OPENGL_COMMAND_GLCREATESHADER,
        NH_GFX_OPENGL_COMMAND_GLCULLFACE,
        NH_GFX_OPENGL_COMMAND_GLDELETELISTS,
        NH_GFX_OPENGL_COMMAND_GLDELETETEXTURES,
        NH_GFX_OPENGL_COMMAND_GLDEPTHFUNC,
        NH_GFX_OPENGL_COMMAND_GLDEPTHMASK,
        NH_GFX_OPENGL_COMMAND_GLDEPTHRANGE,
        NH_GFX_OPENGL_COMMAND_GLDRAWARRAYS,
        NH_GFX_OPENGL_COMMAND_GLDRAWBUFFER,
        NH_GFX_OPENGL_COMMAND_GLDRAWELEMENTS,
        NH_GFX_OPENGL_COMMAND_GLDRAWPIXELS,
        NH_GFX_OPENGL_COMMAND_GLEDGEFLAG,
        NH_GFX_OPENGL_COMMAND_GLEDGEFLAGV,
        NH_GFX_OPENGL_COMMAND_GLEDGEFLAGPOINTER,
        NH_GFX_OPENGL_COMMAND_GLENABLE,
        NH_GFX_OPENGL_COMMAND_GLENABLEVERTEXATTRIBARRAY,
        NH_GFX_OPENGL_COMMAND_GLDISABLE,
        NH_GFX_OPENGL_COMMAND_GLENABLECLIENTSTATE,
        NH_GFX_OPENGL_COMMAND_GLDISABLECLIENTSTATE,
        NH_GFX_OPENGL_COMMAND_GLEVALCOORD1D,
        NH_GFX_OPENGL_COMMAND_GLEVALCOORD1F,
        NH_GFX_OPENGL_COMMAND_GLEVALCOORD2D,
        NH_GFX_OPENGL_COMMAND_GLEVALCOORD2F,
        NH_GFX_OPENGL_COMMAND_GLEVALCOORD1DV,
        NH_GFX_OPENGL_COMMAND_GLEVALCOORD2DV,
        NH_GFX_OPENGL_COMMAND_GLEVALCOORD1FV,
        NH_GFX_OPENGL_COMMAND_GLEVALCOORD2FV,
        NH_GFX_OPENGL_COMMAND_GLEVALMESH1,
        NH_GFX_OPENGL_COMMAND_GLEVALMESH2,
        NH_GFX_OPENGL_COMMAND_GLEVALPOINT1,
        NH_GFX_OPENGL_COMMAND_GLEVALPOINT2,
        NH_GFX_OPENGL_COMMAND_GLFEEDBACKBUFFER,
        NH_GFX_OPENGL_COMMAND_GLFINISH,
        NH_GFX_OPENGL_COMMAND_GLFLUSH,
        NH_GFX_OPENGL_COMMAND_GLFOGF,
        NH_GFX_OPENGL_COMMAND_GLFOGI,
        NH_GFX_OPENGL_COMMAND_GLFOGFV,
        NH_GFX_OPENGL_COMMAND_GLFOGIV,
        NH_GFX_OPENGL_COMMAND_GLFRONTFACE,
        NH_GFX_OPENGL_COMMAND_GLFRUSTUM,
        NH_GFX_OPENGL_COMMAND_GLGENBUFFERS,
        NH_GFX_OPENGL_COMMAND_GLGENLISTS,
        NH_GFX_OPENGL_COMMAND_GLGENTEXTURES,
        NH_GFX_OPENGL_COMMAND_GLGENVERTEXARRAYS,
        NH_GFX_OPENGL_COMMAND_GLGETBOOLEANV,
        NH_GFX_OPENGL_COMMAND_GLGETCLIPPLANE,
        NH_GFX_OPENGL_COMMAND_GLGETCOLORTABLEEXT,
        NH_GFX_OPENGL_COMMAND_GLGETCOLORTABLEPARAMETERFVEXT,
        NH_GFX_OPENGL_COMMAND_GLGETCOLORTABLEPARAMETERIVEXT,
        NH_GFX_OPENGL_COMMAND_GLGETDOUBLEV,
        NH_GFX_OPENGL_COMMAND_GLGETERROR,
        NH_GFX_OPENGL_COMMAND_GLGETFLOATV,
        NH_GFX_OPENGL_COMMAND_GLGETINTEGERV,
        NH_GFX_OPENGL_COMMAND_GLGETLIGHTFV,
        NH_GFX_OPENGL_COMMAND_GLGETLIGHTIV,
        NH_GFX_OPENGL_COMMAND_GLGETMAPDV,
        NH_GFX_OPENGL_COMMAND_GLGETMAPFV,
        NH_GFX_OPENGL_COMMAND_GLGETMAPIV,
        NH_GFX_OPENGL_COMMAND_GLGETMATERIALFV,
        NH_GFX_OPENGL_COMMAND_GLGETMATERIALIV,
        NH_GFX_OPENGL_COMMAND_GLGETPIXELMAPFV,
        NH_GFX_OPENGL_COMMAND_GLGETPIXELMAPUIV,
        NH_GFX_OPENGL_COMMAND_GLGETPIXELMAPUSV,
        NH_GFX_OPENGL_COMMAND_GLGETPOINTERV,
        NH_GFX_OPENGL_COMMAND_GLGETPOLYGONSTIPPLE,
        NH_GFX_OPENGL_COMMAND_GLGETSTRING,
        NH_GFX_OPENGL_COMMAND_GLGETTEXENVFV,
        NH_GFX_OPENGL_COMMAND_GLGETTEXENVIV,
        NH_GFX_OPENGL_COMMAND_GLGETTEXGENDV,
        NH_GFX_OPENGL_COMMAND_GLGETTEXGENFV,
        NH_GFX_OPENGL_COMMAND_GLGETTEXGENIV,
        NH_GFX_OPENGL_COMMAND_GLGETTEXIMAGE,
        NH_GFX_OPENGL_COMMAND_GLGETTEXLEVELPARAMETERFV,
        NH_GFX_OPENGL_COMMAND_GLGETTEXLEVELPARAMETERIV,
        NH_GFX_OPENGL_COMMAND_GLGETTEXPARAMETERFV,
        NH_GFX_OPENGL_COMMAND_GLGETTEXPARAMETERIV,
        NH_GFX_OPENGL_COMMAND_GLGETUNIFORMLOCATION,
        NH_GFX_OPENGL_COMMAND_GLHINT,
        NH_GFX_OPENGL_COMMAND_GLINDEXD,
        NH_GFX_OPENGL_COMMAND_GLINDEXF,
        NH_GFX_OPENGL_COMMAND_GLINDEXI,
        NH_GFX_OPENGL_COMMAND_GLINDEXS,
        NH_GFX_OPENGL_COMMAND_GLINDEXDV,
        NH_GFX_OPENGL_COMMAND_GLINDEXFV,
        NH_GFX_OPENGL_COMMAND_GLINDEXIV,
        NH_GFX_OPENGL_COMMAND_GLINDEXSV,
        NH_GFX_OPENGL_COMMAND_GLINDEXMASK,
        NH_GFX_OPENGL_COMMAND_GLINDEXPOINTER,
        NH_GFX_OPENGL_COMMAND_GLINITNAMES,
        NH_GFX_OPENGL_COMMAND_GLINTERLEAVEDARRAYS,
        NH_GFX_OPENGL_COMMAND_GLISENABLED,
        NH_GFX_OPENGL_COMMAND_GLISLIST,
        NH_GFX_OPENGL_COMMAND_GLISTEXTURE,
        NH_GFX_OPENGL_COMMAND_GLLIGHTF,
        NH_GFX_OPENGL_COMMAND_GLLIGHTI,
        NH_GFX_OPENGL_COMMAND_GLLIGHTFV,
        NH_GFX_OPENGL_COMMAND_GLLIGHTIV,
        NH_GFX_OPENGL_COMMAND_GLLIGHTMODELF,
        NH_GFX_OPENGL_COMMAND_GLLIGHTMODELFV,
        NH_GFX_OPENGL_COMMAND_GLLIGHTMODELI,
        NH_GFX_OPENGL_COMMAND_GLLIGHTMODELIV,
        NH_GFX_OPENGL_COMMAND_GLLINESTIPPLE,
        NH_GFX_OPENGL_COMMAND_GLLINEWIDTH,
        NH_GFX_OPENGL_COMMAND_GLLINKPROGRAM,
        NH_GFX_OPENGL_COMMAND_GLLISTBASE,
        NH_GFX_OPENGL_COMMAND_GLLOADIDENTITY,
        NH_GFX_OPENGL_COMMAND_GLLOADMATRIXD,
        NH_GFX_OPENGL_COMMAND_GLLOADMATRIXF,
        NH_GFX_OPENGL_COMMAND_GLLOADNAME,
        NH_GFX_OPENGL_COMMAND_GLLOGICOP,
        NH_GFX_OPENGL_COMMAND_GLMAP1D,
        NH_GFX_OPENGL_COMMAND_GLMAP1F,
        NH_GFX_OPENGL_COMMAND_GLMAP2D,
        NH_GFX_OPENGL_COMMAND_GLMAP2F,
        NH_GFX_OPENGL_COMMAND_GLMAPGRID1D,
        NH_GFX_OPENGL_COMMAND_GLMAPGRID1F,
        NH_GFX_OPENGL_COMMAND_GLMAPGRID2D,
        NH_GFX_OPENGL_COMMAND_GLMAPGRID2F,
        NH_GFX_OPENGL_COMMAND_GLMATERIALF,
        NH_GFX_OPENGL_COMMAND_GLMATERIALI,
        NH_GFX_OPENGL_COMMAND_GLMATERIALFV,
        NH_GFX_OPENGL_COMMAND_GLMATERIALIV,
        NH_GFX_OPENGL_COMMAND_GLMATRIXMODE,
        NH_GFX_OPENGL_COMMAND_GLMULTMATRIXD,
        NH_GFX_OPENGL_COMMAND_GLMULTMATRIXF,
        NH_GFX_OPENGL_COMMAND_GLNEWLIST,
        NH_GFX_OPENGL_COMMAND_GLENDLIST,
        NH_GFX_OPENGL_COMMAND_GLNORMAL3B,
        NH_GFX_OPENGL_COMMAND_GLNORMAL3D,
        NH_GFX_OPENGL_COMMAND_GLNORMAL3F,
        NH_GFX_OPENGL_COMMAND_GLNORMAL3I,
        NH_GFX_OPENGL_COMMAND_GLNORMAL3S,
        NH_GFX_OPENGL_COMMAND_GLNORMAL3BV,
        NH_GFX_OPENGL_COMMAND_GLNORMAL3DV,
        NH_GFX_OPENGL_COMMAND_GLNORMAL3FV,
        NH_GFX_OPENGL_COMMAND_GLNORMAL3IV,
        NH_GFX_OPENGL_COMMAND_GLNORMAL3SV,
        NH_GFX_OPENGL_COMMAND_GLNORMALPOINTER,
        NH_GFX_OPENGL_COMMAND_GLORTHO,
        NH_GFX_OPENGL_COMMAND_GLPASSTHROUGH,
        NH_GFX_OPENGL_COMMAND_GLPIXELMAPFV,
        NH_GFX_OPENGL_COMMAND_GLPIXELMAPUIV,
        NH_GFX_OPENGL_COMMAND_GLPIXELMAPUSV,
        NH_GFX_OPENGL_COMMAND_GLPIXELSTOREF,
        NH_GFX_OPENGL_COMMAND_GLPIXELSTOREI,
        NH_GFX_OPENGL_COMMAND_GLPIXELTRANSFERF,
        NH_GFX_OPENGL_COMMAND_GLPIXELTRANSFERI,
        NH_GFX_OPENGL_COMMAND_GLPIXELZOOM,
        NH_GFX_OPENGL_COMMAND_GLPOINTSIZE,
        NH_GFX_OPENGL_COMMAND_GLPOLYGONMODE,
        NH_GFX_OPENGL_COMMAND_GLPOLYGONOFFSET,
        NH_GFX_OPENGL_COMMAND_GLPOLYGONSTIPPLE,
        NH_GFX_OPENGL_COMMAND_GLPRIORITIZETEXTURES,
        NH_GFX_OPENGL_COMMAND_GLPUSHATTRIB,
        NH_GFX_OPENGL_COMMAND_GLPOPATTRIB,
        NH_GFX_OPENGL_COMMAND_GLPUSHCLIENTATTRIB,
        NH_GFX_OPENGL_COMMAND_GLPOPCLIENTATTRIB,
        NH_GFX_OPENGL_COMMAND_GLPUSHMATRIX,
        NH_GFX_OPENGL_COMMAND_GLPOPMATRIX,
        NH_GFX_OPENGL_COMMAND_GLPUSHNAME,
        NH_GFX_OPENGL_COMMAND_GLPOPNAME,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS2D,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS2F,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS2I,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS2S,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS3D,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS3F,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS3I,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS3S,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS4D,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS4F,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS4I,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS4S,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS2DV,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS2FV,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS2IV,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS2SV,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS3DV,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS3FV,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS3IV,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS3SV,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS4DV,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS4FV,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS4IV,
        NH_GFX_OPENGL_COMMAND_GLRASTERPOS4SV,
        NH_GFX_OPENGL_COMMAND_GLREADBUFFER,
        NH_GFX_OPENGL_COMMAND_GLREADPIXELS,
        NH_GFX_OPENGL_COMMAND_GLRECTD,
        NH_GFX_OPENGL_COMMAND_GLRECTF,
        NH_GFX_OPENGL_COMMAND_GLRECTI,
        NH_GFX_OPENGL_COMMAND_GLRECTS,
        NH_GFX_OPENGL_COMMAND_GLRECTDV,
        NH_GFX_OPENGL_COMMAND_GLRECTFV,
        NH_GFX_OPENGL_COMMAND_GLRECTIV,
        NH_GFX_OPENGL_COMMAND_GLRECTSV,
        NH_GFX_OPENGL_COMMAND_GLRENDERMODE,
        NH_GFX_OPENGL_COMMAND_GLROTATED,
        NH_GFX_OPENGL_COMMAND_GLROTATEF,
        NH_GFX_OPENGL_COMMAND_GLSCALED,
        NH_GFX_OPENGL_COMMAND_GLSCALEF,
        NH_GFX_OPENGL_COMMAND_GLSCISSOR,
        NH_GFX_OPENGL_COMMAND_GLSELECTBUFFER,
        NH_GFX_OPENGL_COMMAND_GLSHADEMODEL,
        NH_GFX_OPENGL_COMMAND_GLSHADERSOURCE,
        NH_GFX_OPENGL_COMMAND_GLSTENCILFUNC,
        NH_GFX_OPENGL_COMMAND_GLSTENCILMASK,
        NH_GFX_OPENGL_COMMAND_GLSTENCILOP,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD1D,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD1F,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD1I,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD1S,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD2D,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD2I,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD2S,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD3D,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD3F,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD3I,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD3S,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD4D,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD4F,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD4I,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD4S,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD1DV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD1FV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD1IV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD1SV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD2DV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD2FV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD2IV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD2SV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD3DV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD3FV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD3IV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD3SV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD4DV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD4FV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD4IV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORD4SV,
        NH_GFX_OPENGL_COMMAND_GLTEXCOORDPOINTER,
        NH_GFX_OPENGL_COMMAND_GLTEXENVF,
        NH_GFX_OPENGL_COMMAND_GLTEXENVI,
        NH_GFX_OPENGL_COMMAND_GLTEXENVFV,
        NH_GFX_OPENGL_COMMAND_GLTEXENVIV,
        NH_GFX_OPENGL_COMMAND_GLTEXGEND,
        NH_GFX_OPENGL_COMMAND_GLTEXGENF,
        NH_GFX_OPENGL_COMMAND_GLTEXGENI,
        NH_GFX_OPENGL_COMMAND_GLTEXGENDV,
        NH_GFX_OPENGL_COMMAND_GLTEXGENFV,
        NH_GFX_OPENGL_COMMAND_GLTEXGENIV,
        NH_GFX_OPENGL_COMMAND_GLTEXIMAGE1D,
        NH_GFX_OPENGL_COMMAND_GLTEXIMAGE2D,
        NH_GFX_OPENGL_COMMAND_GLTEXPARAMETERF,
        NH_GFX_OPENGL_COMMAND_GLTEXPARAMETERI,
        NH_GFX_OPENGL_COMMAND_GLTEXPARAMETERFV,
        NH_GFX_OPENGL_COMMAND_GLTEXPARAMETERIV,
        NH_GFX_OPENGL_COMMAND_GLTEXSUBIMAGE1D,
        NH_GFX_OPENGL_COMMAND_GLTEXSUBIMAGE2D,
        NH_GFX_OPENGL_COMMAND_GLTRANSLATED,
        NH_GFX_OPENGL_COMMAND_GLTRANSLATEF,
        NH_GFX_OPENGL_COMMAND_GLUNIFORM1I,
        NH_GFX_OPENGL_COMMAND_GLUNIFORM3F,
        NH_GFX_OPENGL_COMMAND_GLUSEPROGRAM,
        NH_GFX_OPENGL_COMMAND_GLVERTEX2D, 
        NH_GFX_OPENGL_COMMAND_GLVERTEX2F,
        NH_GFX_OPENGL_COMMAND_GLVERTEX2I,
        NH_GFX_OPENGL_COMMAND_GLVERTEX2S,
        NH_GFX_OPENGL_COMMAND_GLVERTEX3D,
        NH_GFX_OPENGL_COMMAND_GLVERTEX3F,
        NH_GFX_OPENGL_COMMAND_GLVERTEX3I,
        NH_GFX_OPENGL_COMMAND_GLVERTEX3S,
        NH_GFX_OPENGL_COMMAND_GLVERTEX4D,
        NH_GFX_OPENGL_COMMAND_GLVERTEX4F,
        NH_GFX_OPENGL_COMMAND_GLVERTEX4I,
        NH_GFX_OPENGL_COMMAND_GLVERTEX4S,
        NH_GFX_OPENGL_COMMAND_GLVERTEX2DV, 
        NH_GFX_OPENGL_COMMAND_GLVERTEX2FV,
        NH_GFX_OPENGL_COMMAND_GLVERTEX2IV,
        NH_GFX_OPENGL_COMMAND_GLVERTEX2SV,
        NH_GFX_OPENGL_COMMAND_GLVERTEX3DV,
        NH_GFX_OPENGL_COMMAND_GLVERTEX3FV,
        NH_GFX_OPENGL_COMMAND_GLVERTEX3IV,
        NH_GFX_OPENGL_COMMAND_GLVERTEX3SV,
        NH_GFX_OPENGL_COMMAND_GLVERTEX4DV,
        NH_GFX_OPENGL_COMMAND_GLVERTEX4FV,
        NH_GFX_OPENGL_COMMAND_GLVERTEX4IV,
        NH_GFX_OPENGL_COMMAND_GLVERTEX4SV,
        NH_GFX_OPENGL_COMMAND_GLVERTEXATTRIBPOINTER,
        NH_GFX_OPENGL_COMMAND_GLVERTEXPOINTER,
        NH_GFX_OPENGL_COMMAND_GLVIEWPORT,
	NH_GFX_OPENGL_COMMAND_UNDEFINED,
    } NH_GFX_OPENGL_COMMAND_E;

/** @} */

/** @addtogroup lib_nh-gfx_functions
 *  @{
 */

    NH_GFX_OPENGL_COMMAND_E nh_gfx_getOpenGLCommandType(
        char *name_p
    );

    int nh_gfx_getOpenGLCommandParameterCount(
        NH_GFX_OPENGL_COMMAND_E type
    );

/** @} */

#endif
