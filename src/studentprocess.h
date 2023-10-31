/*************************************************************************
���ļ�����studentprocess.h
������ģ���Ŀ�ġ�ѧ��ҵ������������
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-12
����Ȩ��Ϣ�������߷�����(fanjingtao@tsinghua.edu.cn)���������κΰ�Ȩ�����κ�ʹ���߿������κ��޸ġ������κ�Ŀ��
�����ļ�¼��
    2020-05-19 �ɷ������޸�Ϊ��QObject�̳У����ź�ʵ�ֽ������
*************************************************************************/
#ifndef STUDENTPROCESS_H
#define STUDENTPROCESS_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QComboBox>
#include <QScrollArea>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <string>
#include "client.h"
#include "Message.h"
#include "audio.h"
#include "user.h"
#include "Constant.h"
using namespace std;

/*************************************************************************
��������StudentProcess
�����ܡ�ѧ���Ͽ�ҵ��������
���ӿ�˵����
    ���캯��StudentProcess
    ��������~StudentProcess
    ����EnterClass����ָ��IP�Ŀ���
    ����ExitClass�˳�����
    ����Send���ʦ�����ı���Ϣ
    ���������ݳ�ԱIsInClass��ʾ�Ƿ����Ͽ�
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-12
�����ļ�¼��
    2020-05-19 �ɷ������޸�Ϊ��QObject�̳У����ź�ʵ�ֽ������
*************************************************************************/
class StudentProcess : public QObject {
    Q_OBJECT
public:
    //���캯��
    explicit StudentProcess(QObject* Parent = nullptr);

    //��������
    ~StudentProcess();

    //���ÿ������캯��
    StudentProcess(const StudentProcess&) = delete;

    //���ø�ֵ�����
    StudentProcess& operator=(const StudentProcess&) = delete;

    //�������
    bool EnterClass(const QString& IP);

    //�˳�����
    bool ExitClass();

    //�����ı���Ϣ����ʦ
    bool Send(const QString& Msg);

    bool SendAnsw(const QString& Answ); //6-17

    bool SendActProp(const QString& ActProp); //6-18

    //�Ƿ����Ͽ�
    const bool& IsInClass;

signals:
    //��������ź�
    void ClassEntered();
    //�˳������ź�
    void ClassExited();

    //6-19
    void RecvSoonExit();

    //�յ�������Ϣ�ź�
    void RecvChat(QString Msg);

    //6-16
    void RecvQues(QString Ques);

    //6-17
    void RecvChoice(QString Ques, QString OptionA, QString OptionB, QString OptionC, QString OptionD);

    //�յ���Ļ������Ϣ�ź�
    void RecvScreen(QImage Img);

private:
    //�Ƿ����Ͽ�
    bool m_bIsInClass;

    //Socket�ͻ��˶���ָ��
    Client* m_pClient;

    //��Ƶ���Ŷ���ָ��
    Audio* m_pVoicePlayer;

    //������Ϣ��������Ϣ���̺߳���
    static DWORD WINAPI MsgReceiveThread(LPVOID lpParameter);
    //���յ�����Ϣ����ִ�е��߳̾��
    HANDLE m_hMsgReceiveThread;
    Message m_RemoteLoginMsg;
};

#endif // STUDENTPROCESS_H
