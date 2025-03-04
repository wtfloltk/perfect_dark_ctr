#ifndef _IN_GAME_GFXMEMORY_H
#define _IN_GAME_GFXMEMORY_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

extern u8 *g_GfxBuffers[3];

void gfxReset(void);
Gfx *gfxGetMasterDisplayList(void);
Vtx *gfxAllocateVertices(u32 count);
void *gfxAllocateMatrix(void);
LookAt *gfxAllocateLookAt(s32 count);
Col *gfxAllocateColours(s32 count);
void *gfxAllocate(u32 size);
void gfxSwapBuffers(void);
s32 gfxGetFreeGfx(Gfx *gdl);

#endif
