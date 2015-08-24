#ifndef	_Hekr_Protocol_H_
#define	_Hekr_Protocol_H_


// Hekr USER API **************************************************************

// 使用前要定义用户所需要的最大数组  
// 如果有多条不等长命令  取最长长度
// #define User_Max_Len 0x0F

//传入串口接收的数据数组  
//返回值见头文件 RecvData_Handle_Code
//数据保存在对应数组中 Valid_Data 和 Module_Status
//unsigned char Hekr_RecvData_Handle(unsigned char* data);

//配置及查询hekr模块状态 传入码值见头文件 Hekr_Module_Control_Code
//状态值保存在Module_Status数组中
//void Hekr_Module_Control(unsigned char data);


//上传用户有效数据
//数据存放在Valid_Data数组中 len 为用户数据长度  非整帧长度
//void Hekr_ValidData_Upload(unsigned char len);


//如果修改串口则需要修改此函数  及对应头文件
//static void Hekr_Send_Byte(unsigned char ch);
//
// 协议网址  http://docs.hekr.me/protocol/
// BUG 反馈  pengyu.zhang@hekr.me
//					 965006619@qq.com
//*****************************************************************************

#include "uart.h"

#define User_Max_Len 0x0F


extern unsigned char Hekr_Send_Buffer[User_Max_Len+5];
extern unsigned char Valid_Data[User_Max_Len];
extern unsigned char Module_Status[20];

#define Hekr_Frame_Header 0x48u

//*************************************************************************
//Hekr 帧格式
//*************************************************************************

//通用帧头格式 
typedef struct
{
	unsigned char header;
	unsigned char length;
	unsigned char type;
	unsigned char number;
}General_header;

//模块查询帧格式
typedef struct
{
	//通用帧头
	General_header header;
	//有效数据
	unsigned char CMD;
	unsigned char Reserved;
	//和校验
	unsigned char SUM;
}Module_Query_Frame; 

//模块应答帧格式
typedef struct
{
	//通用帧头
	General_header header;
	//有效数据
	unsigned char CMD;
	unsigned char Mode;
	unsigned char WIFI_Status;
	unsigned char Cloud_Status;
	unsigned char Signal_Strength;
	unsigned char Reserved;
	//和校验
	unsigned char SUM;
}Module_Response_Frame; 

//错误帧格式
typedef struct
{
	//通用帧头
	General_header header;
	//有效数据
	unsigned char Error_Code;
	unsigned char Reserved;
	//和校验
	unsigned char SUM;
}Error_Frame; 

//LED 控制帧格式
typedef struct
{
	//通用帧头
	General_header header;
	//有效数据
	unsigned char CMD;
	unsigned char Change_Rate;
	unsigned char Brightness;
	unsigned char Color_Temperature;
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char Reserved;
	//和校验
	unsigned char SUM;
}Led_Control_Frame;


//*************************************************************************
//Hekr 具体码值
//*************************************************************************

//Hekr各帧长度
typedef	enum
{
	Module_Query_Frame_Length = 0x07,
	Module_Response_Frame_Length = 0x0B,
	Led_Control_Frame_Length = 0x0E,
	Error_Frame_Length = 0x07
}All_Frame_Length;

//Hekr各帧类型
typedef	enum
{
	Device_Upload_Type = 0x01,
	Module_Download_Type = 0x02,
	Module_Operation_Type = 0xFE,
	Error_Frame_Type = 0xFF
}All_Frame_Type;

//Hekr错误码取值
typedef	enum
{
	Error_Operation = 0x01,
	Error_Sum_Check = 0x02,
	Error_Data_Range = 0x03,
	Error_No_CMD = 0xFF
}All_Error_Value;

//Hekr数据处理返回值
typedef	enum
{
	RecvData_SumCheckErr = 0x01,
	Last_Frame_Send_Err = 0x02,
	MCU_Upload_ACK = 0x03,
	Valid_Data_Update = 0x04,
	RecvData_Useless = 0x05,
	Hekr_Module_State_Update = 0x06
}RecvData_Handle_Code;

//Hekr模块控制码
typedef	enum
{
	Module_Query = 0x01,
	Module_Restart = 0x02,
	Module_Recover = 0x03,
	Hekr_Config = 0x04
}Hekr_Module_Control_Code;

//Hekr模块状态码
typedef	enum
{
	STA_Mode = 0x01,
	Hekr_Config_Mode = 0x02,
	AP_Mode = 0x03,
	STA_AP_Mode = 0x04,
	RF_OFF_Mode = 0x05
}Hekr_Module_Work_Code;

//Hekr WIFI状态码
typedef	enum
{
	Router_Connected = 0x01,
	Router_Connected_Fail = 0x02,
	Router_Connecting = 0x03,
	Password_Err = 0x04,
	No_Router = 0x05,
	Router_Time_Over = 0x06
}Hekr_Module_WIFI_Code;

//Hekr Cloud状态码
typedef	enum
{
	Cloud_Connected = 0x01,
	DNS_Fail = 0x02,
	Cloud_Time_Over = 0x03
}Hekr_Module_Cloud_Code;

/*智能照明控制命令码*/
typedef	enum
{
	LED_Query = 0x00,						      //查询设备当前状态
	LED_Preset = 0x01,			          //即所带参数全部有效，切换到预设状态
	LED_PowerONOFF = 0x02,				    //开关灯具
	LED_Bright_Control = 0x03,			  //调整亮度到相应值
	LED_Bright_UP = 0x04,			        //调亮命令
	LED_Bright_DOWN = 0x05,			      //调暗命令
	LED_Color_Temperature = 0x06,			//调整色温到相应值
	LED_Color_Chroma = 0x07,			    //调色彩度到相应值
	LED_Recover_LastShutdown = 0x08	  //恢复上次关闭时的状态，例如亮度色彩色温
}LED_Control_Code;

//*************************************************************************
//函数列表
//*************************************************************************

// Hekr USER API 
unsigned char Hekr_RecvData_Handle(unsigned char* data);
void Hekr_Module_Control(unsigned char data);
void Hekr_ValidData_Upload(unsigned char len);

//如果修改串口则需要修改此函数
static void Hekr_Send_Byte(unsigned char ch);

// Static Function
static void Hekr_Send_Frame(unsigned char *data);
static unsigned char Sum_Check_Is_Err(unsigned char* data);
static void Err_Response(unsigned char data);
static unsigned char Sum_Calculate(unsigned char* data);
static void Hekr_ValidData_Copy(unsigned char* data);
static void Hekr_Module_State_Copy(unsigned char* data);

#endif
