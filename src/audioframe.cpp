/*************************************************************************
���ļ�����audioframe.h
������ģ���Ŀ�ġ���Ƶ������
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-5
����Ȩ��Ϣ�����´�����Դ�ڶ�CSDNΪ����"_��̶��Ӱ"2ƪԭ������Դ����޸ĺͷ�װ����
    �����߷�����(fanjingtao@tsinghua.edu.cn)�����������޸Ĳ��ֵ��κΰ�Ȩ�����κ�ʹ���߿������κ��޸ġ������κ�Ŀ��
    ԭ����ѭ CC 4.0 BY-SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӻͱ�����
    https://blog.csdn.net/oHanTanYanYing/article/details/31155985
    https://blog.csdn.net/oHanTanYanYing/article/details/29943973
    CC BY-SA 4.0 ��һ�����Э�飬����������������ҪȨ����
    һ�������Ȩ��������ͨ���κ�ý����κ���ʽ���ơ�������Ʒ��
    �����ı��Ȩ����������μӹ���ת���ͻ�����Ʒ���д�������������;����������ҵӦ�á�
�����ļ�¼��
    2020-05-07 �ɷ��������������淶���޸ĺ���ṹ�Ż�
    2020-05-15 �ɷ���������ע��
*************************************************************************/
#include "audioframe.h"

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

/*************************************************************************
���������ơ�AudioFrame::AudioFrame
���������ܡ����캯��������һ��ͷ��һ��BUF_SIZE��С�������������߹���
����������
������ֵ�����캯�������з���ֵ
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-5
�����ļ�¼��
    2020-05-07 �ɷ��������������淶���޸�
    2020-05-15 �ɷ���������ע��
*************************************************************************/
AudioFrame::AudioFrame() : pBuffer(m_pBuffer), Header(m_Header) {
    m_pBuffer = new BYTE[BUF_SZIE];

    m_Header.lpData = (LPSTR)m_pBuffer;
    m_Header.dwBufferLength = BUF_SZIE;
    m_Header.dwBytesRecorded = 0L;
    m_Header.dwUser = 0L;
    m_Header.dwFlags = 0L;
    m_Header.dwLoops = 1L;
}

/*************************************************************************
���������ơ�AudioFrame::AudioFrame��const BYTE* pInBuffer, unsigned int Length��
���������ܡ����캯��������һ��ͷ��һ��Legnth��С�������������߹�����������������ݱ����ΪpInBuffer��֪�ռ��������
��������pInBuffer�����������ָ����Ƶ���ݣ�Length�������������ʾ��Ƶ���ݳ���
������ֵ�����캯�������з���ֵ
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-5
�����ļ�¼��
    2020-05-07 �ɷ��������������淶���޸�
    2020-05-15 �ɷ���������ע��
*************************************************************************/
AudioFrame::AudioFrame(const BYTE* pInBuffer, unsigned int Length) : pBuffer(m_pBuffer), Header(m_Header) {
    m_pBuffer = new BYTE[Length];
    memcpy(m_pBuffer, pInBuffer, Length);

    m_Header.lpData = (LPSTR)m_pBuffer;
    m_Header.dwBufferLength = Length;
    m_Header.dwBytesRecorded = Length;
    m_Header.dwUser = 0L;
    m_Header.dwFlags = 0L;
    m_Header.dwLoops = 1L;
}

/*************************************************************************
���������ơ�AudioFrame::AudioFrame��const AudioFrame& Frame��
���������ܡ��������캯�������
��������Frame�������������ʾԴ����
������ֵ�����캯�������з���ֵ
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-5
�����ļ�¼��
    2020-05-07 �ɷ��������������淶���޸�
    2020-05-15 �ɷ���������ע��
*************************************************************************/
AudioFrame::AudioFrame(const AudioFrame& Frame) :pBuffer(m_pBuffer), Header(m_Header) {
    m_Header = Frame.m_Header;
    m_pBuffer = new BYTE[m_Header.dwBufferLength];
    memcpy(m_pBuffer, Frame.m_pBuffer, m_Header.dwBufferLength);
    m_Header.lpData = (LPSTR)m_pBuffer;
}

/*************************************************************************
���������ơ�AudioFrame::operator=
���������ܡ���ֵ��������������
��������Frame�������������ʾԴ����
������ֵ������ֵ���������
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-5
�����ļ�¼��
    2020-05-07 �ɷ��������������淶���޸�
    2020-05-15 �ɷ���������ע��
*************************************************************************/
AudioFrame& AudioFrame::operator= (const AudioFrame& Frame) {
    if (this != &Frame) {
        delete[] m_pBuffer;
        m_Header = Frame.m_Header;
        m_pBuffer = new BYTE[m_Header.dwBufferLength];
        memcpy(m_pBuffer, Frame.m_pBuffer, m_Header.dwBufferLength);
        m_Header.lpData = (LPSTR)m_pBuffer;
    }
    return *this;
}

/*************************************************************************
���������ơ�AudioFrame::~AudioFrame
���������ܡ���������
����������
������ֵ���������������з���ֵ
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-5
�����ļ�¼��
    2020-05-07 �ɷ��������������淶���޸�
    2020-05-15 �ɷ���������ע��
*************************************************************************/
AudioFrame::~AudioFrame() {
    delete[] m_pBuffer;
}
