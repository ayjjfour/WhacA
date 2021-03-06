#pragma once

enum emMoleError
{
	emME_OK					= 0,

	emME_MONSTER_TYPE,

	emME_ARENA_FULL,		// 区域为空
	emME_ARENA_CREATE,		// 区域创建失败

	emME_OBJ_USEDOUT,
	emME_OBJ_NULL,			// 对象为空
	emME_OBJ_CREATE,		// 创建对象失败

	emME_HIT_TYPE,			// 未知打击类型（目前有三种，正常敲死，技能打死，鼠王暴击）
	emME_HIT_CHAIRID,		// 玩家座位ID
	emME_HIT_WEAPONID,		// 未知武器ID

	emME_PROTOCAL_NULL,		// 协议数据为空
	emME_PROTOCAL_PRASE,	// 解析协议失败

};

#define		_MODE_(_v_)		((0xFFFF)&(_v_))
#define		BUILD_ERRORCODE(_sys_, _pro_)		((((int)(_MODE_(_sys_)|0x8000))<<16) | (_MODE_(_pro_)|0x8000))
#define		GETSYS_ERROR(_err_)					((0x7FFF)&((_sys_)>>16))
#define		GETPRO_ERROR(_err_)					((0x7FFF)&(_err_))