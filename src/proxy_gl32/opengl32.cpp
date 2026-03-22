#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include "proxy_gl32.h"

#pragma comment(lib, "opengl32.lib")

typedef const GLubyte* (WINAPI* PFN_glGetString)(GLenum name);
typedef void (WINAPI* PFN_glEnable)(GLenum cap);
typedef void (WINAPI* PFN_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
typedef PROC (WINAPI* PFN_wglGetProcAddress)(LPCSTR name);
typedef BOOL (WINAPI* PFN_wglSwapBuffers)(HDC hdc);

PFN_glGetString orig_glGetString = nullptr;
PFN_glEnable orig_glEnable = nullptr;
PFN_glTexParameterf orig_glTexParameterf = nullptr;
PFN_wglGetProcAddress orig_wglGetProcAddress = nullptr;
PFN_wglSwapBuffers orig_wglSwapBuffers = nullptr;
HINSTANCE mHinst = 0, mHinstDLL = 0;

BOOL WINAPI fake_wglSwapIntervalEXT(int interval) {
    return TRUE; 
}

extern "C" UINT_PTR mProcs[368] = {0};

LPCSTR mImportNames[] = {
  "GlmfBeginGlsBlock",
  "GlmfCloseMetaFile",
  "GlmfEndGlsBlock",
  "GlmfEndPlayback",
  "GlmfInitPlayback",
  "GlmfPlayGlsRecord",
  "glAccum",
  "glAlphaFunc",
  "glAreTexturesResident",
  "glArrayElement",
  "glBegin",
  "glBindTexture",
  "glBitmap",
  "glBlendFunc",
  "glCallList",
  "glCallLists",
  "glClear",
  "glClearAccum",
  "glClearColor",
  "glClearDepth",
  "glClearIndex",
  "glClearStencil",
  "glClipPlane",
  "glColor3b",
  "glColor3bv",
  "glColor3d",
  "glColor3dv",
  "glColor3f",
  "glColor3fv",
  "glColor3i",
  "glColor3iv",
  "glColor3s",
  "glColor3sv",
  "glColor3ub",
  "glColor3ubv",
  "glColor3ui",
  "glColor3uiv",
  "glColor3us",
  "glColor3usv",
  "glColor4b",
  "glColor4bv",
  "glColor4d",
  "glColor4dv",
  "glColor4f",
  "glColor4fv",
  "glColor4i",
  "glColor4iv",
  "glColor4s",
  "glColor4sv",
  "glColor4ub",
  "glColor4ubv",
  "glColor4ui",
  "glColor4uiv",
  "glColor4us",
  "glColor4usv",
  "glColorMask",
  "glColorMaterial",
  "glColorPointer",
  "glCopyPixels",
  "glCopyTexImage1D",
  "glCopyTexImage2D",
  "glCopyTexSubImage1D",
  "glCopyTexSubImage2D",
  "glCullFace",
  "glDebugEntry",
  "glDeleteLists",
  "glDeleteTextures",
  "glDepthFunc",
  "glDepthMask",
  "glDepthRange",
  "glDisable",
  "glDisableClientState",
  "glDrawArrays",
  "glDrawBuffer",
  "glDrawElements",
  "glDrawPixels",
  "glEdgeFlag",
  "glEdgeFlagPointer",
  "glEdgeFlagv",
  "glEnable",
  "glEnableClientState",
  "glEnd",
  "glEndList",
  "glEvalCoord1d",
  "glEvalCoord1dv",
  "glEvalCoord1f",
  "glEvalCoord1fv",
  "glEvalCoord2d",
  "glEvalCoord2dv",
  "glEvalCoord2f",
  "glEvalCoord2fv",
  "glEvalMesh1",
  "glEvalMesh2",
  "glEvalPoint1",
  "glEvalPoint2",
  "glFeedbackBuffer",
  "glFinish",
  "glFlush",
  "glFogf",
  "glFogfv",
  "glFogi",
  "glFogiv",
  "glFrontFace",
  "glFrustum",
  "glGenLists",
  "glGenTextures",
  "glGetBooleanv",
  "glGetClipPlane",
  "glGetDoublev",
  "glGetError",
  "glGetFloatv",
  "glGetIntegerv",
  "glGetLightfv",
  "glGetLightiv",
  "glGetMapdv",
  "glGetMapfv",
  "glGetMapiv",
  "glGetMaterialfv",
  "glGetMaterialiv",
  "glGetPixelMapfv",
  "glGetPixelMapuiv",
  "glGetPixelMapusv",
  "glGetPointerv",
  "glGetPolygonStipple",
  "glGetString",
  "glGetTexEnvfv",
  "glGetTexEnviv",
  "glGetTexGendv",
  "glGetTexGenfv",
  "glGetTexGeniv",
  "glGetTexImage",
  "glGetTexLevelParameterfv",
  "glGetTexLevelParameteriv",
  "glGetTexParameterfv",
  "glGetTexParameteriv",
  "glHint",
  "glIndexMask",
  "glIndexPointer",
  "glIndexd",
  "glIndexdv",
  "glIndexf",
  "glIndexfv",
  "glIndexi",
  "glIndexiv",
  "glIndexs",
  "glIndexsv",
  "glIndexub",
  "glIndexubv",
  "glInitNames",
  "glInterleavedArrays",
  "glIsEnabled",
  "glIsList",
  "glIsTexture",
  "glLightModelf",
  "glLightModelfv",
  "glLightModeli",
  "glLightModeliv",
  "glLightf",
  "glLightfv",
  "glLighti",
  "glLightiv",
  "glLineStipple",
  "glLineWidth",
  "glListBase",
  "glLoadIdentity",
  "glLoadMatrixd",
  "glLoadMatrixf",
  "glLoadName",
  "glLogicOp",
  "glMap1d",
  "glMap1f",
  "glMap2d",
  "glMap2f",
  "glMapGrid1d",
  "glMapGrid1f",
  "glMapGrid2d",
  "glMapGrid2f",
  "glMaterialf",
  "glMaterialfv",
  "glMateriali",
  "glMaterialiv",
  "glMatrixMode",
  "glMultMatrixd",
  "glMultMatrixf",
  "glNewList",
  "glNormal3b",
  "glNormal3bv",
  "glNormal3d",
  "glNormal3dv",
  "glNormal3f",
  "glNormal3fv",
  "glNormal3i",
  "glNormal3iv",
  "glNormal3s",
  "glNormal3sv",
  "glNormalPointer",
  "glOrtho",
  "glPassThrough",
  "glPixelMapfv",
  "glPixelMapuiv",
  "glPixelMapusv",
  "glPixelStoref",
  "glPixelStorei",
  "glPixelTransferf",
  "glPixelTransferi",
  "glPixelZoom",
  "glPointSize",
  "glPolygonMode",
  "glPolygonOffset",
  "glPolygonStipple",
  "glPopAttrib",
  "glPopClientAttrib",
  "glPopMatrix",
  "glPopName",
  "glPrioritizeTextures",
  "glPushAttrib",
  "glPushClientAttrib",
  "glPushMatrix",
  "glPushName",
  "glRasterPos2d",
  "glRasterPos2dv",
  "glRasterPos2f",
  "glRasterPos2fv",
  "glRasterPos2i",
  "glRasterPos2iv",
  "glRasterPos2s",
  "glRasterPos2sv",
  "glRasterPos3d",
  "glRasterPos3dv",
  "glRasterPos3f",
  "glRasterPos3fv",
  "glRasterPos3i",
  "glRasterPos3iv",
  "glRasterPos3s",
  "glRasterPos3sv",
  "glRasterPos4d",
  "glRasterPos4dv",
  "glRasterPos4f",
  "glRasterPos4fv",
  "glRasterPos4i",
  "glRasterPos4iv",
  "glRasterPos4s",
  "glRasterPos4sv",
  "glReadBuffer",
  "glReadPixels",
  "glRectd",
  "glRectdv",
  "glRectf",
  "glRectfv",
  "glRecti",
  "glRectiv",
  "glRects",
  "glRectsv",
  "glRenderMode",
  "glRotated",
  "glRotatef",
  "glScaled",
  "glScalef",
  "glScissor",
  "glSelectBuffer",
  "glShadeModel",
  "glStencilFunc",
  "glStencilMask",
  "glStencilOp",
  "glTexCoord1d",
  "glTexCoord1dv",
  "glTexCoord1f",
  "glTexCoord1fv",
  "glTexCoord1i",
  "glTexCoord1iv",
  "glTexCoord1s",
  "glTexCoord1sv",
  "glTexCoord2d",
  "glTexCoord2dv",
  "glTexCoord2f",
  "glTexCoord2fv",
  "glTexCoord2i",
  "glTexCoord2iv",
  "glTexCoord2s",
  "glTexCoord2sv",
  "glTexCoord3d",
  "glTexCoord3dv",
  "glTexCoord3f",
  "glTexCoord3fv",
  "glTexCoord3i",
  "glTexCoord3iv",
  "glTexCoord3s",
  "glTexCoord3sv",
  "glTexCoord4d",
  "glTexCoord4dv",
  "glTexCoord4f",
  "glTexCoord4fv",
  "glTexCoord4i",
  "glTexCoord4iv",
  "glTexCoord4s",
  "glTexCoord4sv",
  "glTexCoordPointer",
  "glTexEnvf",
  "glTexEnvfv",
  "glTexEnvi",
  "glTexEnviv",
  "glTexGend",
  "glTexGendv",
  "glTexGenf",
  "glTexGenfv",
  "glTexGeni",
  "glTexGeniv",
  "glTexImage1D",
  "glTexImage2D",
  "glTexParameterf",
  "glTexParameterfv",
  "glTexParameteri",
  "glTexParameteriv",
  "glTexSubImage1D",
  "glTexSubImage2D",
  "glTranslated",
  "glTranslatef",
  "glVertex2d",
  "glVertex2dv",
  "glVertex2f",
  "glVertex2fv",
  "glVertex2i",
  "glVertex2iv",
  "glVertex2s",
  "glVertex2sv",
  "glVertex3d",
  "glVertex3dv",
  "glVertex3f",
  "glVertex3fv",
  "glVertex3i",
  "glVertex3iv",
  "glVertex3s",
  "glVertex3sv",
  "glVertex4d",
  "glVertex4dv",
  "glVertex4f",
  "glVertex4fv",
  "glVertex4i",
  "glVertex4iv",
  "glVertex4s",
  "glVertex4sv",
  "glVertexPointer",
  "glViewport",
  "wglChoosePixelFormat",
  "wglCopyContext",
  "wglCreateContext",
  "wglCreateLayerContext",
  "wglDeleteContext",
  "wglDescribeLayerPlane",
  "wglDescribePixelFormat",
  "wglGetCurrentContext",
  "wglGetCurrentDC",
  "wglGetDefaultProcAddress",
  "wglGetLayerPaletteEntries",
  "wglGetPixelFormat",
  "wglGetProcAddress",
  "wglMakeCurrent",
  "wglRealizeLayerPalette",
  "wglSetLayerPaletteEntries",
  "wglSetPixelFormat",
  "wglShareLists",
  "wglSwapBuffers",
  "wglSwapLayerBuffers",
  "wglSwapMultipleBuffers",
  "wglUseFontBitmapsA",
  "wglUseFontBitmapsW",
  "wglUseFontOutlinesA",
  "wglUseFontOutlinesW",
};

const GLubyte* WINAPI h_glGetString(GLenum name) {
    if (name == GL_VENDOR) return (const GLubyte*)"NVIDIA Corporation";
    if (name == GL_RENDERER) return (const GLubyte*)"NVIDIA GeForce RTX 4090";
    if (name == GL_VERSION) return (const GLubyte*)"4.6.0 NVIDIA 551.23";
    if (orig_glGetString) return orig_glGetString(name);
    return (const GLubyte*)"";
}

void WINAPI h_glEnable(GLenum cap) {
    if (cap == GL_FOG || cap == GL_LIGHTING) return;
    if (orig_glEnable) orig_glEnable(cap);
}

void WINAPI h_glTexParameterf(GLenum target, GLenum pname, GLfloat param) {
    if (pname == 0x85B3) {
        if (orig_glTexParameterf) orig_glTexParameterf(target, pname, 3.0f);
        return;
    }
    if (orig_glTexParameterf) orig_glTexParameterf(target, pname, param);
}

BOOL WINAPI h_wglSwapBuffers(HDC hdc) {
    glFlush(); 
    if (orig_wglSwapBuffers) return orig_wglSwapBuffers(hdc);
    return FALSE;
}

PROC WINAPI h_wglGetProcAddress(LPCSTR name) {
    if (name && strcmp(name, "wglSwapIntervalEXT") == 0) {
        return (PROC)fake_wglSwapIntervalEXT;
    }
    if (orig_wglGetProcAddress) return orig_wglGetProcAddress(name);
    return nullptr;
}

#ifndef _DEBUG
inline void log_info(const char* info) {
}
#else
FILE* debug;
inline void log_info(const char* info) {
  fprintf(debug, "%s\n", info);
  fflush(debug);
}
#endif

#include "empty.h"

inline void _hook_setup() {
  for (int i = 0; i < 368; i++) {
    if (!mImportNames[i]) continue;
    
    if (strcmp(mImportNames[i], "glTexParameterf") == 0) {
        orig_glTexParameterf = (PFN_glTexParameterf)mProcs[i];
        mProcs[i] = (UINT_PTR)h_glTexParameterf;
    }
    else if (strcmp(mImportNames[i], "glGetString") == 0) {
        orig_glGetString = (PFN_glGetString)mProcs[i];
        mProcs[i] = (UINT_PTR)h_glGetString;
    }
    else if (strcmp(mImportNames[i], "glEnable") == 0) {
        orig_glEnable = (PFN_glEnable)mProcs[i];
        mProcs[i] = (UINT_PTR)h_glEnable;
    }
    else if (strcmp(mImportNames[i], "wglSwapBuffers") == 0) {
        orig_wglSwapBuffers = (PFN_wglSwapBuffers)mProcs[i];
        mProcs[i] = (UINT_PTR)h_wglSwapBuffers;
    }
    else if (strcmp(mImportNames[i], "wglGetProcAddress") == 0) {
        orig_wglGetProcAddress = (PFN_wglGetProcAddress)mProcs[i];
        mProcs[i] = (UINT_PTR)h_wglGetProcAddress;
    }
}

#ifdef GLMFBEGINGLSBLOCK
  GlmfBeginGlsBlock_real = (GlmfBeginGlsBlock_ptr)mProcs[0];
  mProcs[0] = (UINT_PTR)&GlmfBeginGlsBlock_fake;
#endif
#ifdef GLMFCLOSEMETAFILE
  GlmfCloseMetaFile_real = (GlmfCloseMetaFile_ptr)mProcs[1];
  mProcs[1] = (UINT_PTR)&GlmfCloseMetaFile_fake;
#endif
#ifdef GLMFENDGLSBLOCK
  GlmfEndGlsBlock_real = (GlmfEndGlsBlock_ptr)mProcs[2];
  mProcs[2] = (UINT_PTR)&GlmfEndGlsBlock_fake;
#endif
#ifdef GLMFENDPLAYBACK
  GlmfEndPlayback_real = (GlmfEndPlayback_ptr)mProcs[3];
  mProcs[3] = (UINT_PTR)&GlmfEndPlayback_fake;
#endif
#ifdef GLMFINITPLAYBACK
  GlmfInitPlayback_real = (GlmfInitPlayback_ptr)mProcs[4];
  mProcs[4] = (UINT_PTR)&GlmfInitPlayback_fake;
#endif
#ifdef GLMFPLAYGLSRECORD
  GlmfPlayGlsRecord_real = (GlmfPlayGlsRecord_ptr)mProcs[5];
  mProcs[5] = (UINT_PTR)&GlmfPlayGlsRecord_fake;
#endif
#ifdef GLACCUM
  glAccum_real = (glAccum_ptr)mProcs[6];
  mProcs[6] = (UINT_PTR)&glAccum_fake;
#endif
#ifdef GLALPHAFUNC
  glAlphaFunc_real = (glAlphaFunc_ptr)mProcs[7];
  mProcs[7] = (UINT_PTR)&glAlphaFunc_fake;
#endif
#ifdef GLARETEXTURESRESIDENT
  glAreTexturesResident_real = (glAreTexturesResident_ptr)mProcs[8];
  mProcs[8] = (UINT_PTR)&glAreTexturesResident_fake;
#endif
#ifdef GLARRAYELEMENT
  glArrayElement_real = (glArrayElement_ptr)mProcs[9];
  mProcs[9] = (UINT_PTR)&glArrayElement_fake;
#endif
#ifdef GLBEGIN
  glBegin_real = (glBegin_ptr)mProcs[10];
  mProcs[10] = (UINT_PTR)&glBegin_fake;
#endif
#ifdef GLBINDTEXTURE
  glBindTexture_real = (glBindTexture_ptr)mProcs[11];
  mProcs[11] = (UINT_PTR)&glBindTexture_fake;
#endif
#ifdef GLBITMAP
  glBitmap_real = (glBitmap_ptr)mProcs[12];
  mProcs[12] = (UINT_PTR)&glBitmap_fake;
#endif
#ifdef GLBLENDFUNC
  glBlendFunc_real = (glBlendFunc_ptr)mProcs[13];
  mProcs[13] = (UINT_PTR)&glBlendFunc_fake;
#endif
#ifdef GLCALLLIST
  glCallList_real = (glCallList_ptr)mProcs[14];
  mProcs[14] = (UINT_PTR)&glCallList_fake;
#endif
#ifdef GLCALLLISTS
  glCallLists_real = (glCallLists_ptr)mProcs[15];
  mProcs[15] = (UINT_PTR)&glCallLists_fake;
#endif
#ifdef GLCLEAR
  glClear_real = (glClear_ptr)mProcs[16];
  mProcs[16] = (UINT_PTR)&glClear_fake;
#endif
#ifdef GLCLEARACCUM
  glClearAccum_real = (glClearAccum_ptr)mProcs[17];
  mProcs[17] = (UINT_PTR)&glClearAccum_fake;
#endif
#ifdef GLCLEARCOLOR
  glClearColor_real = (glClearColor_ptr)mProcs[18];
  mProcs[18] = (UINT_PTR)&glClearColor_fake;
#endif
#ifdef GLCLEARDEPTH
  glClearDepth_real = (glClearDepth_ptr)mProcs[19];
  mProcs[19] = (UINT_PTR)&glClearDepth_fake;
#endif
#ifdef GLCLEARINDEX
  glClearIndex_real = (glClearIndex_ptr)mProcs[20];
  mProcs[20] = (UINT_PTR)&glClearIndex_fake;
#endif
#ifdef GLCLEARSTENCIL
  glClearStencil_real = (glClearStencil_ptr)mProcs[21];
  mProcs[21] = (UINT_PTR)&glClearStencil_fake;
#endif
#ifdef GLCLIPPLANE
  glClipPlane_real = (glClipPlane_ptr)mProcs[22];
  mProcs[22] = (UINT_PTR)&glClipPlane_fake;
#endif
#ifdef GLCOLOR3B
  glColor3b_real = (glColor3b_ptr)mProcs[23];
  mProcs[23] = (UINT_PTR)&glColor3b_fake;
#endif
#ifdef GLCOLOR3BV
  glColor3bv_real = (glColor3bv_ptr)mProcs[24];
  mProcs[24] = (UINT_PTR)&glColor3bv_fake;
#endif
#ifdef GLCOLOR3D
  glColor3d_real = (glColor3d_ptr)mProcs[25];
  mProcs[25] = (UINT_PTR)&glColor3d_fake;
#endif
#ifdef GLCOLOR3DV
  glColor3dv_real = (glColor3dv_ptr)mProcs[26];
  mProcs[26] = (UINT_PTR)&glColor3dv_fake;
#endif
#ifdef GLCOLOR3F
  glColor3f_real = (glColor3f_ptr)mProcs[27];
  mProcs[27] = (UINT_PTR)&glColor3f_fake;
#endif
#ifdef GLCOLOR3FV
  glColor3fv_real = (glColor3fv_ptr)mProcs[28];
  mProcs[28] = (UINT_PTR)&glColor3fv_fake;
#endif
#ifdef GLCOLOR3I
  glColor3i_real = (glColor3i_ptr)mProcs[29];
  mProcs[29] = (UINT_PTR)&glColor3i_fake;
#endif
#ifdef GLCOLOR3IV
  glColor3iv_real = (glColor3iv_ptr)mProcs[30];
  mProcs[30] = (UINT_PTR)&glColor3iv_fake;
#endif
#ifdef GLCOLOR3S
  glColor3s_real = (glColor3s_ptr)mProcs[31];
  mProcs[31] = (UINT_PTR)&glColor3s_fake;
#endif
#ifdef GLCOLOR3SV
  glColor3sv_real = (glColor3sv_ptr)mProcs[32];
  mProcs[32] = (UINT_PTR)&glColor3sv_fake;
#endif
#ifdef GLCOLOR3UB
  glColor3ub_real = (glColor3ub_ptr)mProcs[33];
  mProcs[33] = (UINT_PTR)&glColor3ub_fake;
#endif
#ifdef GLCOLOR3UBV
  glColor3ubv_real = (glColor3ubv_ptr)mProcs[34];
  mProcs[34] = (UINT_PTR)&glColor3ubv_fake;
#endif
#ifdef GLCOLOR3UI
  glColor3ui_real = (glColor3ui_ptr)mProcs[35];
  mProcs[35] = (UINT_PTR)&glColor3ui_fake;
#endif
#ifdef GLCOLOR3UIV
  glColor3uiv_real = (glColor3uiv_ptr)mProcs[36];
  mProcs[36] = (UINT_PTR)&glColor3uiv_fake;
#endif
#ifdef GLCOLOR3US
  glColor3us_real = (glColor3us_ptr)mProcs[37];
  mProcs[37] = (UINT_PTR)&glColor3us_fake;
#endif
#ifdef GLCOLOR3USV
  glColor3usv_real = (glColor3usv_ptr)mProcs[38];
  mProcs[38] = (UINT_PTR)&glColor3usv_fake;
#endif
#ifdef GLCOLOR4B
  glColor4b_real = (glColor4b_ptr)mProcs[39];
  mProcs[39] = (UINT_PTR)&glColor4b_fake;
#endif
#ifdef GLCOLOR4BV
  glColor4bv_real = (glColor4bv_ptr)mProcs[40];
  mProcs[40] = (UINT_PTR)&glColor4bv_fake;
#endif
#ifdef GLCOLOR4D
  glColor4d_real = (glColor4d_ptr)mProcs[41];
  mProcs[41] = (UINT_PTR)&glColor4d_fake;
#endif
#ifdef GLCOLOR4DV
  glColor4dv_real = (glColor4dv_ptr)mProcs[42];
  mProcs[42] = (UINT_PTR)&glColor4dv_fake;
#endif
#ifdef GLCOLOR4F
  glColor4f_real = (glColor4f_ptr)mProcs[43];
  mProcs[43] = (UINT_PTR)&glColor4f_fake;
#endif
#ifdef GLCOLOR4FV
  glColor4fv_real = (glColor4fv_ptr)mProcs[44];
  mProcs[44] = (UINT_PTR)&glColor4fv_fake;
#endif
#ifdef GLCOLOR4I
  glColor4i_real = (glColor4i_ptr)mProcs[45];
  mProcs[45] = (UINT_PTR)&glColor4i_fake;
#endif
#ifdef GLCOLOR4IV
  glColor4iv_real = (glColor4iv_ptr)mProcs[46];
  mProcs[46] = (UINT_PTR)&glColor4iv_fake;
#endif
#ifdef GLCOLOR4S
  glColor4s_real = (glColor4s_ptr)mProcs[47];
  mProcs[47] = (UINT_PTR)&glColor4s_fake;
#endif
#ifdef GLCOLOR4SV
  glColor4sv_real = (glColor4sv_ptr)mProcs[48];
  mProcs[48] = (UINT_PTR)&glColor4sv_fake;
#endif
#ifdef GLCOLOR4UB
  glColor4ub_real = (glColor4ub_ptr)mProcs[49];
  mProcs[49] = (UINT_PTR)&glColor4ub_fake;
#endif
#ifdef GLCOLOR4UBV
  glColor4ubv_real = (glColor4ubv_ptr)mProcs[50];
  mProcs[50] = (UINT_PTR)&glColor4ubv_fake;
#endif
#ifdef GLCOLOR4UI
  glColor4ui_real = (glColor4ui_ptr)mProcs[51];
  mProcs[51] = (UINT_PTR)&glColor4ui_fake;
#endif
#ifdef GLCOLOR4UIV
  glColor4uiv_real = (glColor4uiv_ptr)mProcs[52];
  mProcs[52] = (UINT_PTR)&glColor4uiv_fake;
#endif
#ifdef GLCOLOR4US
  glColor4us_real = (glColor4us_ptr)mProcs[53];
  mProcs[53] = (UINT_PTR)&glColor4us_fake;
#endif
#ifdef GLCOLOR4USV
  glColor4usv_real = (glColor4usv_ptr)mProcs[54];
  mProcs[54] = (UINT_PTR)&glColor4usv_fake;
#endif
#ifdef GLCOLORMASK
  glColorMask_real = (glColorMask_ptr)mProcs[55];
  mProcs[55] = (UINT_PTR)&glColorMask_fake;
#endif
#ifdef GLCOLORMATERIAL
  glColorMaterial_real = (glColorMaterial_ptr)mProcs[56];
  mProcs[56] = (UINT_PTR)&glColorMaterial_fake;
#endif
#ifdef GLCOLORPOINTER
  glColorPointer_real = (glColorPointer_ptr)mProcs[57];
  mProcs[57] = (UINT_PTR)&glColorPointer_fake;
#endif
#ifdef GLCOPYPIXELS
  glCopyPixels_real = (glCopyPixels_ptr)mProcs[58];
  mProcs[58] = (UINT_PTR)&glCopyPixels_fake;
#endif
#ifdef GLCOPYTEXIMAGE1D
  glCopyTexImage1D_real = (glCopyTexImage1D_ptr)mProcs[59];
  mProcs[59] = (UINT_PTR)&glCopyTexImage1D_fake;
#endif
#ifdef GLCOPYTEXIMAGE2D
  glCopyTexImage2D_real = (glCopyTexImage2D_ptr)mProcs[60];
  mProcs[60] = (UINT_PTR)&glCopyTexImage2D_fake;
#endif
#ifdef GLCOPYTEXSUBIMAGE1D
  glCopyTexSubImage1D_real = (glCopyTexSubImage1D_ptr)mProcs[61];
  mProcs[61] = (UINT_PTR)&glCopyTexSubImage1D_fake;
#endif
#ifdef GLCOPYTEXSUBIMAGE2D
  glCopyTexSubImage2D_real = (glCopyTexSubImage2D_ptr)mProcs[62];
  mProcs[62] = (UINT_PTR)&glCopyTexSubImage2D_fake;
#endif
#ifdef GLCULLFACE
  glCullFace_real = (glCullFace_ptr)mProcs[63];
  mProcs[63] = (UINT_PTR)&glCullFace_fake;
#endif
#ifdef GLDEBUGENTRY
  glDebugEntry_real = (glDebugEntry_ptr)mProcs[64];
  mProcs[64] = (UINT_PTR)&glDebugEntry_fake;
#endif
#ifdef GLDELETELISTS
  glDeleteLists_real = (glDeleteLists_ptr)mProcs[65];
  mProcs[65] = (UINT_PTR)&glDeleteLists_fake;
#endif
#ifdef GLDELETETEXTURES
  glDeleteTextures_real = (glDeleteTextures_ptr)mProcs[66];
  mProcs[66] = (UINT_PTR)&glDeleteTextures_fake;
#endif
#ifdef GLDEPTHFUNC
  glDepthFunc_real = (glDepthFunc_ptr)mProcs[67];
  mProcs[67] = (UINT_PTR)&glDepthFunc_fake;
#endif
#ifdef GLDEPTHMASK
  glDepthMask_real = (glDepthMask_ptr)mProcs[68];
  mProcs[68] = (UINT_PTR)&glDepthMask_fake;
#endif
#ifdef GLDEPTHRANGE
  glDepthRange_real = (glDepthRange_ptr)mProcs[69];
  mProcs[69] = (UINT_PTR)&glDepthRange_fake;
#endif
#ifdef GLDISABLE
  glDisable_real = (glDisable_ptr)mProcs[70];
  mProcs[70] = (UINT_PTR)&glDisable_fake;
#endif
#ifdef GLDISABLECLIENTSTATE
  glDisableClientState_real = (glDisableClientState_ptr)mProcs[71];
  mProcs[71] = (UINT_PTR)&glDisableClientState_fake;
#endif
#ifdef GLDRAWARRAYS
  glDrawArrays_real = (glDrawArrays_ptr)mProcs[72];
  mProcs[72] = (UINT_PTR)&glDrawArrays_fake;
#endif
#ifdef GLDRAWBUFFER
  glDrawBuffer_real = (glDrawBuffer_ptr)mProcs[73];
  mProcs[73] = (UINT_PTR)&glDrawBuffer_fake;
#endif
#ifdef GLDRAWELEMENTS
  glDrawElements_real = (glDrawElements_ptr)mProcs[74];
  mProcs[74] = (UINT_PTR)&glDrawElements_fake;
#endif
#ifdef GLDRAWPIXELS
  glDrawPixels_real = (glDrawPixels_ptr)mProcs[75];
  mProcs[75] = (UINT_PTR)&glDrawPixels_fake;
#endif
#ifdef GLEDGEFLAG
  glEdgeFlag_real = (glEdgeFlag_ptr)mProcs[76];
  mProcs[76] = (UINT_PTR)&glEdgeFlag_fake;
#endif
#ifdef GLEDGEFLAGPOINTER
  glEdgeFlagPointer_real = (glEdgeFlagPointer_ptr)mProcs[77];
  mProcs[77] = (UINT_PTR)&glEdgeFlagPointer_fake;
#endif
#ifdef GLEDGEFLAGV
  glEdgeFlagv_real = (glEdgeFlagv_ptr)mProcs[78];
  mProcs[78] = (UINT_PTR)&glEdgeFlagv_fake;
#endif
#ifdef GLENABLE
  glEnable_real = (glEnable_ptr)mProcs[79];
  mProcs[79] = (UINT_PTR)&glEnable_fake;
#endif
#ifdef GLENABLECLIENTSTATE
  glEnableClientState_real = (glEnableClientState_ptr)mProcs[80];
  mProcs[80] = (UINT_PTR)&glEnableClientState_fake;
#endif
#ifdef GLEND
  glEnd_real = (glEnd_ptr)mProcs[81];
  mProcs[81] = (UINT_PTR)&glEnd_fake;
#endif
#ifdef GLENDLIST
  glEndList_real = (glEndList_ptr)mProcs[82];
  mProcs[82] = (UINT_PTR)&glEndList_fake;
#endif
#ifdef GLEVALCOORD1D
  glEvalCoord1d_real = (glEvalCoord1d_ptr)mProcs[83];
  mProcs[83] = (UINT_PTR)&glEvalCoord1d_fake;
#endif
#ifdef GLEVALCOORD1DV
  glEvalCoord1dv_real = (glEvalCoord1dv_ptr)mProcs[84];
  mProcs[84] = (UINT_PTR)&glEvalCoord1dv_fake;
#endif
#ifdef GLEVALCOORD1F
  glEvalCoord1f_real = (glEvalCoord1f_ptr)mProcs[85];
  mProcs[85] = (UINT_PTR)&glEvalCoord1f_fake;
#endif
#ifdef GLEVALCOORD1FV
  glEvalCoord1fv_real = (glEvalCoord1fv_ptr)mProcs[86];
  mProcs[86] = (UINT_PTR)&glEvalCoord1fv_fake;
#endif
#ifdef GLEVALCOORD2D
  glEvalCoord2d_real = (glEvalCoord2d_ptr)mProcs[87];
  mProcs[87] = (UINT_PTR)&glEvalCoord2d_fake;
#endif
#ifdef GLEVALCOORD2DV
  glEvalCoord2dv_real = (glEvalCoord2dv_ptr)mProcs[88];
  mProcs[88] = (UINT_PTR)&glEvalCoord2dv_fake;
#endif
#ifdef GLEVALCOORD2F
  glEvalCoord2f_real = (glEvalCoord2f_ptr)mProcs[89];
  mProcs[89] = (UINT_PTR)&glEvalCoord2f_fake;
#endif
#ifdef GLEVALCOORD2FV
  glEvalCoord2fv_real = (glEvalCoord2fv_ptr)mProcs[90];
  mProcs[90] = (UINT_PTR)&glEvalCoord2fv_fake;
#endif
#ifdef GLEVALMESH1
  glEvalMesh1_real = (glEvalMesh1_ptr)mProcs[91];
  mProcs[91] = (UINT_PTR)&glEvalMesh1_fake;
#endif
#ifdef GLEVALMESH2
  glEvalMesh2_real = (glEvalMesh2_ptr)mProcs[92];
  mProcs[92] = (UINT_PTR)&glEvalMesh2_fake;
#endif
#ifdef GLEVALPOINT1
  glEvalPoint1_real = (glEvalPoint1_ptr)mProcs[93];
  mProcs[93] = (UINT_PTR)&glEvalPoint1_fake;
#endif
#ifdef GLEVALPOINT2
  glEvalPoint2_real = (glEvalPoint2_ptr)mProcs[94];
  mProcs[94] = (UINT_PTR)&glEvalPoint2_fake;
#endif
#ifdef GLFEEDBACKBUFFER
  glFeedbackBuffer_real = (glFeedbackBuffer_ptr)mProcs[95];
  mProcs[95] = (UINT_PTR)&glFeedbackBuffer_fake;
#endif
#ifdef GLFINISH
  glFinish_real = (glFinish_ptr)mProcs[96];
  mProcs[96] = (UINT_PTR)&glFinish_fake;
#endif
#ifdef GLFLUSH
  glFlush_real = (glFlush_ptr)mProcs[97];
  mProcs[97] = (UINT_PTR)&glFlush_fake;
#endif
#ifdef GLFOGF
  glFogf_real = (glFogf_ptr)mProcs[98];
  mProcs[98] = (UINT_PTR)&glFogf_fake;
#endif
#ifdef GLFOGFV
  glFogfv_real = (glFogfv_ptr)mProcs[99];
  mProcs[99] = (UINT_PTR)&glFogfv_fake;
#endif
#ifdef GLFOGI
  glFogi_real = (glFogi_ptr)mProcs[100];
  mProcs[100] = (UINT_PTR)&glFogi_fake;
#endif
#ifdef GLFOGIV
  glFogiv_real = (glFogiv_ptr)mProcs[101];
  mProcs[101] = (UINT_PTR)&glFogiv_fake;
#endif
#ifdef GLFRONTFACE
  glFrontFace_real = (glFrontFace_ptr)mProcs[102];
  mProcs[102] = (UINT_PTR)&glFrontFace_fake;
#endif
#ifdef GLFRUSTUM
  glFrustum_real = (glFrustum_ptr)mProcs[103];
  mProcs[103] = (UINT_PTR)&glFrustum_fake;
#endif
#ifdef GLGENLISTS
  glGenLists_real = (glGenLists_ptr)mProcs[104];
  mProcs[104] = (UINT_PTR)&glGenLists_fake;
#endif
#ifdef GLGENTEXTURES
  glGenTextures_real = (glGenTextures_ptr)mProcs[105];
  mProcs[105] = (UINT_PTR)&glGenTextures_fake;
#endif
#ifdef GLGETBOOLEANV
  glGetBooleanv_real = (glGetBooleanv_ptr)mProcs[106];
  mProcs[106] = (UINT_PTR)&glGetBooleanv_fake;
#endif
#ifdef GLGETCLIPPLANE
  glGetClipPlane_real = (glGetClipPlane_ptr)mProcs[107];
  mProcs[107] = (UINT_PTR)&glGetClipPlane_fake;
#endif
#ifdef GLGETDOUBLEV
  glGetDoublev_real = (glGetDoublev_ptr)mProcs[108];
  mProcs[108] = (UINT_PTR)&glGetDoublev_fake;
#endif
#ifdef GLGETERROR
  glGetError_real = (glGetError_ptr)mProcs[109];
  mProcs[109] = (UINT_PTR)&glGetError_fake;
#endif
#ifdef GLGETFLOATV
  glGetFloatv_real = (glGetFloatv_ptr)mProcs[110];
  mProcs[110] = (UINT_PTR)&glGetFloatv_fake;
#endif
#ifdef GLGETINTEGERV
  glGetIntegerv_real = (glGetIntegerv_ptr)mProcs[111];
  mProcs[111] = (UINT_PTR)&glGetIntegerv_fake;
#endif
#ifdef GLGETLIGHTFV
  glGetLightfv_real = (glGetLightfv_ptr)mProcs[112];
  mProcs[112] = (UINT_PTR)&glGetLightfv_fake;
#endif
#ifdef GLGETLIGHTIV
  glGetLightiv_real = (glGetLightiv_ptr)mProcs[113];
  mProcs[113] = (UINT_PTR)&glGetLightiv_fake;
#endif
#ifdef GLGETMAPDV
  glGetMapdv_real = (glGetMapdv_ptr)mProcs[114];
  mProcs[114] = (UINT_PTR)&glGetMapdv_fake;
#endif
#ifdef GLGETMAPFV
  glGetMapfv_real = (glGetMapfv_ptr)mProcs[115];
  mProcs[115] = (UINT_PTR)&glGetMapfv_fake;
#endif
#ifdef GLGETMAPIV
  glGetMapiv_real = (glGetMapiv_ptr)mProcs[116];
  mProcs[116] = (UINT_PTR)&glGetMapiv_fake;
#endif
#ifdef GLGETMATERIALFV
  glGetMaterialfv_real = (glGetMaterialfv_ptr)mProcs[117];
  mProcs[117] = (UINT_PTR)&glGetMaterialfv_fake;
#endif
#ifdef GLGETMATERIALIV
  glGetMaterialiv_real = (glGetMaterialiv_ptr)mProcs[118];
  mProcs[118] = (UINT_PTR)&glGetMaterialiv_fake;
#endif
#ifdef GLGETPIXELMAPFV
  glGetPixelMapfv_real = (glGetPixelMapfv_ptr)mProcs[119];
  mProcs[119] = (UINT_PTR)&glGetPixelMapfv_fake;
#endif
#ifdef GLGETPIXELMAPUIV
  glGetPixelMapuiv_real = (glGetPixelMapuiv_ptr)mProcs[120];
  mProcs[120] = (UINT_PTR)&glGetPixelMapuiv_fake;
#endif
#ifdef GLGETPIXELMAPUSV
  glGetPixelMapusv_real = (glGetPixelMapusv_ptr)mProcs[121];
  mProcs[121] = (UINT_PTR)&glGetPixelMapusv_fake;
#endif
#ifdef GLGETPOINTERV
  glGetPointerv_real = (glGetPointerv_ptr)mProcs[122];
  mProcs[122] = (UINT_PTR)&glGetPointerv_fake;
#endif
#ifdef GLGETPOLYGONSTIPPLE
  glGetPolygonStipple_real = (glGetPolygonStipple_ptr)mProcs[123];
  orig_glGetString = (PFN_glGetString)mProcs[124];
  mProcs[124] = (UINT_PTR)h_glGetString;
#endif
#ifdef GLGETSTRING
  glGetString_real = (glGetString_ptr)mProcs[124];
  mProcs[124] = (UINT_PTR)&glGetString_fake;
#endif
#ifdef GLGETTEXENVFV
  glGetTexEnvfv_real = (glGetTexEnvfv_ptr)mProcs[125];
  mProcs[125] = (UINT_PTR)&glGetTexEnvfv_fake;
#endif
#ifdef GLGETTEXENVIV
  glGetTexEnviv_real = (glGetTexEnviv_ptr)mProcs[126];
  mProcs[126] = (UINT_PTR)&glGetTexEnviv_fake;
#endif
#ifdef GLGETTEXGENDV
  glGetTexGendv_real = (glGetTexGendv_ptr)mProcs[127];
  mProcs[127] = (UINT_PTR)&glGetTexGendv_fake;
#endif
#ifdef GLGETTEXGENFV
  glGetTexGenfv_real = (glGetTexGenfv_ptr)mProcs[128];
  mProcs[128] = (UINT_PTR)&glGetTexGenfv_fake;
#endif
#ifdef GLGETTEXGENIV
  glGetTexGeniv_real = (glGetTexGeniv_ptr)mProcs[129];
  mProcs[129] = (UINT_PTR)&glGetTexGeniv_fake;
#endif
#ifdef GLGETTEXIMAGE
  glGetTexImage_real = (glGetTexImage_ptr)mProcs[130];
  mProcs[130] = (UINT_PTR)&glGetTexImage_fake;
#endif
#ifdef GLGETTEXLEVELPARAMETERFV
  glGetTexLevelParameterfv_real = (glGetTexLevelParameterfv_ptr)mProcs[131];
  mProcs[131] = (UINT_PTR)&glGetTexLevelParameterfv_fake;
#endif
#ifdef GLGETTEXLEVELPARAMETERIV
  glGetTexLevelParameteriv_real = (glGetTexLevelParameteriv_ptr)mProcs[132];
  mProcs[132] = (UINT_PTR)&glGetTexLevelParameteriv_fake;
#endif
#ifdef GLGETTEXPARAMETERFV
  glGetTexParameterfv_real = (glGetTexParameterfv_ptr)mProcs[133];
  mProcs[133] = (UINT_PTR)&glGetTexParameterfv_fake;
#endif
#ifdef GLGETTEXPARAMETERIV
  glGetTexParameteriv_real = (glGetTexParameteriv_ptr)mProcs[134];
  mProcs[134] = (UINT_PTR)&glGetTexParameteriv_fake;
#endif
#ifdef GLHINT
  glHint_real = (glHint_ptr)mProcs[135];
  mProcs[135] = (UINT_PTR)&glHint_fake;
#endif
#ifdef GLINDEXMASK
  glIndexMask_real = (glIndexMask_ptr)mProcs[136];
  mProcs[136] = (UINT_PTR)&glIndexMask_fake;
#endif
#ifdef GLINDEXPOINTER
  glIndexPointer_real = (glIndexPointer_ptr)mProcs[137];
  mProcs[137] = (UINT_PTR)&glIndexPointer_fake;
#endif
#ifdef GLINDEXD
  glIndexd_real = (glIndexd_ptr)mProcs[138];
  mProcs[138] = (UINT_PTR)&glIndexd_fake;
#endif
#ifdef GLINDEXDV
  glIndexdv_real = (glIndexdv_ptr)mProcs[139];
  mProcs[139] = (UINT_PTR)&glIndexdv_fake;
#endif
#ifdef GLINDEXF
  glIndexf_real = (glIndexf_ptr)mProcs[140];
  mProcs[140] = (UINT_PTR)&glIndexf_fake;
#endif
#ifdef GLINDEXFV
  glIndexfv_real = (glIndexfv_ptr)mProcs[141];
  mProcs[141] = (UINT_PTR)&glIndexfv_fake;
#endif
#ifdef GLINDEXI
  glIndexi_real = (glIndexi_ptr)mProcs[142];
  mProcs[142] = (UINT_PTR)&glIndexi_fake;
#endif
#ifdef GLINDEXIV
  glIndexiv_real = (glIndexiv_ptr)mProcs[143];
  mProcs[143] = (UINT_PTR)&glIndexiv_fake;
#endif
#ifdef GLINDEXS
  glIndexs_real = (glIndexs_ptr)mProcs[144];
  mProcs[144] = (UINT_PTR)&glIndexs_fake;
#endif
#ifdef GLINDEXSV
  glIndexsv_real = (glIndexsv_ptr)mProcs[145];
  mProcs[145] = (UINT_PTR)&glIndexsv_fake;
#endif
#ifdef GLINDEXUB
  glIndexub_real = (glIndexub_ptr)mProcs[146];
  mProcs[146] = (UINT_PTR)&glIndexub_fake;
#endif
#ifdef GLINDEXUBV
  glIndexubv_real = (glIndexubv_ptr)mProcs[147];
  mProcs[147] = (UINT_PTR)&glIndexubv_fake;
#endif
#ifdef GLINITNAMES
  glInitNames_real = (glInitNames_ptr)mProcs[148];
  mProcs[148] = (UINT_PTR)&glInitNames_fake;
#endif
#ifdef GLINTERLEAVEDARRAYS
  glInterleavedArrays_real = (glInterleavedArrays_ptr)mProcs[149];
  mProcs[149] = (UINT_PTR)&glInterleavedArrays_fake;
#endif
#ifdef GLISENABLED
  glIsEnabled_real = (glIsEnabled_ptr)mProcs[150];
  mProcs[150] = (UINT_PTR)&glIsEnabled_fake;
#endif
#ifdef GLISLIST
  glIsList_real = (glIsList_ptr)mProcs[151];
  mProcs[151] = (UINT_PTR)&glIsList_fake;
#endif
#ifdef GLISTEXTURE
  glIsTexture_real = (glIsTexture_ptr)mProcs[152];
  mProcs[152] = (UINT_PTR)&glIsTexture_fake;
#endif
#ifdef GLLIGHTMODELF
  glLightModelf_real = (glLightModelf_ptr)mProcs[153];
  mProcs[153] = (UINT_PTR)&glLightModelf_fake;
#endif
#ifdef GLLIGHTMODELFV
  glLightModelfv_real = (glLightModelfv_ptr)mProcs[154];
  mProcs[154] = (UINT_PTR)&glLightModelfv_fake;
#endif
#ifdef GLLIGHTMODELI
  glLightModeli_real = (glLightModeli_ptr)mProcs[155];
  mProcs[155] = (UINT_PTR)&glLightModeli_fake;
#endif
#ifdef GLLIGHTMODELIV
  glLightModeliv_real = (glLightModeliv_ptr)mProcs[156];
  mProcs[156] = (UINT_PTR)&glLightModeliv_fake;
#endif
#ifdef GLLIGHTF
  glLightf_real = (glLightf_ptr)mProcs[157];
  mProcs[157] = (UINT_PTR)&glLightf_fake;
#endif
#ifdef GLLIGHTFV
  glLightfv_real = (glLightfv_ptr)mProcs[158];
  mProcs[158] = (UINT_PTR)&glLightfv_fake;
#endif
#ifdef GLLIGHTI
  glLighti_real = (glLighti_ptr)mProcs[159];
  mProcs[159] = (UINT_PTR)&glLighti_fake;
#endif
#ifdef GLLIGHTIV
  glLightiv_real = (glLightiv_ptr)mProcs[160];
  mProcs[160] = (UINT_PTR)&glLightiv_fake;
#endif
#ifdef GLLINESTIPPLE
  glLineStipple_real = (glLineStipple_ptr)mProcs[161];
  mProcs[161] = (UINT_PTR)&glLineStipple_fake;
#endif
#ifdef GLLINEWIDTH
  glLineWidth_real = (glLineWidth_ptr)mProcs[162];
  mProcs[162] = (UINT_PTR)&glLineWidth_fake;
#endif
#ifdef GLLISTBASE
  glListBase_real = (glListBase_ptr)mProcs[163];
  mProcs[163] = (UINT_PTR)&glListBase_fake;
#endif
#ifdef GLLOADIDENTITY
  glLoadIdentity_real = (glLoadIdentity_ptr)mProcs[164];
  mProcs[164] = (UINT_PTR)&glLoadIdentity_fake;
#endif
#ifdef GLLOADMATRIXD
  glLoadMatrixd_real = (glLoadMatrixd_ptr)mProcs[165];
  mProcs[165] = (UINT_PTR)&glLoadMatrixd_fake;
#endif
#ifdef GLLOADMATRIXF
  glLoadMatrixf_real = (glLoadMatrixf_ptr)mProcs[166];
  mProcs[166] = (UINT_PTR)&glLoadMatrixf_fake;
#endif
#ifdef GLLOADNAME
  glLoadName_real = (glLoadName_ptr)mProcs[167];
  mProcs[167] = (UINT_PTR)&glLoadName_fake;
#endif
#ifdef GLLOGICOP
  glLogicOp_real = (glLogicOp_ptr)mProcs[168];
  mProcs[168] = (UINT_PTR)&glLogicOp_fake;
#endif
#ifdef GLMAP1D
  glMap1d_real = (glMap1d_ptr)mProcs[169];
  mProcs[169] = (UINT_PTR)&glMap1d_fake;
#endif
#ifdef GLMAP1F
  glMap1f_real = (glMap1f_ptr)mProcs[170];
  mProcs[170] = (UINT_PTR)&glMap1f_fake;
#endif
#ifdef GLMAP2D
  glMap2d_real = (glMap2d_ptr)mProcs[171];
  mProcs[171] = (UINT_PTR)&glMap2d_fake;
#endif
#ifdef GLMAP2F
  glMap2f_real = (glMap2f_ptr)mProcs[172];
  mProcs[172] = (UINT_PTR)&glMap2f_fake;
#endif
#ifdef GLMAPGRID1D
  glMapGrid1d_real = (glMapGrid1d_ptr)mProcs[173];
  mProcs[173] = (UINT_PTR)&glMapGrid1d_fake;
#endif
#ifdef GLMAPGRID1F
  glMapGrid1f_real = (glMapGrid1f_ptr)mProcs[174];
  mProcs[174] = (UINT_PTR)&glMapGrid1f_fake;
#endif
#ifdef GLMAPGRID2D
  glMapGrid2d_real = (glMapGrid2d_ptr)mProcs[175];
  mProcs[175] = (UINT_PTR)&glMapGrid2d_fake;
#endif
#ifdef GLMAPGRID2F
  glMapGrid2f_real = (glMapGrid2f_ptr)mProcs[176];
  mProcs[176] = (UINT_PTR)&glMapGrid2f_fake;
#endif
#ifdef GLMATERIALF
  glMaterialf_real = (glMaterialf_ptr)mProcs[177];
  mProcs[177] = (UINT_PTR)&glMaterialf_fake;
#endif
#ifdef GLMATERIALFV
  glMaterialfv_real = (glMaterialfv_ptr)mProcs[178];
  mProcs[178] = (UINT_PTR)&glMaterialfv_fake;
#endif
#ifdef GLMATERIALI
  glMateriali_real = (glMateriali_ptr)mProcs[179];
  mProcs[179] = (UINT_PTR)&glMateriali_fake;
#endif
#ifdef GLMATERIALIV
  glMaterialiv_real = (glMaterialiv_ptr)mProcs[180];
  mProcs[180] = (UINT_PTR)&glMaterialiv_fake;
#endif
#ifdef GLMATRIXMODE
  glMatrixMode_real = (glMatrixMode_ptr)mProcs[181];
  mProcs[181] = (UINT_PTR)&glMatrixMode_fake;
#endif
#ifdef GLMULTMATRIXD
  glMultMatrixd_real = (glMultMatrixd_ptr)mProcs[182];
  mProcs[182] = (UINT_PTR)&glMultMatrixd_fake;
#endif
#ifdef GLMULTMATRIXF
  glMultMatrixf_real = (glMultMatrixf_ptr)mProcs[183];
  mProcs[183] = (UINT_PTR)&glMultMatrixf_fake;
#endif
#ifdef GLNEWLIST
  glNewList_real = (glNewList_ptr)mProcs[184];
  mProcs[184] = (UINT_PTR)&glNewList_fake;
#endif
#ifdef GLNORMAL3B
  glNormal3b_real = (glNormal3b_ptr)mProcs[185];
  mProcs[185] = (UINT_PTR)&glNormal3b_fake;
#endif
#ifdef GLNORMAL3BV
  glNormal3bv_real = (glNormal3bv_ptr)mProcs[186];
  mProcs[186] = (UINT_PTR)&glNormal3bv_fake;
#endif
#ifdef GLNORMAL3D
  glNormal3d_real = (glNormal3d_ptr)mProcs[187];
  mProcs[187] = (UINT_PTR)&glNormal3d_fake;
#endif
#ifdef GLNORMAL3DV
  glNormal3dv_real = (glNormal3dv_ptr)mProcs[188];
  mProcs[188] = (UINT_PTR)&glNormal3dv_fake;
#endif
#ifdef GLNORMAL3F
  glNormal3f_real = (glNormal3f_ptr)mProcs[189];
  mProcs[189] = (UINT_PTR)&glNormal3f_fake;
#endif
#ifdef GLNORMAL3FV
  glNormal3fv_real = (glNormal3fv_ptr)mProcs[190];
  mProcs[190] = (UINT_PTR)&glNormal3fv_fake;
#endif
#ifdef GLNORMAL3I
  glNormal3i_real = (glNormal3i_ptr)mProcs[191];
  mProcs[191] = (UINT_PTR)&glNormal3i_fake;
#endif
#ifdef GLNORMAL3IV
  glNormal3iv_real = (glNormal3iv_ptr)mProcs[192];
  mProcs[192] = (UINT_PTR)&glNormal3iv_fake;
#endif
#ifdef GLNORMAL3S
  glNormal3s_real = (glNormal3s_ptr)mProcs[193];
  mProcs[193] = (UINT_PTR)&glNormal3s_fake;
#endif
#ifdef GLNORMAL3SV
  glNormal3sv_real = (glNormal3sv_ptr)mProcs[194];
  mProcs[194] = (UINT_PTR)&glNormal3sv_fake;
#endif
#ifdef GLNORMALPOINTER
  glNormalPointer_real = (glNormalPointer_ptr)mProcs[195];
  mProcs[195] = (UINT_PTR)&glNormalPointer_fake;
#endif
#ifdef GLORTHO
  glOrtho_real = (glOrtho_ptr)mProcs[196];
  mProcs[196] = (UINT_PTR)&glOrtho_fake;
#endif
#ifdef GLPASSTHROUGH
  glPassThrough_real = (glPassThrough_ptr)mProcs[197];
  mProcs[197] = (UINT_PTR)&glPassThrough_fake;
#endif
#ifdef GLPIXELMAPFV
  glPixelMapfv_real = (glPixelMapfv_ptr)mProcs[198];
  mProcs[198] = (UINT_PTR)&glPixelMapfv_fake;
#endif
#ifdef GLPIXELMAPUIV
  glPixelMapuiv_real = (glPixelMapuiv_ptr)mProcs[199];
  mProcs[199] = (UINT_PTR)&glPixelMapuiv_fake;
#endif
#ifdef GLPIXELMAPUSV
  glPixelMapusv_real = (glPixelMapusv_ptr)mProcs[200];
  mProcs[200] = (UINT_PTR)&glPixelMapusv_fake;
#endif
#ifdef GLPIXELSTOREF
  glPixelStoref_real = (glPixelStoref_ptr)mProcs[201];
  mProcs[201] = (UINT_PTR)&glPixelStoref_fake;
#endif
#ifdef GLPIXELSTOREI
  glPixelStorei_real = (glPixelStorei_ptr)mProcs[202];
  mProcs[202] = (UINT_PTR)&glPixelStorei_fake;
#endif
#ifdef GLPIXELTRANSFERF
  glPixelTransferf_real = (glPixelTransferf_ptr)mProcs[203];
  mProcs[203] = (UINT_PTR)&glPixelTransferf_fake;
#endif
#ifdef GLPIXELTRANSFERI
  glPixelTransferi_real = (glPixelTransferi_ptr)mProcs[204];
  mProcs[204] = (UINT_PTR)&glPixelTransferi_fake;
#endif
#ifdef GLPIXELZOOM
  glPixelZoom_real = (glPixelZoom_ptr)mProcs[205];
  mProcs[205] = (UINT_PTR)&glPixelZoom_fake;
#endif
#ifdef GLPOINTSIZE
  glPointSize_real = (glPointSize_ptr)mProcs[206];
  mProcs[206] = (UINT_PTR)&glPointSize_fake;
#endif
#ifdef GLPOLYGONMODE
  glPolygonMode_real = (glPolygonMode_ptr)mProcs[207];
  mProcs[207] = (UINT_PTR)&glPolygonMode_fake;
#endif
#ifdef GLPOLYGONOFFSET
  glPolygonOffset_real = (glPolygonOffset_ptr)mProcs[208];
  mProcs[208] = (UINT_PTR)&glPolygonOffset_fake;
#endif
#ifdef GLPOLYGONSTIPPLE
  glPolygonStipple_real = (glPolygonStipple_ptr)mProcs[209];
  mProcs[209] = (UINT_PTR)&glPolygonStipple_fake;
#endif
#ifdef GLPOPATTRIB
  glPopAttrib_real = (glPopAttrib_ptr)mProcs[210];
  mProcs[210] = (UINT_PTR)&glPopAttrib_fake;
#endif
#ifdef GLPOPCLIENTATTRIB
  glPopClientAttrib_real = (glPopClientAttrib_ptr)mProcs[211];
  mProcs[211] = (UINT_PTR)&glPopClientAttrib_fake;
#endif
#ifdef GLPOPMATRIX
  glPopMatrix_real = (glPopMatrix_ptr)mProcs[212];
  mProcs[212] = (UINT_PTR)&glPopMatrix_fake;
#endif
#ifdef GLPOPNAME
  glPopName_real = (glPopName_ptr)mProcs[213];
  mProcs[213] = (UINT_PTR)&glPopName_fake;
#endif
#ifdef GLPRIORITIZETEXTURES
  glPrioritizeTextures_real = (glPrioritizeTextures_ptr)mProcs[214];
  mProcs[214] = (UINT_PTR)&glPrioritizeTextures_fake;
#endif
#ifdef GLPUSHATTRIB
  glPushAttrib_real = (glPushAttrib_ptr)mProcs[215];
  mProcs[215] = (UINT_PTR)&glPushAttrib_fake;
#endif
#ifdef GLPUSHCLIENTATTRIB
  glPushClientAttrib_real = (glPushClientAttrib_ptr)mProcs[216];
  mProcs[216] = (UINT_PTR)&glPushClientAttrib_fake;
#endif
#ifdef GLPUSHMATRIX
  glPushMatrix_real = (glPushMatrix_ptr)mProcs[217];
  mProcs[217] = (UINT_PTR)&glPushMatrix_fake;
#endif
#ifdef GLPUSHNAME
  glPushName_real = (glPushName_ptr)mProcs[218];
  mProcs[218] = (UINT_PTR)&glPushName_fake;
#endif
#ifdef GLRASTERPOS2D
  glRasterPos2d_real = (glRasterPos2d_ptr)mProcs[219];
  mProcs[219] = (UINT_PTR)&glRasterPos2d_fake;
#endif
#ifdef GLRASTERPOS2DV
  glRasterPos2dv_real = (glRasterPos2dv_ptr)mProcs[220];
  mProcs[220] = (UINT_PTR)&glRasterPos2dv_fake;
#endif
#ifdef GLRASTERPOS2F
  glRasterPos2f_real = (glRasterPos2f_ptr)mProcs[221];
  mProcs[221] = (UINT_PTR)&glRasterPos2f_fake;
#endif
#ifdef GLRASTERPOS2FV
  glRasterPos2fv_real = (glRasterPos2fv_ptr)mProcs[222];
  mProcs[222] = (UINT_PTR)&glRasterPos2fv_fake;
#endif
#ifdef GLRASTERPOS2I
  glRasterPos2i_real = (glRasterPos2i_ptr)mProcs[223];
  mProcs[223] = (UINT_PTR)&glRasterPos2i_fake;
#endif
#ifdef GLRASTERPOS2IV
  glRasterPos2iv_real = (glRasterPos2iv_ptr)mProcs[224];
  mProcs[224] = (UINT_PTR)&glRasterPos2iv_fake;
#endif
#ifdef GLRASTERPOS2S
  glRasterPos2s_real = (glRasterPos2s_ptr)mProcs[225];
  mProcs[225] = (UINT_PTR)&glRasterPos2s_fake;
#endif
#ifdef GLRASTERPOS2SV
  glRasterPos2sv_real = (glRasterPos2sv_ptr)mProcs[226];
  mProcs[226] = (UINT_PTR)&glRasterPos2sv_fake;
#endif
#ifdef GLRASTERPOS3D
  glRasterPos3d_real = (glRasterPos3d_ptr)mProcs[227];
  mProcs[227] = (UINT_PTR)&glRasterPos3d_fake;
#endif
#ifdef GLRASTERPOS3DV
  glRasterPos3dv_real = (glRasterPos3dv_ptr)mProcs[228];
  mProcs[228] = (UINT_PTR)&glRasterPos3dv_fake;
#endif
#ifdef GLRASTERPOS3F
  glRasterPos3f_real = (glRasterPos3f_ptr)mProcs[229];
  mProcs[229] = (UINT_PTR)&glRasterPos3f_fake;
#endif
#ifdef GLRASTERPOS3FV
  glRasterPos3fv_real = (glRasterPos3fv_ptr)mProcs[230];
  mProcs[230] = (UINT_PTR)&glRasterPos3fv_fake;
#endif
#ifdef GLRASTERPOS3I
  glRasterPos3i_real = (glRasterPos3i_ptr)mProcs[231];
  mProcs[231] = (UINT_PTR)&glRasterPos3i_fake;
#endif
#ifdef GLRASTERPOS3IV
  glRasterPos3iv_real = (glRasterPos3iv_ptr)mProcs[232];
  mProcs[232] = (UINT_PTR)&glRasterPos3iv_fake;
#endif
#ifdef GLRASTERPOS3S
  glRasterPos3s_real = (glRasterPos3s_ptr)mProcs[233];
  mProcs[233] = (UINT_PTR)&glRasterPos3s_fake;
#endif
#ifdef GLRASTERPOS3SV
  glRasterPos3sv_real = (glRasterPos3sv_ptr)mProcs[234];
  mProcs[234] = (UINT_PTR)&glRasterPos3sv_fake;
#endif
#ifdef GLRASTERPOS4D
  glRasterPos4d_real = (glRasterPos4d_ptr)mProcs[235];
  mProcs[235] = (UINT_PTR)&glRasterPos4d_fake;
#endif
#ifdef GLRASTERPOS4DV
  glRasterPos4dv_real = (glRasterPos4dv_ptr)mProcs[236];
  mProcs[236] = (UINT_PTR)&glRasterPos4dv_fake;
#endif
#ifdef GLRASTERPOS4F
  glRasterPos4f_real = (glRasterPos4f_ptr)mProcs[237];
  mProcs[237] = (UINT_PTR)&glRasterPos4f_fake;
#endif
#ifdef GLRASTERPOS4FV
  glRasterPos4fv_real = (glRasterPos4fv_ptr)mProcs[238];
  mProcs[238] = (UINT_PTR)&glRasterPos4fv_fake;
#endif
#ifdef GLRASTERPOS4I
  glRasterPos4i_real = (glRasterPos4i_ptr)mProcs[239];
  mProcs[239] = (UINT_PTR)&glRasterPos4i_fake;
#endif
#ifdef GLRASTERPOS4IV
  glRasterPos4iv_real = (glRasterPos4iv_ptr)mProcs[240];
  mProcs[240] = (UINT_PTR)&glRasterPos4iv_fake;
#endif
#ifdef GLRASTERPOS4S
  glRasterPos4s_real = (glRasterPos4s_ptr)mProcs[241];
  mProcs[241] = (UINT_PTR)&glRasterPos4s_fake;
#endif
#ifdef GLRASTERPOS4SV
  glRasterPos4sv_real = (glRasterPos4sv_ptr)mProcs[242];
  mProcs[242] = (UINT_PTR)&glRasterPos4sv_fake;
#endif
#ifdef GLREADBUFFER
  glReadBuffer_real = (glReadBuffer_ptr)mProcs[243];
  mProcs[243] = (UINT_PTR)&glReadBuffer_fake;
#endif
#ifdef GLREADPIXELS
  glReadPixels_real = (glReadPixels_ptr)mProcs[244];
  mProcs[244] = (UINT_PTR)&glReadPixels_fake;
#endif
#ifdef GLRECTD
  glRectd_real = (glRectd_ptr)mProcs[245];
  mProcs[245] = (UINT_PTR)&glRectd_fake;
#endif
#ifdef GLRECTDV
  glRectdv_real = (glRectdv_ptr)mProcs[246];
  mProcs[246] = (UINT_PTR)&glRectdv_fake;
#endif
#ifdef GLRECTF
  glRectf_real = (glRectf_ptr)mProcs[247];
  mProcs[247] = (UINT_PTR)&glRectf_fake;
#endif
#ifdef GLRECTFV
  glRectfv_real = (glRectfv_ptr)mProcs[248];
  mProcs[248] = (UINT_PTR)&glRectfv_fake;
#endif
#ifdef GLRECTI
  glRecti_real = (glRecti_ptr)mProcs[249];
  mProcs[249] = (UINT_PTR)&glRecti_fake;
#endif
#ifdef GLRECTIV
  glRectiv_real = (glRectiv_ptr)mProcs[250];
  mProcs[250] = (UINT_PTR)&glRectiv_fake;
#endif
#ifdef GLRECTS
  glRects_real = (glRects_ptr)mProcs[251];
  mProcs[251] = (UINT_PTR)&glRects_fake;
#endif
#ifdef GLRECTSV
  glRectsv_real = (glRectsv_ptr)mProcs[252];
  mProcs[252] = (UINT_PTR)&glRectsv_fake;
#endif
#ifdef GLRENDERMODE
  glRenderMode_real = (glRenderMode_ptr)mProcs[253];
  mProcs[253] = (UINT_PTR)&glRenderMode_fake;
#endif
#ifdef GLROTATED
  glRotated_real = (glRotated_ptr)mProcs[254];
  mProcs[254] = (UINT_PTR)&glRotated_fake;
#endif
#ifdef GLROTATEF
  glRotatef_real = (glRotatef_ptr)mProcs[255];
  mProcs[255] = (UINT_PTR)&glRotatef_fake;
#endif
#ifdef GLSCALED
  glScaled_real = (glScaled_ptr)mProcs[256];
  mProcs[256] = (UINT_PTR)&glScaled_fake;
#endif
#ifdef GLSCALEF
  glScalef_real = (glScalef_ptr)mProcs[257];
  mProcs[257] = (UINT_PTR)&glScalef_fake;
#endif
#ifdef GLSCISSOR
  glScissor_real = (glScissor_ptr)mProcs[258];
  mProcs[258] = (UINT_PTR)&glScissor_fake;
#endif
#ifdef GLSELECTBUFFER
  glSelectBuffer_real = (glSelectBuffer_ptr)mProcs[259];
  mProcs[259] = (UINT_PTR)&glSelectBuffer_fake;
#endif
#ifdef GLSHADEMODEL
  glShadeModel_real = (glShadeModel_ptr)mProcs[260];
  mProcs[260] = (UINT_PTR)&glShadeModel_fake;
#endif
#ifdef GLSTENCILFUNC
  glStencilFunc_real = (glStencilFunc_ptr)mProcs[261];
  mProcs[261] = (UINT_PTR)&glStencilFunc_fake;
#endif
#ifdef GLSTENCILMASK
  glStencilMask_real = (glStencilMask_ptr)mProcs[262];
  mProcs[262] = (UINT_PTR)&glStencilMask_fake;
#endif
#ifdef GLSTENCILOP
  glStencilOp_real = (glStencilOp_ptr)mProcs[263];
  mProcs[263] = (UINT_PTR)&glStencilOp_fake;
#endif
#ifdef GLTEXCOORD1D
  glTexCoord1d_real = (glTexCoord1d_ptr)mProcs[264];
  mProcs[264] = (UINT_PTR)&glTexCoord1d_fake;
#endif
#ifdef GLTEXCOORD1DV
  glTexCoord1dv_real = (glTexCoord1dv_ptr)mProcs[265];
  mProcs[265] = (UINT_PTR)&glTexCoord1dv_fake;
#endif
#ifdef GLTEXCOORD1F
  glTexCoord1f_real = (glTexCoord1f_ptr)mProcs[266];
  mProcs[266] = (UINT_PTR)&glTexCoord1f_fake;
#endif
#ifdef GLTEXCOORD1FV
  glTexCoord1fv_real = (glTexCoord1fv_ptr)mProcs[267];
  mProcs[267] = (UINT_PTR)&glTexCoord1fv_fake;
#endif
#ifdef GLTEXCOORD1I
  glTexCoord1i_real = (glTexCoord1i_ptr)mProcs[268];
  mProcs[268] = (UINT_PTR)&glTexCoord1i_fake;
#endif
#ifdef GLTEXCOORD1IV
  glTexCoord1iv_real = (glTexCoord1iv_ptr)mProcs[269];
  mProcs[269] = (UINT_PTR)&glTexCoord1iv_fake;
#endif
#ifdef GLTEXCOORD1S
  glTexCoord1s_real = (glTexCoord1s_ptr)mProcs[270];
  mProcs[270] = (UINT_PTR)&glTexCoord1s_fake;
#endif
#ifdef GLTEXCOORD1SV
  glTexCoord1sv_real = (glTexCoord1sv_ptr)mProcs[271];
  mProcs[271] = (UINT_PTR)&glTexCoord1sv_fake;
#endif
#ifdef GLTEXCOORD2D
  glTexCoord2d_real = (glTexCoord2d_ptr)mProcs[272];
  mProcs[272] = (UINT_PTR)&glTexCoord2d_fake;
#endif
#ifdef GLTEXCOORD2DV
  glTexCoord2dv_real = (glTexCoord2dv_ptr)mProcs[273];
  mProcs[273] = (UINT_PTR)&glTexCoord2dv_fake;
#endif
#ifdef GLTEXCOORD2F
  glTexCoord2f_real = (glTexCoord2f_ptr)mProcs[274];
  mProcs[274] = (UINT_PTR)&glTexCoord2f_fake;
#endif
#ifdef GLTEXCOORD2FV
  glTexCoord2fv_real = (glTexCoord2fv_ptr)mProcs[275];
  mProcs[275] = (UINT_PTR)&glTexCoord2fv_fake;
#endif
#ifdef GLTEXCOORD2I
  glTexCoord2i_real = (glTexCoord2i_ptr)mProcs[276];
  mProcs[276] = (UINT_PTR)&glTexCoord2i_fake;
#endif
#ifdef GLTEXCOORD2IV
  glTexCoord2iv_real = (glTexCoord2iv_ptr)mProcs[277];
  mProcs[277] = (UINT_PTR)&glTexCoord2iv_fake;
#endif
#ifdef GLTEXCOORD2S
  glTexCoord2s_real = (glTexCoord2s_ptr)mProcs[278];
  mProcs[278] = (UINT_PTR)&glTexCoord2s_fake;
#endif
#ifdef GLTEXCOORD2SV
  glTexCoord2sv_real = (glTexCoord2sv_ptr)mProcs[279];
  mProcs[279] = (UINT_PTR)&glTexCoord2sv_fake;
#endif
#ifdef GLTEXCOORD3D
  glTexCoord3d_real = (glTexCoord3d_ptr)mProcs[280];
  mProcs[280] = (UINT_PTR)&glTexCoord3d_fake;
#endif
#ifdef GLTEXCOORD3DV
  glTexCoord3dv_real = (glTexCoord3dv_ptr)mProcs[281];
  mProcs[281] = (UINT_PTR)&glTexCoord3dv_fake;
#endif
#ifdef GLTEXCOORD3F
  glTexCoord3f_real = (glTexCoord3f_ptr)mProcs[282];
  mProcs[282] = (UINT_PTR)&glTexCoord3f_fake;
#endif
#ifdef GLTEXCOORD3FV
  glTexCoord3fv_real = (glTexCoord3fv_ptr)mProcs[283];
  mProcs[283] = (UINT_PTR)&glTexCoord3fv_fake;
#endif
#ifdef GLTEXCOORD3I
  glTexCoord3i_real = (glTexCoord3i_ptr)mProcs[284];
  mProcs[284] = (UINT_PTR)&glTexCoord3i_fake;
#endif
#ifdef GLTEXCOORD3IV
  glTexCoord3iv_real = (glTexCoord3iv_ptr)mProcs[285];
  mProcs[285] = (UINT_PTR)&glTexCoord3iv_fake;
#endif
#ifdef GLTEXCOORD3S
  glTexCoord3s_real = (glTexCoord3s_ptr)mProcs[286];
  mProcs[286] = (UINT_PTR)&glTexCoord3s_fake;
#endif
#ifdef GLTEXCOORD3SV
  glTexCoord3sv_real = (glTexCoord3sv_ptr)mProcs[287];
  mProcs[287] = (UINT_PTR)&glTexCoord3sv_fake;
#endif
#ifdef GLTEXCOORD4D
  glTexCoord4d_real = (glTexCoord4d_ptr)mProcs[288];
  mProcs[288] = (UINT_PTR)&glTexCoord4d_fake;
#endif
#ifdef GLTEXCOORD4DV
  glTexCoord4dv_real = (glTexCoord4dv_ptr)mProcs[289];
  mProcs[289] = (UINT_PTR)&glTexCoord4dv_fake;
#endif
#ifdef GLTEXCOORD4F
  glTexCoord4f_real = (glTexCoord4f_ptr)mProcs[290];
  mProcs[290] = (UINT_PTR)&glTexCoord4f_fake;
#endif
#ifdef GLTEXCOORD4FV
  glTexCoord4fv_real = (glTexCoord4fv_ptr)mProcs[291];
  mProcs[291] = (UINT_PTR)&glTexCoord4fv_fake;
#endif
#ifdef GLTEXCOORD4I
  glTexCoord4i_real = (glTexCoord4i_ptr)mProcs[292];
  mProcs[292] = (UINT_PTR)&glTexCoord4i_fake;
#endif
#ifdef GLTEXCOORD4IV
  glTexCoord4iv_real = (glTexCoord4iv_ptr)mProcs[293];
  mProcs[293] = (UINT_PTR)&glTexCoord4iv_fake;
#endif
#ifdef GLTEXCOORD4S
  glTexCoord4s_real = (glTexCoord4s_ptr)mProcs[294];
  mProcs[294] = (UINT_PTR)&glTexCoord4s_fake;
#endif
#ifdef GLTEXCOORD4SV
  glTexCoord4sv_real = (glTexCoord4sv_ptr)mProcs[295];
  mProcs[295] = (UINT_PTR)&glTexCoord4sv_fake;
#endif
#ifdef GLTEXCOORDPOINTER
  glTexCoordPointer_real = (glTexCoordPointer_ptr)mProcs[296];
  mProcs[296] = (UINT_PTR)&glTexCoordPointer_fake;
#endif
#ifdef GLTEXENVF
  glTexEnvf_real = (glTexEnvf_ptr)mProcs[297];
  mProcs[297] = (UINT_PTR)&glTexEnvf_fake;
#endif
#ifdef GLTEXENVFV
  glTexEnvfv_real = (glTexEnvfv_ptr)mProcs[298];
  mProcs[298] = (UINT_PTR)&glTexEnvfv_fake;
#endif
#ifdef GLTEXENVI
  glTexEnvi_real = (glTexEnvi_ptr)mProcs[299];
  mProcs[299] = (UINT_PTR)&glTexEnvi_fake;
#endif
#ifdef GLTEXENVIV
  glTexEnviv_real = (glTexEnviv_ptr)mProcs[300];
  mProcs[300] = (UINT_PTR)&glTexEnviv_fake;
#endif
#ifdef GLTEXGEND
  glTexGend_real = (glTexGend_ptr)mProcs[301];
  mProcs[301] = (UINT_PTR)&glTexGend_fake;
#endif
#ifdef GLTEXGENDV
  glTexGendv_real = (glTexGendv_ptr)mProcs[302];
  mProcs[302] = (UINT_PTR)&glTexGendv_fake;
#endif
#ifdef GLTEXGENF
  glTexGenf_real = (glTexGenf_ptr)mProcs[303];
  mProcs[303] = (UINT_PTR)&glTexGenf_fake;
#endif
#ifdef GLTEXGENFV
  glTexGenfv_real = (glTexGenfv_ptr)mProcs[304];
  mProcs[304] = (UINT_PTR)&glTexGenfv_fake;
#endif
#ifdef GLTEXGENI
  glTexGeni_real = (glTexGeni_ptr)mProcs[305];
  mProcs[305] = (UINT_PTR)&glTexGeni_fake;
#endif
#ifdef GLTEXGENIV
  glTexGeniv_real = (glTexGeniv_ptr)mProcs[306];
  mProcs[306] = (UINT_PTR)&glTexGeniv_fake;
#endif
#ifdef GLTEXIMAGE1D
  glTexImage1D_real = (glTexImage1D_ptr)mProcs[307];
  mProcs[307] = (UINT_PTR)&glTexImage1D_fake;
#endif
#ifdef GLTEXIMAGE2D
  glTexImage2D_real = (glTexImage2D_ptr)mProcs[308];
  mProcs[308] = (UINT_PTR)&glTexImage2D_fake;
#endif
#ifdef GLTEXPARAMETERF
  glTexParameterf_real = (glTexParameterf_ptr)mProcs[309];
  mProcs[309] = (UINT_PTR)&glTexParameterf_fake;
#endif
#ifdef GLTEXPARAMETERFV
  glTexParameterfv_real = (glTexParameterfv_ptr)mProcs[310];
  mProcs[310] = (UINT_PTR)&glTexParameterfv_fake;
#endif
#ifdef GLTEXPARAMETERI
  glTexParameteri_real = (glTexParameteri_ptr)mProcs[311];
  mProcs[311] = (UINT_PTR)&glTexParameteri_fake;
#endif
#ifdef GLTEXPARAMETERIV
  glTexParameteriv_real = (glTexParameteriv_ptr)mProcs[312];
  mProcs[312] = (UINT_PTR)&glTexParameteriv_fake;
#endif
#ifdef GLTEXSUBIMAGE1D
  glTexSubImage1D_real = (glTexSubImage1D_ptr)mProcs[313];
  mProcs[313] = (UINT_PTR)&glTexSubImage1D_fake;
#endif
#ifdef GLTEXSUBIMAGE2D
  glTexSubImage2D_real = (glTexSubImage2D_ptr)mProcs[314];
  mProcs[314] = (UINT_PTR)&glTexSubImage2D_fake;
#endif
#ifdef GLTRANSLATED
  glTranslated_real = (glTranslated_ptr)mProcs[315];
  mProcs[315] = (UINT_PTR)&glTranslated_fake;
#endif
#ifdef GLTRANSLATEF
  glTranslatef_real = (glTranslatef_ptr)mProcs[316];
  mProcs[316] = (UINT_PTR)&glTranslatef_fake;
#endif
#ifdef GLVERTEX2D
  glVertex2d_real = (glVertex2d_ptr)mProcs[317];
  mProcs[317] = (UINT_PTR)&glVertex2d_fake;
#endif
#ifdef GLVERTEX2DV
  glVertex2dv_real = (glVertex2dv_ptr)mProcs[318];
  mProcs[318] = (UINT_PTR)&glVertex2dv_fake;
#endif
#ifdef GLVERTEX2F
  glVertex2f_real = (glVertex2f_ptr)mProcs[319];
  mProcs[319] = (UINT_PTR)&glVertex2f_fake;
#endif
#ifdef GLVERTEX2FV
  glVertex2fv_real = (glVertex2fv_ptr)mProcs[320];
  mProcs[320] = (UINT_PTR)&glVertex2fv_fake;
#endif
#ifdef GLVERTEX2I
  glVertex2i_real = (glVertex2i_ptr)mProcs[321];
  mProcs[321] = (UINT_PTR)&glVertex2i_fake;
#endif
#ifdef GLVERTEX2IV
  glVertex2iv_real = (glVertex2iv_ptr)mProcs[322];
  mProcs[322] = (UINT_PTR)&glVertex2iv_fake;
#endif
#ifdef GLVERTEX2S
  glVertex2s_real = (glVertex2s_ptr)mProcs[323];
  mProcs[323] = (UINT_PTR)&glVertex2s_fake;
#endif
#ifdef GLVERTEX2SV
  glVertex2sv_real = (glVertex2sv_ptr)mProcs[324];
  mProcs[324] = (UINT_PTR)&glVertex2sv_fake;
#endif
#ifdef GLVERTEX3D
  glVertex3d_real = (glVertex3d_ptr)mProcs[325];
  mProcs[325] = (UINT_PTR)&glVertex3d_fake;
#endif
#ifdef GLVERTEX3DV
  glVertex3dv_real = (glVertex3dv_ptr)mProcs[326];
  mProcs[326] = (UINT_PTR)&glVertex3dv_fake;
#endif
#ifdef GLVERTEX3F
  glVertex3f_real = (glVertex3f_ptr)mProcs[327];
  mProcs[327] = (UINT_PTR)&glVertex3f_fake;
#endif
#ifdef GLVERTEX3FV
  glVertex3fv_real = (glVertex3fv_ptr)mProcs[328];
  mProcs[328] = (UINT_PTR)&glVertex3fv_fake;
#endif
#ifdef GLVERTEX3I
  glVertex3i_real = (glVertex3i_ptr)mProcs[329];
  mProcs[329] = (UINT_PTR)&glVertex3i_fake;
#endif
#ifdef GLVERTEX3IV
  glVertex3iv_real = (glVertex3iv_ptr)mProcs[330];
  mProcs[330] = (UINT_PTR)&glVertex3iv_fake;
#endif
#ifdef GLVERTEX3S
  glVertex3s_real = (glVertex3s_ptr)mProcs[331];
  mProcs[331] = (UINT_PTR)&glVertex3s_fake;
#endif
#ifdef GLVERTEX3SV
  glVertex3sv_real = (glVertex3sv_ptr)mProcs[332];
  mProcs[332] = (UINT_PTR)&glVertex3sv_fake;
#endif
#ifdef GLVERTEX4D
  glVertex4d_real = (glVertex4d_ptr)mProcs[333];
  mProcs[333] = (UINT_PTR)&glVertex4d_fake;
#endif
#ifdef GLVERTEX4DV
  glVertex4dv_real = (glVertex4dv_ptr)mProcs[334];
  mProcs[334] = (UINT_PTR)&glVertex4dv_fake;
#endif
#ifdef GLVERTEX4F
  glVertex4f_real = (glVertex4f_ptr)mProcs[335];
  mProcs[335] = (UINT_PTR)&glVertex4f_fake;
#endif
#ifdef GLVERTEX4FV
  glVertex4fv_real = (glVertex4fv_ptr)mProcs[336];
  mProcs[336] = (UINT_PTR)&glVertex4fv_fake;
#endif
#ifdef GLVERTEX4I
  glVertex4i_real = (glVertex4i_ptr)mProcs[337];
  mProcs[337] = (UINT_PTR)&glVertex4i_fake;
#endif
#ifdef GLVERTEX4IV
  glVertex4iv_real = (glVertex4iv_ptr)mProcs[338];
  mProcs[338] = (UINT_PTR)&glVertex4iv_fake;
#endif
#ifdef GLVERTEX4S
  glVertex4s_real = (glVertex4s_ptr)mProcs[339];
  mProcs[339] = (UINT_PTR)&glVertex4s_fake;
#endif
#ifdef GLVERTEX4SV
  glVertex4sv_real = (glVertex4sv_ptr)mProcs[340];
  mProcs[340] = (UINT_PTR)&glVertex4sv_fake;
#endif
#ifdef GLVERTEXPOINTER
  glVertexPointer_real = (glVertexPointer_ptr)mProcs[341];
  mProcs[341] = (UINT_PTR)&glVertexPointer_fake;
#endif
#ifdef GLVIEWPORT
  glViewport_real = (glViewport_ptr)mProcs[342];
  mProcs[342] = (UINT_PTR)&glViewport_fake;
#endif
#ifdef WGLCHOOSEPIXELFORMAT
  wglChoosePixelFormat_real = (wglChoosePixelFormat_ptr)mProcs[343];
  mProcs[343] = (UINT_PTR)&wglChoosePixelFormat_fake;
#endif
#ifdef WGLCOPYCONTEXT
  wglCopyContext_real = (wglCopyContext_ptr)mProcs[344];
  mProcs[344] = (UINT_PTR)&wglCopyContext_fake;
#endif
#ifdef WGLCREATECONTEXT
  wglCreateContext_real = (wglCreateContext_ptr)mProcs[345];
  mProcs[345] = (UINT_PTR)&wglCreateContext_fake;
#endif
#ifdef WGLCREATELAYERCONTEXT
  wglCreateLayerContext_real = (wglCreateLayerContext_ptr)mProcs[346];
  mProcs[346] = (UINT_PTR)&wglCreateLayerContext_fake;
#endif
#ifdef WGLDELETECONTEXT
  wglDeleteContext_real = (wglDeleteContext_ptr)mProcs[347];
  mProcs[347] = (UINT_PTR)&wglDeleteContext_fake;
#endif
#ifdef WGLDESCRIBELAYERPLANE
  wglDescribeLayerPlane_real = (wglDescribeLayerPlane_ptr)mProcs[348];
  mProcs[348] = (UINT_PTR)&wglDescribeLayerPlane_fake;
#endif
#ifdef WGLDESCRIBEPIXELFORMAT
  wglDescribePixelFormat_real = (wglDescribePixelFormat_ptr)mProcs[349];
  mProcs[349] = (UINT_PTR)&wglDescribePixelFormat_fake;
#endif
#ifdef WGLGETCURRENTCONTEXT
  wglGetCurrentContext_real = (wglGetCurrentContext_ptr)mProcs[350];
  mProcs[350] = (UINT_PTR)&wglGetCurrentContext_fake;
#endif
#ifdef WGLGETCURRENTDC
  wglGetCurrentDC_real = (wglGetCurrentDC_ptr)mProcs[351];
  mProcs[351] = (UINT_PTR)&wglGetCurrentDC_fake;
#endif
#ifdef WGLGETDEFAULTPROCADDRESS
  wglGetDefaultProcAddress_real = (wglGetDefaultProcAddress_ptr)mProcs[352];
  mProcs[352] = (UINT_PTR)&wglGetDefaultProcAddress_fake;
#endif
#ifdef WGLGETLAYERPALETTEENTRIES
  wglGetLayerPaletteEntries_real = (wglGetLayerPaletteEntries_ptr)mProcs[353];
  mProcs[353] = (UINT_PTR)&wglGetLayerPaletteEntries_fake;
#endif
#ifdef WGLGETPIXELFORMAT
  wglGetPixelFormat_real = (wglGetPixelFormat_ptr)mProcs[354];
  mProcs[354] = (UINT_PTR)&wglGetPixelFormat_fake;
#endif
#ifdef WGLGETPROCADDRESS
  wglGetProcAddress_real = (wglGetProcAddress_ptr)mProcs[355];
  mProcs[355] = (UINT_PTR)&wglGetProcAddress_fake;
#endif
#ifdef WGLMAKECURRENT
  wglMakeCurrent_real = (wglMakeCurrent_ptr)mProcs[356];
  mProcs[356] = (UINT_PTR)&wglMakeCurrent_fake;
#endif
#ifdef WGLREALIZELAYERPALETTE
  wglRealizeLayerPalette_real = (wglRealizeLayerPalette_ptr)mProcs[357];
  mProcs[357] = (UINT_PTR)&wglRealizeLayerPalette_fake;
#endif
#ifdef WGLSETLAYERPALETTEENTRIES
  wglSetLayerPaletteEntries_real = (wglSetLayerPaletteEntries_ptr)mProcs[358];
  mProcs[358] = (UINT_PTR)&wglSetLayerPaletteEntries_fake;
#endif
#ifdef WGLSETPIXELFORMAT
  wglSetPixelFormat_real = (wglSetPixelFormat_ptr)mProcs[359];
  mProcs[359] = (UINT_PTR)&wglSetPixelFormat_fake;
#endif
#ifdef WGLSHARELISTS
  wglShareLists_real = (wglShareLists_ptr)mProcs[360];
  mProcs[360] = (UINT_PTR)&wglShareLists_fake;
#endif
#ifdef WGLSWAPBUFFERS
  wglSwapBuffers_real = (wglSwapBuffers_ptr)mProcs[361];
  mProcs[361] = (UINT_PTR)&wglSwapBuffers_fake;
#endif
#ifdef WGLSWAPLAYERBUFFERS
  wglSwapLayerBuffers_real = (wglSwapLayerBuffers_ptr)mProcs[362];
  mProcs[362] = (UINT_PTR)&wglSwapLayerBuffers_fake;
#endif
#ifdef WGLSWAPMULTIPLEBUFFERS
  wglSwapMultipleBuffers_real = (wglSwapMultipleBuffers_ptr)mProcs[363];
  mProcs[363] = (UINT_PTR)&wglSwapMultipleBuffers_fake;
#endif
#ifdef WGLUSEFONTBITMAPSA
  wglUseFontBitmapsA_real = (wglUseFontBitmapsA_ptr)mProcs[364];
  mProcs[364] = (UINT_PTR)&wglUseFontBitmapsA_fake;
#endif
#ifdef WGLUSEFONTBITMAPSW
  wglUseFontBitmapsW_real = (wglUseFontBitmapsW_ptr)mProcs[365];
  mProcs[365] = (UINT_PTR)&wglUseFontBitmapsW_fake;
#endif
#ifdef WGLUSEFONTOUTLINESA
  wglUseFontOutlinesA_real = (wglUseFontOutlinesA_ptr)mProcs[366];
  mProcs[366] = (UINT_PTR)&wglUseFontOutlinesA_fake;
#endif
#ifdef WGLUSEFONTOUTLINESW
  wglUseFontOutlinesW_real = (wglUseFontOutlinesW_ptr)mProcs[367];
  mProcs[367] = (UINT_PTR)&wglUseFontOutlinesW_fake;
#endif
}

void proxy_gl32::setup_proxy()
{
    char sysPath[MAX_PATH];
    GetSystemDirectoryA(sysPath, MAX_PATH);
    strcat_s(sysPath, "\\opengl32.dll");

    mHinstDLL = LoadLibrary(sysPath);
    if (!mHinstDLL)
    {
        return;
    }
    for (int i = 0; i < 368; ++i)
    {
        mProcs[i] = (UINT_PTR)GetProcAddress(mHinstDLL, mImportNames[i]);
    }
    _hook_setup();
}

extern "C" void GlmfBeginGlsBlock_wrapper();
extern "C" void GlmfCloseMetaFile_wrapper();
extern "C" void GlmfEndGlsBlock_wrapper();
extern "C" void GlmfEndPlayback_wrapper();
extern "C" void GlmfInitPlayback_wrapper();
extern "C" void GlmfPlayGlsRecord_wrapper();
extern "C" void glAccum_wrapper();
extern "C" void glAlphaFunc_wrapper();
extern "C" void glAreTexturesResident_wrapper();
extern "C" void glArrayElement_wrapper();
extern "C" void glBegin_wrapper();
extern "C" void glBindTexture_wrapper();
extern "C" void glBitmap_wrapper();
extern "C" void glBlendFunc_wrapper();
extern "C" void glCallList_wrapper();
extern "C" void glCallLists_wrapper();
extern "C" void glClear_wrapper();
extern "C" void glClearAccum_wrapper();
extern "C" void glClearColor_wrapper();
extern "C" void glClearDepth_wrapper();
extern "C" void glClearIndex_wrapper();
extern "C" void glClearStencil_wrapper();
extern "C" void glClipPlane_wrapper();
extern "C" void glColor3b_wrapper();
extern "C" void glColor3bv_wrapper();
extern "C" void glColor3d_wrapper();
extern "C" void glColor3dv_wrapper();
extern "C" void glColor3f_wrapper();
extern "C" void glColor3fv_wrapper();
extern "C" void glColor3i_wrapper();
extern "C" void glColor3iv_wrapper();
extern "C" void glColor3s_wrapper();
extern "C" void glColor3sv_wrapper();
extern "C" void glColor3ub_wrapper();
extern "C" void glColor3ubv_wrapper();
extern "C" void glColor3ui_wrapper();
extern "C" void glColor3uiv_wrapper();
extern "C" void glColor3us_wrapper();
extern "C" void glColor3usv_wrapper();
extern "C" void glColor4b_wrapper();
extern "C" void glColor4bv_wrapper();
extern "C" void glColor4d_wrapper();
extern "C" void glColor4dv_wrapper();
extern "C" void glColor4f_wrapper();
extern "C" void glColor4fv_wrapper();
extern "C" void glColor4i_wrapper();
extern "C" void glColor4iv_wrapper();
extern "C" void glColor4s_wrapper();
extern "C" void glColor4sv_wrapper();
extern "C" void glColor4ub_wrapper();
extern "C" void glColor4ubv_wrapper();
extern "C" void glColor4ui_wrapper();
extern "C" void glColor4uiv_wrapper();
extern "C" void glColor4us_wrapper();
extern "C" void glColor4usv_wrapper();
extern "C" void glColorMask_wrapper();
extern "C" void glColorMaterial_wrapper();
extern "C" void glColorPointer_wrapper();
extern "C" void glCopyPixels_wrapper();
extern "C" void glCopyTexImage1D_wrapper();
extern "C" void glCopyTexImage2D_wrapper();
extern "C" void glCopyTexSubImage1D_wrapper();
extern "C" void glCopyTexSubImage2D_wrapper();
extern "C" void glCullFace_wrapper();
extern "C" void glDebugEntry_wrapper();
extern "C" void glDeleteLists_wrapper();
extern "C" void glDeleteTextures_wrapper();
extern "C" void glDepthFunc_wrapper();
extern "C" void glDepthMask_wrapper();
extern "C" void glDepthRange_wrapper();
extern "C" void glDisable_wrapper();
extern "C" void glDisableClientState_wrapper();
extern "C" void glDrawArrays_wrapper();
extern "C" void glDrawBuffer_wrapper();
extern "C" void glDrawElements_wrapper();
extern "C" void glDrawPixels_wrapper();
extern "C" void glEdgeFlag_wrapper();
extern "C" void glEdgeFlagPointer_wrapper();
extern "C" void glEdgeFlagv_wrapper();
extern "C" void glEnable_wrapper();
extern "C" void glEnableClientState_wrapper();
extern "C" void glEnd_wrapper();
extern "C" void glEndList_wrapper();
extern "C" void glEvalCoord1d_wrapper();
extern "C" void glEvalCoord1dv_wrapper();
extern "C" void glEvalCoord1f_wrapper();
extern "C" void glEvalCoord1fv_wrapper();
extern "C" void glEvalCoord2d_wrapper();
extern "C" void glEvalCoord2dv_wrapper();
extern "C" void glEvalCoord2f_wrapper();
extern "C" void glEvalCoord2fv_wrapper();
extern "C" void glEvalMesh1_wrapper();
extern "C" void glEvalMesh2_wrapper();
extern "C" void glEvalPoint1_wrapper();
extern "C" void glEvalPoint2_wrapper();
extern "C" void glFeedbackBuffer_wrapper();
extern "C" void glFinish_wrapper();
extern "C" void glFlush_wrapper();
extern "C" void glFogf_wrapper();
extern "C" void glFogfv_wrapper();
extern "C" void glFogi_wrapper();
extern "C" void glFogiv_wrapper();
extern "C" void glFrontFace_wrapper();
extern "C" void glFrustum_wrapper();
extern "C" void glGenLists_wrapper();
extern "C" void glGenTextures_wrapper();
extern "C" void glGetBooleanv_wrapper();
extern "C" void glGetClipPlane_wrapper();
extern "C" void glGetDoublev_wrapper();
extern "C" void glGetError_wrapper();
extern "C" void glGetFloatv_wrapper();
extern "C" void glGetIntegerv_wrapper();
extern "C" void glGetLightfv_wrapper();
extern "C" void glGetLightiv_wrapper();
extern "C" void glGetMapdv_wrapper();
extern "C" void glGetMapfv_wrapper();
extern "C" void glGetMapiv_wrapper();
extern "C" void glGetMaterialfv_wrapper();
extern "C" void glGetMaterialiv_wrapper();
extern "C" void glGetPixelMapfv_wrapper();
extern "C" void glGetPixelMapuiv_wrapper();
extern "C" void glGetPixelMapusv_wrapper();
extern "C" void glGetPointerv_wrapper();
extern "C" void glGetPolygonStipple_wrapper();
extern "C" void glGetString_wrapper();
extern "C" void glGetTexEnvfv_wrapper();
extern "C" void glGetTexEnviv_wrapper();
extern "C" void glGetTexGendv_wrapper();
extern "C" void glGetTexGenfv_wrapper();
extern "C" void glGetTexGeniv_wrapper();
extern "C" void glGetTexImage_wrapper();
extern "C" void glGetTexLevelParameterfv_wrapper();
extern "C" void glGetTexLevelParameteriv_wrapper();
extern "C" void glGetTexParameterfv_wrapper();
extern "C" void glGetTexParameteriv_wrapper();
extern "C" void glHint_wrapper();
extern "C" void glIndexMask_wrapper();
extern "C" void glIndexPointer_wrapper();
extern "C" void glIndexd_wrapper();
extern "C" void glIndexdv_wrapper();
extern "C" void glIndexf_wrapper();
extern "C" void glIndexfv_wrapper();
extern "C" void glIndexi_wrapper();
extern "C" void glIndexiv_wrapper();
extern "C" void glIndexs_wrapper();
extern "C" void glIndexsv_wrapper();
extern "C" void glIndexub_wrapper();
extern "C" void glIndexubv_wrapper();
extern "C" void glInitNames_wrapper();
extern "C" void glInterleavedArrays_wrapper();
extern "C" void glIsEnabled_wrapper();
extern "C" void glIsList_wrapper();
extern "C" void glIsTexture_wrapper();
extern "C" void glLightModelf_wrapper();
extern "C" void glLightModelfv_wrapper();
extern "C" void glLightModeli_wrapper();
extern "C" void glLightModeliv_wrapper();
extern "C" void glLightf_wrapper();
extern "C" void glLightfv_wrapper();
extern "C" void glLighti_wrapper();
extern "C" void glLightiv_wrapper();
extern "C" void glLineStipple_wrapper();
extern "C" void glLineWidth_wrapper();
extern "C" void glListBase_wrapper();
extern "C" void glLoadIdentity_wrapper();
extern "C" void glLoadMatrixd_wrapper();
extern "C" void glLoadMatrixf_wrapper();
extern "C" void glLoadName_wrapper();
extern "C" void glLogicOp_wrapper();
extern "C" void glMap1d_wrapper();
extern "C" void glMap1f_wrapper();
extern "C" void glMap2d_wrapper();
extern "C" void glMap2f_wrapper();
extern "C" void glMapGrid1d_wrapper();
extern "C" void glMapGrid1f_wrapper();
extern "C" void glMapGrid2d_wrapper();
extern "C" void glMapGrid2f_wrapper();
extern "C" void glMaterialf_wrapper();
extern "C" void glMaterialfv_wrapper();
extern "C" void glMateriali_wrapper();
extern "C" void glMaterialiv_wrapper();
extern "C" void glMatrixMode_wrapper();
extern "C" void glMultMatrixd_wrapper();
extern "C" void glMultMatrixf_wrapper();
extern "C" void glNewList_wrapper();
extern "C" void glNormal3b_wrapper();
extern "C" void glNormal3bv_wrapper();
extern "C" void glNormal3d_wrapper();
extern "C" void glNormal3dv_wrapper();
extern "C" void glNormal3f_wrapper();
extern "C" void glNormal3fv_wrapper();
extern "C" void glNormal3i_wrapper();
extern "C" void glNormal3iv_wrapper();
extern "C" void glNormal3s_wrapper();
extern "C" void glNormal3sv_wrapper();
extern "C" void glNormalPointer_wrapper();
extern "C" void glOrtho_wrapper();
extern "C" void glPassThrough_wrapper();
extern "C" void glPixelMapfv_wrapper();
extern "C" void glPixelMapuiv_wrapper();
extern "C" void glPixelMapusv_wrapper();
extern "C" void glPixelStoref_wrapper();
extern "C" void glPixelStorei_wrapper();
extern "C" void glPixelTransferf_wrapper();
extern "C" void glPixelTransferi_wrapper();
extern "C" void glPixelZoom_wrapper();
extern "C" void glPointSize_wrapper();
extern "C" void glPolygonMode_wrapper();
extern "C" void glPolygonOffset_wrapper();
extern "C" void glPolygonStipple_wrapper();
extern "C" void glPopAttrib_wrapper();
extern "C" void glPopClientAttrib_wrapper();
extern "C" void glPopMatrix_wrapper();
extern "C" void glPopName_wrapper();
extern "C" void glPrioritizeTextures_wrapper();
extern "C" void glPushAttrib_wrapper();
extern "C" void glPushClientAttrib_wrapper();
extern "C" void glPushMatrix_wrapper();
extern "C" void glPushName_wrapper();
extern "C" void glRasterPos2d_wrapper();
extern "C" void glRasterPos2dv_wrapper();
extern "C" void glRasterPos2f_wrapper();
extern "C" void glRasterPos2fv_wrapper();
extern "C" void glRasterPos2i_wrapper();
extern "C" void glRasterPos2iv_wrapper();
extern "C" void glRasterPos2s_wrapper();
extern "C" void glRasterPos2sv_wrapper();
extern "C" void glRasterPos3d_wrapper();
extern "C" void glRasterPos3dv_wrapper();
extern "C" void glRasterPos3f_wrapper();
extern "C" void glRasterPos3fv_wrapper();
extern "C" void glRasterPos3i_wrapper();
extern "C" void glRasterPos3iv_wrapper();
extern "C" void glRasterPos3s_wrapper();
extern "C" void glRasterPos3sv_wrapper();
extern "C" void glRasterPos4d_wrapper();
extern "C" void glRasterPos4dv_wrapper();
extern "C" void glRasterPos4f_wrapper();
extern "C" void glRasterPos4fv_wrapper();
extern "C" void glRasterPos4i_wrapper();
extern "C" void glRasterPos4iv_wrapper();
extern "C" void glRasterPos4s_wrapper();
extern "C" void glRasterPos4sv_wrapper();
extern "C" void glReadBuffer_wrapper();
extern "C" void glReadPixels_wrapper();
extern "C" void glRectd_wrapper();
extern "C" void glRectdv_wrapper();
extern "C" void glRectf_wrapper();
extern "C" void glRectfv_wrapper();
extern "C" void glRecti_wrapper();
extern "C" void glRectiv_wrapper();
extern "C" void glRects_wrapper();
extern "C" void glRectsv_wrapper();
extern "C" void glRenderMode_wrapper();
extern "C" void glRotated_wrapper();
extern "C" void glRotatef_wrapper();
extern "C" void glScaled_wrapper();
extern "C" void glScalef_wrapper();
extern "C" void glScissor_wrapper();
extern "C" void glSelectBuffer_wrapper();
extern "C" void glShadeModel_wrapper();
extern "C" void glStencilFunc_wrapper();
extern "C" void glStencilMask_wrapper();
extern "C" void glStencilOp_wrapper();
extern "C" void glTexCoord1d_wrapper();
extern "C" void glTexCoord1dv_wrapper();
extern "C" void glTexCoord1f_wrapper();
extern "C" void glTexCoord1fv_wrapper();
extern "C" void glTexCoord1i_wrapper();
extern "C" void glTexCoord1iv_wrapper();
extern "C" void glTexCoord1s_wrapper();
extern "C" void glTexCoord1sv_wrapper();
extern "C" void glTexCoord2d_wrapper();
extern "C" void glTexCoord2dv_wrapper();
extern "C" void glTexCoord2f_wrapper();
extern "C" void glTexCoord2fv_wrapper();
extern "C" void glTexCoord2i_wrapper();
extern "C" void glTexCoord2iv_wrapper();
extern "C" void glTexCoord2s_wrapper();
extern "C" void glTexCoord2sv_wrapper();
extern "C" void glTexCoord3d_wrapper();
extern "C" void glTexCoord3dv_wrapper();
extern "C" void glTexCoord3f_wrapper();
extern "C" void glTexCoord3fv_wrapper();
extern "C" void glTexCoord3i_wrapper();
extern "C" void glTexCoord3iv_wrapper();
extern "C" void glTexCoord3s_wrapper();
extern "C" void glTexCoord3sv_wrapper();
extern "C" void glTexCoord4d_wrapper();
extern "C" void glTexCoord4dv_wrapper();
extern "C" void glTexCoord4f_wrapper();
extern "C" void glTexCoord4fv_wrapper();
extern "C" void glTexCoord4i_wrapper();
extern "C" void glTexCoord4iv_wrapper();
extern "C" void glTexCoord4s_wrapper();
extern "C" void glTexCoord4sv_wrapper();
extern "C" void glTexCoordPointer_wrapper();
extern "C" void glTexEnvf_wrapper();
extern "C" void glTexEnvfv_wrapper();
extern "C" void glTexEnvi_wrapper();
extern "C" void glTexEnviv_wrapper();
extern "C" void glTexGend_wrapper();
extern "C" void glTexGendv_wrapper();
extern "C" void glTexGenf_wrapper();
extern "C" void glTexGenfv_wrapper();
extern "C" void glTexGeni_wrapper();
extern "C" void glTexGeniv_wrapper();
extern "C" void glTexImage1D_wrapper();
extern "C" void glTexImage2D_wrapper();
extern "C" void glTexParameterf_wrapper();
extern "C" void glTexParameterfv_wrapper();
extern "C" void glTexParameteri_wrapper();
extern "C" void glTexParameteriv_wrapper();
extern "C" void glTexSubImage1D_wrapper();
extern "C" void glTexSubImage2D_wrapper();
extern "C" void glTranslated_wrapper();
extern "C" void glTranslatef_wrapper();
extern "C" void glVertex2d_wrapper();
extern "C" void glVertex2dv_wrapper();
extern "C" void glVertex2f_wrapper();
extern "C" void glVertex2fv_wrapper();
extern "C" void glVertex2i_wrapper();
extern "C" void glVertex2iv_wrapper();
extern "C" void glVertex2s_wrapper();
extern "C" void glVertex2sv_wrapper();
extern "C" void glVertex3d_wrapper();
extern "C" void glVertex3dv_wrapper();
extern "C" void glVertex3f_wrapper();
extern "C" void glVertex3fv_wrapper();
extern "C" void glVertex3i_wrapper();
extern "C" void glVertex3iv_wrapper();
extern "C" void glVertex3s_wrapper();
extern "C" void glVertex3sv_wrapper();
extern "C" void glVertex4d_wrapper();
extern "C" void glVertex4dv_wrapper();
extern "C" void glVertex4f_wrapper();
extern "C" void glVertex4fv_wrapper();
extern "C" void glVertex4i_wrapper();
extern "C" void glVertex4iv_wrapper();
extern "C" void glVertex4s_wrapper();
extern "C" void glVertex4sv_wrapper();
extern "C" void glVertexPointer_wrapper();
extern "C" void glViewport_wrapper();
extern "C" void wglChoosePixelFormat_wrapper();
extern "C" void wglCopyContext_wrapper();
extern "C" void wglCreateContext_wrapper();
extern "C" void wglCreateLayerContext_wrapper();
extern "C" void wglDeleteContext_wrapper();
extern "C" void wglDescribeLayerPlane_wrapper();
extern "C" void wglDescribePixelFormat_wrapper();
extern "C" void wglGetCurrentContext_wrapper();
extern "C" void wglGetCurrentDC_wrapper();
extern "C" void wglGetDefaultProcAddress_wrapper();
extern "C" void wglGetLayerPaletteEntries_wrapper();
extern "C" void wglGetPixelFormat_wrapper();
extern "C" void wglGetProcAddress_wrapper();
extern "C" void wglMakeCurrent_wrapper();
extern "C" void wglRealizeLayerPalette_wrapper();
extern "C" void wglSetLayerPaletteEntries_wrapper();
extern "C" void wglSetPixelFormat_wrapper();
extern "C" void wglShareLists_wrapper();
extern "C" void wglSwapBuffers_wrapper();
extern "C" void wglSwapLayerBuffers_wrapper();
extern "C" void wglSwapMultipleBuffers_wrapper();
extern "C" void wglUseFontBitmapsA_wrapper();
extern "C" void wglUseFontBitmapsW_wrapper();
extern "C" void wglUseFontOutlinesA_wrapper();
extern "C" void wglUseFontOutlinesW_wrapper();
