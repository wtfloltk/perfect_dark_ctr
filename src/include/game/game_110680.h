#ifndef IN_GAME_GAME_110680_H
#define IN_GAME_GAME_110680_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

bool bossfileLoadFull(void);
u32 func0f110720(void);
void bossfileLoad(void);
void bossfileSave(void);
void bossfileSetDefaults(void);
void func0f110bf0(void);
void func0f110bf8(void);
void filelistCreate(s32 listnum, u8 filetype);
s32 filelistFindOrCreate(u8 filetype);
void func0f110d90(s32 index);
void filelistsTick(void);
void filelistUpdate(struct filelist *list);

#endif
