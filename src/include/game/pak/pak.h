#ifndef IN_GAME_PAK_PAK_H
#define IN_GAME_PAK_PAK_H
#include <ultra64.h>
#include "types.h"

u32 func0f1165d0(s8 arg0);
u32 func0f1165f8(void);
u32 func0f116658(s8 arg0, u32 arg1);
u32 func0f116684(u32 arg0);
u32 func0f11668c(void);
bool pakIsConnected(s32 paknum);
u32 func0f1167b0(void);
u32 func0f1167d8(s8 arg0);
u32 func0f116800(void);
u32 func0f116828(void);
u32 func0f116860(void);
s32 pakDeleteGameNote(s8 device, u16 company_code, u32 game_code, char *game_name, char *ext_name);
s32 func0f1168c4(s8 device, struct pakdata **arg1);
u32 func0f116914(void);
u32 func0f11693c(void);
void func0f116994(void);
u32 func0f1169c8(void);
u32 func0f116aec(void);
u32 func0f116b5c(void);
u32 func0f116bdc(void);
u32 func0f116c54(void);
u32 func0f116c94(void);
void func0f116db0(s8 arg0, s32 arg1);
u32 func0f116df0(void);
u32 func0f116e84(void);
u32 func0f116fa0(void);
u32 func0f11702c(void);
s32 func0f11706c(s8 arg0);
s32 func0f117094(s8 arg0, u32 arg1);
u32 func0f117150(void);
u32 func0f1171b4(void);
u32 func0f117210(void);
u32 func0f117430(void);
u32 func0f117520(s8 arg0, u32 arg1, u32 *arg2);
u32 func0f11776c(void);
u32 func0f117848(void);
u32 func0f11789c(void);
u32 func0f117b04(void);
u32 func0f117b4c(void);
u32 func0f117c0c(void);
u32 func0f117c80(void);
u32 func0f117ce4(void);
u32 func0f117d90(u32 arg0, u16 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 *arg6);
u32 func0f117e00(u32 arg0, u16 arg1, u32 arg2, u32 arg3, u32 arg4);
u32 func0f117e58(u32 arg0, u16 arg1, u32 arg2, u32 arg3, u32 arg4, u32 *arg5);
u32 func0f117ec0(void);
u32 func0f117f80(void);
u32 func0f117fc0(s8 arg0);
u32 func0f118000(void);
u32 func0f11807c(void);
u32 func0f118148(void);
u32 func0f118230(void);
u32 func0f118334(void);
u32 func0f1185e0(void);
u32 func0f118674(s8 arg0, u32 arg1, u32 arg2);
void func0f1189d8(void);
void func0f118ae4(u8 *arg0, u8 *arg1, u16 *arg2);
u32 func0f118bc8(void);
u32 func0f118d18(void);
u32 func0f1190bc(void);
u32 func0f119298(s8 index);
void func0f119340(u32 arg0);
u32 func0f119368(void);
#if VERSION >= VERSION_NTSC_FINAL
bool func0f119478(u32 arg0, u32 arg1, u32 *arg2);
#endif
u32 func0f1194e0(s8 arg0, u32 *arg1, u32 arg2);
u32 func0f11970c(void);
u32 func0f119da8(void);
u32 func0f119e8c(void);
u32 func0f11a0e8(void);
u32 func0f11a1d0(void);
void func0f11a2e4(void);
u32 func0f11a32c(void);
u32 func0f11a434(void);
u32 func0f11a504(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u16 *arg6);
u32 func0f11a574(void);
u32 func0f11a7dc(void);
u32 func0f11a8f4(void);
u32 func0f11ac7c(void);
u32 func0f11afb0(void);
u32 func0f11b178(void);
u32 func0f11b488(void);
u32 func0f11b548(void);
u32 func0f11b75c(void);
u32 func0f11b86c(void);
u32 func0f11bbd8(void);
u32 func0f11bc54(s8 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, u32 arg7, u32 arg8);
bool pakRepair(s32 arg0);
u32 func0f11c39c(u32 arg0, u32 arg1, u32 ar2, u32 arg3);
void func0f11c54c(void);
void func0f11c6d0(void);
void func0f11c7a0(void);
u32 func0f11ca30(void);
void func0f11cb9c(u32 arg0);
u32 func0f11cbd8(void);
u32 func0f11cc6c(void);
u32 func0f11cd00(void);
u32 func0f11ce00(void);
u32 func0f11d118(void);
u32 func0f11d174(void);
u32 func0f11d214(void);
u32 func0f11d3f8(void);
u32 func0f11d478(void);
u32 func0f11d4dc(void);
s32 func0f11d540(s8 index, s32 arg1);
s32 func0f11d5b0(s8 index);
u32 func0f11d620(void);
u32 func0f11d8b4(void);
u32 func0f11d9c4(void);
u32 func0f11dc04(void);
void func0f11dcb0(s32 arg0);
void func0f11dd58(s8 playernum);
u32 func0f11de20(void);
void func0f11deb8(void);
void func0f11df38(void);
void func0f11df8c(void);
u32 func0f11df94(void);
u32 func0f11e3bc(void);
u32 func0f11e3fc(void);
u32 func0f11e478(void);
u32 func0f11e4d4(void);
void bitSetByIndex(u32 value, u32 *flags, bool set);
u32 bitGetByIndex(u32 value, u32 *flags);
void func0f11e5bc(u32 *flags);
u32 func0f11e618(void);
s32 func0f11e6b0(s32 arg0);
u32 func0f11e750(void);
u32 func0f11e78c(void);
u32 func0f11e7f0(void);
u32 func0f11e844(void);
u32 func0f11ea34(void);

extern const char var7f1b423c[];
extern const char var7f1b4244[];
extern const char var7f1b424c[];
extern const char var7f1b4254[];
extern const char var7f1b425c[];

#endif
