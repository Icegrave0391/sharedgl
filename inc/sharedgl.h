#ifndef _SHAREDGL_H_
#define _SHAREDGL_H_

#ifdef SHAREDGL_HOST
#include <epoxy/gl.h>
#endif

#ifdef _WIN32
#define GLAPI __declspec(dllexport)
#else
#define GLAPI
#endif

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define PRINT_LOG(...) \
    { \
        time_t current_time; \
        time(&current_time); \
        char *time_cstr = ctime(&current_time); \
        time_cstr[strlen(time_cstr) - 1] = 0; \
        fprintf(stderr, "[%s] ", time_cstr); \
        fprintf(stderr, __VA_ARGS__); \
    }

#define SGL_OFFSET_REGISTER_SUBMIT (sizeof(int) * 0)
#define SGL_OFFSET_REGISTER_RETVAL (sizeof(int) * 1)
#define SGL_OFFSET_REGISTER_READY_HINT (sizeof(int) * 2)
#define SGL_OFFSET_REGISTER_LOCK (sizeof(int) * 3)
#define SGL_OFFSET_REGISTER_CLAIM_ID (sizeof(int) * 4)
#define SGL_OFFSET_REGISTER_CONNECT (sizeof(int) * 5)
#define SGL_OFFSET_REGISTER_FBSTART (sizeof(int) * 6)
#define SGL_OFFSET_REGISTER_MEMSIZE (sizeof(int) * 8)
#define SGL_OFFSET_REGISTER_GLMAJ (sizeof(int) * 11)
#define SGL_OFFSET_REGISTER_GLMIN (sizeof(int) * 12)
#define SGL_OFFSET_REGISTER_RETVAL_V (sizeof(int) * 13)
#define SGL_OFFSET_COMMAND_START 0x1000

/*
 * max return in RETVAL_V is 4044
 */
#define SGL_VP_DOWNLOAD_BLOCK_SIZE_IN_BYTES 3072
#define SGL_VP_DOWNLOAD_BLOCK_SIZE (SGL_VP_DOWNLOAD_BLOCK_SIZE_IN_BYTES / sizeof(int))

#define SGL_DEFAULT_MAJOR 4
#define SGL_DEFAULT_MINOR 6

#define SGL_SHARED_MEMORY_NAME "sharedgl_shared_memory"

#define CEIL_DIV(num, den) ((num + den - 1) / den)

#define PACK(a, b) (((a) << 16) | ((b) & 0xFFFF))
#define UNPACK_A(packed) (((packed) >> 16) & 0xFFFF)
#define UNPACK_B(packed) ((packed) & 0xFFFF)

#ifdef _WIN32
#   define FORCEINLINE __forceinline
#else
#   define FORCEINLINE __attribute__((always_inline))
#endif

static inline bool is_value_likely_an_offset(const void *p)
{
    uintptr_t v = (uintptr_t)p;
    return v < 0x100000;
}

/*
 * commands, pretty much 1:1 mapping for opengl
 */
enum {
    SGL_CMD_INVALID,
    SGL_CMD_FLIP,               // USE SGL_CMD_REQUEST_FRAMEBUFFER INSTEAD
    SGL_CMD_SEND_DATA,
    SGL_CMD_GET_CONTEXT,
    SGL_CMD_SET_CONTEXT,
    SGL_CMD_GET_SIZE,
    SGL_CMD_VP_UPLOAD,
    SGL_CMD_VP_NULL,
    SGL_CMD_VP_UPLOAD_STAY,
    SGL_CMD_VP_DOWNLOAD,        // UNLIKE VP_UPLOAD, WE USE BYTES INSTEAD OF INTS
    SGL_CMD_CREATE_CONTEXT,
    SGL_CMD_REPORT_DIMS,        // NOT USED
    SGL_CMD_HELLO_WORLD,
    SGL_CMD_GOODBYE_WORLD,
    SGL_CMD_REQUEST_FRAMEBUFFER,

    SGL_CMD_CULLFACE,
    SGL_CMD_FRONTFACE,
    SGL_CMD_HINT,
    SGL_CMD_LINEWIDTH,
    SGL_CMD_POINTSIZE,
    SGL_CMD_POLYGONMODE,
    SGL_CMD_SCISSOR,
    SGL_CMD_TEXPARAMETERF,
    SGL_CMD_TEXPARAMETERFV,
    SGL_CMD_TEXPARAMETERI,
    SGL_CMD_TEXPARAMETERIV,
    SGL_CMD_TEXIMAGE1D,
    SGL_CMD_TEXIMAGE2D,
    SGL_CMD_DRAWBUFFER,
    SGL_CMD_CLEAR,
    SGL_CMD_CLEARCOLOR,
    SGL_CMD_CLEARSTENCIL,
    SGL_CMD_CLEARDEPTH,
    SGL_CMD_STENCILMASK,
    SGL_CMD_COLORMASK,
    SGL_CMD_DEPTHMASK,
    SGL_CMD_DISABLE,
    SGL_CMD_ENABLE,
    SGL_CMD_FINISH,
    SGL_CMD_FLUSH,
    SGL_CMD_BLENDFUNC,
    SGL_CMD_LOGICOP,
    SGL_CMD_STENCILFUNC,
    SGL_CMD_STENCILOP,
    SGL_CMD_DEPTHFUNC,
    SGL_CMD_PIXELSTOREF,
    SGL_CMD_PIXELSTOREI,
    SGL_CMD_READBUFFER,
    SGL_CMD_READPIXELS,
    SGL_CMD_GETBOOLEANV,
    SGL_CMD_GETDOUBLEV,
    SGL_CMD_GETERROR,
    SGL_CMD_GETFLOATV,
    SGL_CMD_GETINTEGERV,
    SGL_CMD_GETSTRING,
    SGL_CMD_GETTEXIMAGE,
    SGL_CMD_GETTEXPARAMETERFV,
    SGL_CMD_GETTEXPARAMETERIV,
    SGL_CMD_GETTEXLEVELPARAMETERFV,
    SGL_CMD_GETTEXLEVELPARAMETERIV,
    SGL_CMD_ISENABLED,
    SGL_CMD_DEPTHRANGE,
    SGL_CMD_VIEWPORT,
    SGL_CMD_NEWLIST,
    SGL_CMD_ENDLIST,
    SGL_CMD_CALLLIST,
    SGL_CMD_CALLLISTS,
    SGL_CMD_DELETELISTS,
    SGL_CMD_GENLISTS,
    SGL_CMD_LISTBASE,
    SGL_CMD_BEGIN,
    SGL_CMD_BITMAP,
    SGL_CMD_COLOR3B,
    SGL_CMD_COLOR3BV,
    SGL_CMD_COLOR3D,
    SGL_CMD_COLOR3DV,
    SGL_CMD_COLOR3F,
    SGL_CMD_COLOR3FV,
    SGL_CMD_COLOR3I,
    SGL_CMD_COLOR3IV,
    SGL_CMD_COLOR3S,
    SGL_CMD_COLOR3SV,
    SGL_CMD_COLOR3UB,
    SGL_CMD_COLOR3UBV,
    SGL_CMD_COLOR3UI,
    SGL_CMD_COLOR3UIV,
    SGL_CMD_COLOR3US,
    SGL_CMD_COLOR3USV,
    SGL_CMD_COLOR4B,
    SGL_CMD_COLOR4BV,
    SGL_CMD_COLOR4D,
    SGL_CMD_COLOR4DV,
    SGL_CMD_COLOR4F,
    SGL_CMD_COLOR4FV,
    SGL_CMD_COLOR4I,
    SGL_CMD_COLOR4IV,
    SGL_CMD_COLOR4S,
    SGL_CMD_COLOR4SV,
    SGL_CMD_COLOR4UB,
    SGL_CMD_COLOR4UBV,
    SGL_CMD_COLOR4UI,
    SGL_CMD_COLOR4UIV,
    SGL_CMD_COLOR4US,
    SGL_CMD_COLOR4USV,
    SGL_CMD_EDGEFLAG,
    SGL_CMD_EDGEFLAGV,
    SGL_CMD_END,
    SGL_CMD_INDEXD,
    SGL_CMD_INDEXDV,
    SGL_CMD_INDEXF,
    SGL_CMD_INDEXFV,
    SGL_CMD_INDEXI,
    SGL_CMD_INDEXIV,
    SGL_CMD_INDEXS,
    SGL_CMD_INDEXSV,
    SGL_CMD_NORMAL3B,
    SGL_CMD_NORMAL3BV,
    SGL_CMD_NORMAL3D,
    SGL_CMD_NORMAL3DV,
    SGL_CMD_NORMAL3F,
    SGL_CMD_NORMAL3FV,
    SGL_CMD_NORMAL3I,
    SGL_CMD_NORMAL3IV,
    SGL_CMD_NORMAL3S,
    SGL_CMD_NORMAL3SV,
    SGL_CMD_RASTERPOS2D,
    SGL_CMD_RASTERPOS2DV,
    SGL_CMD_RASTERPOS2F,
    SGL_CMD_RASTERPOS2FV,
    SGL_CMD_RASTERPOS2I,
    SGL_CMD_RASTERPOS2IV,
    SGL_CMD_RASTERPOS2S,
    SGL_CMD_RASTERPOS2SV,
    SGL_CMD_RASTERPOS3D,
    SGL_CMD_RASTERPOS3DV,
    SGL_CMD_RASTERPOS3F,
    SGL_CMD_RASTERPOS3FV,
    SGL_CMD_RASTERPOS3I,
    SGL_CMD_RASTERPOS3IV,
    SGL_CMD_RASTERPOS3S,
    SGL_CMD_RASTERPOS3SV,
    SGL_CMD_RASTERPOS4D,
    SGL_CMD_RASTERPOS4DV,
    SGL_CMD_RASTERPOS4F,
    SGL_CMD_RASTERPOS4FV,
    SGL_CMD_RASTERPOS4I,
    SGL_CMD_RASTERPOS4IV,
    SGL_CMD_RASTERPOS4S,
    SGL_CMD_RASTERPOS4SV,
    SGL_CMD_RECTD,
    SGL_CMD_RECTDV,
    SGL_CMD_RECTF,
    SGL_CMD_RECTFV,
    SGL_CMD_RECTI,
    SGL_CMD_RECTIV,
    SGL_CMD_RECTS,
    SGL_CMD_RECTSV,
    SGL_CMD_TEXCOORD1D,
    SGL_CMD_TEXCOORD1DV,
    SGL_CMD_TEXCOORD1F,
    SGL_CMD_TEXCOORD1FV,
    SGL_CMD_TEXCOORD1I,
    SGL_CMD_TEXCOORD1IV,
    SGL_CMD_TEXCOORD1S,
    SGL_CMD_TEXCOORD1SV,
    SGL_CMD_TEXCOORD2D,
    SGL_CMD_TEXCOORD2DV,
    SGL_CMD_TEXCOORD2F,
    SGL_CMD_TEXCOORD2FV,
    SGL_CMD_TEXCOORD2I,
    SGL_CMD_TEXCOORD2IV,
    SGL_CMD_TEXCOORD2S,
    SGL_CMD_TEXCOORD2SV,
    SGL_CMD_TEXCOORD3D,
    SGL_CMD_TEXCOORD3DV,
    SGL_CMD_TEXCOORD3F,
    SGL_CMD_TEXCOORD3FV,
    SGL_CMD_TEXCOORD3I,
    SGL_CMD_TEXCOORD3IV,
    SGL_CMD_TEXCOORD3S,
    SGL_CMD_TEXCOORD3SV,
    SGL_CMD_TEXCOORD4D,
    SGL_CMD_TEXCOORD4DV,
    SGL_CMD_TEXCOORD4F,
    SGL_CMD_TEXCOORD4FV,
    SGL_CMD_TEXCOORD4I,
    SGL_CMD_TEXCOORD4IV,
    SGL_CMD_TEXCOORD4S,
    SGL_CMD_TEXCOORD4SV,
    SGL_CMD_VERTEX2D,
    SGL_CMD_VERTEX2DV,
    SGL_CMD_VERTEX2F,
    SGL_CMD_VERTEX2FV,
    SGL_CMD_VERTEX2I,
    SGL_CMD_VERTEX2IV,
    SGL_CMD_VERTEX2S,
    SGL_CMD_VERTEX2SV,
    SGL_CMD_VERTEX3D,
    SGL_CMD_VERTEX3DV,
    SGL_CMD_VERTEX3F,
    SGL_CMD_VERTEX3FV,
    SGL_CMD_VERTEX3I,
    SGL_CMD_VERTEX3IV,
    SGL_CMD_VERTEX3S,
    SGL_CMD_VERTEX3SV,
    SGL_CMD_VERTEX4D,
    SGL_CMD_VERTEX4DV,
    SGL_CMD_VERTEX4F,
    SGL_CMD_VERTEX4FV,
    SGL_CMD_VERTEX4I,
    SGL_CMD_VERTEX4IV,
    SGL_CMD_VERTEX4S,
    SGL_CMD_VERTEX4SV,
    SGL_CMD_CLIPPLANE,
    SGL_CMD_COLORMATERIAL,
    SGL_CMD_FOGF,
    SGL_CMD_FOGFV,
    SGL_CMD_FOGI,
    SGL_CMD_FOGIV,
    SGL_CMD_LIGHTF,
    SGL_CMD_LIGHTFV,
    SGL_CMD_LIGHTI,
    SGL_CMD_LIGHTIV,
    SGL_CMD_LIGHTMODELF,
    SGL_CMD_LIGHTMODELFV,
    SGL_CMD_LIGHTMODELI,
    SGL_CMD_LIGHTMODELIV,
    SGL_CMD_LINESTIPPLE,
    SGL_CMD_MATERIALF,
    SGL_CMD_MATERIALFV,
    SGL_CMD_MATERIALI,
    SGL_CMD_MATERIALIV,
    SGL_CMD_POLYGONSTIPPLE,
    SGL_CMD_SHADEMODEL,
    SGL_CMD_TEXENVF,
    SGL_CMD_TEXENVFV,
    SGL_CMD_TEXENVI,
    SGL_CMD_TEXENVIV,
    SGL_CMD_TEXGEND,
    SGL_CMD_TEXGENDV,
    SGL_CMD_TEXGENF,
    SGL_CMD_TEXGENFV,
    SGL_CMD_TEXGENI,
    SGL_CMD_TEXGENIV,
    SGL_CMD_FEEDBACKBUFFER,
    SGL_CMD_SELECTBUFFER,
    SGL_CMD_RENDERMODE,
    SGL_CMD_INITNAMES,
    SGL_CMD_LOADNAME,
    SGL_CMD_PASSTHROUGH,
    SGL_CMD_POPNAME,
    SGL_CMD_PUSHNAME,
    SGL_CMD_CLEARACCUM,
    SGL_CMD_CLEARINDEX,
    SGL_CMD_INDEXMASK,
    SGL_CMD_ACCUM,
    SGL_CMD_POPATTRIB,
    SGL_CMD_PUSHATTRIB,
    SGL_CMD_MAP1D,
    SGL_CMD_MAP1F,
    SGL_CMD_MAP2D,
    SGL_CMD_MAP2F,
    SGL_CMD_MAPGRID1D,
    SGL_CMD_MAPGRID1F,
    SGL_CMD_MAPGRID2D,
    SGL_CMD_MAPGRID2F,
    SGL_CMD_EVALCOORD1D,
    SGL_CMD_EVALCOORD1DV,
    SGL_CMD_EVALCOORD1F,
    SGL_CMD_EVALCOORD1FV,
    SGL_CMD_EVALCOORD2D,
    SGL_CMD_EVALCOORD2DV,
    SGL_CMD_EVALCOORD2F,
    SGL_CMD_EVALCOORD2FV,
    SGL_CMD_EVALMESH1,
    SGL_CMD_EVALPOINT1,
    SGL_CMD_EVALMESH2,
    SGL_CMD_EVALPOINT2,
    SGL_CMD_ALPHAFUNC,
    SGL_CMD_PIXELZOOM,
    SGL_CMD_PIXELTRANSFERF,
    SGL_CMD_PIXELTRANSFERI,
    SGL_CMD_PIXELMAPFV,
    SGL_CMD_PIXELMAPUIV,
    SGL_CMD_PIXELMAPUSV,
    SGL_CMD_COPYPIXELS,
    SGL_CMD_DRAWPIXELS,
    SGL_CMD_GETCLIPPLANE,
    SGL_CMD_GETLIGHTFV,
    SGL_CMD_GETLIGHTIV,
    SGL_CMD_GETMAPDV,
    SGL_CMD_GETMAPFV,
    SGL_CMD_GETMAPIV,
    SGL_CMD_GETMATERIALFV,
    SGL_CMD_GETMATERIALIV,
    SGL_CMD_GETPIXELMAPFV,
    SGL_CMD_GETPIXELMAPUIV,
    SGL_CMD_GETPIXELMAPUSV,
    SGL_CMD_GETPOLYGONSTIPPLE,
    SGL_CMD_GETTEXENVFV,
    SGL_CMD_GETTEXENVIV,
    SGL_CMD_GETTEXGENDV,
    SGL_CMD_GETTEXGENFV,
    SGL_CMD_GETTEXGENIV,
    SGL_CMD_ISLIST,
    SGL_CMD_FRUSTUM,
    SGL_CMD_LOADIDENTITY,
    SGL_CMD_LOADMATRIXF,
    SGL_CMD_LOADMATRIXD,
    SGL_CMD_MATRIXMODE,
    SGL_CMD_MULTMATRIXF,
    SGL_CMD_MULTMATRIXD,
    SGL_CMD_ORTHO,
    SGL_CMD_POPMATRIX,
    SGL_CMD_PUSHMATRIX,
    SGL_CMD_ROTATED,
    SGL_CMD_ROTATEF,
    SGL_CMD_SCALED,
    SGL_CMD_SCALEF,
    SGL_CMD_TRANSLATED,
    SGL_CMD_TRANSLATEF,
    SGL_CMD_DRAWARRAYS,
    SGL_CMD_DRAWELEMENTS,
    SGL_CMD_GETPOINTERV,
    SGL_CMD_POLYGONOFFSET,
    SGL_CMD_COPYTEXIMAGE1D,
    SGL_CMD_COPYTEXIMAGE2D,
    SGL_CMD_COPYTEXSUBIMAGE1D,
    SGL_CMD_COPYTEXSUBIMAGE2D,
    SGL_CMD_TEXSUBIMAGE1D,
    SGL_CMD_TEXSUBIMAGE2D,
    SGL_CMD_BINDTEXTURE,
    SGL_CMD_DELETETEXTURES,
    SGL_CMD_GENTEXTURES,
    SGL_CMD_ISTEXTURE,
    SGL_CMD_ARRAYELEMENT,
    SGL_CMD_COLORPOINTER,
    SGL_CMD_DISABLECLIENTSTATE,
    SGL_CMD_EDGEFLAGPOINTER,
    SGL_CMD_ENABLECLIENTSTATE,
    SGL_CMD_INDEXPOINTER,
    SGL_CMD_INTERLEAVEDARRAYS,
    SGL_CMD_NORMALPOINTER,
    SGL_CMD_TEXCOORDPOINTER,
    SGL_CMD_VERTEXPOINTER,
    SGL_CMD_ARETEXTURESRESIDENT,
    SGL_CMD_PRIORITIZETEXTURES,
    SGL_CMD_INDEXUB,
    SGL_CMD_INDEXUBV,
    SGL_CMD_POPCLIENTATTRIB,
    SGL_CMD_PUSHCLIENTATTRIB,
    SGL_CMD_DRAWRANGEELEMENTS,
    SGL_CMD_TEXIMAGE3D,
    SGL_CMD_TEXSUBIMAGE3D,
    SGL_CMD_COPYTEXSUBIMAGE3D,
    SGL_CMD_ACTIVETEXTURE,
    SGL_CMD_SAMPLECOVERAGE,
    SGL_CMD_COMPRESSEDTEXIMAGE3D,
    SGL_CMD_COMPRESSEDTEXIMAGE2D,
    SGL_CMD_COMPRESSEDTEXIMAGE1D,
    SGL_CMD_COMPRESSEDTEXSUBIMAGE3D,
    SGL_CMD_COMPRESSEDTEXSUBIMAGE2D,
    SGL_CMD_COMPRESSEDTEXSUBIMAGE1D,
    SGL_CMD_GETCOMPRESSEDTEXIMAGE,
    SGL_CMD_CLIENTACTIVETEXTURE,
    SGL_CMD_MULTITEXCOORD1D,
    SGL_CMD_MULTITEXCOORD1DV,
    SGL_CMD_MULTITEXCOORD1F,
    SGL_CMD_MULTITEXCOORD1FV,
    SGL_CMD_MULTITEXCOORD1I,
    SGL_CMD_MULTITEXCOORD1IV,
    SGL_CMD_MULTITEXCOORD1S,
    SGL_CMD_MULTITEXCOORD1SV,
    SGL_CMD_MULTITEXCOORD2D,
    SGL_CMD_MULTITEXCOORD2DV,
    SGL_CMD_MULTITEXCOORD2F,
    SGL_CMD_MULTITEXCOORD2FV,
    SGL_CMD_MULTITEXCOORD2I,
    SGL_CMD_MULTITEXCOORD2IV,
    SGL_CMD_MULTITEXCOORD2S,
    SGL_CMD_MULTITEXCOORD2SV,
    SGL_CMD_MULTITEXCOORD3D,
    SGL_CMD_MULTITEXCOORD3DV,
    SGL_CMD_MULTITEXCOORD3F,
    SGL_CMD_MULTITEXCOORD3FV,
    SGL_CMD_MULTITEXCOORD3I,
    SGL_CMD_MULTITEXCOORD3IV,
    SGL_CMD_MULTITEXCOORD3S,
    SGL_CMD_MULTITEXCOORD3SV,
    SGL_CMD_MULTITEXCOORD4D,
    SGL_CMD_MULTITEXCOORD4DV,
    SGL_CMD_MULTITEXCOORD4F,
    SGL_CMD_MULTITEXCOORD4FV,
    SGL_CMD_MULTITEXCOORD4I,
    SGL_CMD_MULTITEXCOORD4IV,
    SGL_CMD_MULTITEXCOORD4S,
    SGL_CMD_MULTITEXCOORD4SV,
    SGL_CMD_LOADTRANSPOSEMATRIXF,
    SGL_CMD_LOADTRANSPOSEMATRIXD,
    SGL_CMD_MULTTRANSPOSEMATRIXF,
    SGL_CMD_MULTTRANSPOSEMATRIXD,
    SGL_CMD_BLENDFUNCSEPARATE,
    SGL_CMD_MULTIDRAWARRAYS,
    SGL_CMD_MULTIDRAWELEMENTS,
    SGL_CMD_POINTPARAMETERF,
    SGL_CMD_POINTPARAMETERFV,
    SGL_CMD_POINTPARAMETERI,
    SGL_CMD_POINTPARAMETERIV,
    SGL_CMD_FOGCOORDF,
    SGL_CMD_FOGCOORDFV,
    SGL_CMD_FOGCOORDD,
    SGL_CMD_FOGCOORDDV,
    SGL_CMD_FOGCOORDPOINTER,
    SGL_CMD_SECONDARYCOLOR3B,
    SGL_CMD_SECONDARYCOLOR3BV,
    SGL_CMD_SECONDARYCOLOR3D,
    SGL_CMD_SECONDARYCOLOR3DV,
    SGL_CMD_SECONDARYCOLOR3F,
    SGL_CMD_SECONDARYCOLOR3FV,
    SGL_CMD_SECONDARYCOLOR3I,
    SGL_CMD_SECONDARYCOLOR3IV,
    SGL_CMD_SECONDARYCOLOR3S,
    SGL_CMD_SECONDARYCOLOR3SV,
    SGL_CMD_SECONDARYCOLOR3UB,
    SGL_CMD_SECONDARYCOLOR3UBV,
    SGL_CMD_SECONDARYCOLOR3UI,
    SGL_CMD_SECONDARYCOLOR3UIV,
    SGL_CMD_SECONDARYCOLOR3US,
    SGL_CMD_SECONDARYCOLOR3USV,
    SGL_CMD_SECONDARYCOLORPOINTER,
    SGL_CMD_WINDOWPOS2D,
    SGL_CMD_WINDOWPOS2DV,
    SGL_CMD_WINDOWPOS2F,
    SGL_CMD_WINDOWPOS2FV,
    SGL_CMD_WINDOWPOS2I,
    SGL_CMD_WINDOWPOS2IV,
    SGL_CMD_WINDOWPOS2S,
    SGL_CMD_WINDOWPOS2SV,
    SGL_CMD_WINDOWPOS3D,
    SGL_CMD_WINDOWPOS3DV,
    SGL_CMD_WINDOWPOS3F,
    SGL_CMD_WINDOWPOS3FV,
    SGL_CMD_WINDOWPOS3I,
    SGL_CMD_WINDOWPOS3IV,
    SGL_CMD_WINDOWPOS3S,
    SGL_CMD_WINDOWPOS3SV,
    SGL_CMD_BLENDCOLOR,
    SGL_CMD_BLENDEQUATION,
    SGL_CMD_GENQUERIES,
    SGL_CMD_DELETEQUERIES,
    SGL_CMD_ISQUERY,
    SGL_CMD_BEGINQUERY,
    SGL_CMD_ENDQUERY,
    SGL_CMD_GETQUERYIV,
    SGL_CMD_GETQUERYOBJECTIV,
    SGL_CMD_GETQUERYOBJECTUIV,
    SGL_CMD_BINDBUFFER,
    SGL_CMD_DELETEBUFFERS,
    SGL_CMD_GENBUFFERS,
    SGL_CMD_ISBUFFER,
    SGL_CMD_BUFFERDATA,
    SGL_CMD_BUFFERSUBDATA,
    SGL_CMD_GETBUFFERSUBDATA,
    SGL_CMD_MAPBUFFER,
    SGL_CMD_UNMAPBUFFER,
    SGL_CMD_GETBUFFERPARAMETERIV,
    SGL_CMD_GETBUFFERPOINTERV,
    SGL_CMD_BLENDEQUATIONSEPARATE,
    SGL_CMD_DRAWBUFFERS,
    SGL_CMD_STENCILOPSEPARATE,
    SGL_CMD_STENCILFUNCSEPARATE,
    SGL_CMD_STENCILMASKSEPARATE,
    SGL_CMD_ATTACHSHADER,
    SGL_CMD_BINDATTRIBLOCATION,
    SGL_CMD_COMPILESHADER,
    SGL_CMD_CREATEPROGRAM,
    SGL_CMD_CREATESHADER,
    SGL_CMD_DELETEPROGRAM,
    SGL_CMD_DELETESHADER,
    SGL_CMD_DETACHSHADER,
    SGL_CMD_DISABLEVERTEXATTRIBARRAY,
    SGL_CMD_ENABLEVERTEXATTRIBARRAY,
    SGL_CMD_GETACTIVEATTRIB,
    SGL_CMD_GETACTIVEUNIFORM,
    SGL_CMD_GETATTACHEDSHADERS,
    SGL_CMD_GETATTRIBLOCATION,
    SGL_CMD_GETPROGRAMIV,
    SGL_CMD_GETPROGRAMINFOLOG,
    SGL_CMD_GETSHADERIV,
    SGL_CMD_GETSHADERINFOLOG,
    SGL_CMD_GETSHADERSOURCE,
    SGL_CMD_GETUNIFORMLOCATION,
    SGL_CMD_GETUNIFORMFV,
    SGL_CMD_GETUNIFORMIV,
    SGL_CMD_GETVERTEXATTRIBDV,
    SGL_CMD_GETVERTEXATTRIBFV,
    SGL_CMD_GETVERTEXATTRIBIV,
    SGL_CMD_GETVERTEXATTRIBPOINTERV,
    SGL_CMD_ISPROGRAM,
    SGL_CMD_ISSHADER,
    SGL_CMD_LINKPROGRAM,
    SGL_CMD_SHADERSOURCE,
    SGL_CMD_USEPROGRAM,
    SGL_CMD_UNIFORM1F,
    SGL_CMD_UNIFORM2F,
    SGL_CMD_UNIFORM3F,
    SGL_CMD_UNIFORM4F,
    SGL_CMD_UNIFORM1I,
    SGL_CMD_UNIFORM2I,
    SGL_CMD_UNIFORM3I,
    SGL_CMD_UNIFORM4I,
    SGL_CMD_UNIFORM1FV,
    SGL_CMD_UNIFORM2FV,
    SGL_CMD_UNIFORM3FV,
    SGL_CMD_UNIFORM4FV,
    SGL_CMD_UNIFORM1IV,
    SGL_CMD_UNIFORM2IV,
    SGL_CMD_UNIFORM3IV,
    SGL_CMD_UNIFORM4IV,
    SGL_CMD_UNIFORMMATRIX2FV,
    SGL_CMD_UNIFORMMATRIX3FV,
    SGL_CMD_UNIFORMMATRIX4FV,
    SGL_CMD_VALIDATEPROGRAM,
    SGL_CMD_VERTEXATTRIB1D,
    SGL_CMD_VERTEXATTRIB1DV,
    SGL_CMD_VERTEXATTRIB1F,
    SGL_CMD_VERTEXATTRIB1FV,
    SGL_CMD_VERTEXATTRIB1S,
    SGL_CMD_VERTEXATTRIB1SV,
    SGL_CMD_VERTEXATTRIB2D,
    SGL_CMD_VERTEXATTRIB2DV,
    SGL_CMD_VERTEXATTRIB2F,
    SGL_CMD_VERTEXATTRIB2FV,
    SGL_CMD_VERTEXATTRIB2S,
    SGL_CMD_VERTEXATTRIB2SV,
    SGL_CMD_VERTEXATTRIB3D,
    SGL_CMD_VERTEXATTRIB3DV,
    SGL_CMD_VERTEXATTRIB3F,
    SGL_CMD_VERTEXATTRIB3FV,
    SGL_CMD_VERTEXATTRIB3S,
    SGL_CMD_VERTEXATTRIB3SV,
    SGL_CMD_VERTEXATTRIB4NBV,
    SGL_CMD_VERTEXATTRIB4NIV,
    SGL_CMD_VERTEXATTRIB4NSV,
    SGL_CMD_VERTEXATTRIB4NUB,
    SGL_CMD_VERTEXATTRIB4NUBV,
    SGL_CMD_VERTEXATTRIB4NUIV,
    SGL_CMD_VERTEXATTRIB4NUSV,
    SGL_CMD_VERTEXATTRIB4BV,
    SGL_CMD_VERTEXATTRIB4D,
    SGL_CMD_VERTEXATTRIB4DV,
    SGL_CMD_VERTEXATTRIB4F,
    SGL_CMD_VERTEXATTRIB4FV,
    SGL_CMD_VERTEXATTRIB4IV,
    SGL_CMD_VERTEXATTRIB4S,
    SGL_CMD_VERTEXATTRIB4SV,
    SGL_CMD_VERTEXATTRIB4UBV,
    SGL_CMD_VERTEXATTRIB4UIV,
    SGL_CMD_VERTEXATTRIB4USV,
    SGL_CMD_VERTEXATTRIBPOINTER,
    SGL_CMD_UNIFORMMATRIX2X3FV,
    SGL_CMD_UNIFORMMATRIX3X2FV,
    SGL_CMD_UNIFORMMATRIX2X4FV,
    SGL_CMD_UNIFORMMATRIX4X2FV,
    SGL_CMD_UNIFORMMATRIX3X4FV,
    SGL_CMD_UNIFORMMATRIX4X3FV,
    SGL_CMD_COLORMASKI,
    SGL_CMD_GETBOOLEANI_V,
    SGL_CMD_GETINTEGERI_V,
    SGL_CMD_ENABLEI,
    SGL_CMD_DISABLEI,
    SGL_CMD_ISENABLEDI,
    SGL_CMD_BEGINTRANSFORMFEEDBACK,
    SGL_CMD_ENDTRANSFORMFEEDBACK,
    SGL_CMD_BINDBUFFERRANGE,
    SGL_CMD_BINDBUFFERBASE,
    SGL_CMD_TRANSFORMFEEDBACKVARYINGS,
    SGL_CMD_GETTRANSFORMFEEDBACKVARYING,
    SGL_CMD_CLAMPCOLOR,
    SGL_CMD_BEGINCONDITIONALRENDER,
    SGL_CMD_ENDCONDITIONALRENDER,
    SGL_CMD_VERTEXATTRIBIPOINTER,
    SGL_CMD_GETVERTEXATTRIBIIV,
    SGL_CMD_GETVERTEXATTRIBIUIV,
    SGL_CMD_VERTEXATTRIBI1I,
    SGL_CMD_VERTEXATTRIBI2I,
    SGL_CMD_VERTEXATTRIBI3I,
    SGL_CMD_VERTEXATTRIBI4I,
    SGL_CMD_VERTEXATTRIBI1UI,
    SGL_CMD_VERTEXATTRIBI2UI,
    SGL_CMD_VERTEXATTRIBI3UI,
    SGL_CMD_VERTEXATTRIBI4UI,
    SGL_CMD_VERTEXATTRIBI1IV,
    SGL_CMD_VERTEXATTRIBI2IV,
    SGL_CMD_VERTEXATTRIBI3IV,
    SGL_CMD_VERTEXATTRIBI4IV,
    SGL_CMD_VERTEXATTRIBI1UIV,
    SGL_CMD_VERTEXATTRIBI2UIV,
    SGL_CMD_VERTEXATTRIBI3UIV,
    SGL_CMD_VERTEXATTRIBI4UIV,
    SGL_CMD_VERTEXATTRIBI4BV,
    SGL_CMD_VERTEXATTRIBI4SV,
    SGL_CMD_VERTEXATTRIBI4UBV,
    SGL_CMD_VERTEXATTRIBI4USV,
    SGL_CMD_GETUNIFORMUIV,
    SGL_CMD_BINDFRAGDATALOCATION,
    SGL_CMD_GETFRAGDATALOCATION,
    SGL_CMD_UNIFORM1UI,
    SGL_CMD_UNIFORM2UI,
    SGL_CMD_UNIFORM3UI,
    SGL_CMD_UNIFORM4UI,
    SGL_CMD_UNIFORM1UIV,
    SGL_CMD_UNIFORM2UIV,
    SGL_CMD_UNIFORM3UIV,
    SGL_CMD_UNIFORM4UIV,
    SGL_CMD_TEXPARAMETERIIV,
    SGL_CMD_TEXPARAMETERIUIV,
    SGL_CMD_GETTEXPARAMETERIIV,
    SGL_CMD_GETTEXPARAMETERIUIV,
    SGL_CMD_CLEARBUFFERIV,
    SGL_CMD_CLEARBUFFERUIV,
    SGL_CMD_CLEARBUFFERFV,
    SGL_CMD_CLEARBUFFERFI,
    SGL_CMD_GETSTRINGI,
    SGL_CMD_ISRENDERBUFFER,
    SGL_CMD_BINDRENDERBUFFER,
    SGL_CMD_DELETERENDERBUFFERS,
    SGL_CMD_GENRENDERBUFFERS,
    SGL_CMD_RENDERBUFFERSTORAGE,
    SGL_CMD_GETRENDERBUFFERPARAMETERIV,
    SGL_CMD_ISFRAMEBUFFER,
    SGL_CMD_BINDFRAMEBUFFER,
    SGL_CMD_DELETEFRAMEBUFFERS,
    SGL_CMD_GENFRAMEBUFFERS,
    SGL_CMD_CHECKFRAMEBUFFERSTATUS,
    SGL_CMD_FRAMEBUFFERTEXTURE1D,
    SGL_CMD_FRAMEBUFFERTEXTURE2D,
    SGL_CMD_FRAMEBUFFERTEXTURE3D,
    SGL_CMD_FRAMEBUFFERRENDERBUFFER,
    SGL_CMD_GETFRAMEBUFFERATTACHMENTPARAMETERIV,
    SGL_CMD_GENERATEMIPMAP,
    SGL_CMD_BLITFRAMEBUFFER,
    SGL_CMD_RENDERBUFFERSTORAGEMULTISAMPLE,
    SGL_CMD_FRAMEBUFFERTEXTURELAYER,
    SGL_CMD_MAPBUFFERRANGE,
    SGL_CMD_FLUSHMAPPEDBUFFERRANGE,
    SGL_CMD_BINDVERTEXARRAY,
    SGL_CMD_DELETEVERTEXARRAYS,
    SGL_CMD_GENVERTEXARRAYS,
    SGL_CMD_ISVERTEXARRAY,
    SGL_CMD_DRAWARRAYSINSTANCED,
    SGL_CMD_DRAWELEMENTSINSTANCED,
    SGL_CMD_TEXBUFFER,
    SGL_CMD_PRIMITIVERESTARTINDEX,
    SGL_CMD_COPYBUFFERSUBDATA,
    SGL_CMD_GETUNIFORMINDICES,
    SGL_CMD_GETACTIVEUNIFORMSIV,
    SGL_CMD_GETACTIVEUNIFORMNAME,
    SGL_CMD_GETUNIFORMBLOCKINDEX,
    SGL_CMD_GETACTIVEUNIFORMBLOCKIV,
    SGL_CMD_GETACTIVEUNIFORMBLOCKNAME,
    SGL_CMD_UNIFORMBLOCKBINDING,
    SGL_CMD_DRAWELEMENTSBASEVERTEX,
    SGL_CMD_DRAWRANGEELEMENTSBASEVERTEX,
    SGL_CMD_DRAWELEMENTSINSTANCEDBASEVERTEX,
    SGL_CMD_MULTIDRAWELEMENTSBASEVERTEX,
    SGL_CMD_PROVOKINGVERTEX,
    SGL_CMD_FENCESYNC,
    SGL_CMD_ISSYNC,
    SGL_CMD_DELETESYNC,
    SGL_CMD_CLIENTWAITSYNC,
    SGL_CMD_WAITSYNC,
    SGL_CMD_GETINTEGER64V,
    SGL_CMD_GETSYNCIV,
    SGL_CMD_GETINTEGER64I_V,
    SGL_CMD_GETBUFFERPARAMETERI64V,
    SGL_CMD_FRAMEBUFFERTEXTURE,
    SGL_CMD_TEXIMAGE2DMULTISAMPLE,
    SGL_CMD_TEXIMAGE3DMULTISAMPLE,
    SGL_CMD_GETMULTISAMPLEFV,
    SGL_CMD_SAMPLEMASKI,
    SGL_CMD_BINDFRAGDATALOCATIONINDEXED,
    SGL_CMD_GETFRAGDATAINDEX,
    SGL_CMD_GENSAMPLERS,
    SGL_CMD_DELETESAMPLERS,
    SGL_CMD_ISSAMPLER,
    SGL_CMD_BINDSAMPLER,
    SGL_CMD_SAMPLERPARAMETERI,
    SGL_CMD_SAMPLERPARAMETERIV,
    SGL_CMD_SAMPLERPARAMETERF,
    SGL_CMD_SAMPLERPARAMETERFV,
    SGL_CMD_SAMPLERPARAMETERIIV,
    SGL_CMD_SAMPLERPARAMETERIUIV,
    SGL_CMD_GETSAMPLERPARAMETERIV,
    SGL_CMD_GETSAMPLERPARAMETERIIV,
    SGL_CMD_GETSAMPLERPARAMETERFV,
    SGL_CMD_GETSAMPLERPARAMETERIUIV,
    SGL_CMD_QUERYCOUNTER,
    SGL_CMD_GETQUERYOBJECTI64V,
    SGL_CMD_GETQUERYOBJECTUI64V,
    SGL_CMD_VERTEXATTRIBDIVISOR,
    SGL_CMD_VERTEXATTRIBP1UI,
    SGL_CMD_VERTEXATTRIBP1UIV,
    SGL_CMD_VERTEXATTRIBP2UI,
    SGL_CMD_VERTEXATTRIBP2UIV,
    SGL_CMD_VERTEXATTRIBP3UI,
    SGL_CMD_VERTEXATTRIBP3UIV,
    SGL_CMD_VERTEXATTRIBP4UI,
    SGL_CMD_VERTEXATTRIBP4UIV,
    SGL_CMD_VERTEXP2UI,
    SGL_CMD_VERTEXP2UIV,
    SGL_CMD_VERTEXP3UI,
    SGL_CMD_VERTEXP3UIV,
    SGL_CMD_VERTEXP4UI,
    SGL_CMD_VERTEXP4UIV,
    SGL_CMD_TEXCOORDP1UI,
    SGL_CMD_TEXCOORDP1UIV,
    SGL_CMD_TEXCOORDP2UI,
    SGL_CMD_TEXCOORDP2UIV,
    SGL_CMD_TEXCOORDP3UI,
    SGL_CMD_TEXCOORDP3UIV,
    SGL_CMD_TEXCOORDP4UI,
    SGL_CMD_TEXCOORDP4UIV,
    SGL_CMD_MULTITEXCOORDP1UI,
    SGL_CMD_MULTITEXCOORDP1UIV,
    SGL_CMD_MULTITEXCOORDP2UI,
    SGL_CMD_MULTITEXCOORDP2UIV,
    SGL_CMD_MULTITEXCOORDP3UI,
    SGL_CMD_MULTITEXCOORDP3UIV,
    SGL_CMD_MULTITEXCOORDP4UI,
    SGL_CMD_MULTITEXCOORDP4UIV,
    SGL_CMD_NORMALP3UI,
    SGL_CMD_NORMALP3UIV,
    SGL_CMD_COLORP3UI,
    SGL_CMD_COLORP3UIV,
    SGL_CMD_COLORP4UI,
    SGL_CMD_COLORP4UIV,
    SGL_CMD_SECONDARYCOLORP3UI,
    SGL_CMD_SECONDARYCOLORP3UIV,
    SGL_CMD_MINSAMPLESHADING,
    SGL_CMD_BLENDEQUATIONI,
    SGL_CMD_BLENDEQUATIONSEPARATEI,
    SGL_CMD_BLENDFUNCI,
    SGL_CMD_BLENDFUNCSEPARATEI,
    SGL_CMD_DRAWARRAYSINDIRECT,
    SGL_CMD_DRAWELEMENTSINDIRECT,
    SGL_CMD_UNIFORM1D,
    SGL_CMD_UNIFORM2D,
    SGL_CMD_UNIFORM3D,
    SGL_CMD_UNIFORM4D,
    SGL_CMD_UNIFORM1DV,
    SGL_CMD_UNIFORM2DV,
    SGL_CMD_UNIFORM3DV,
    SGL_CMD_UNIFORM4DV,
    SGL_CMD_UNIFORMMATRIX2DV,
    SGL_CMD_UNIFORMMATRIX3DV,
    SGL_CMD_UNIFORMMATRIX4DV,
    SGL_CMD_UNIFORMMATRIX2X3DV,
    SGL_CMD_UNIFORMMATRIX2X4DV,
    SGL_CMD_UNIFORMMATRIX3X2DV,
    SGL_CMD_UNIFORMMATRIX3X4DV,
    SGL_CMD_UNIFORMMATRIX4X2DV,
    SGL_CMD_UNIFORMMATRIX4X3DV,
    SGL_CMD_GETUNIFORMDV,
    SGL_CMD_GETSUBROUTINEUNIFORMLOCATION,
    SGL_CMD_GETSUBROUTINEINDEX,
    SGL_CMD_GETACTIVESUBROUTINEUNIFORMIV,
    SGL_CMD_GETACTIVESUBROUTINEUNIFORMNAME,
    SGL_CMD_GETACTIVESUBROUTINENAME,
    SGL_CMD_UNIFORMSUBROUTINESUIV,
    SGL_CMD_GETUNIFORMSUBROUTINEUIV,
    SGL_CMD_GETPROGRAMSTAGEIV,
    SGL_CMD_PATCHPARAMETERI,
    SGL_CMD_PATCHPARAMETERFV,
    SGL_CMD_BINDTRANSFORMFEEDBACK,
    SGL_CMD_DELETETRANSFORMFEEDBACKS,
    SGL_CMD_GENTRANSFORMFEEDBACKS,
    SGL_CMD_ISTRANSFORMFEEDBACK,
    SGL_CMD_PAUSETRANSFORMFEEDBACK,
    SGL_CMD_RESUMETRANSFORMFEEDBACK,
    SGL_CMD_DRAWTRANSFORMFEEDBACK,
    SGL_CMD_DRAWTRANSFORMFEEDBACKSTREAM,
    SGL_CMD_BEGINQUERYINDEXED,
    SGL_CMD_ENDQUERYINDEXED,
    SGL_CMD_GETQUERYINDEXEDIV,
    SGL_CMD_RELEASESHADERCOMPILER,
    SGL_CMD_SHADERBINARY,
    SGL_CMD_GETSHADERPRECISIONFORMAT,
    SGL_CMD_DEPTHRANGEF,
    SGL_CMD_CLEARDEPTHF,
    SGL_CMD_GETPROGRAMBINARY,
    SGL_CMD_PROGRAMBINARY,
    SGL_CMD_PROGRAMPARAMETERI,
    SGL_CMD_USEPROGRAMSTAGES,
    SGL_CMD_ACTIVESHADERPROGRAM,
    SGL_CMD_CREATESHADERPROGRAMV,
    SGL_CMD_BINDPROGRAMPIPELINE,
    SGL_CMD_DELETEPROGRAMPIPELINES,
    SGL_CMD_GENPROGRAMPIPELINES,
    SGL_CMD_ISPROGRAMPIPELINE,
    SGL_CMD_GETPROGRAMPIPELINEIV,
    SGL_CMD_PROGRAMUNIFORM1I,
    SGL_CMD_PROGRAMUNIFORM1IV,
    SGL_CMD_PROGRAMUNIFORM1F,
    SGL_CMD_PROGRAMUNIFORM1FV,
    SGL_CMD_PROGRAMUNIFORM1D,
    SGL_CMD_PROGRAMUNIFORM1DV,
    SGL_CMD_PROGRAMUNIFORM1UI,
    SGL_CMD_PROGRAMUNIFORM1UIV,
    SGL_CMD_PROGRAMUNIFORM2I,
    SGL_CMD_PROGRAMUNIFORM2IV,
    SGL_CMD_PROGRAMUNIFORM2F,
    SGL_CMD_PROGRAMUNIFORM2FV,
    SGL_CMD_PROGRAMUNIFORM2D,
    SGL_CMD_PROGRAMUNIFORM2DV,
    SGL_CMD_PROGRAMUNIFORM2UI,
    SGL_CMD_PROGRAMUNIFORM2UIV,
    SGL_CMD_PROGRAMUNIFORM3I,
    SGL_CMD_PROGRAMUNIFORM3IV,
    SGL_CMD_PROGRAMUNIFORM3F,
    SGL_CMD_PROGRAMUNIFORM3FV,
    SGL_CMD_PROGRAMUNIFORM3D,
    SGL_CMD_PROGRAMUNIFORM3DV,
    SGL_CMD_PROGRAMUNIFORM3UI,
    SGL_CMD_PROGRAMUNIFORM3UIV,
    SGL_CMD_PROGRAMUNIFORM4I,
    SGL_CMD_PROGRAMUNIFORM4IV,
    SGL_CMD_PROGRAMUNIFORM4F,
    SGL_CMD_PROGRAMUNIFORM4FV,
    SGL_CMD_PROGRAMUNIFORM4D,
    SGL_CMD_PROGRAMUNIFORM4DV,
    SGL_CMD_PROGRAMUNIFORM4UI,
    SGL_CMD_PROGRAMUNIFORM4UIV,
    SGL_CMD_PROGRAMUNIFORMMATRIX2FV,
    SGL_CMD_PROGRAMUNIFORMMATRIX3FV,
    SGL_CMD_PROGRAMUNIFORMMATRIX4FV,
    SGL_CMD_PROGRAMUNIFORMMATRIX2DV,
    SGL_CMD_PROGRAMUNIFORMMATRIX3DV,
    SGL_CMD_PROGRAMUNIFORMMATRIX4DV,
    SGL_CMD_PROGRAMUNIFORMMATRIX2X3FV,
    SGL_CMD_PROGRAMUNIFORMMATRIX3X2FV,
    SGL_CMD_PROGRAMUNIFORMMATRIX2X4FV,
    SGL_CMD_PROGRAMUNIFORMMATRIX4X2FV,
    SGL_CMD_PROGRAMUNIFORMMATRIX3X4FV,
    SGL_CMD_PROGRAMUNIFORMMATRIX4X3FV,
    SGL_CMD_PROGRAMUNIFORMMATRIX2X3DV,
    SGL_CMD_PROGRAMUNIFORMMATRIX3X2DV,
    SGL_CMD_PROGRAMUNIFORMMATRIX2X4DV,
    SGL_CMD_PROGRAMUNIFORMMATRIX4X2DV,
    SGL_CMD_PROGRAMUNIFORMMATRIX3X4DV,
    SGL_CMD_PROGRAMUNIFORMMATRIX4X3DV,
    SGL_CMD_VALIDATEPROGRAMPIPELINE,
    SGL_CMD_GETPROGRAMPIPELINEINFOLOG,
    SGL_CMD_VERTEXATTRIBL1D,
    SGL_CMD_VERTEXATTRIBL2D,
    SGL_CMD_VERTEXATTRIBL3D,
    SGL_CMD_VERTEXATTRIBL4D,
    SGL_CMD_VERTEXATTRIBL1DV,
    SGL_CMD_VERTEXATTRIBL2DV,
    SGL_CMD_VERTEXATTRIBL3DV,
    SGL_CMD_VERTEXATTRIBL4DV,
    SGL_CMD_VERTEXATTRIBLPOINTER,
    SGL_CMD_GETVERTEXATTRIBLDV,
    SGL_CMD_VIEWPORTARRAYV,
    SGL_CMD_VIEWPORTINDEXEDF,
    SGL_CMD_VIEWPORTINDEXEDFV,
    SGL_CMD_SCISSORARRAYV,
    SGL_CMD_SCISSORINDEXED,
    SGL_CMD_SCISSORINDEXEDV,
    SGL_CMD_DEPTHRANGEARRAYV,
    SGL_CMD_DEPTHRANGEINDEXED,
    SGL_CMD_GETFLOATI_V,
    SGL_CMD_GETDOUBLEI_V,
    SGL_CMD_DRAWARRAYSINSTANCEDBASEINSTANCE,
    SGL_CMD_DRAWELEMENTSINSTANCEDBASEINSTANCE,
    SGL_CMD_DRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCE,
    SGL_CMD_GETINTERNALFORMATIV,
    SGL_CMD_GETACTIVEATOMICCOUNTERBUFFERIV,
    SGL_CMD_BINDIMAGETEXTURE,
    SGL_CMD_MEMORYBARRIER,
    SGL_CMD_TEXSTORAGE1D,
    SGL_CMD_TEXSTORAGE2D,
    SGL_CMD_TEXSTORAGE3D,
    SGL_CMD_DRAWTRANSFORMFEEDBACKINSTANCED,
    SGL_CMD_DRAWTRANSFORMFEEDBACKSTREAMINSTANCED,
    SGL_CMD_CLEARBUFFERDATA,
    SGL_CMD_CLEARBUFFERSUBDATA,
    SGL_CMD_DISPATCHCOMPUTE,
    SGL_CMD_DISPATCHCOMPUTEINDIRECT,
    SGL_CMD_COPYIMAGESUBDATA,
    SGL_CMD_FRAMEBUFFERPARAMETERI,
    SGL_CMD_GETFRAMEBUFFERPARAMETERIV,
    SGL_CMD_GETINTERNALFORMATI64V,
    SGL_CMD_INVALIDATETEXSUBIMAGE,
    SGL_CMD_INVALIDATETEXIMAGE,
    SGL_CMD_INVALIDATEBUFFERSUBDATA,
    SGL_CMD_INVALIDATEBUFFERDATA,
    SGL_CMD_INVALIDATEFRAMEBUFFER,
    SGL_CMD_INVALIDATESUBFRAMEBUFFER,
    SGL_CMD_MULTIDRAWARRAYSINDIRECT,
    SGL_CMD_MULTIDRAWELEMENTSINDIRECT,
    SGL_CMD_GETPROGRAMINTERFACEIV,
    SGL_CMD_GETPROGRAMRESOURCEINDEX,
    SGL_CMD_GETPROGRAMRESOURCENAME,
    SGL_CMD_GETPROGRAMRESOURCEIV,
    SGL_CMD_GETPROGRAMRESOURCELOCATION,
    SGL_CMD_GETPROGRAMRESOURCELOCATIONINDEX,
    SGL_CMD_SHADERSTORAGEBLOCKBINDING,
    SGL_CMD_TEXBUFFERRANGE,
    SGL_CMD_TEXSTORAGE2DMULTISAMPLE,
    SGL_CMD_TEXSTORAGE3DMULTISAMPLE,
    SGL_CMD_TEXTUREVIEW,
    SGL_CMD_BINDVERTEXBUFFER,
    SGL_CMD_VERTEXATTRIBFORMAT,
    SGL_CMD_VERTEXATTRIBIFORMAT,
    SGL_CMD_VERTEXATTRIBLFORMAT,
    SGL_CMD_VERTEXATTRIBBINDING,
    SGL_CMD_VERTEXBINDINGDIVISOR,
    SGL_CMD_DEBUGMESSAGECONTROL,
    SGL_CMD_DEBUGMESSAGEINSERT,
    SGL_CMD_DEBUGMESSAGECALLBACK,
    SGL_CMD_GETDEBUGMESSAGELOG,
    SGL_CMD_PUSHDEBUGGROUP,
    SGL_CMD_POPDEBUGGROUP,
    SGL_CMD_OBJECTLABEL,
    SGL_CMD_GETOBJECTLABEL,
    SGL_CMD_OBJECTPTRLABEL,
    SGL_CMD_GETOBJECTPTRLABEL,
    SGL_CMD_BUFFERSTORAGE,
    SGL_CMD_CLEARTEXIMAGE,
    SGL_CMD_CLEARTEXSUBIMAGE,
    SGL_CMD_BINDBUFFERSBASE,
    SGL_CMD_BINDBUFFERSRANGE,
    SGL_CMD_BINDTEXTURES,
    SGL_CMD_BINDSAMPLERS,
    SGL_CMD_BINDIMAGETEXTURES,
    SGL_CMD_BINDVERTEXBUFFERS,
    SGL_CMD_CLIPCONTROL,
    SGL_CMD_CREATETRANSFORMFEEDBACKS,
    SGL_CMD_TRANSFORMFEEDBACKBUFFERBASE,
    SGL_CMD_TRANSFORMFEEDBACKBUFFERRANGE,
    SGL_CMD_GETTRANSFORMFEEDBACKIV,
    SGL_CMD_GETTRANSFORMFEEDBACKI_V,
    SGL_CMD_GETTRANSFORMFEEDBACKI64_V,
    SGL_CMD_CREATEBUFFERS,
    SGL_CMD_NAMEDBUFFERSTORAGE,
    SGL_CMD_NAMEDBUFFERDATA,
    SGL_CMD_NAMEDBUFFERSUBDATA,
    SGL_CMD_COPYNAMEDBUFFERSUBDATA,
    SGL_CMD_CLEARNAMEDBUFFERDATA,
    SGL_CMD_CLEARNAMEDBUFFERSUBDATA,
    SGL_CMD_MAPNAMEDBUFFER,
    SGL_CMD_MAPNAMEDBUFFERRANGE,
    SGL_CMD_UNMAPNAMEDBUFFER,
    SGL_CMD_FLUSHMAPPEDNAMEDBUFFERRANGE,
    SGL_CMD_GETNAMEDBUFFERPARAMETERIV,
    SGL_CMD_GETNAMEDBUFFERPARAMETERI64V,
    SGL_CMD_GETNAMEDBUFFERPOINTERV,
    SGL_CMD_GETNAMEDBUFFERSUBDATA,
    SGL_CMD_CREATEFRAMEBUFFERS,
    SGL_CMD_NAMEDFRAMEBUFFERRENDERBUFFER,
    SGL_CMD_NAMEDFRAMEBUFFERPARAMETERI,
    SGL_CMD_NAMEDFRAMEBUFFERTEXTURE,
    SGL_CMD_NAMEDFRAMEBUFFERTEXTURELAYER,
    SGL_CMD_NAMEDFRAMEBUFFERDRAWBUFFER,
    SGL_CMD_NAMEDFRAMEBUFFERDRAWBUFFERS,
    SGL_CMD_NAMEDFRAMEBUFFERREADBUFFER,
    SGL_CMD_INVALIDATENAMEDFRAMEBUFFERDATA,
    SGL_CMD_INVALIDATENAMEDFRAMEBUFFERSUBDATA,
    SGL_CMD_CLEARNAMEDFRAMEBUFFERIV,
    SGL_CMD_CLEARNAMEDFRAMEBUFFERUIV,
    SGL_CMD_CLEARNAMEDFRAMEBUFFERFV,
    SGL_CMD_CLEARNAMEDFRAMEBUFFERFI,
    SGL_CMD_BLITNAMEDFRAMEBUFFER,
    SGL_CMD_CHECKNAMEDFRAMEBUFFERSTATUS,
    SGL_CMD_GETNAMEDFRAMEBUFFERPARAMETERIV,
    SGL_CMD_GETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIV,
    SGL_CMD_CREATERENDERBUFFERS,
    SGL_CMD_NAMEDRENDERBUFFERSTORAGE,
    SGL_CMD_NAMEDRENDERBUFFERSTORAGEMULTISAMPLE,
    SGL_CMD_GETNAMEDRENDERBUFFERPARAMETERIV,
    SGL_CMD_CREATETEXTURES,
    SGL_CMD_TEXTUREBUFFER,
    SGL_CMD_TEXTUREBUFFERRANGE,
    SGL_CMD_TEXTURESTORAGE1D,
    SGL_CMD_TEXTURESTORAGE2D,
    SGL_CMD_TEXTURESTORAGE3D,
    SGL_CMD_TEXTURESTORAGE2DMULTISAMPLE,
    SGL_CMD_TEXTURESTORAGE3DMULTISAMPLE,
    SGL_CMD_TEXTURESUBIMAGE1D,
    SGL_CMD_TEXTURESUBIMAGE2D,
    SGL_CMD_TEXTURESUBIMAGE3D,
    SGL_CMD_COMPRESSEDTEXTURESUBIMAGE1D,
    SGL_CMD_COMPRESSEDTEXTURESUBIMAGE2D,
    SGL_CMD_COMPRESSEDTEXTURESUBIMAGE3D,
    SGL_CMD_COPYTEXTURESUBIMAGE1D,
    SGL_CMD_COPYTEXTURESUBIMAGE2D,
    SGL_CMD_COPYTEXTURESUBIMAGE3D,
    SGL_CMD_TEXTUREPARAMETERF,
    SGL_CMD_TEXTUREPARAMETERFV,
    SGL_CMD_TEXTUREPARAMETERI,
    SGL_CMD_TEXTUREPARAMETERIIV,
    SGL_CMD_TEXTUREPARAMETERIUIV,
    SGL_CMD_TEXTUREPARAMETERIV,
    SGL_CMD_GENERATETEXTUREMIPMAP,
    SGL_CMD_BINDTEXTUREUNIT,
    SGL_CMD_GETTEXTUREIMAGE,
    SGL_CMD_GETCOMPRESSEDTEXTUREIMAGE,
    SGL_CMD_GETTEXTURELEVELPARAMETERFV,
    SGL_CMD_GETTEXTURELEVELPARAMETERIV,
    SGL_CMD_GETTEXTUREPARAMETERFV,
    SGL_CMD_GETTEXTUREPARAMETERIIV,
    SGL_CMD_GETTEXTUREPARAMETERIUIV,
    SGL_CMD_GETTEXTUREPARAMETERIV,
    SGL_CMD_CREATEVERTEXARRAYS,
    SGL_CMD_DISABLEVERTEXARRAYATTRIB,
    SGL_CMD_ENABLEVERTEXARRAYATTRIB,
    SGL_CMD_VERTEXARRAYELEMENTBUFFER,
    SGL_CMD_VERTEXARRAYVERTEXBUFFER,
    SGL_CMD_VERTEXARRAYVERTEXBUFFERS,
    SGL_CMD_VERTEXARRAYATTRIBBINDING,
    SGL_CMD_VERTEXARRAYATTRIBFORMAT,
    SGL_CMD_VERTEXARRAYATTRIBIFORMAT,
    SGL_CMD_VERTEXARRAYATTRIBLFORMAT,
    SGL_CMD_VERTEXARRAYBINDINGDIVISOR,
    SGL_CMD_GETVERTEXARRAYIV,
    SGL_CMD_GETVERTEXARRAYINDEXEDIV,
    SGL_CMD_GETVERTEXARRAYINDEXED64IV,
    SGL_CMD_CREATESAMPLERS,
    SGL_CMD_CREATEPROGRAMPIPELINES,
    SGL_CMD_CREATEQUERIES,
    SGL_CMD_GETQUERYBUFFEROBJECTI64V,
    SGL_CMD_GETQUERYBUFFEROBJECTIV,
    SGL_CMD_GETQUERYBUFFEROBJECTUI64V,
    SGL_CMD_GETQUERYBUFFEROBJECTUIV,
    SGL_CMD_MEMORYBARRIERBYREGION,
    SGL_CMD_GETTEXTURESUBIMAGE,
    SGL_CMD_GETCOMPRESSEDTEXTURESUBIMAGE,
    SGL_CMD_GETGRAPHICSRESETSTATUS,
    SGL_CMD_GETNCOMPRESSEDTEXIMAGE,
    SGL_CMD_GETNTEXIMAGE,
    SGL_CMD_GETNUNIFORMDV,
    SGL_CMD_GETNUNIFORMFV,
    SGL_CMD_GETNUNIFORMIV,
    SGL_CMD_GETNUNIFORMUIV,
    SGL_CMD_READNPIXELS,
    SGL_CMD_GETNMAPDV,
    SGL_CMD_GETNMAPFV,
    SGL_CMD_GETNMAPIV,
    SGL_CMD_GETNPIXELMAPFV,
    SGL_CMD_GETNPIXELMAPUIV,
    SGL_CMD_GETNPIXELMAPUSV,
    SGL_CMD_GETNPOLYGONSTIPPLE,
    SGL_CMD_GETNCOLORTABLE,
    SGL_CMD_GETNCONVOLUTIONFILTER,
    SGL_CMD_GETNSEPARABLEFILTER,
    SGL_CMD_GETNHISTOGRAM,
    SGL_CMD_GETNMINMAX,
    SGL_CMD_TEXTUREBARRIER,
    SGL_CMD_SPECIALIZESHADER,
    SGL_CMD_MULTIDRAWARRAYSINDIRECTCOUNT,
    SGL_CMD_MULTIDRAWELEMENTSINDIRECTCOUNT,
    SGL_CMD_POLYGONOFFSETCLAMP,
    SGL_CMD_MAX
};

#endif