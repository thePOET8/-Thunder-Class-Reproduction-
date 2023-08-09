/*************************************************************************
���ļ�����audioframe.h
������ģ���Ŀ�ġ���Ƶ������

*************************************************************************/

#ifndef	AUDIOFRAME_H
#define AUDIOFRAME_H

#include <Windows.h>

//���ʹ��vs����ȡ�� ��һ�е�ע��
//#pragma comment(lib, "winmm.lib")

//������Ԫ��ǰ��������
class Audio; 


/*************************************************************************
* ��������AudioCreate
* �����ܡ����졢����һ�ο���Ƶ֡������ʵ��¼������
* ���ӿ�˵����
*       ���캯��AudioCreate()����һ���յ���Ƶ֡������������10k�ֽ�  
*       ���캯��AudioCreate(const BYTE* pInBuffer, unsigned int Length)�����ض���Ƶ���ݵ���Ƶ֡
*		��������~AudioCreate()�ͷ�ʹ�õ���Դ�������ٶ���ķ�static���ݳ�Ա
*		�������캯��AudioCreate(const AudioCreate& Frame);
*		��ֵ�����AudioCreate& operator= (const AudioCreate& Frame);
*		��̬����BUF_SZIE����������С���̶�Ϊ10k�ֽ� 
*		��̬�����ṹ��FORMAT���ɼ�/������Ƶ�ĸ�ʽ
*		������ָ��pBuffer�ĳ�����
*		��Ƶͷ�ĳ�����Header
* *************************************************************************/
class  AudioCreate	{
public:
	//���캯��AudioCreate()����һ���յ���Ƶ֡������������10k�ֽ� 
	 AudioCreate();
	 //�����ض���Ƶ���ݵ���Ƶ֡
	 AudioCreate(const BYTE* pInBuffer, unsigned int Length);
	 //��������
	~ AudioCreate();
	//�������캯��
	AudioCreate(const AudioCreate& Frame);
	//��ֵ�����
	AudioCreate& operator= (const AudioCreate& Frame);
	//��̬����BUF_SZIE����������С���̶�Ϊ10k�ֽ�
	static const unsigned int BUF_SZIE;
	//��̬�����ṹ��FORMAT���ɼ�/������Ƶ�ĸ�ʽ
	static const WAVEFORMATEX FORMAT;
	//������ָ��pBuffer�ĳ�����
	BYTE* const& pBuffer;
	//��Ƶͷ�ĳ�����Header(�ڴ��õ���WINDOWS API�����Կ�ͷ������ͷ�ļ�<Windows.h>��
	const WAVEHDR& Header;
private:
	//��Ԫ
	friend class Audio;
	//�ɼ�/������Ƶ�ĸ�ʽ���ṹ��
	WAVEHDR m_Header;
	//��Ƶ������ָ��
	BYTE* m_pBuffer;
};
#endif // AUDIOCREATE_H
