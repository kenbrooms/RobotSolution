#ifndef _PUSICAN_CONTROL_LIB_H
#define _PUSICAN_CONTROL_LIB_H

#include <windows.h>
/**************************************宏定义**************************************/
/*跟踪等级*/
#define TRACE_LEVEL0				0
#define TRACE_LEVEL1				1
/*马达状态标志定义*/
#define ES_UVLO						0   //欠压
#define ES_BERR					    1   //B相错误
#define ES_AERR					    2   //A相错误
#define ES_BOC					    3   //B相过流
#define ES_AOC					    4   //A相过流
#define ES_OTS					    5   //过热保护
/*控制器状态标志定义*/
#define CS_EXT1						0	//外部停止1
#define CS_EXT2						1	//外部停止2
#define CS_STALL					2	//堵转标志
#define CS_BUSY						3	//忙标志
#define CS_EXT3						4	//外部停止3
#define CS_PVT3_FIFO_EMPTY			5	//PVT模式3下FIFO为空
#define CS_PVT3_LOW_THRESHOLD		6	//PVT模式3下FIFO深度低于下限
#define CS_PVT3_HIGH_THRESHOLD		7	//PVT模式3下FIFO深度高于上限

/*细分定义*/
#define MS_0						0	//0细分
#define MS_2						2	//2细分
#define MS_4						4	//4细分
#define MS_8						8	//8细分
#define MS_16						16	//16细分
#define MS_32						32	//32细分
#define MS_64						64	//64细分
#define MS_128						128	//128细分
#define MS_256						256	//256细分
/*工作模式定义*/
#define WM_POS						0	//位置模式
#define WM_VELOCITY					1	//速度模式
#define WM_PVT						2	//PVT模式
#define WM_ENC_FOLLOW				3	//编码器跟随模式
/*转动方向定义*/
#define MOTOR_FORWARD				1	//正向转动
#define MOTOR_REVERSE				0	//反向转动
/*外部停止定义*/
#define	EXT_STOP1					0	//外部停止1
#define	EXT_STOP2					1	//外部停止2
#define	EXT_STOP3					4	//外部停止3
/*外部停止触发类型定义*/
#define	EXT_TRIG_FALLING			0	//下降沿触发
#define	EXT_TRIG_RISING				1	//上升沿触发

/*PVT模式定义*/
#define	PVT_MODE1					0	//PVT模式1,单次模式
#define	PVT_MODE2					1	//PVT模式2,循环模式
#define	PVT_MODE3					2	//PVT模式3,无限FIFO模式

/*GPIO定义*/
#define GPIO1						0
#define GPIO2						1
#define GPIO3						2
#define GPIO4						3
#define GPIO5						4
#define GPIO6						5
#define GPIO7						6
#define GPIO_EXT1					7
#define GPIO_EXT2					8
#define GPIO_EXT3					9
#define GPIO_ENC1					9
#define GPIO_ENC2					10
#define GPIO8						11
/*GPIO方向*/
#define GPIO_DIR_IN					0
#define GPIO_DIR_OUT				1
/*GPIO输入端口配置*/
#define GPIO_IN_FLOATING			0
#define GPIO_IN_IPU					1
#define GPIO_IN_IPD					2
#define GPIO_IN_AIN					3
/*GPIO输出端口配置*/
#define GPIO_OUT_OD					0
#define GPIO_OUT_PP					1

/*颜色配置*/
#ifndef RGB
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

/*RPDO通道配置*/
#define RPDO_CH1					0 //接收PDO通道1
#define RPDO_CH2					1 //接收PDO通道2
#define RPDO_CH3					2 //接收PDO通道3
#define RPDO_CH4					3 //接收PDO通道4

/*TPDO通道配置*/
#define TPDO_CH1					0 //发送PDO通道1
#define TPDO_CH2					1 //发送PDO通道2
#define TPDO_CH3					2 //发送PDO通道3
#define TPDO_CH4					3 //发送PDO通道4

/**************************************类型定义**************************************/
/*适配器型号*/
typedef enum{
	LANMA_A1PLUS = 0,//蓝马电子A1+
	LEDIA = 1,//乐的USB-CAN
	YL9100 = 2,//YL9100
	IXXAT = 3,//IXXAT
	GC_USBCAN_I = 4,//广成USBCAN-I
	ZLG_USBCAN_I = 5,//周立功USBCAN-I
	ZLG_USBCAN_E_U = 6,//周立功USBCAN-E-U
	ZLG_CANET_TCPC = 7,//周立功CANET-TCP客户端
	CX_CANALYST_II	= 8,//创芯CANalyst-II
	ZLG_CANCOM_100IE = 9,//周立功CANCOM-100IE
}ADAPT_TYPE_T;

/*PUSI CAN设备型号*/
typedef enum{
	PMC007C3S = 0,
	PMC007C6S = 1,
	PMC007C3SE = 2,
	PMC007C6SE = 3,
}PCAN_TYPE_T;

typedef enum{
	BR_10KBPS = 0,
	BR_20KBPS = 1,
	BR_50KBPS = 2,
	BR_100KBPS = 3,
	BR_125KBPS = 4,
	BR_250KBPS = 5,
	BR_500KBPS = 6,
	BR_800KBPS = 7,
	BR_1000KBPS = 8,
}BAUDRATE_T;

typedef enum
{
	PCAN_SUCCESS = 0, /*操作成功*/
	PCAN_GENERNAL_ERR = 1, /*通用错误*/
	PCAN_LOADDRIVER_FAIL = 2, /* 装载驱动失败 */
	PCAN_OPEN_FAIL = 3,  /*打开适配器失败*/
	PCAN_READSDO_FAIL = 4, /*读SDO失败*/
	PCAN_READSDO_TIMEOUT = 5, /*读SDO超时*/
	PCAN_WRITESDO_FAIL = 6, /*写SDO失败*/
	PCAN_WRITESDO_TIMEOUT = 7, /*写SDO超时*/	
	PCAN_NOIDLE_SDO_CLIENT = 8,/*SDO客户端没有可用的通道*/
	PCAN_WRITEPDO_FAIL = 9,/*写PDO失败*/
	PCAN_NO_SUPPORT_TCP_CONNECT = 10,/*不支持TCP连接*/
	PCAN_NO_SUPPORT_SP_CONNECT = 11,/*不支持串口连接*/
}PCANResult;

/**************************************导出函数定义**************************************/
#ifdef __cplusplus
extern "C" {
#endif

typedef PCANResult (__stdcall * LPPCAN_SLAVECHANGECB)(DWORD dwNodeID,BOOL bOnline);
typedef PCANResult (__stdcall * LPPCAN_TRACECB)(char* szTrace);
typedef PCANResult (__stdcall * LPPCAN_TPDOCB)(DWORD dwNodeID,DWORD dwTPDOChannel,BYTE* pTPDOData,DWORD dwLen);

/*********************通用控制函数*********************/
/*设置回调函数*/
PCANResult __stdcall PCAN_SetEventCallback(LPPCAN_SLAVECHANGECB funcSlaveChange,\
	LPPCAN_TRACECB funcTraceCallback,LPPCAN_TPDOCB funcTPDOCallback);
/*初始化*/
PCANResult __stdcall PCAN_Init(ADAPT_TYPE_T adaptType,PCAN_TYPE_T devType,DWORD dwTraceLevel);
/*设置TCP通信参数*/
PCANResult __stdcall PCAN_SetTCPClient(char *szIPAddr,DWORD dwPort);
/*设置串口参数*/
PCANResult __stdcall PCAN_SetSerialPort(DWORD dwPort,DWORD dwBaud);
/*打开端口*/
PCANResult __stdcall PCAN_OpenPort(BAUDRATE_T baudrate);
/* 调用此函数关闭设备 */
PCANResult __stdcall PCAN_ClosePort(void);

/*********************NMT节点管理*********************/
/*节点上线状态*/
PCANResult __stdcall PCAN_IsSlaveOnline(DWORD dwNodeID,BOOL *pOnline);
/*启动节点*/
PCANResult __stdcall PCAN_StartNode(DWORD dwNodeID);
/*停止节点*/
PCANResult __stdcall PCAN_StopNode(DWORD dwNodeID);
/*复位节点*/
PCANResult __stdcall PCAN_ResetNode(DWORD dwNodeID);
/*复位通信*/
PCANResult __stdcall PCAN_ResetCommunication(DWORD dwNodeID);
/*进入预操作状态*/
PCANResult __stdcall PCAN_EnterPreoperational(DWORD dwNodeID);

/*********************系统控制*********************/
/*保存对象字典参数*/
PCANResult __stdcall PCAN_SaveObjectDict(DWORD dwNodeID);

/*********************基本马达运动控制*********************/
/*获取马达状态*/
PCANResult __stdcall PCAN_GetMotorStatus(DWORD dwNodeID,DWORD*	pMotorStatus);
/*获取控制状态*/
PCANResult __stdcall PCAN_GetControlStatus(DWORD dwNodeID,DWORD* pControlStatus);

/*获取电机使能*/
PCANResult __stdcall PCAN_GetMotorEnable(DWORD dwNodeID,BOOL *pMotorEnable);
/*设置电机使能*/
PCANResult __stdcall PCAN_SetMotorEnable(DWORD dwNodeID,BOOL bMotorEnable);

/*获取峰值电流*/
PCANResult __stdcall PCAN_GetPeakCurrent(DWORD dwNodeID,DWORD *pPeakCurrent);
/*设置峰值电流*/
PCANResult __stdcall PCAN_SetPeakCurrent(DWORD dwNodeID,DWORD dwPeakCurrent);
/*获取电流衰减*/
PCANResult __stdcall PCAN_GetCurrentDecay(DWORD dwNodeID,DWORD *pCurrentDecay);
/*设置电流衰减*/
PCANResult __stdcall PCAN_SetCurrentDecay(DWORD dwNodeID,DWORD dwCurrentDecay);

/*获取细分数*/
PCANResult __stdcall PCAN_GetMicroStep(DWORD dwNodeID,DWORD *pMicroStep);
/*设置细分数*/
PCANResult __stdcall PCAN_SetMicroStep(DWORD dwNodeID,DWORD dwMicroStep);

/*获取工作模式*/
PCANResult __stdcall PCAN_GetWorkMode(DWORD dwNodeID,DWORD *pWorkMode);
/*设置工作模式*/
PCANResult __stdcall PCAN_SetWorkMode(DWORD dwNodeID,DWORD dwWorkMode);

/*获取转动方向*/
PCANResult __stdcall PCAN_GetDir(DWORD dwNodeID,DWORD *pDir);
/*设置转动方向*/
PCANResult __stdcall PCAN_SetDir(DWORD dwNodeID,DWORD dir);

/*获取启动速度*/
PCANResult __stdcall PCAN_GetStartSpeed(DWORD dwNodeID,DWORD *pStartSpeed);
/*设置启动速度*/
PCANResult __stdcall PCAN_SetStartSpeed(DWORD dwNodeID,DWORD dwStartSpeed);

/*获取停止速度*/
PCANResult __stdcall PCAN_GetStopSpeed(DWORD dwNodeID,DWORD *pStopSpeed);
/*设置停止速度*/
PCANResult __stdcall PCAN_SetStopSpeed(DWORD dwNodeID,DWORD dwStopSpeed);

/*获取加速度系数*/
PCANResult __stdcall PCAN_GetAccel(DWORD dwNodeID,DWORD *pAccel);
/*设置加速度系数*/
PCANResult __stdcall PCAN_SetAccel(DWORD dwNodeID,DWORD dwAccel);

/*获取减速度系数*/
PCANResult __stdcall PCAN_GetDecel(DWORD dwNodeID,DWORD *pDecel);
/*设置减速度系数*/
PCANResult __stdcall PCAN_SetDecel(DWORD dwNodeID,DWORD dwDecel);

/*获取最大速度*/
PCANResult __stdcall PCAN_GetMaxSpeed(DWORD dwNodeID,int *pMaxSpeed);
/*设置最大速度*/
PCANResult __stdcall PCAN_SetMaxSpeed(DWORD dwNodeID,int nMaxSpeed);

/*获取马达位置*/
PCANResult __stdcall PCAN_GetMotorPos(DWORD dwNodeID,int *pMotorPos);
/*设置马达位置*/
PCANResult __stdcall PCAN_SetMotorPos(DWORD dwNodeID,int nMotorPos);

/*相对位置步进*/
PCANResult __stdcall PCAN_StartRelStep(DWORD dwNodeID,DWORD dwStepNum);
/*绝对位置步进*/
PCANResult __stdcall PCAN_StartAbsStep(DWORD dwNodeID,int nAbsPos);
/*终止步进*/
PCANResult __stdcall PCAN_AbortStep(DWORD dwNodeID);

/*********************传感器输入*********************/
/*获取外部紧急停止使能*/
PCANResult __stdcall PCAN_GetExtStopEnable(DWORD dwNodeID,DWORD *pExtStopEnable);
/*设置外部紧急停止使能*/
PCANResult __stdcall PCAN_SetExtStopEnable(DWORD dwNodeID,DWORD dwExtStopEnable);
/*获取外部紧急停止触发方式*/
PCANResult __stdcall PCAN_GetExtStopTrigger(DWORD dwNodeID,DWORD *pExtStopTrigger);
/*设置外部紧急停止触发方式*/
PCANResult __stdcall PCAN_SetExtStopTrigger(DWORD dwNodeID,DWORD dwExtStopTrigger);
/*获取外部紧急停止去抖延时*/
PCANResult __stdcall PCAN_GetDebounceDelay(DWORD dwNodeID,DWORD *pDebounceDelay);
/*设置外部紧急停止去抖延时*/
PCANResult __stdcall PCAN_SetDebounceDelay(DWORD dwNodeID,DWORD dwDebounceDelay);
/*清除外部紧急停止标志*/
PCANResult __stdcall PCAN_ClearExtStopFlag(DWORD dwNodeID,DWORD dwExtStopFlag);


/*********************PVT运动控制*********************/
/*设置组ID*/
PCANResult __stdcall PCAN_SetGroupID(DWORD dwNodeID,DWORD dwGroupID);
/*设置PVT模式*/
PCANResult __stdcall PCAN_SetPVTMode(DWORD dwNodeID,DWORD dwPVTMode);
/*设置最大PVT数据个数*/
PCANResult __stdcall PCAN_SetMaxPVTNum(DWORD dwNodeID,DWORD dwMaxPVTNum);
/*设置PVT1参数*/
PCANResult __stdcall PCAN_SetPVT1Para(DWORD dwNodeID,DWORD dwStartIndex,DWORD dwEndIndex);
/*设置PVT2参数*/
PCANResult __stdcall PCAN_SetPVT2Para(DWORD dwNodeID,DWORD dwAccStartIndex,DWORD dwAccEndIndex,\
	DWORD dwLoopStartIndex,DWORD dwLoopEndIndex,DWORD dwLoopCount,DWORD dwDecStartIndex,DWORD dwDecEndIndex);
/*设置PVT3参数*/
PCANResult __stdcall PCAN_SetPVT3Para(DWORD dwNodeID,DWORD dwLowThreshold,DWORD dwHighThreshold);
/*写PVT参数*/
PCANResult __stdcall PCAN_WritePVT(DWORD dwNodeID,int nPosition,int nVelocity,DWORD dwTime);

/*启动PVT步进*/
PCANResult __stdcall PCAN_StartPVTStep(DWORD dwGoupID);
/*停止PVT步进*/
PCANResult __stdcall PCAN_StopPVTStep(DWORD dwGoupID);

/*********************PV运动控制*********************/
/*写PV参数*/
PCANResult __stdcall PCAN_WritePV(DWORD dwNodeID,int nPosition,int nVelocity);
/*启动PV步进*/
PCANResult __stdcall PCAN_StartPVStep(DWORD dwGoupID);
/*********************端口控制*********************/
/*获取GPIO方向*/
PCANResult __stdcall PCAN_GetGPIODir(DWORD dwNodeID,DWORD *pGPIODir);
/*设置GPIO方向*/
PCANResult __stdcall PCAN_SetGPIODir(DWORD dwNodeID,DWORD dwGPIODir);
/*获取GPIO配置*/
PCANResult __stdcall PCAN_GetGPIOConfig(DWORD dwNodeID,DWORD *pGPIOConfig);
/*设置GPIO配置*/
PCANResult __stdcall PCAN_SetGPIOConfig(DWORD dwNodeID,DWORD dwGPIOConfig);
/*获取GPIO值*/
PCANResult __stdcall PCAN_GetGPIOValue(DWORD dwNodeID,DWORD *pGPIOValue);
/*设置GPIO值*/
PCANResult __stdcall PCAN_SetGPIOValue(DWORD dwNodeID,DWORD dwGPIOValue);


/*********************幻彩灯控制*********************/
/*幻彩灯参数*/
PCANResult __stdcall PCAN_SetColorLedPara(DWORD dwNodeID,DWORD dwFreq,DWORD dwDutyCycle0,DWORD dwDutyCycle1);
/*幻彩灯使能*/
PCANResult __stdcall PCAN_SetColorLedEnable(DWORD dwNodeID,BOOL enable);
/*幻彩灯颜色设置*/
PCANResult __stdcall PCAN_SetColorLed(DWORD dwNodeID,DWORD dwColor);

/*********************PDO控制接口*********************/
PCANResult __stdcall PCAN_WritePDO(DWORD dwNodeID,DWORD dwRPDOChannel,BYTE *data,DWORD dwLen);
PCANResult __stdcall PCAN_ReadPDO(DWORD dwNodeID,DWORD dwTPDOChannel,BYTE *data,DWORD *pLen);

#ifdef __cplusplus
}
#endif

#endif // _PUSICAN_CONTROL_LIB_H

