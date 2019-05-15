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

/* �豸������� */
typedef enum {
	RET_SUCCESS = 0, /*�����ɹ�*/
	RET_GENERNAL_ERR = 1, /*ͨ�ô���*/
	RET_LOADDRIVER_FAIL = 2, /* װ������ʧ�� */
	RET_OPEN_FAIL = 3,  /*��������ʧ��*/
	RET_READSDO_FAIL = 4, /*��SDOʧ��*/
	RET_READSDO_TIMEOUT = 5, /*��SDO��ʱ*/
	RET_WRITESDO_FAIL = 6, /*дSDOʧ��*/
	RET_WRITESDO_TIMEOUT = 7, /*дSDO��ʱ*/	
	RET_NOIDLE_SDO_CLIENT = 8,/*SDO�ͻ���û�п��õ�ͨ��*/
	RET_WRITEPDO_FAIL = 9,/*дPDOʧ��*/
}PUSIResult;

/* ��վ���� */
typedef enum{
    SLAVE_START = 1, /* ������վ */
    SLAVE_STOP = 2, /* ֹͣ��վ */
    SLAVE_PRE_OPERATIONAL = 128, /* ʹ��վ����Ԥ����״̬ */
    SLAVE_RESET = 129, /* ��λ��վ */
    SLAVE_RESET_CONNECTION = 130, /* ��λ��վ���� */
	SLAVE_PV_STEP = 10,   /*�����趨���ٶ�/λ����������(�Զ���NMT)*/
	SLAVE_PVT_START = 11,   /*����PVT����*/
	SLAVE_PVT_STOP = 12,   /*ֹͣPVT����*/
}SLAVE_MANAGEMENT;

/* ��վ״̬ */
typedef enum{
    SLAVESTATUS_INIT = 1, /* ��վ���ڳ�ʼ��(Ҳ�п��ܴ��ڵ���״̬) */
    SLAVESTATUS_STOP = 4, /* ��վ��ֹͣ */
    SLAVESTATUS_WORK = 5, /* ��վ���ڹ��� */
    SLAVESTATUS_PREWORK = 127, /* ��վ����Ԥ����״̬ */
    SLAVESTATUS_DISCONNECT = 15 /* ��վδ���� */
}SLAVE_STATUS;

/*��������*/
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

/*PDO����*/
typedef struct{
	DWORD dwNodeID;  //�ڵ�ID
	DWORD dwPDONum;  //PDO���
	BYTE *pData;
	DWORD dwDataLen;
}PDO_DATA;

/*��վ״̬�ı�����*/
typedef struct
{
	DWORD dwNodeID;  //��վ�ڵ�ID
	SLAVE_STATUS status;  //��վ״̬
}STATUS_CHANGE;

/*SDO�ص�����*/
typedef struct
{
	PUSIResult result;  //SDO���ʽ��
	DWORD dwNodeID;  //��վ�ڵ�ID
	DWORD dwAbortCode;  //�쳣����
	BYTE data[4]; //����
	DWORD dwDataLen; //���ݳ���
}SDO_RESP;

/*�¼��ص���������*/
typedef enum{
	CBT_TRACE = 0, //TRACE
	CBT_SLAVE_STATUS_CHANGE = 1, //�ӻ�״̬�ı�	
	CBT_PDO_DATA = 2, //�յ�PDO����
	CBT_SDO_RESP = 3, //�յ�SDO��Ӧ
}CB_TYPE;


#ifdef __cplusplus
extern "C" {
#endif
	
/*�¼��ص�����:
CBT_TRACE:
	pData:char*����,������Ϣ����
CBT_SLAVE_STATUS_CHANGE:
	pData:STATUS_CHANGE*����,״̬�ı���Ϣ
CBT_RPDO_MESSAGE
	pData:PDO_DATA*����,PDO������Ϣ
*/
typedef PUSIResult (__stdcall * LPPUSICO_EVENTCB)(CB_TYPE callbackType,LPVOID pData);

/*
�������ƣ�PUSICO_SetDriver
�������ܣ�����USB-CAN����������
���������
	  dll_name:USB-CAN������������̬��
����ֵ��RET_SUCCESS,�������سɹ�
		RET_LOADDRIVER_FAIL,��������ʧ��
*/
PUSIResult __stdcall PUSICO_SetDriver(char* dll_name,HINSTANCE *hDll);
/*
�������ƣ�PUSICO_Open
�������ܣ���������
���������
	  busname:���ڵײ���������������ͨ������Ϣ
	  baudrate:���õĲ�����
����ֵ��RET_SUCCESS,�������سɹ�
		RET_LOADDRIVER_FAIL,��������ʧ��
*/
PUSIResult __stdcall PUSICO_Open(char* busname,char* baudrate,int nBufferTimer,int nBufferSize);

/* ���ô˺����ر��豸 */
PUSIResult __stdcall PUSICO_Close(void);

/* ������Ӳ����Ĵ�վ�ڵ�*/
PUSIResult __stdcall PUSICO_AddNode(DWORD NodeID);

/* �Ƴ������Ĵ�վ�ڵ�*/
PUSIResult __stdcall PUSICO_RemoveNode(DWORD NodeID);

/* ���ô˺�����ȡ��վSDO */
PUSIResult __stdcall PUSICO_ReadSDO(DWORD NodeID, DWORD Index, DWORD SubIndex,\
	BYTE *pRecData,DATA_TYPE DataType, DWORD *pRecLen, DWORD WaitTm);
/* ���ô˺�����ȡ��վSDO,ͨ���¼��ص���������дSDO���*/
PUSIResult __stdcall PUSICO_ReadSDOCallBack(DWORD NodeID, DWORD Index, DWORD SubIndex,DATA_TYPE DataType);

/* ���ô˺���д��վSDO */
PUSIResult __stdcall PUSICO_WriteSDO(DWORD NodeID, DWORD Index, DWORD SubIndex,\
	BYTE *pSendData,DATA_TYPE DataType, DWORD SendLen, DWORD WaitTm);
/* ���ô˺���д��վSDO,ͨ���¼��ص���������дSDO���*/
PUSIResult __stdcall PUSICO_WriteSDOCallBack(DWORD NodeID, DWORD Index, DWORD SubIndex,\
	BYTE *pSendData,DATA_TYPE DataType, DWORD SendLen);

/*дPDO*/
PUSIResult __stdcall PUSICO_WritePDO(DWORD NodeID,DWORD dwPDONum,BYTE* pSendData,DWORD dwLen);

/*��PDO*/
PUSIResult __stdcall PUSICO_ReadPDO(DWORD NodeID,DWORD dwPDONum,BYTE* pRecData,DWORD* pdwLen);

/* ���ô˺������ô�վ����״̬ */
PUSIResult __stdcall PUSICO_SetNodeState(DWORD NodeID, SLAVE_MANAGEMENT slaveManagement);

/* ���ô˺�����ȡ��վ����״̬ */
PUSIResult __stdcall PUSICO_GetNodeStatus(DWORD NodeID,SLAVE_STATUS *pSlaveStatus);

/* �����¼��ص����� */
PUSIResult __stdcall PUSICO_SetEventCallback(LPPUSICO_EVENTCB callback);


#ifdef __cplusplus
}
#endif

#endif // _PUSICO_H

