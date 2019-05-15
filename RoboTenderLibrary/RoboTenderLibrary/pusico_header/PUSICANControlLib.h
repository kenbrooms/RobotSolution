#ifndef _PUSICAN_CONTROL_LIB_H
#define _PUSICAN_CONTROL_LIB_H

#include <windows.h>
/**************************************�궨��**************************************/
/*���ٵȼ�*/
#define TRACE_LEVEL0				0
#define TRACE_LEVEL1				1
/*���״̬��־����*/
#define ES_UVLO						0   //Ƿѹ
#define ES_BERR					    1   //B�����
#define ES_AERR					    2   //A�����
#define ES_BOC					    3   //B�����
#define ES_AOC					    4   //A�����
#define ES_OTS					    5   //���ȱ���
/*������״̬��־����*/
#define CS_EXT1						0	//�ⲿֹͣ1
#define CS_EXT2						1	//�ⲿֹͣ2
#define CS_STALL					2	//��ת��־
#define CS_BUSY						3	//æ��־
#define CS_EXT3						4	//�ⲿֹͣ3
#define CS_PVT3_FIFO_EMPTY			5	//PVTģʽ3��FIFOΪ��
#define CS_PVT3_LOW_THRESHOLD		6	//PVTģʽ3��FIFO��ȵ�������
#define CS_PVT3_HIGH_THRESHOLD		7	//PVTģʽ3��FIFO��ȸ�������

/*ϸ�ֶ���*/
#define MS_0						0	//0ϸ��
#define MS_2						2	//2ϸ��
#define MS_4						4	//4ϸ��
#define MS_8						8	//8ϸ��
#define MS_16						16	//16ϸ��
#define MS_32						32	//32ϸ��
#define MS_64						64	//64ϸ��
#define MS_128						128	//128ϸ��
#define MS_256						256	//256ϸ��
/*����ģʽ����*/
#define WM_POS						0	//λ��ģʽ
#define WM_VELOCITY					1	//�ٶ�ģʽ
#define WM_PVT						2	//PVTģʽ
#define WM_ENC_FOLLOW				3	//����������ģʽ
/*ת��������*/
#define MOTOR_FORWARD				1	//����ת��
#define MOTOR_REVERSE				0	//����ת��
/*�ⲿֹͣ����*/
#define	EXT_STOP1					0	//�ⲿֹͣ1
#define	EXT_STOP2					1	//�ⲿֹͣ2
#define	EXT_STOP3					4	//�ⲿֹͣ3
/*�ⲿֹͣ�������Ͷ���*/
#define	EXT_TRIG_FALLING			0	//�½��ش���
#define	EXT_TRIG_RISING				1	//�����ش���

/*PVTģʽ����*/
#define	PVT_MODE1					0	//PVTģʽ1,����ģʽ
#define	PVT_MODE2					1	//PVTģʽ2,ѭ��ģʽ
#define	PVT_MODE3					2	//PVTģʽ3,����FIFOģʽ

/*GPIO����*/
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
/*GPIO����*/
#define GPIO_DIR_IN					0
#define GPIO_DIR_OUT				1
/*GPIO����˿�����*/
#define GPIO_IN_FLOATING			0
#define GPIO_IN_IPU					1
#define GPIO_IN_IPD					2
#define GPIO_IN_AIN					3
/*GPIO����˿�����*/
#define GPIO_OUT_OD					0
#define GPIO_OUT_PP					1

/*��ɫ����*/
#ifndef RGB
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

/*RPDOͨ������*/
#define RPDO_CH1					0 //����PDOͨ��1
#define RPDO_CH2					1 //����PDOͨ��2
#define RPDO_CH3					2 //����PDOͨ��3
#define RPDO_CH4					3 //����PDOͨ��4

/*TPDOͨ������*/
#define TPDO_CH1					0 //����PDOͨ��1
#define TPDO_CH2					1 //����PDOͨ��2
#define TPDO_CH3					2 //����PDOͨ��3
#define TPDO_CH4					3 //����PDOͨ��4

/**************************************���Ͷ���**************************************/
/*�������ͺ�*/
typedef enum{
	LANMA_A1PLUS = 0,//�������A1+
	LEDIA = 1,//�ֵ�USB-CAN
	YL9100 = 2,//YL9100
	IXXAT = 3,//IXXAT
	GC_USBCAN_I = 4,//���USBCAN-I
	ZLG_USBCAN_I = 5,//������USBCAN-I
	ZLG_USBCAN_E_U = 6,//������USBCAN-E-U
	ZLG_CANET_TCPC = 7,//������CANET-TCP�ͻ���
	CX_CANALYST_II	= 8,//��оCANalyst-II
	ZLG_CANCOM_100IE = 9,//������CANCOM-100IE
}ADAPT_TYPE_T;

/*PUSI CAN�豸�ͺ�*/
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
	PCAN_SUCCESS = 0, /*�����ɹ�*/
	PCAN_GENERNAL_ERR = 1, /*ͨ�ô���*/
	PCAN_LOADDRIVER_FAIL = 2, /* װ������ʧ�� */
	PCAN_OPEN_FAIL = 3,  /*��������ʧ��*/
	PCAN_READSDO_FAIL = 4, /*��SDOʧ��*/
	PCAN_READSDO_TIMEOUT = 5, /*��SDO��ʱ*/
	PCAN_WRITESDO_FAIL = 6, /*дSDOʧ��*/
	PCAN_WRITESDO_TIMEOUT = 7, /*дSDO��ʱ*/	
	PCAN_NOIDLE_SDO_CLIENT = 8,/*SDO�ͻ���û�п��õ�ͨ��*/
	PCAN_WRITEPDO_FAIL = 9,/*дPDOʧ��*/
	PCAN_NO_SUPPORT_TCP_CONNECT = 10,/*��֧��TCP����*/
	PCAN_NO_SUPPORT_SP_CONNECT = 11,/*��֧�ִ�������*/
}PCANResult;

/**************************************������������**************************************/
#ifdef __cplusplus
extern "C" {
#endif

typedef PCANResult (__stdcall * LPPCAN_SLAVECHANGECB)(DWORD dwNodeID,BOOL bOnline);
typedef PCANResult (__stdcall * LPPCAN_TRACECB)(char* szTrace);
typedef PCANResult (__stdcall * LPPCAN_TPDOCB)(DWORD dwNodeID,DWORD dwTPDOChannel,BYTE* pTPDOData,DWORD dwLen);

/*********************ͨ�ÿ��ƺ���*********************/
/*���ûص�����*/
PCANResult __stdcall PCAN_SetEventCallback(LPPCAN_SLAVECHANGECB funcSlaveChange,\
	LPPCAN_TRACECB funcTraceCallback,LPPCAN_TPDOCB funcTPDOCallback);
/*��ʼ��*/
PCANResult __stdcall PCAN_Init(ADAPT_TYPE_T adaptType,PCAN_TYPE_T devType,DWORD dwTraceLevel);
/*����TCPͨ�Ų���*/
PCANResult __stdcall PCAN_SetTCPClient(char *szIPAddr,DWORD dwPort);
/*���ô��ڲ���*/
PCANResult __stdcall PCAN_SetSerialPort(DWORD dwPort,DWORD dwBaud);
/*�򿪶˿�*/
PCANResult __stdcall PCAN_OpenPort(BAUDRATE_T baudrate);
/* ���ô˺����ر��豸 */
PCANResult __stdcall PCAN_ClosePort(void);

/*********************NMT�ڵ����*********************/
/*�ڵ�����״̬*/
PCANResult __stdcall PCAN_IsSlaveOnline(DWORD dwNodeID,BOOL *pOnline);
/*�����ڵ�*/
PCANResult __stdcall PCAN_StartNode(DWORD dwNodeID);
/*ֹͣ�ڵ�*/
PCANResult __stdcall PCAN_StopNode(DWORD dwNodeID);
/*��λ�ڵ�*/
PCANResult __stdcall PCAN_ResetNode(DWORD dwNodeID);
/*��λͨ��*/
PCANResult __stdcall PCAN_ResetCommunication(DWORD dwNodeID);
/*����Ԥ����״̬*/
PCANResult __stdcall PCAN_EnterPreoperational(DWORD dwNodeID);

/*********************ϵͳ����*********************/
/*��������ֵ����*/
PCANResult __stdcall PCAN_SaveObjectDict(DWORD dwNodeID);

/*********************��������˶�����*********************/
/*��ȡ���״̬*/
PCANResult __stdcall PCAN_GetMotorStatus(DWORD dwNodeID,DWORD*	pMotorStatus);
/*��ȡ����״̬*/
PCANResult __stdcall PCAN_GetControlStatus(DWORD dwNodeID,DWORD* pControlStatus);

/*��ȡ���ʹ��*/
PCANResult __stdcall PCAN_GetMotorEnable(DWORD dwNodeID,BOOL *pMotorEnable);
/*���õ��ʹ��*/
PCANResult __stdcall PCAN_SetMotorEnable(DWORD dwNodeID,BOOL bMotorEnable);

/*��ȡ��ֵ����*/
PCANResult __stdcall PCAN_GetPeakCurrent(DWORD dwNodeID,DWORD *pPeakCurrent);
/*���÷�ֵ����*/
PCANResult __stdcall PCAN_SetPeakCurrent(DWORD dwNodeID,DWORD dwPeakCurrent);
/*��ȡ����˥��*/
PCANResult __stdcall PCAN_GetCurrentDecay(DWORD dwNodeID,DWORD *pCurrentDecay);
/*���õ���˥��*/
PCANResult __stdcall PCAN_SetCurrentDecay(DWORD dwNodeID,DWORD dwCurrentDecay);

/*��ȡϸ����*/
PCANResult __stdcall PCAN_GetMicroStep(DWORD dwNodeID,DWORD *pMicroStep);
/*����ϸ����*/
PCANResult __stdcall PCAN_SetMicroStep(DWORD dwNodeID,DWORD dwMicroStep);

/*��ȡ����ģʽ*/
PCANResult __stdcall PCAN_GetWorkMode(DWORD dwNodeID,DWORD *pWorkMode);
/*���ù���ģʽ*/
PCANResult __stdcall PCAN_SetWorkMode(DWORD dwNodeID,DWORD dwWorkMode);

/*��ȡת������*/
PCANResult __stdcall PCAN_GetDir(DWORD dwNodeID,DWORD *pDir);
/*����ת������*/
PCANResult __stdcall PCAN_SetDir(DWORD dwNodeID,DWORD dir);

/*��ȡ�����ٶ�*/
PCANResult __stdcall PCAN_GetStartSpeed(DWORD dwNodeID,DWORD *pStartSpeed);
/*���������ٶ�*/
PCANResult __stdcall PCAN_SetStartSpeed(DWORD dwNodeID,DWORD dwStartSpeed);

/*��ȡֹͣ�ٶ�*/
PCANResult __stdcall PCAN_GetStopSpeed(DWORD dwNodeID,DWORD *pStopSpeed);
/*����ֹͣ�ٶ�*/
PCANResult __stdcall PCAN_SetStopSpeed(DWORD dwNodeID,DWORD dwStopSpeed);

/*��ȡ���ٶ�ϵ��*/
PCANResult __stdcall PCAN_GetAccel(DWORD dwNodeID,DWORD *pAccel);
/*���ü��ٶ�ϵ��*/
PCANResult __stdcall PCAN_SetAccel(DWORD dwNodeID,DWORD dwAccel);

/*��ȡ���ٶ�ϵ��*/
PCANResult __stdcall PCAN_GetDecel(DWORD dwNodeID,DWORD *pDecel);
/*���ü��ٶ�ϵ��*/
PCANResult __stdcall PCAN_SetDecel(DWORD dwNodeID,DWORD dwDecel);

/*��ȡ����ٶ�*/
PCANResult __stdcall PCAN_GetMaxSpeed(DWORD dwNodeID,int *pMaxSpeed);
/*��������ٶ�*/
PCANResult __stdcall PCAN_SetMaxSpeed(DWORD dwNodeID,int nMaxSpeed);

/*��ȡ���λ��*/
PCANResult __stdcall PCAN_GetMotorPos(DWORD dwNodeID,int *pMotorPos);
/*�������λ��*/
PCANResult __stdcall PCAN_SetMotorPos(DWORD dwNodeID,int nMotorPos);

/*���λ�ò���*/
PCANResult __stdcall PCAN_StartRelStep(DWORD dwNodeID,DWORD dwStepNum);
/*����λ�ò���*/
PCANResult __stdcall PCAN_StartAbsStep(DWORD dwNodeID,int nAbsPos);
/*��ֹ����*/
PCANResult __stdcall PCAN_AbortStep(DWORD dwNodeID);

/*********************����������*********************/
/*��ȡ�ⲿ����ֹͣʹ��*/
PCANResult __stdcall PCAN_GetExtStopEnable(DWORD dwNodeID,DWORD *pExtStopEnable);
/*�����ⲿ����ֹͣʹ��*/
PCANResult __stdcall PCAN_SetExtStopEnable(DWORD dwNodeID,DWORD dwExtStopEnable);
/*��ȡ�ⲿ����ֹͣ������ʽ*/
PCANResult __stdcall PCAN_GetExtStopTrigger(DWORD dwNodeID,DWORD *pExtStopTrigger);
/*�����ⲿ����ֹͣ������ʽ*/
PCANResult __stdcall PCAN_SetExtStopTrigger(DWORD dwNodeID,DWORD dwExtStopTrigger);
/*��ȡ�ⲿ����ֹͣȥ����ʱ*/
PCANResult __stdcall PCAN_GetDebounceDelay(DWORD dwNodeID,DWORD *pDebounceDelay);
/*�����ⲿ����ֹͣȥ����ʱ*/
PCANResult __stdcall PCAN_SetDebounceDelay(DWORD dwNodeID,DWORD dwDebounceDelay);
/*����ⲿ����ֹͣ��־*/
PCANResult __stdcall PCAN_ClearExtStopFlag(DWORD dwNodeID,DWORD dwExtStopFlag);


/*********************PVT�˶�����*********************/
/*������ID*/
PCANResult __stdcall PCAN_SetGroupID(DWORD dwNodeID,DWORD dwGroupID);
/*����PVTģʽ*/
PCANResult __stdcall PCAN_SetPVTMode(DWORD dwNodeID,DWORD dwPVTMode);
/*�������PVT���ݸ���*/
PCANResult __stdcall PCAN_SetMaxPVTNum(DWORD dwNodeID,DWORD dwMaxPVTNum);
/*����PVT1����*/
PCANResult __stdcall PCAN_SetPVT1Para(DWORD dwNodeID,DWORD dwStartIndex,DWORD dwEndIndex);
/*����PVT2����*/
PCANResult __stdcall PCAN_SetPVT2Para(DWORD dwNodeID,DWORD dwAccStartIndex,DWORD dwAccEndIndex,\
	DWORD dwLoopStartIndex,DWORD dwLoopEndIndex,DWORD dwLoopCount,DWORD dwDecStartIndex,DWORD dwDecEndIndex);
/*����PVT3����*/
PCANResult __stdcall PCAN_SetPVT3Para(DWORD dwNodeID,DWORD dwLowThreshold,DWORD dwHighThreshold);
/*дPVT����*/
PCANResult __stdcall PCAN_WritePVT(DWORD dwNodeID,int nPosition,int nVelocity,DWORD dwTime);

/*����PVT����*/
PCANResult __stdcall PCAN_StartPVTStep(DWORD dwGoupID);
/*ֹͣPVT����*/
PCANResult __stdcall PCAN_StopPVTStep(DWORD dwGoupID);

/*********************PV�˶�����*********************/
/*дPV����*/
PCANResult __stdcall PCAN_WritePV(DWORD dwNodeID,int nPosition,int nVelocity);
/*����PV����*/
PCANResult __stdcall PCAN_StartPVStep(DWORD dwGoupID);
/*********************�˿ڿ���*********************/
/*��ȡGPIO����*/
PCANResult __stdcall PCAN_GetGPIODir(DWORD dwNodeID,DWORD *pGPIODir);
/*����GPIO����*/
PCANResult __stdcall PCAN_SetGPIODir(DWORD dwNodeID,DWORD dwGPIODir);
/*��ȡGPIO����*/
PCANResult __stdcall PCAN_GetGPIOConfig(DWORD dwNodeID,DWORD *pGPIOConfig);
/*����GPIO����*/
PCANResult __stdcall PCAN_SetGPIOConfig(DWORD dwNodeID,DWORD dwGPIOConfig);
/*��ȡGPIOֵ*/
PCANResult __stdcall PCAN_GetGPIOValue(DWORD dwNodeID,DWORD *pGPIOValue);
/*����GPIOֵ*/
PCANResult __stdcall PCAN_SetGPIOValue(DWORD dwNodeID,DWORD dwGPIOValue);


/*********************�òʵƿ���*********************/
/*�òʵƲ���*/
PCANResult __stdcall PCAN_SetColorLedPara(DWORD dwNodeID,DWORD dwFreq,DWORD dwDutyCycle0,DWORD dwDutyCycle1);
/*�òʵ�ʹ��*/
PCANResult __stdcall PCAN_SetColorLedEnable(DWORD dwNodeID,BOOL enable);
/*�òʵ���ɫ����*/
PCANResult __stdcall PCAN_SetColorLed(DWORD dwNodeID,DWORD dwColor);

/*********************PDO���ƽӿ�*********************/
PCANResult __stdcall PCAN_WritePDO(DWORD dwNodeID,DWORD dwRPDOChannel,BYTE *data,DWORD dwLen);
PCANResult __stdcall PCAN_ReadPDO(DWORD dwNodeID,DWORD dwTPDOChannel,BYTE *data,DWORD *pLen);

#ifdef __cplusplus
}
#endif

#endif // _PUSICAN_CONTROL_LIB_H

