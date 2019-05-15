#ifndef _PUSICO_H
#define _PUSICO_H

#include <windows.h>

#define TPDO1	0
#define TPDO2	1
#define TPDO3	2
#define TPDO4	3

#define RPDO1	0
#define RPDO2	1
#define RPDO3	2
#define RPDO4	3

/* 设备错误代码 */
typedef enum {
	RET_SUCCESS = 0, /*操作成功*/
	RET_GENERNAL_ERR = 1, /*通用错误*/
	RET_LOADDRIVER_FAIL = 2, /* 装载驱动失败 */
	RET_OPEN_FAIL = 3,  /*打开适配器失败*/
	RET_READSDO_FAIL = 4, /*读SDO失败*/
	RET_READSDO_TIMEOUT = 5, /*读SDO超时*/
	RET_WRITESDO_FAIL = 6, /*写SDO失败*/
	RET_WRITESDO_TIMEOUT = 7, /*写SDO超时*/	
	RET_NOIDLE_SDO_CLIENT = 8,/*SDO客户端没有可用的通道*/
	RET_WRITEPDO_FAIL = 9,/*写PDO失败*/
}PUSIResult;

/* 从站管理 */
typedef enum{
    SLAVE_START = 1, /* 启动从站 */
    SLAVE_STOP = 2, /* 停止从站 */
    SLAVE_PRE_OPERATIONAL = 128, /* 使从站进入预工作状态 */
    SLAVE_RESET = 129, /* 复位从站 */
    SLAVE_RESET_CONNECTION = 130, /* 复位从站连接 */
	SLAVE_PV_STEP = 10,   /*根据设定的速度/位置启动步进(自定义NMT)*/
	SLAVE_PVT_START = 11,   /*启动PVT步进*/
	SLAVE_PVT_STOP = 12,   /*停止PVT步进*/
}SLAVE_MANAGEMENT;

/* 从站状态 */
typedef enum{
    SLAVESTATUS_INIT = 1, /* 从站正在初始化(也有可能处于掉线状态) */
    SLAVESTATUS_STOP = 4, /* 从站已停止 */
    SLAVESTATUS_WORK = 5, /* 从站正在工作 */
    SLAVESTATUS_PREWORK = 127, /* 从站处于预工作状态 */
    SLAVESTATUS_DISCONNECT = 15 /* 从站未连接 */
}SLAVE_STATUS;

/*数据类型*/
typedef enum{
	DT_BOOL = 0x01,
	DT_INT8 = 0x02,
	DT_INT16 = 0x03,
	DT_INT32 = 0x04,
	DT_UINT8 = 0x05,
	DT_UINT16 = 0x06,
	DT_UINT32 = 0x07,
	DT_VISIBLE_STRING = 0x09,
	DT_DOMAIN = 0x0F,
}DATA_TYPE;

/*PDO数据*/
typedef struct{
	DWORD dwNodeID;  //节点ID
	DWORD dwPDONum;  //PDO编号
	BYTE *pData;
	DWORD dwDataLen;
}PDO_DATA;

/*从站状态改变数据*/
typedef struct
{
	DWORD dwNodeID;  //从站节点ID
	SLAVE_STATUS status;  //从站状态
}STATUS_CHANGE;

/*SDO回调参数*/
typedef struct
{
	PUSIResult result;  //SDO访问结果
	DWORD dwNodeID;  //从站节点ID
	DWORD dwAbortCode;  //异常代码
	BYTE data[4]; //数据
	DWORD dwDataLen; //数据长度
}SDO_RESP;

/*事件回调参数类型*/
typedef enum{
	CBT_TRACE = 0, //TRACE
	CBT_SLAVE_STATUS_CHANGE = 1, //从机状态改变	
	CBT_PDO_DATA = 2, //收到PDO数据
	CBT_SDO_RESP = 3, //收到SDO响应
}CB_TYPE;


#ifdef __cplusplus
extern "C" {
#endif
	
/*事件回调函数:
CBT_TRACE:
	pData:char*类型,跟踪信息数据
CBT_SLAVE_STATUS_CHANGE:
	pData:STATUS_CHANGE*类型,状态改变信息
CBT_RPDO_MESSAGE
	pData:PDO_DATA*类型,PDO数据信息
*/
typedef PUSIResult (__stdcall * LPPUSICO_EVENTCB)(CB_TYPE callbackType,LPVOID pData);

/*
函数名称：PUSICO_SetDriver
函数功能：设置USB-CAN适配器驱动
输入参数：
	  dll_name:USB-CAN适配器驱动动态库
返回值：RET_SUCCESS,驱动加载成功
		RET_LOADDRIVER_FAIL,驱动加载失败
*/
PUSIResult __stdcall PUSICO_SetDriver(char* dll_name,HINSTANCE *hDll);
/*
函数名称：PUSICO_Open
函数功能：打开适配器
输入参数：
	  busname:用于底层驱动区分适配器通道等信息
	  baudrate:设置的波特率
返回值：RET_SUCCESS,驱动加载成功
		RET_LOADDRIVER_FAIL,驱动加载失败
*/
PUSIResult __stdcall PUSICO_Open(char* busname,char* baudrate,int nBufferTimer,int nBufferSize);

/* 调用此函数关闭设备 */
PUSIResult __stdcall PUSICO_Close(void);

/* 设置添加操作的从站节点*/
PUSIResult __stdcall PUSICO_AddNode(DWORD NodeID);

/* 移除操作的从站节点*/
PUSIResult __stdcall PUSICO_RemoveNode(DWORD NodeID);

/* 调用此函数读取从站SDO */
PUSIResult __stdcall PUSICO_ReadSDO(DWORD NodeID, DWORD Index, DWORD SubIndex,\
	BYTE *pRecData,DATA_TYPE DataType, DWORD *pRecLen, DWORD WaitTm);
/* 调用此函数读取从站SDO,通过事件回调函数返回写SDO结果*/
PUSIResult __stdcall PUSICO_ReadSDOCallBack(DWORD NodeID, DWORD Index, DWORD SubIndex,DATA_TYPE DataType);

/* 调用此函数写从站SDO */
PUSIResult __stdcall PUSICO_WriteSDO(DWORD NodeID, DWORD Index, DWORD SubIndex,\
	BYTE *pSendData,DATA_TYPE DataType, DWORD SendLen, DWORD WaitTm);
/* 调用此函数写从站SDO,通过事件回调函数返回写SDO结果*/
PUSIResult __stdcall PUSICO_WriteSDOCallBack(DWORD NodeID, DWORD Index, DWORD SubIndex,\
	BYTE *pSendData,DATA_TYPE DataType, DWORD SendLen);

/*写PDO*/
PUSIResult __stdcall PUSICO_WritePDO(DWORD NodeID,DWORD dwPDONum,BYTE* pSendData,DWORD dwLen);

/*读PDO*/
PUSIResult __stdcall PUSICO_ReadPDO(DWORD NodeID,DWORD dwPDONum,BYTE* pRecData,DWORD* pdwLen);

/* 调用此函数设置从站工作状态 */
PUSIResult __stdcall PUSICO_SetNodeState(DWORD NodeID, SLAVE_MANAGEMENT slaveManagement);

/* 调用此函数获取从站工作状态 */
PUSIResult __stdcall PUSICO_GetNodeStatus(DWORD NodeID,SLAVE_STATUS *pSlaveStatus);

/* 设置事件回调函数 */
PUSIResult __stdcall PUSICO_SetEventCallback(LPPUSICO_EVENTCB callback);


#ifdef __cplusplus
}
#endif

#endif // _PUSICO_H

