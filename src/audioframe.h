/*************************************************************************
【文件名】audioframe.h
【功能模块和目的】音频类声明

*************************************************************************/

#ifndef	AUDIOFRAME_H
#define AUDIOFRAME_H

#include <Windows.h>

//如果使用vs，请取消 下一行的注释
//#pragma comment(lib, "winmm.lib")

//用于友元的前置类声明
class Audio; 


/*************************************************************************
* 【类名】AudioCreate
* 【功能】构造、储存一段空音频帧，用于实现录音功能
* 【接口说明】
*       构造函数AudioCreate()构造一个空的音频帧，可容纳数据10k字节  
*       构造函数AudioCreate(const BYTE* pInBuffer, unsigned int Length)构造特定音频数据的音频帧
*		析构函数~AudioCreate()释放使用的资源，并销毁对象的非static数据成员
*		拷贝构造函数AudioCreate(const AudioCreate& Frame);
*		赋值运算符AudioCreate& operator= (const AudioCreate& Frame);
*		静态常量BUF_SZIE，数据区大小，固定为10k字节 
*		静态常量结构体FORMAT，采集/播放音频的格式
*		数据区指针pBuffer的常引用
*		音频头的常引用Header
* *************************************************************************/
class  AudioCreate	{
public:
	//构造函数AudioCreate()构造一个空的音频帧，可容纳数据10k字节 
	 AudioCreate();
	 //构造特定音频数据的音频帧
	 AudioCreate(const BYTE* pInBuffer, unsigned int Length);
	 //析构函数
	~ AudioCreate();
	//拷贝构造函数
	AudioCreate(const AudioCreate& Frame);
	//赋值运算符
	AudioCreate& operator= (const AudioCreate& Frame);
	//静态常量BUF_SZIE，数据区大小，固定为10k字节
	static const unsigned int BUF_SZIE;
	//静态常量结构体FORMAT，采集/播放音频的格式
	static const WAVEFORMATEX FORMAT;
	//数据区指针pBuffer的常引用
	BYTE* const& pBuffer;
	//音频头的常引用Header(于此用到了WINDOWS API，所以开头引入了头文件<Windows.h>）
	const WAVEHDR& Header;
private:
	//友元
	friend class Audio;
	//采集/播放音频的格式，结构体
	WAVEHDR m_Header;
	//音频数据区指针
	BYTE* m_pBuffer;
};
#endif // AUDIOCREATE_H
