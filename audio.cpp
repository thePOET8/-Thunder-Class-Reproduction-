/*************************************************************************
���ļ�����audio.cpp
������ģ���Ŀ�ġ���Ƶ������
*************************************************************************/


//�ྲ̬��Ա��ʼ������ʾ������Ĭ�ϴ�С10k�ֽ�
const unsigned int AudioFrame::BUF_SZIE = 1024 * 10;

//�ྲ̬��Ա��ʼ������ʾ¼���Ͳ��ŵ���Ƶ��ʽ
//��ע�⣬���ֽṹ����Ϊ��̬��Ա�ĳ�ʼ����ʽ�Ƚ��ټ�����ʼ��Ҫ��.��Ա��
const WAVEFORMATEX AudioFrame::FORMAT = {
    .wFormatTag = WAVE_FORMAT_PCM, //FORMAT.wFormatTag, ������ʽΪPCM
    .nChannels = 1,                //FORMAT.nChannels, ������������1����
    .nSamplesPerSec = 8000,        //FORMAT.nSamplesPerSec, �����ʣ�8000��/��
    .nAvgBytesPerSec = 8000,       //FORMAT.nAvgBytesPerSec, ÿ��������ʣ�����ÿ���ܲɼ������ֽڵ�����
    .nBlockAlign = 1,              //FORMAT.nBlockAlign, һ����Ķ����ֽ���������bit���ֽ�������������
    .wBitsPerSample = 8,           //FORMAT.wBitsPerSample, �������أ�16bits/��
    .cbSize = 0                    //FORMAT.cbSize, һ��Ϊ0
};
