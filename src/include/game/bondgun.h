#ifndef _IN_GAME_BONDGUN_H
#define _IN_GAME_BONDGUN_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

void bgunReset(void);

void bgunStop(void);

void bgunRumble(s32 handnum, s32 weaponnum);
s32 bgunGetUnequippedReloadIndex(s32 weaponnum);
void bgunTickUnequippedReload(void);
bool bgun0f097df0(struct inventory_typef *arg0, struct hand *hand);
void bgunSetPartVisible(s16 partnum, bool visible, struct hand *hand, struct modelfiledata *filedata);
void bgun0f097f28(struct hand *hand, struct modelfiledata *arg1, struct inventory_typef *arg2);
void bgun0f098030(struct hand *hand, struct modelfiledata *arg1);
f32 bgun0f09815c(struct hand *hand);
void bgun0f0981e8(struct hand *hand, struct modelfiledata *modeldef);
bool bgun0f098884(struct guncmd *cmd, struct gset *gset);
void bgunStartAnimation(struct guncmd *cmd, s32 handnum, struct hand *hand);
bool bgun0f098a44(struct hand *hand, s32 time);
bool bgunIsAnimBusy(struct hand *hand);
void bgunResetAnim(struct hand *hand);
void bgunGetWeaponInfo(struct handweaponinfo *info, s32 handnum);
s32 bgun0f098ca0(s32 arg0, struct handweaponinfo *info, struct hand *hand);
void bgun0f098df8(s32 weaponfunc, struct handweaponinfo *info, struct hand *hand, u8 onebullet, u8 checkunequipped);
void bgun0f098f8c(struct handweaponinfo *info, struct hand *hand);
bool bgun0f099008(s32 handnum);
bool bgun0f0990b0(struct weaponfunc *basefunc, struct weapon *weapon);
bool bgun0f099188(struct hand *hand, s32 gunfunc);
s32 bgunTickIncIdle(struct handweaponinfo *info, s32 handnum, struct hand *hand, s32 lvupdate);
void bgun0f099780(struct hand *hand, f32 angle);
s32 bgunTickIncAutoSwitch(struct handweaponinfo *info, s32 handnum, struct hand *hand, s32 lvupdate);
bool bgunIsReloading(struct hand *hand);
s32 bgunTickIncReload(struct handweaponinfo *info, s32 handnum, struct hand *hand, s32 lvupdate);
s32 bgunTickIncChangeFunc(struct handweaponinfo *info, s32 handnum, struct hand *hand, s32 lvupdate);
s32 bgun0f09a3f8(struct hand *hand, struct weaponfunc *func);
void bgun0f09a6f8(struct handweaponinfo *info, s32 handnum, struct hand *hand, struct weaponfunc *func);
bool bgun0f09aba4(struct hand *hand, struct handweaponinfo *info, s32 handnum, struct weaponfunc_shoot *func);
bool bgunTickIncAttackingShoot(struct handweaponinfo *info, s32 handnum, struct hand *hand);
bool bgunTickIncAttackingThrow(s32 handnum, struct hand *hand);
s32 bgunGetMinClipQty(s32 weaponnum, s32 funcnum);
bool bgunTickIncAttackingClose(s32 handnum, struct hand *hand);
bool bgunTickIncAttackingSpecial(struct hand *hand);
s32 bgunTickIncAttackEmpty(struct handweaponinfo *info, s32 handnum, struct hand *hand, s32 lvupdate);
s32 bgunTickIncAttack(struct handweaponinfo *info, s32 handnum, struct hand *hand, s32 lvupdate);
bool bgunIsReadyToSwitch(s32 handnum);
bool bgunCanFreeWeapon(s32 handnum);
bool bgun0f09bf44(s32 handnum);
s32 bgunTickIncChangeGun(struct handweaponinfo *info, s32 handnum, struct hand *hand, s32 lvupdate);
s32 bgunTickIncState2(struct handweaponinfo *info, s32 handnum, struct hand *hand, s32 lvupdate);
s32 bgunTickInc(struct handweaponinfo *info, s32 handnum, s32 lvupdate);
bool bgunSetState(s32 handnum, s32 state);
void bgunTickHand(s32 handnum);
void bgunTickSwitch(void);
void bgunInitHandAnims(void);
f32 bgunGetNoiseRadius(s32 handnum);
void bgunDecreaseNoiseRadius(void);
void bgunCalculateBlend(s32 hand);
void bgunUpdateBlend(struct hand *hand, s32 handnum);
void bgun0f09d8dc(f32 breathing, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
bool bgun0f09dd7c(void);
u32 bgunGetGunMemType(void);
u8 *bgunGetGunMem(void);
u32 bgunCalculateGunMemCapacity(void);
void bgunFreeGunMem(void);
void bgunSetGunMemWeapon(s32 weaponnum);
void bgun0f09df9c(void);
bool bgun0f09e004(s32 newowner);
void bgunTickGunLoad(void);
void bgunTickMasterLoad(void);
void bgunTickLoad(void);
bool bgun0f09eae4(void);
struct modelfiledata *bgunGetCartModeldef(void);
void bgun0f09ebcc(struct defaultobj *obj, struct coord *coord, s16 *rooms, Mtxf *matrix1, struct coord *velocity, Mtxf *matrix2, struct prop *prop, struct coord *pos);
void bgun0f09ed2c(struct defaultobj *obj, struct coord *coord, Mtxf *arg2, struct coord *velocity, Mtxf *arg4);
struct defaultobj *bgunCreateThrownProjectile2(struct chrdata *chr, struct gset *gset, struct coord *pos, s16 *rooms, Mtxf *arg4, struct coord *velocity);
void bgunCreateThrownProjectile(s32 handnum, struct gset *gset);
void bgunUpdateHeldRocket(s32 handnum);
void bgunCreateHeldRocket(s32 handnum, struct weaponfunc_shootprojectile *func);
void bgunFreeHeldRocket(s32 handnum);
void bgunCreateFiredProjectile(s32 handnum);
void bgunSwivel(f32 autoaimx, f32 autoaimy, f32 crossdamp, f32 aimdamp);
void bgunSwivelWithDamp(f32 screenx, f32 screeny, f32 damp);
void bgunSwivelWithoutDamp(f32 arg0, f32 arg1);
void bgunGetCrossPos(f32 *x, f32 *y);
void bgun0f0a0c08(struct coord *arg0, struct coord *arg1);
void bgun0f0a0c44(s32 handnum, struct coord *arg1, struct coord *arg2);
void bgunCalculatePlayerShotSpread(struct coord *arg0, struct coord *arg1, s32 handnum, bool dorandom);
void bgunCalculateBotShotSpread(struct coord *arg0, s32 weaponnum, s32 funcnum, bool arg3, s32 crouchpos, bool dual);
void bgunSetLastShootInfo(struct coord *pos, struct coord *dir, s32 handnum);
s32 bgunGetShotsToTake(s32 handnum);
void bgunFreeWeapon(s32 handnum);
void bgunTickSwitch2(void);
void bgunEquipWeapon(s32 weaponnum);
s32 bgunGetWeaponNum(s32 handnum);
bool bgun0f0a1a10(s32 weaponnum);
s32 bgunGetSwitchToWeapon(s32 handnum);
void bgunSwitchToPrevious(void);
void bgunCycleForward(void);
void bgunCycleBack(void);
bool bgunHasAmmoForWeapon(s32 weaponnum);
void bgunAutoSwitchWeapon(void);
void bgunEquipWeapon2(s32 handnum, s32 weaponnum);
s32 bgunIsFiring(s32 handnum);
s32 bgunGetAttackType(s32 handnum);
char *bgunGetName(s32 weaponnum);
u16 bgunGetNameId(s32 weaponnum);
char *bgunGetShortName(s32 arg0);
void bgunReloadIfPossible(s32 handnum);
void bgunSetAdjustPos(f32 angle);
void bgunStartSlide(s32 handnum);
void bgunUpdateSlide(s32 handnum);
f32 bgun0f0a2498(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void bgun0f0a24f0(struct coord *arg0, s32 handnum);
bool bgun0f0a27c8(void);
void bgunHandlePlayerDead(void);
bool bgunIsMissionCritical(s32 weaponnum);
void bgunDisarm(struct prop *attacker);
void bgunExecuteModelCmdList(s32 *arg0);
s32 bgunCreateModelCmdList(struct model *model, struct modelnode *node, s32 *ptr);
void bgunStartDetonateAnimation(s32 playernum);
void bgunUpdateGangsta(struct hand *hand, s32 handnum, struct coord *arg2, struct weaponfunc *funcdef, Mtxf *arg4, Mtxf *arg5);
void bgunUpdateSmoke(struct hand *hand, s32 handnum, s32 weaponnum, struct weaponfunc *funcdef);
void bgunUpdateLasersight(struct hand *hand, struct modelfiledata *modeldef, s32 handnum, u8 *allocation);
void bgunUpdateReaper(struct hand *hand, struct modelfiledata *modeldef);
void bgunUpdateSniperRifle(struct modelfiledata *modeldef, u8 *allocation);
void bgunUpdateDevastator(struct hand *hand, u8 *allocation, struct modelfiledata *modeldef);
void bgunUpdateShotgun(struct hand *hand, u8 *allocation, bool *arg2, struct modelfiledata *modeldef);
void bgunUpdateLaser(struct hand *hand);
void bgunUpdateMagnum(struct hand *hand, s32 handnum, struct modelfiledata *modeldef, Mtxf *mtx);
void bgunUpdateRocketLauncher(struct hand *hand, s32 handnum, struct weaponfunc_shootprojectile *func);
void bgun0f0a45d0(struct hand *hand, struct modelfiledata *modeldef, bool isdetonator);
void bgun0f0a46a4(struct hand *hand, struct modelfiledata *modeldef, bool isdetonator);
void bgun0f0a4e44(struct hand *hand, struct weapon *weapondef, struct modelfiledata *modeldef, struct weaponfunc *funcdef, s32 maxburst, u8 *allocation, s32 weaponnum, bool **arg7, s32 mtxindex, Mtxf *arg9, Mtxf *arg10);
void bgunCreateFx(struct hand *hand, s32 handnum, struct weaponfunc *funcdef, s32 weaponnum, struct modelfiledata *modeldef, u8 *allocation);
void bgun0f0a5550(s32 handnum);
void bgunTickMaulerCharge(void);
void bgunTickGameplay2(void);
s32 bgunAllocateFireslot(void);
void bgunRender(Gfx **gdl);
struct sndstate **bgunAllocateAudioHandle(void);
void bgunPlayPropHitSound(struct gset *gset, struct prop *prop, s32 texturenum);
void bgunPlayGlassHitSound(struct coord *pos, s16 *rooms, s32 texturenum);
void bgunPlayBgHitSound(struct gset *gset, struct coord *hitpos, s32 texturenum, s16 *arg3);
void bgunSetTriggerOn(s32 handnum, bool on);
s32 bgunConsiderToggleGunFunction(s32 usedowntime, bool firing, s32 arg2);
void bgun0f0a8c50(void);
bool bgunIsUsingSecondaryFunction(void);
void bgunTickGameplay(bool triggeron);
void bgunSetPassiveMode(bool enable);
void bgunSetAimType(u32 aimtype);
void bgunSetAimPos(struct coord *coord);
void bgunSetHitPos(struct coord *coord);
void bgun0f0a9494(u32 operation);
void bgun0f0a94d0(u32 operation, struct coord *pos, struct coord *rot);
void bgunSetGunAmmoVisible(u32 reason, bool enable);
void bgunSetAmmoQuantity(s32 ammotype, s32 quantity);
s32 bgunGetReservedAmmoCount(s32 type);
s32 bgunGetAmmoCount(s32 ammotype);
s32 bgunGetCapacityByAmmotype(s32 ammotype);
bool bgunAmmotypeAllowsUnlimitedAmmo(u32 ammotype);
void bgunGiveMaxAmmo(bool force);
u32 bgunGetAmmoTypeForWeapon(u32 weaponnum, u32 func);
s32 bgunGetAmmoQtyForWeapon(u32 weaponnum, u32 func);
void bgunSetAmmoQtyForWeapon(u32 weaponnum, u32 func, u32 quantity);
s32 bgunGetAmmoCapacityForWeapon(s32 weaponnum, s32 func);
Gfx *bgunDrawHudString(Gfx *gdl, char *text, s32 x, bool halign, s32 y, s32 valign, u32 colour);
Gfx *bgunDrawHudInteger(Gfx *gdl, s32 value, s32 x, bool halign, s32 y, s32 valign, u32 colour);
void bgunResetAbmag(struct abmag *abmag);
void bgun0f0a9da8(struct abmag *abmag, s32 remaining, s32 capacity, s32 height);
Gfx *bgunDrawHudGauge(Gfx *gdl, s32 x1, s32 y1, s32 x2, s32 y2, struct abmag *abmag, s32 remaining, s32 capacity, u32 vacantcolour, u32 occupiedcolour, bool flip);
Gfx *bgunDrawHud(Gfx *gdl);
void bgunAddBoost(s32 arg0);
void bgunSubtractBoost(s32 arg0);
void bgunApplyBoost(void);
void bgunRevertBoost(void);
void bgunTickBoost(void);
void bgunSetSightVisible(u32 bits, bool visible);
Gfx *bgunDrawSight(Gfx *gdl);
void bgun0f0abd30(s32 handnum);
s32 bgunGetWeaponNum2(s32 handnum);
s8 bgunFreeFireslotWrapper(s32 fireslot);
s8 bgunFreeFireslot(s32 fireslot);

#endif
