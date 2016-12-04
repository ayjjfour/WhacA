#pragma once

enum emMoleError
{
	emME_OK					= 0,

	emME_MONSTER_TYPE,

	emME_ARENA_FULL,		// ����Ϊ��
	emME_ARENA_CREATE,		// ���򴴽�ʧ��

	emME_OBJ_USEDOUT,
	emME_OBJ_NULL,			// ����Ϊ��
	emME_OBJ_CREATE,		// ��������ʧ��
};

#define		_MODE_(_v_)		((0xFFFF)&(_v_))
#define		BUILD_ERRORCODE(_sys_, _pro_)		((((int)(_MODE_(_sys_)|0x8000))<<16) | (_MODE_(_pro_)|0x8000))
#define		GETSYS_ERROR(_err_)					((0x7FFF)&((_sys_)>>16))
#define		GETPRO_ERROR(_err_)					((0x7FFF)&(_err_))