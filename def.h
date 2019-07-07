#pragma once

#ifndef UINT
typedef unsigned int UINT;
#endif
#ifndef NULL
#define NULL 0
#endif

typedef float		MATDATA;//矩阵数据类型
typedef unsigned int 	MATRET;//函数返回值

#define RET_OK 						0x0000
#define RET_NOT_ROW_MATCH 			0x0001
#define RET_NOT_COL_MATCH 			0x0002
#define RET_INDEX_NOT_IN_ROW 		0x0003
#define RET_INDEX_NOT_IN_COL 		0x0004
#define RET_PARAM_POINT_NULL 		0x0005
#define RET_PARAM_POINT_NOT_NULL 	0x0006
#define RET_NOT_ENOUGH_MEMERY	 	0x0007
