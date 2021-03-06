#include <stdio.h>
#include <string.h>

#ifndef  __FINGER_H
#define  __FINGER_H


/**********************错误返回码***********************/

#define ZAZ_OK                0x00	    //表示指令执行OK
#define ZAZ_COMM_ERR          0x01		//表示数据包接受错误
#define ZAZ_NO_FINGER         0x02		//表示无指纹输入
#define ZAZ_GET_IMG_ERR       0x03		//表示录入指纹图像失败
#define ZAZ_FP_TOO_DRY        0x04		
#define ZAZ_FP_TOO_WET        0x05
#define ZAZ_FP_DISORDER       0x06
#define ZAZ_LITTLE_FEATURE    0x07	   //表示特征点太少而生不成特征
#define ZAZ_NOT_MATCH         0x08	   //表示指纹不匹配
#define ZAZ_NOT_SEARCHED      0x09	   //表示没搜索到指纹
#define ZAZ_MERGE_ERR         0x0a	   //表示特征合并失败
#define ZAZ_ADDRESS_OVER      0x0b	   //表示访问指纹库时地址序号超出指纹库范围
#define ZAZ_READ_ERR          0x0c	   //表示指纹库读模版出错或无效
#define ZAZ_UP_TEMP_ERR       0x0d	   //表示上传特征失败
#define ZAZ_RECV_ERR          0x0e	   //表示特征不能接受后续数据包
#define ZAZ_UP_IMG_ERR        0x0f	   //表示上传图像失败
#define ZAZ_DEL_TEMP_ERR      0x10	   //表示删除模版失败
#define ZAZ_CLEAR_TEMP_ERR    0x11	   //表示清空指纹库失败
#define ZAZ_SLEEP_ERR         0x12
#define ZAZ_INVALID_PASSWORD  0x13	   //表示口令不正确
#define ZAZ_RESET_ERR         0x14	   //表示复位失败
#define ZAZ_INVALID_IMAGE     0x15	   
#define ZAZ_HANGOVER_UNREMOVE 0x17
#define ZAZ_FLASH_ERR         0x18
#define ZAZ_NODEFINE_ERR      0x19


/**********************缓冲区*************************/
#define CHAR_BUFFER_1          0x01
#define CHAR_BUFFER_2          0x02
#define CHAR_BUFFER_3          0x03
#define CHAR_BUFFER_4		   0x04
#define MODEL_BUFFER           0x05

/************************系统基本参数序号*****************/
int SysPara_num[3]={0x04,0x05,0x06};

int ZAZ_Read_SysPara[6]={0x01,0x00,0x03,0x3f,0x00,0x43}; //读系统参数

/**************************应答包************************/
int UART_RECEVICE_BUFFER[24]={0};			  //应答包
int Subsequent_RECEVICE_BUFFER[2048];				  //后续包	  
int Subsequent_RECEVICE_DATA[1024]={0};
int Subsequent_RECEVICE_LENGTH[24]={0};
int Subsequent_RECEVICE_SUM[10]={0};

int BUFFER_NUM;

/*********************ZAZ-404-B通信协议定义*********************/
int ZAZ_Pack_Head[6]     = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};      //协议包头
// system command
int ZAZ_Templete_Num[6]  ={0x01,0x00,0x03,0x4D,0x00,0x51 };      //获得模版总数															 

// Fingerprint processing 
int ZAZ_Set_Syspara[8]   ={0x01,0x00,0x05,0x3e,0x05,0x02,0x00,0x4b};	 //设置系统基本参数安全等级为2
int ZAZ_Get_Img[6]       = {0x01,0x00,0x03,0x31,0x00,0x35};       //录指纹图像
int ZAZ_Up_Image[6]      = {0x01,0x00,0x03,0x3a,0x00,0x3e};      //上传图像
int ZAZ_Down_Image[6]    = {0x01,0x00,0x03,0x3b,0x00,0x3f};      //下载图像
int ZAZ_Img_To_Buffer[7] = {0x01,0x00,0x04,0x32,0x01,0x00,0x38}; //将图像放入到CHAR_BUFFER
int ZAZ_Reg_Model[6]     = {0x01,0x00,0x03,0x35,0x00,0x39};        //将CHAR_BUFFER_1、2、3、4合成特征模版
int ZAZ_Up_Buffer[7]    = {0x01,0x00,0x04,0x38,0x01,0x00,0x3e};  //将CHAR_BUFFER上传给上位机
int ZAZ_Down_To_Buffer[7] = {0x01,0x00,0x04,0x39,0x01,0x00,0x3f};	//上位机下载特征文件到CHAR_BUFFER
int ZAZ_Match[6]       = {0x01,0x00,0x03,0x33,0x00,0x37};        //精确比对两枚指纹特征
int ZAZ_Search[11]     ={0x01,0x00,0x08,0x34,0x01,0x00,0x00,0x03,0xA1,0x00,0xe2}; //搜索指纹搜索范围0 - 929
int ZAZ_Delet_All_Model[6]={0x01,0x00,0x03,0x3d,0x00,0x41};//删除指纹模块里所有的模版
int ZAZ_Save_Finger[9]={0x01,0x00,0x06,0x36,0x01,0x00,0x0B,0x00,0x49};//将BUFFER1中的特征码存放到指定的位置
int ZAZ_Load_Char[9]  ={0x01,0x00,0x06,0x37,0x01,0x00,0x0A,0x00,0x49};	 //将 flash 数据库中指定 ID 号的指纹模板读入到模板缓冲区
int ZAZ_Delete_Model[10]={0x01,0x00,0x07,0x3C,0x00,0x00,0x00,0x01,0x00,0x45}; //删除指定的模版
int YXJ_FG[1024] = {
0xef,0x1,0xff,0xff,0xff,0xff,0x2,0x0,0x82,0x5b,0x38,0xdf,0x39,0x24,0xae,0xa4,0xd6,0x58,0xc2,0xdf,0xb6,0x39,0xc3,0x42,0xd6,0x3d,0xaa,0x81,0xb7,0x4b,0xc1,0x1a,0xf4,0x20,0x3f,0x24,0x15,0x3e,0x2c,0xd5,0xae,0x31,0xb8,0xac,0xcf,0x27,0xab,0x4e,0x4c,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x13,0xcc,0xef,0x1,0xff,0xff,0xff,0xff,0x2,0x0,0x82,0x3,0x1,0x3e,0x23,0x0,0x0,0xff,0xfe,0xff,0xfe,0xfc,0x1e,0xf8,0xe,0xf0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x5b,0x91,0xc1,0xfe,0x3c,0x12,0xab,0xde,0x3d,0x98,0x14,0x3e,0x2b,0x22,0x2a,0x3e,0x20,0xa5,0xa7,0xbe,0x4e,0x40,0x45,
0x3e,0x43,0x8d,0x55,0x3f,0x2f,0x1a,0x2a,0x7f,0x51,0x28,0x97,0x7f,0x41,0x2f,0xc1,0xbf,0x52,0x30,0xc4,0x3f,0x4e,0x10,0x0,0x7c,0x28,0x43,0xe3,0xbc,0x4a,0xb5,0xd6,0xdd,0x5e,0x41,0x5f,0x3d,0x4d,0x8c,0xd5,0xfa,0x27,0xaf,0xa6,0x9b,0x35,0xc3,0x0,0xf8,0x31,0x9c,0xef,0x1,0xff,0xff,0xff,0xff,0x2,0x0,0x82,0x22,0xa9,0xa7,0x59,0x22,0xab,0xe5,0x39,0x5e,0x3d,0x5e,0x99,0x45,0x3e,0x9b,0xd9,0x41,0xc0,0x1b,0xb6,0x5e,0x3b,0x1c,0x97,0x2e,0xb1,0x8b,0xf5,0x23,0x38,0xe2,0x35,0x43,0xb6,0x81,0x31,0x36,0x33,0x4e,0xaa,0x32,
0x3b,0x21,0x8f,0x22,0xbf,0xe4,0x2b,0x2d,0xbb,0x8e,0x2c,0x36,0xbd,0x4b,0xad,0x2a,0xbf,0xa5,0xcd,0x39,0xbc,0x6,0x8,0x38,0x34,0x2b,0xe9,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1d,0x36,0xef,0x1,0xff,0xff,0xff,0xff,0x2,0x0,0x82,0x3,0x1,0x43,0x21,0x0,0x0,0xff,0xfe,0xff,0xfe,0xff,0xfe,0xfc,0x1e,0xf0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0xe0,0xe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x50,0x12,0x41,0xbe,0x3e,0x94,0xac,0x3e,0x5c,0x9e,0x6a,0x9e,0x4d,0x40,0x45,0xfe,0x43,0x1a,0x95,0x3f,0x30,0x1b,0x6a,0xdf,0x29,0xa2,0x6a,0x9f,0x4f,0xa8,0x96,0xff,0x53,0xb1,0x3,0x7f,0x5f,0x31,0x5a,0x1c,0x43,0x43,0x57,0x9c,0x58,0x43,0xdb,0xfc,0x5e,0xad,0x99,0xfd,0x22,0x31,0xe4,0xdb,0x5d,0xba,0xdc,0x7b,0x5e,0x41,0x9e,0xfb,0x41,0x30,0x1,0x59,0x5d,0xbd,0x1e,0x99,0x34,0xa3,0xef,0x1,0xff,0xff,0xff,0xff,0x2,0x0,0x82,0x3f,0xbd,0x48,0x90,0x2c,0x3f,0xe5,0x96,0x38,0x42,0x80,0xf6,0x22,0x2f,0x27,0x57,0x45,0xb7,0x15,0x97,0x28,0x36,0xe5,0x94,0x2d,0xbb,0xcf,0x14,0x41,0xbf,0xdf,0xe,0x23,0xc0,0x65,0xb4,0x35,0x35,0xe9,0x35,0x21,0xbd,0x64,0x55,0x3f,0xb8,0xec,0x93,0x28,0xc0,0x4f,0xf3,0x42,0xb2,0x54,0x90,0x44,0x33,0xc2,0xef,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1b,0xef,0xef,0x1,0xff,0xff,0xff,0xff,0x2,0x0,0x82,0x3,0x1,0x36,0x19,0x0,0x0,0xff,0xfe,0xff,0xfe,0xf8,0x3e,0xe0,0x1e,0xc0,0x1e,0xc0,0x1e,0xc0,0x1e,0xc0,0x1e,0xc0,0x1e,0xc0,0x1e,0xc0,0x1e,0xc0,0x1e,0xc0,0x1e,0xc0,0x1e,0xc0,0xe,0xc0,0xe,0xe0,0xe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x44,0xd,0x80,0x9e,0x33,0xf,0x6c,0x7e,0x37,0x96,0x54,0x5e,0x22,0x1e,0xaa,0x5e,0x25,0x96,0xaa,0x9f,0x45,0x24,0x16,0xff,0x47,0x29,0xc3,0x9f,0x53,0x97,0x98,0x3c,0x43,0x42,0x9c,0xfc,0x4e,0x99,0xc2,0xbd,0x58,0x43,0x1f,0x1a,0x38,0x2b,0xc1,0xbb,0x5d,0x41,0x9e,0xbb,0x1a,0x23,0xe8,0x56,0x3b,0x2e,0xd5,0x77,0x57,0xb5,0x9c,0xb7,0x57,0x38,0x5f,0x57,0x44,0x3c,0x6,0x74,0x2f,0xaa,0xef,0x1,0xff,0xff,0xff,0xff,0x8,0x0,0x82,0x3b,0xb0,0x83,0x52,0x3c,0xb2,0xd7,0x13,0x3a,0xb6,0x56,0x4c,0x20,0x41,0xa3,0xd,0x2d,0x2e,0xec,0x8a,0x1e,0x31,0xa3,0xaa,0x2f,0x3e,0x10,0x26,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xa,0xd5
};


#endif







/*------------------ FINGERPRINT命令字 --------------------------*/
//接收反馈数据缓冲
int FINGERPRINT_Recevice_Data(int ucLength)
{
	int i=0;
	/*	memset(UART_RECEVICE_BUFFER,0,24);
		for(i = 0;i < ucLength;i++)
		{
		getkey3(UART_RECEVICE_BUFFER[i], 1);
		printf("read data = %x\n",UART_RECEVICE_BUFFER[i]);
		}*/
	int ch;
	int timeout = 0;
	while(1) {	 
		if(timeout++ >= 1000000000) {
			return -1;
		} 

		ch = getkey3();		
		if(ch == 0xef) {	
			UART_RECEVICE_BUFFER[0] = ch;
			ch = getkey3();		
			if(ch == 0x1) {	
				UART_RECEVICE_BUFFER[1] = ch;

				ch = getkey3();		
				if(ch == 0xff) {	
					UART_RECEVICE_BUFFER[2] = ch;

					ch = getkey3();		
					if(ch == 0xff) {	
						UART_RECEVICE_BUFFER[3] = ch;

						ch = getkey3();		
						if(ch == 0xff) {	
							UART_RECEVICE_BUFFER[4] = ch;

							ch = getkey3();		
							if(ch == 0xff) {	
								UART_RECEVICE_BUFFER[5] = ch;
								for(i = 6; i < ucLength; i++){
									UART_RECEVICE_BUFFER[i] = getkey3();
								}

							}
						}
					}
				}
			}
			break;
		}
	}
	return 	UART_RECEVICE_BUFFER[9];
}


//读模块系统基本参数
int ZAZ_SetSysPara(void)
{
	int i;
	for(i=0;i<6;i++) //发送包头 
	{
		SER_PutChar3(ZAZ_Pack_Head[i]);
	}

	for(i=0;i<8;i++){
		SER_PutChar3(ZAZ_Set_Syspara[i]);

	}
	clear_buf();

	FINGERPRINT_Recevice_Data(12);

	return 0; 

}

int * ZAZ_ReadSysPara(void)
{
	int i;
	int ret[17];
	for(i=0;i<6;i++) //发送包头 
	{
		SER_PutChar3(ZAZ_Pack_Head[i]);
	}
	for(i=0;i<6;i++) //发送命令 0x1d
	{
		SER_PutChar3(ZAZ_Read_SysPara[i]);
	}

	FINGERPRINT_Recevice_Data(28);
	for(i=0;i<17;i++){
		ret[i]=	UART_RECEVICE_BUFFER[i+9];
	}

	return ret;
}

static int FINGERPRINT_Cmd_Get_Img(void)
{
	int i;

	for(i=0;i<6;i++) //发送包头
	{  
		SER_PutChar3(ZAZ_Pack_Head[i]);
	}
	for(i=0;i<6;i++) //发送命令 0x1d
	{
		SER_PutChar3(ZAZ_Get_Img[i]);
	}
	clear_buf();

	return 0;
}

//录入指纹图像
int ZAZ_GetImag(void)
{
	int ret = 0;
	do{	
		FINGERPRINT_Cmd_Get_Img(); //获得指纹图像
		ret=FINGERPRINT_Recevice_Data(12); //接收12个长度的反馈码
		usleep(5000);
	}while(ret!=ZAZ_OK);	

	return 0;
}



static void FINGERPRINT_Img_To_Buffer(int BufferID)
{
	unsigned long temp = 0;
	int i;
	ZAZ_Img_To_Buffer[4]=BufferID;

	for(i=0;i<5;i++)   //计算校验和
		temp = temp + ZAZ_Img_To_Buffer[i];

	ZAZ_Img_To_Buffer[5]=(temp & 0xFF00) >> 8; //存放校验数据
	ZAZ_Img_To_Buffer[6]= temp & 0x00FF;

	for(i=0;i<6;i++)    //发送包头
		SER_PutChar3(ZAZ_Pack_Head[i]);   

	for(i=0;i<7;i++)
		SER_PutChar3(ZAZ_Img_To_Buffer[i]);
	clear_buf();


}

//图像生成特征存于BufferID中
int ZAZ_GenChar(int BufferID)
{
	int ret=0;
	FINGERPRINT_Img_To_Buffer(BufferID); //发送命令 将图像转换成 特征码 存放在 CHAR_buffer
	ret=FINGERPRINT_Recevice_Data(12); //接收12个长度的反馈码
	return ret;

}


//将BUFFER1 跟 BUFFER2 中的特征码合并成指纹模版
int ZAZ_RegModel(void)
{
	int i;    
	int ret=0;
	for(i=0;i<6;i++) //包头
	{
		SER_PutChar3(ZAZ_Pack_Head[i]);
	}  

	for(i=0;i<6;i++)  //命令合并指纹模版
	{
		SER_PutChar3(ZAZ_Reg_Model[i]); 
	}
	clear_buf();
	ret=FINGERPRINT_Recevice_Data(12); //接收12个长度的反馈码

	return ret;
}

//接收后续数据包
// /***start: 2 adder: 4  pid: 1 length: 2 data: 128 sum: 2  共139个字节  发送7个数据包 1个结束数据包****/
static int Subsequent_Recevice_Data()
{
	int ch;
	static int n=0;
	int i;
	int cnt;
	int DATA_LONG=0;
	int Subsequent_RECEVICE_HEAD[6]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF};
	int Subsequent_PID[2]={0x02,0x08};
	int NUM=0;
	BUFFER_NUM=0;

	/*
	   for(i = 0;i <= 1111;i++) {
	   getkey3(Subsequent_RECEVICE_BUFFER[i],1);
	   }*/

	while(1){
		ch = getkey3();		
		if(ch == 0xef) {	
			Subsequent_RECEVICE_BUFFER[0] = ch;
			ch = getkey3();		
			if(ch == 0x1) {	
				Subsequent_RECEVICE_BUFFER[1] = ch;

				ch = getkey3();		
				if(ch == 0xff) {	
					Subsequent_RECEVICE_BUFFER[2] = ch;

					ch = getkey3();		
					if(ch == 0xff) {	
						Subsequent_RECEVICE_BUFFER[3] = ch;

						ch = getkey3();		
						if(ch == 0xff) {	
							Subsequent_RECEVICE_BUFFER[4] = ch;

							ch = getkey3();		
							if(ch == 0xff) {	
								Subsequent_RECEVICE_BUFFER[5] = ch;
								for(i = 6; i < 1112; i++){
									Subsequent_RECEVICE_BUFFER[i] = getkey3();
								}
							}
						}
					}
				}
			}
			break;
		}

		/*
		   if(ch!=-1){
		   Subsequent_RECEVICE_BUFFER[BUFFER_NUM] = ch;
		//	SER_PutChar2(Subsequent_RECEVICE_BUFFER[BUFFER_NUM]); 
		if(BUFFER_NUM >= 1111){
		break;
		}
		BUFFER_NUM++;
		}
		 */
	}

	printf("BUFFER_NUM=%d\n",BUFFER_NUM);

	while(1){
		if((Subsequent_RECEVICE_BUFFER[NUM]==Subsequent_RECEVICE_HEAD[0])&&(Subsequent_RECEVICE_BUFFER[NUM+1]==Subsequent_RECEVICE_HEAD[1])&&(Subsequent_RECEVICE_BUFFER[NUM+2]==Subsequent_RECEVICE_HEAD[2])&&(Subsequent_RECEVICE_BUFFER[NUM+3]==Subsequent_RECEVICE_HEAD[3])&&(Subsequent_RECEVICE_BUFFER[NUM+4]==Subsequent_RECEVICE_HEAD[4])&&(Subsequent_RECEVICE_BUFFER[NUM+5]==Subsequent_RECEVICE_HEAD[5])){		
			NUM+=6;
			printf("*****************\n");
			if(Subsequent_RECEVICE_BUFFER[NUM]==Subsequent_PID[0]){
				Subsequent_RECEVICE_LENGTH[0]=Subsequent_RECEVICE_BUFFER[++NUM];
				Subsequent_RECEVICE_LENGTH[1]=Subsequent_RECEVICE_BUFFER[++NUM];
				DATA_LONG=Subsequent_RECEVICE_LENGTH[0];
				DATA_LONG=DATA_LONG << 8 | Subsequent_RECEVICE_LENGTH[1];
				DATA_LONG -= 2;
				printf("DATA=%d\n",DATA_LONG);
				cnt=0;
				while(cnt < DATA_LONG){	  	
					Subsequent_RECEVICE_DATA[n]=Subsequent_RECEVICE_BUFFER[++NUM];
					n++;
					cnt++;
				} 
				printf("n=%d\n",n);
				Subsequent_RECEVICE_SUM[0]=Subsequent_RECEVICE_BUFFER[++NUM];
				Subsequent_RECEVICE_SUM[1]=Subsequent_RECEVICE_BUFFER[++NUM];

			}else if(Subsequent_RECEVICE_BUFFER[NUM]==Subsequent_PID[1]){

				Subsequent_RECEVICE_LENGTH[0]=Subsequent_RECEVICE_BUFFER[++NUM];
				Subsequent_RECEVICE_LENGTH[1]=Subsequent_RECEVICE_BUFFER[++NUM];
				DATA_LONG=Subsequent_RECEVICE_LENGTH[0];
				DATA_LONG=DATA_LONG << 8 | Subsequent_RECEVICE_LENGTH[1];
				DATA_LONG -= 2;
				printf("END_DATA=%d\n",DATA_LONG);
				cnt=0;
				while(cnt < DATA_LONG){	  	
					Subsequent_RECEVICE_DATA[n]=Subsequent_RECEVICE_BUFFER[++NUM];				 	
					n++;
					cnt++;
				} 
				printf("end_data_sum=%d\n",n);
				Subsequent_RECEVICE_SUM[0]=Subsequent_RECEVICE_BUFFER[++NUM];
				Subsequent_RECEVICE_SUM[1]=Subsequent_RECEVICE_BUFFER[++NUM];

				break;

			}
		}
		NUM++;
	}
	return 0;
}

//发送后续数据包
static int Subsequent_Send_Data()
{
	int i;
	int ret;
	BUFFER_NUM=1024;
	for(i=0;i < BUFFER_NUM;i++){
			SER_PutChar3(YXJ_FG[i]);
	}
	ret=FINGERPRINT_Recevice_Data(12);
		
	   return ret;

}

//发送后续数据包
/*
static int Subsequent_Send_Data(int *Subsequent_RECEVICE_DATA)
{
	int i=0,ret;
	int cnt=0;
	static int n=0;
	int ZAZ_CMD_LENGTH[3]={0x02,0x00,0x82};
	int ZAZ_CMD_LENGTH_END[3]={0x08,0x00,0x82};
	unsigned long temp=0;
	int DATA[1024]={0};
	int SUM[2]={0};

	for(i=0;i<1024;i++){
		DATA[i]=*Subsequent_RECEVICE_DATA++;
	}

	while(cnt<7){
		for(i=0;i<6;i++)    //发送包头
			SER_PutChar3(ZAZ_Pack_Head[i]);

		for(i=0;i<3;i++)    //发送包标示和包长度
		{
			SER_PutChar3(ZAZ_CMD_LENGTH[i]);
			temp=temp+ZAZ_CMD_LENGTH[i];
		}
		for(n = cnt*128;n<(cnt+1)*128;n++){
			SER_PutChar3(DATA[n]);
			temp=temp+DATA[n];
		}
		SUM[0]=(temp & 0xFF00) >> 8; //存放校验数据
		SUM[1]=(temp & 0xFF);

		for(i=0;i<2;i++)
			SER_PutChar3(SUM[i]);

		temp=0;

		cnt++;	  	   
	}

	for(i=0;i<6;i++)    //发送包头
		SER_PutChar3(ZAZ_Pack_Head[i]);

	for(i=0;i<3;i++)    //发送包头
	{
		SER_PutChar3(ZAZ_CMD_LENGTH_END[i]);
		temp=temp+ZAZ_CMD_LENGTH_END[i];
	}
	for(n=cnt*128;n<(cnt+1)*128;n++){
		SER_PutChar3(DATA[n]);
		temp=temp+DATA[n];
	}

	SUM[0]=(temp & 0x00FF00) >> 8; //存放校验数据
	SUM[1]= (temp & 0x0000FF);	

	for(i=0;i<2;i++)
		SER_PutChar3(SUM[i]);

	ret=FINGERPRINT_Recevice_Data(12);

	return ret;


}
*/

//将特征缓冲区 CharBuffer中的特征文件上传给上位机
int ZAZ_UpChar( int BufferID)
{
	unsigned long temp=0x3d;
	int i,ret;
	ZAZ_Up_Buffer[4]= BufferID;

	//		  for(i=0;i<5;i++)   //计算校验和
	//		   	   temp = temp + ZAZ_Up_Buffer[i];

	temp=temp+ZAZ_Up_Buffer[4]; 

	ZAZ_Up_Buffer[5]=(temp & 0x00FF00) >> 8; //存放校验数据
	ZAZ_Up_Buffer[6]= (temp & 0x0000FF);

	for(i=0;i<6;i++)    //发送包头
	{
		SER_PutChar3(ZAZ_Pack_Head[i]); 
	}
	usleep(10000);
	for(i=0;i<7;i++)
	{
		SER_PutChar3(ZAZ_Up_Buffer[i]);
	}
	ret=FINGERPRINT_Recevice_Data(12); //接收12个长度的反馈码

	if(ret==0){
		Subsequent_Recevice_Data();
		printf("ret_Subsequent_Recevice_Data success");
	}
	return ret;
}

//上位机下载特征文件到模块的一个特征缓冲区中
int ZAZ_DownChar(int BufferID)
{
	unsigned long temp=0x3e;
	int i,ret=0,ret1=0;
	ZAZ_Down_To_Buffer[4]=BufferID;

	temp=temp+ ZAZ_Down_To_Buffer[4];
	ZAZ_Down_To_Buffer[5]=(temp & 0xFF00) >> 8; //存放校验数据
	ZAZ_Down_To_Buffer[6]= temp & 0x00FF;

	for(i=0;i<6;i++)    //发送包头
	{
		SER_PutChar3(ZAZ_Pack_Head[i]); 
	}
	for(i=0;i<7;i++)
	{
		SER_PutChar3(ZAZ_Down_To_Buffer[i]);
	}
	usleep(50000);
//	ret=FINGERPRINT_Recevice_Data(12); //接收12个长度的反馈码
	printf("ret=%x\n",ret);
	if(1){
		printf("Begin Subsequent_Send_Data\n");
//		ret1=Subsequent_Send_Data(Subsequent_RECEVICE_DATA);
		ret1=Subsequent_Send_Data();
		printf("ret1=%x\n",ret1);
		if(ret1==ZAZ_OK){
			printf("ret_Subsequent_Recevice_Data success\n");
		}else{
			printf("ret_Subsequent_Recevice_Data error!!\n");
		}
	}
	return 0;
}


//删除指纹模块里的所有指纹模版
int ZAZ_Empty(void)
{
	int i;    
	int ret=0;
	for(i=0;i<6;i++) //包头
		SER_PutChar3(ZAZ_Pack_Head[i]);   

	for(i=0;i<6;i++) //命令合并指纹模版
		SER_PutChar3(ZAZ_Delet_All_Model[i]);

	ret=FINGERPRINT_Recevice_Data(12); //接收12个长度的反馈码

	return ret;



}



//删除指纹模块里的指定指纹模版
int ZAZ_DeletChar(int uiID_temp,int N_temp )
{
	int uiSum_temp = 0;
	int i,ret=0;    

	ZAZ_Delete_Model[4]=(uiID_temp&0xFF00)>>8;
	ZAZ_Delete_Model[5]=(uiID_temp&0x00FF);

	ZAZ_Delete_Model[6]=(N_temp&0xFF00)>>8;
	ZAZ_Delete_Model[7]=(N_temp&0x00FF);

	for(i=0;i<8;i++)
		uiSum_temp = uiSum_temp +ZAZ_Delete_Model[i];


	ZAZ_Delete_Model[8]=(uiSum_temp&0xFF00)>>8;
	ZAZ_Delete_Model[9]=uiSum_temp&0x00FF;


	for(i=0;i<6;i++) //包头
		SER_PutChar3(ZAZ_Pack_Head[i]);   

	for(i=0;i<10;i++) //命令合并指纹模版
		SER_PutChar3(ZAZ_Delete_Model[i]);   

	ret=FINGERPRINT_Recevice_Data(12); //接收12个长度的反馈码

	return ret;

}




//获得指纹模板数量
int *ZAZ_TempleteNum(void)
{ 
	int i;
	int *p =(int *)malloc(12);
	for(i=0;i<6;i++) //包头
	{
		SER_PutChar3(ZAZ_Pack_Head[i]);
	}
	//发送命令 0x1d
	for(i=0;i<6;i++)
	{
		SER_PutChar3(ZAZ_Templete_Num[i]);
	}

	FINGERPRINT_Recevice_Data(14); //确认字	
	for(i=0;i<3;i++)
		p[i] = UART_RECEVICE_BUFFER[i+9];


	return p;		
}

//精确比对两枚指纹
int * ZAZ_Two_Match(void)
{
	int i;
	int ret[3]={0};

	for(i=0;i<6;i++) //包头
	{
		SER_PutChar3(ZAZ_Pack_Head[i]);
	}

	for(i=0;i<6;i++)
	{
		SER_PutChar3(ZAZ_Match[i]);
	}

	FINGERPRINT_Recevice_Data(14); //接收14个长度的反馈码
	ret[0]=UART_RECEVICE_BUFFER[9];
	ret[1]=UART_RECEVICE_BUFFER[10];
	ret[2]=UART_RECEVICE_BUFFER[11];

	return ret;

}



//搜索指纹库
int * ZAZ_Search_Finger(int BufferID,int StartPage,int PageNum)
{
	int i;
	unsigned long temp;
	int ret[3]={0};
	ZAZ_Search[4] = BufferID;

	ZAZ_Search[5]=(StartPage&0xFF00)>>8;
	ZAZ_Search[6]=(StartPage&0x00FF);

	ZAZ_Search[7]=(PageNum&0xFF00)>>8;
	ZAZ_Search[8]=(PageNum&0x00FF);

	for(i=0;i<9;i++)
		temp = temp +ZAZ_Search[i];

	//UART0_Send_Byte(uiSum_temp);	

	ZAZ_Search[9]=(temp&0xFF00)>>8;
	ZAZ_Search[10]=temp&0x00FF;


	for(i=0;i<6;i++)   //发送命令搜索指纹库
	{
		SER_PutChar3(ZAZ_Pack_Head[i]); 
	}

	for(i=0;i<11;i++)
	{
		SER_PutChar3(ZAZ_Search[i]); 
	}

	FINGERPRINT_Recevice_Data(16); //接收16个长度的反馈码
	ret[0]=UART_RECEVICE_BUFFER[9];
	ret[1]=UART_RECEVICE_BUFFER[10];
	ret[2]=UART_RECEVICE_BUFFER[11];

	return ret;

}



//存储指纹模版
int ZAZ_StoreChar( int BuffID,int Finger_Num)
{
	unsigned long temp = 0;
	int i,ret=0;

	ZAZ_Save_Finger[4] = BuffID;

	ZAZ_Save_Finger[5]=(Finger_Num&0xFF00)>>8;
	ZAZ_Save_Finger[6]=(Finger_Num&0x00FF);
	//           ZAZ_Save_Finger[5] = ucH_Char;
	//           ZAZ_Save_Finger[6] = ucL_Char;

	for(i=0;i<7;i++)   //计算校验和
		temp = temp + ZAZ_Save_Finger[i];

	ZAZ_Save_Finger[7]=(temp & 0x00FF00) >> 8; //存放校验数据
	ZAZ_Save_Finger[8]= temp & 0x0000FF;

	for(i=0;i<6;i++){    
		sendchar3(ZAZ_Pack_Head[i]);        //发送包头
	} 
	for(i=0;i<9;i++){  
		sendchar3(ZAZ_Save_Finger[i]);      //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
	}
	ret=FINGERPRINT_Recevice_Data(12); //接收12个长度的反馈码

	return ret;

}

// 读出模版 ：将 flash 数据库中指定 ID 号的指纹模板读入到模板缓冲区
int ZAZ_Loadchar(int BufferID,int Finger_Num)
{
	unsigned long temp = 0;
	int i,ret=0;

	ZAZ_Load_Char[4] = BufferID;

	ZAZ_Load_Char[5]=(Finger_Num&0xFF00)>>8;
	ZAZ_Load_Char[6]=(Finger_Num&0x00FF);
	//           ZAZ_Load_Char[5] = ucH_Char;
	//           ZAZ_Load_Char[6] = ucL_Char;

	for(i=0;i<7;i++)   //计算校验和
		temp = temp + ZAZ_Load_Char[i];

	ZAZ_Load_Char[7]=(temp & 0x00FF00) >> 8; //存放校验数据
	ZAZ_Load_Char[8]= temp & 0x0000FF;

	for(i=0;i<6;i++){    
		sendchar3(ZAZ_Pack_Head[i]);        //发送包头
	} 
	for(i=0;i<9;i++){  
		sendchar3(ZAZ_Load_Char[i]);      //发送命令 将图像转换成 特征码 存放在 CHAR_buffer
	}
	ret=FINGERPRINT_Recevice_Data(12); //接收12个长度的反馈码

	return ret;


}

//*********************************************************//

//指纹添加新用户 存在在指纹库中
int ZAZ_add_new_user(int BufferID,int Finger_Num)
{
	int i,ret;
	int Buffer[4]={CHAR_BUFFER_1,CHAR_BUFFER_2,CHAR_BUFFER_3,CHAR_BUFFER_4};

	for(i=0;i<4;i++){
		printf("please Input fingerprint\n");
		ret=ZAZ_GetImag();	  //录入指纹图像
		if(ret==0){
			printf("Input fingerprint succeed\n");
		}
		printf("Fingerprint image stored in Buffer[%d]\n",i);
		ret=ZAZ_GenChar(Buffer[i]);     // 将图像转换成特征码存于CHAR_BUFFER
		printf("ret=%x\n",ret);
		if(ret!=ZAZ_OK){
			return -1;
		} 
	}

	printf("Synthetic fingerprint template\n");		
	ret=ZAZ_RegModel();		//合成指纹模版
	printf("ret=%x\n",ret);
	if(ret != ZAZ_OK )
	{
		return -1;
	}
	printf("Fingerprint template stored in fingerprint library\n");
	ret=ZAZ_StoreChar(BufferID,Finger_Num);
	printf("ret=%x\n",ret);
	if(ret!=ZAZ_OK){
		return -1;
	}	


	return 0;

}

//从传感器获取指纹并生成特征然后上传给上位机
int ZAZ_addnewuser_To_Pc(int BufferID,int Finger_Num)
{
	int i,ret;
	int Buffer[4]={CHAR_BUFFER_1,CHAR_BUFFER_2,CHAR_BUFFER_3,CHAR_BUFFER_4};

	for(i=0;i<4;i++){
		printf("please Input fingerprint\n");
		ret=ZAZ_GetImag();	  //录入指纹图像
		if(ret==0){
			printf("Input fingerprint succeed\n");
		} else {
			printf("Input fingerprint error\n");
		}
		printf("Fingerprint image stored in Buffer[%d]\n",i);
		ret=ZAZ_GenChar(Buffer[i]);     // 将图像转换成特征码存于CHAR_BUFFER
		printf("ret=%x\n",ret);
		if(ret!=ZAZ_OK){
			return -1;
		} 
	}

	printf("Synthetic fingerprint template\n");		
	ret=ZAZ_RegModel();		//合成指纹模版
	printf("ret=%x\n",ret);
	if(ret != ZAZ_OK )
	{
		printf("ZAZ_OK is error\n");
		return -1;
	}
	printf("uploading char\n");

	ret=ZAZ_UpChar(BufferID);
	printf("ret=%x\n",ret);
	if(ret!=ZAZ_OK ) {
		return -1;
	}
	return 0;
}


//从 flash 指纹库中读取一个指定的模板上传
int ZAZ_flashlib_to_pc(int BufferID,int Finger_Num)
{
	int ret;
	ret=ZAZ_Loadchar(BufferID,Finger_Num);
	if(ret!=0){
		printf("ZAZ_Loadchar()error\n");
		return -1;
	}
	printf("uploading char\n");
	ret=ZAZ_UpChar(BufferID);
	printf("ret=%x\n",ret);
	if(ret != ZAZ_OK){
		return -1;
	}
	ret=Subsequent_Recevice_Data();
	printf("ret=%x\n",ret);

	return 0;

}

//指纹模块内比对 (1:N)
int ZAZ_Search_Comparison(int BufferID,int StartPage,int PageNum)
{	 	
	int i,ret;
	int Search_ret[3];	
	printf("please Input fingerprint\n");
	ret=ZAZ_GetImag();	  //录入指纹图像
	if(ret==0){
		printf("Input fingerprint succeed\n");
	}
	printf("Fingerprint image stored in Buffer\n");
	ret=ZAZ_GenChar(BufferID);     // 将图像转换成特征码存于CHAR_BUFFER
	printf("ret=%x\n",ret);
	if(ret!=ZAZ_OK){
		return -1;
	}

	ZAZ_Search_Finger(BufferID,StartPage,PageNum);
	for(i=0;i<3;i++){
		Search_ret[i] = UART_RECEVICE_BUFFER[i+9]; 
		printf("Search_ret[%d]=%x\n",i,Search_ret[i]);
	}

	if(Search_ret[0]!=ZAZ_OK){
		return -1;
	}
	return 0;
}


//上位机下载模块到指纹模块内比对（1:1）
int ZAZ_Match_Comparison(int BufferID1,int BufferID2)
{
	int i,ret;
	//int *p;
	int Match_ret[3];

	printf("please Input fingerprint\n");
	ret=ZAZ_GetImag();	  //录入指纹图像
	if(ret==0){
		printf("Input fingerprint succeed\n");
	}
	printf("Fingerprint image stored in Buffer\n");
	ret=ZAZ_GenChar(BufferID1);     // 将图像转换成特征码存于CHAR_BUFFER
	printf("ret=%x\n",ret);
	if(ret!=ZAZ_OK){
		return -1;
	} 

	printf("Begain Downchar\n");
	ret=ZAZ_DownChar(BufferID2);
	printf("ret=%x\n",ret);
	if(ret!=ZAZ_OK){
		return -1;
	} 

	ZAZ_Two_Match();
	for(i=0;i<3;i++){ 
		Match_ret[i] = UART_RECEVICE_BUFFER[i+9];
		printf("Match_ret[%d]=%x\n",i,Match_ret[i]);
	}
	if(Match_ret[0]!=ZAZ_OK){
		return -1;
	}
	return  0;
}

//	用上位机下载一个指纹特征并以该特征搜索指纹库
int ZAZ_FingerLIB_Search_Comparison(int BufferID,int StartPage,int Finger_Num)
{
	int i,ret;
	int Search_ret[3];

	printf("Begain Downchar\n");
	ret=ZAZ_DownChar(BufferID);
	printf("ret=%x\n",ret);
	if(ret!=ZAZ_OK){
		return -1;
	} 
	ret=Subsequent_Recevice_Data();
	printf("ret=%x\n",ret);          


	ZAZ_Search_Finger(BufferID,StartPage,Finger_Num);
	for(i=0;i<3;i++){
		Search_ret[i] = UART_RECEVICE_BUFFER[i+9]; 
		printf("Search_ret[%d]=%x\n",i,Search_ret[i]);
	}

	if(Search_ret[0]!=ZAZ_OK){
		return -1;
	}

	return  0;
}
