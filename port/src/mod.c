#include <stdlib.h>
#include <string.h>
#include <PR/ultratypes.h>
#include "platform.h"
#include "system.h"
#include "fs.h"
#include "utils.h"
#include "romdata.h"
#include "mod.h"
#include "data.h"
#include "game/stagetable.h"

extern struct stagemusic g_StageTracks[];
extern struct stageallocation g_StageAllocations8Mb[];

static inline char *modConfigParseFileValue(char *p, char *token, s32 *filenum)
{
	p = strParseToken(p, token, NULL);
	if (!token[0]) {
		return NULL; // empty 
	}
	// check if it is a number already
	s32 num = strtol(token, NULL, 0);
	if (num > 0 && romdataFileGetName(num)) {
		*filenum = num;
		return p;
	}
	// it's a filename
	num = romdataFileGetNumForName(strUnquote(token));
	if (num >= 0) {
		*filenum = num;
		return p;
	}
	// the filename was invalid
	return NULL;
}

static inline char *modConfigParseNumericValue(char *p, char *token, s32 *out)
{
	p = strParseToken(p, token, NULL);
	if (!token[0]) {
		return NULL; // empty 
	}
	char *endp = token;
	const s32 num = strtol(token, &endp, 0);
	if (num == 0 && (endp == token || *endp != '\0')) {
		return NULL;
	}
	*out = num;
	return p;
}

static inline char *modConfigParseStageMusic(char *p, char *token, s32 stagenum)
{
	struct stagemusic *smus = NULL;
	for (struct stagemusic *p = g_StageTracks; p->stagenum; ++p) {
		if (p->stagenum == stagenum) {
			smus = p;
			break;
		}
	}

	if (!smus) {
		sysLogPrintf(LOG_ERROR, "modconfig: stage 0x%02x: music can't be changed for this stage", stagenum);
		return NULL;
	}

	// eat opening bracket
	p = strParseToken(p, token, NULL);
	if (token[0] != '{' || token[1] != '\0') {
		return NULL;
	}

	// parse keyvalues until } is reached
	s32 tmp = 0;
	p = strParseToken(p, token, NULL);
	while (p && token[0] && strcmp(token, "}") != 0) {
		if (!strcmp(token, "primarytrack")) {
			p = modConfigParseNumericValue(p, token, &tmp);
			if (!p || tmp < 0 || tmp > 128) {
				sysLogPrintf(LOG_ERROR, "modconfig: stage 0x%02x: music: invalid primarytrack value: %s", stagenum, token);
				return NULL;
			}
			smus->primarytrack = tmp;
		} else if (!strcmp(token, "ambienttrack")) {
			p = modConfigParseNumericValue(p, token, &tmp);
			if (!p || tmp < 0 || tmp > 128) {
				sysLogPrintf(LOG_ERROR, "modconfig: stage 0x%02x: music: invalid ambienttrack value: %s", stagenum, token);
				return NULL;
			}
			smus->ambienttrack = tmp;
		} else if (!strcmp(token, "xtrack")) {
			p = modConfigParseNumericValue(p, token, &tmp);
			if (!p || tmp < 0 || tmp > 128) {
				sysLogPrintf(LOG_ERROR, "modconfig: stage 0x%02x: music: invalid xtrack value: %s", stagenum, token);
				return NULL;
			}
			smus->xtrack = tmp;
		} else {
			sysLogPrintf(LOG_ERROR, "modconfig: stage 0x%02x: music: invalid key: %s", stagenum, token);
			return NULL;
		}
		p = strParseToken(p, token, NULL);
	}

	if (token[0] != '}') {
		sysLogPrintf(LOG_ERROR, "modconfig: stage 0x%02x: unterminated music block", stagenum);
		return NULL;
	}

	return p;
}

static inline char *modConfigParseStage(char *p, char *token)
{
	// stage number
	p = strParseToken(p, token, NULL);
	const s32 stagenum = strtol(token, NULL, 0);
	if (stagenum <= 0x01 || stagenum > 0x50) {
		return NULL;
	}

	// eat opening bracket
	p = strParseToken(p, token, NULL);
	if (token[0] != '{' || token[1] != '\0') {
		return NULL;
	}

	// find the stage table pointers this corresponds to
	struct stagetableentry *stab = NULL;
	struct stageallocation *salloc = NULL;
	const s32 sidx = stageGetIndex(stagenum);
	if (sidx >= 0) {
		stab = &g_Stages[sidx];
	}
	for (struct stageallocation *p = g_StageAllocations8Mb; p->stagenum; ++p) {
		if (p->stagenum == stagenum) {
			salloc = p;
			break;
		}
	}

	// parse keyvalues until } is reached
	s32 tmp = 0;
	p = strParseToken(p, token, NULL);
	while (p && token[0] && strcmp(token, "}") != 0) {
		if (!strcmp(token, "bgfile")) {
			// bg FILE_NAME_OR_NUM
			p = modConfigParseFileValue(p, token, &tmp);
			if (p && stab) {
				stab->bgfileid = tmp;
			} else {
				sysLogPrintf(LOG_ERROR, "modconfig: stage 0x%02x: invalid bgfile value: %s", stagenum, token);
				return NULL;
			}
		} else if (!strcmp(token, "tilesfile")) {
			// tiles FILE_NAME_OR_NUM
			p = modConfigParseFileValue(p, token, &tmp);
			if (p && stab) {
				stab->tilefileid = tmp;
			} else {
				sysLogPrintf(LOG_ERROR, "modconfig: stage 0x%02x: invalid tilesfile value: %s", stagenum, token);
				return NULL;
			}
		} else if (!strcmp(token, "padsfile")) {
			// tiles FILE_NAME_OR_NUM
			p = modConfigParseFileValue(p, token, &tmp);
			if (p && stab) {
				stab->padsfileid = tmp;
			} else {
				sysLogPrintf(LOG_ERROR, "modconfig: stage 0x%02x: invalid padsfile value: %s", stagenum, token);
				return NULL;
			}
		} else if (!strcmp(token, "setupfile")) {
			// setup FILE_NAME_OR_NUM
			p = modConfigParseFileValue(p, token, &tmp);
			if (p && stab) {
				stab->setupfileid = tmp;
			} else {
				sysLogPrintf(LOG_ERROR, "modconfig: stage 0x%02x: invalid setupfile value: %s", stagenum, token);
				return NULL;
			}
		} else if (!strcmp(token, "mpsetupfile")) {
			// mpsetup FILE_NAME_OR_NUM
			p = modConfigParseFileValue(p, token, &tmp);
			if (p && stab) {
				stab->mpsetupfileid = tmp;
			} else {
				sysLogPrintf(LOG_ERROR, "modconfig: stage 0x%02x: invalid mpsetupfile value: %s", stagenum, token);
				return NULL;
			}
		} else if (!strcmp(token, "allocation")) {
			// allocation "ALLOCSTRING"
			p = strParseToken(p, token, NULL);
			char *str = strUnquote(token);
			if (!p || !str[0] || !salloc) {
				sysLogPrintf(LOG_ERROR, "modconfig: stage 0x%02x: invalid allocation value: %s", stagenum, token);
				return NULL;
			}
			// FIXME: this leaks
			str = strDuplicate(str);
			if (str) {
				salloc->string = str;
			}
		}	else if (!strcmp(token, "music")) {
			// music { KEYVALUES... }
			p = modConfigParseStageMusic(p, token, stagenum);
			if (!p) {
				return NULL;
			}
		}
		p = strParseToken(p, token, NULL);
	}

	if (token[0] != '}') {
		sysLogPrintf(LOG_ERROR, "modconfig: unterminated stage 0x%02x block", stagenum);
		return NULL;
	}

	return p;
}

s32 modConfigLoad(const char *fname)
{
	u32 dataLen = 0;
	char *data = fsFileLoad(fname, &dataLen);
	if (!data) {
		return false;
	}

	s32 success = true;
	char token[UTIL_MAX_TOKEN + 1] = { 0 };
	char *end = data + dataLen;
	char *p = strParseToken(data, token, NULL);
	while (p && token[0]) {
		if (!strcmp(token, "stage")) {
			// stage NUMBER { KEYVALUES... }
			char *prev = p;
			p = modConfigParseStage(p, token);
			if (!p) {
				sysLogPrintf(LOG_ERROR, "modconfig: malformed stage block at offset %d", prev - data);
				success = false;
				break;
			}
		} else {
			// garbage
			sysLogPrintf(LOG_ERROR, "modconfig: unexpected %s at offset %d", token[0] ? token : "end of file", p - data);
			success = false;
			break;
		}
		p = strParseToken(p, token, NULL);
	}

	sysMemFree(data);
	return success;
}
