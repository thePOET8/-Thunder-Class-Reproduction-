/*************************************************************************
���ļ�����studentprocess.cpp
������ģ���Ŀ�ġ�ѧ��ҵ�������ඨ��
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-12
����Ȩ��Ϣ�������߷�����(fanjingtao@tsinghua.edu.cn)���������κΰ�Ȩ�����κ�ʹ���߿������κ��޸ġ������κ�Ŀ��
�����ļ�¼��
    2020-05-19 �ɷ������޸�Ϊ��QObject�̳У����ź�ʵ�ֽ������
    2020-05-19 �ɷ�������������־���QDebug
*************************************************************************/

#include "studentprocess.h"
#include <windows.h>
#include <QDebug>

/*************************************************************************
���������ơ�StudentProcess::StudentProcess
���������ܡ����캯��
����������ڲ�����������ָ�룬Ĭ��nullptr
������ֵ�����캯�������з���ֵ
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-12
�����ļ�¼��
    2020-05-19 �ɷ�����ɾ������ռ�ָ����������ź�ʵ�ֽ������
    2020-05-19 �ɷ�����������δ��ʼ����Ϣ���մ����߳̾��Ϊnullptr�Ĵ����߼�
*************************************************************************/
StudentProcess::StudentProcess(QObject* Parent) : QObject(Parent), IsInClass(m_bIsInClass)
{
    //׼��һ������Զ�̵�¼����Ϣ�������Լ����û���������
    //GetLoginedUser��ȡ���Ǳ��ص�¼���˻�ָ��
    m_RemoteLoginMsg = User::GetLoginedUser()->ToMessage();
    //��˽�г�Ա�������ؼ�ָ��
    //��ʼ���ڲ�״̬
    m_bIsInClass = false;
    //�½�socket�ͻ���
    m_pClient = new Client();
    //�½���Ƶ���Ŷ���
    m_pVoicePlayer = new Audio();
    //��ʼ����Ϣ���մ����߳̾��Ϊ��
    m_hMsgReceiveThread = nullptr;

    qDebug("SP: Created");
}

/*************************************************************************
���������ơ�StudentProcess::~StudentProcess
���������ܡ���������
����������
������ֵ���������������з���ֵ
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-12
�����ļ�¼��
*************************************************************************/
StudentProcess::~StudentProcess() {
    //�˳�����
    ExitClass();
    //�ͷ�socket�ͻ��˺���Ƶ����
    delete m_pClient;
    m_pClient = nullptr;
    delete m_pVoicePlayer;
    m_pVoicePlayer = nullptr;
    qDebug("SP: Destroyed");
}

/*************************************************************************
���������ơ�StudentProcess::EnterClass
���������ܡ��������
����������ڲ�������ʦ��IP��ַ
������ֵ��true��ʾ��ǰ����״̬���Ƿ��ڿ����
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-12
�����ļ�¼��
    2020-05-19 �ɷ������޸�δ���ź�ʵ�ֽ������
*************************************************************************/
bool StudentProcess::EnterClass(const QString& IP) {
    //����Ѿ�������ã���ִ���κβ���
    if (m_bIsInClass) {
        return m_bIsInClass;
    }

    //�ͻ������ӵ�������
    string IpStr = IP.toStdString();
    m_pClient->ConnectTo(IpStr, PORTNUM);

    //��ʼ��ʱ
    qDebug() << "SP: trying to connect to server @ " << QString::fromStdString(IpStr);

    DWORD BeginTime = GetTickCount();
    DWORD EndTime = BeginTime;
    do {
        //���µ�ǰʱ��
        EndTime = GetTickCount();

        //6-18������һС��ʱ�䣬��ֹ�ܱ��ˣ��������ֺ�ͬ־�Ľ���
        Sleep(SLEEPINWAITMS);

        //30����δ���ӣ������ѭ��,6-18��Ϊ10��,6-19�ָĻ�����
    } while (EndTime - BeginTime <= WAITFORCONNMS && !m_pClient->IsConnected);

    //����ʧ�ܣ�����
    if (!m_pClient->IsConnected) {
        qDebug() << "SP: connect fail after " << EndTime - BeginTime << " ms";
        //�������˳������źš�
        emit ClassExited();
        return false;
    }

    //����Ϊ�Խ������״̬
    m_bIsInClass = true;
    //��������������źš�
    qDebug() << "SP: connected after " << EndTime - BeginTime << " ms";
    emit ClassEntered();
    //������Ϣ���պʹ����߳�
    m_hMsgReceiveThread = CreateThread(nullptr, 0, MsgReceiveThread, (LPVOID)this, 0, nullptr);
    if (m_hMsgReceiveThread == nullptr) {
        qDebug() << "SP: failed to create a MessageRecv&Process thread!";
        throw(runtime_error("Failed to create a MessageRecv&Process thread!"));
    }
    //��һʱ�����ʦ�˷��͵�¼�õ��û���������Ϣ
    qDebug() << "SP: send ID & Password";
    m_pClient->Send(m_RemoteLoginMsg);
    //��ʼ��������(����ӽ�ʦ���յ���)
    m_pVoicePlayer->StartPlay();

    return m_bIsInClass;
}

/*************************************************************************
���������ơ�StudentProcess::ExitClass
���������ܡ��˳�����
����������
������ֵ��true��ʾ��ǰ����״̬���Ƿ��ڿ����
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-12
�����ļ�¼��
    2020-05-19 �ɷ������޸�δ���ź�ʵ�ֽ������
*************************************************************************/
bool StudentProcess::ExitClass() {
    //���δ�ڿ����У�����Ƿ���Ϣ���մ����߳������˳���
    if (!m_bIsInClass) {
        if (m_hMsgReceiveThread != nullptr) {
            qDebug() << "SP: clean MsgRecv&Process thread handle";
            CloseHandle(m_hMsgReceiveThread);
            m_hMsgReceiveThread = nullptr;
        }
        return m_bIsInClass;
    }

    //�Ͽ������������
    m_pClient->DisConnect();
    //ֹͣ������Ƶ
    m_pVoicePlayer->StopPlay();
    //��մ�������Ƶ����
    m_pVoicePlayer->Clear();
    //����Ϊδ�Ͽ�״̬
    m_bIsInClass = false;
    //�ȴ���Ϣ���պʹ����߳̽���
    qDebug() << "SP: wait MsgRecv&Process thread end";
    WaitForSingleObject(m_hMsgReceiveThread, WAITMS);
    //�����߳̾��
    qDebug() << "SP: clean MsgRecv&Process thread handle";
    CloseHandle(m_hMsgReceiveThread);
    m_hMsgReceiveThread = nullptr;
    //�������˳������źš�
    emit ClassExited();
    //���ص�ǰ�Ƿ��ڿ�����
    return m_bIsInClass;
}

/*************************************************************************
���������ơ�StudentProcess::Send
���������ܡ����ʦ�˷���������Ϣ
����������ڲ�����QString�ַ���
������ֵ��true��ʾ��ǰ����״̬���Ƿ��ڿ����
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-12
�����ļ�¼��
*************************************************************************/
bool StudentProcess::Send(const QString& Msg) {
    //���ڿ���
    if (!m_bIsInClass) {
        return m_bIsInClass;
    }
    //δ���ӽ�ʦ��
    if (!m_pClient->IsConnected) {
        return m_pClient->IsConnected;
    }
    //װ����ʽ������
    qDebug() << "SP: send Message: " << Msg;
    string MsgStr = Msg.toStdString();
    return m_pClient->Send(Message::FromString(MsgStr));
}

//6-17
//���ʹ���Ϣ
/*************************************************************************
���������ơ�StudentProcess::SendAnsw
���������ܡ����ʦ�˷��ʹ���Ϣ
����������ڲ�����QString�ַ���
������ֵ��true��ʾ��ǰ����״̬���Ƿ��ڿ����
�������߼����ڡ���չ�� 2020-6-17
�����ļ�¼��2020-6-21���ע��
*************************************************************************/
bool StudentProcess::SendAnsw(const QString& Answ) {
    //���ڿ���
    if (!m_bIsInClass) {
        return m_bIsInClass;
    }
    //δ���ӽ�ʦ��
    if (!m_pClient->IsConnected) {
        return m_pClient->IsConnected;
    }
    //װ����ʽ������
    qDebug() << "SP: send Answer: " << Answ;
    string AnswStr = Answ.toStdString();
    return m_pClient->Send(Message::FromAnsw(AnswStr));
}

//6-17
//����ע������Ϣ
/*************************************************************************
���������ơ�StudentProcess::SendAnsw
���������ܡ����ʦ�˷���ע������Ϣ
����������ڲ�����QString�ַ���
������ֵ��true��ʾ��ǰ����״̬���Ƿ��ڿ����
�������߼����ڡ���չ�� 2020-6-17
�����ļ�¼��2020-6-21���ע��
*************************************************************************/
bool StudentProcess::SendActProp(const QString& ActProp) {
    //���ڿ���
    if (!m_bIsInClass) {
        return m_bIsInClass;
    }
    //δ���ӽ�ʦ��
    if (!m_pClient->IsConnected) {
        return m_pClient->IsConnected;
    }
    //װ����ʽ������
    qDebug() << "SP: send Active Proportion: " << ActProp;
    string ActPropStr = ActProp.toStdString();
    return m_pClient->Send(Message::FromActProp(ActPropStr));
}

/*************************************************************************
���������ơ�StudentProcess::MsgRecieveThread
���������ܡ����ղ�������Ϣ���̺߳���
����������ڲ�������ʾ�߳�������StudentProcess����ָ��
������ֵ��������
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-12
�����ļ�¼��
    2020-05-19 �ɷ������޸�δ���ź�ʵ�ֽ������
    2020-05-19 �ɷ�����������jpg�ռ�δ�ͷŵĴ����߼�
*************************************************************************/
DWORD WINAPI StudentProcess::MsgReceiveThread(LPVOID lpParameter) {
    //��Ϊʵ����StudentProcess*�����Կ���ǿ������װ��
    StudentProcess* pProcess = (StudentProcess*)lpParameter;
    //���ڽ��յ���ʱ��Ϣ�洢����
    Message TempMessage;
    //���յ�����Ϣ������
    MessageType Type;
    //�ڿ�����ͨ���У�ʼ��ִ��ѭ��
    while (pProcess->IsInClass && pProcess->m_pClient->IsConnected) {
        //�д�������Ϣ�������TempMessage��
        if (pProcess->m_pClient->GetAndRemoveFirstRecvMsg(TempMessage)) {
            //�����Ϣ����
            Type = TempMessage.Type();
            //������ı���Ϣ��Ϣ��ת����Ϊ�����󣬷����ź�Ҫ��������
            if (Type == MSG_STRING) {
                qDebug() << "SP: recieved chat message: " << QString::fromStdString(Message::ToString(TempMessage));
                emit pProcess->RecvChat(QString::fromStdString(Message::ToString(TempMessage)));
            }
            else if (Type == MSG_QUES)       //6-16��ӣ������������Ϣ��ת�����ı����󣬷����ź�
            {
                qDebug() << "SP: recieved question message: " << QString::fromStdString(Message::ToString(TempMessage));
                emit pProcess->RecvQues(QString::fromStdString(Message::ToString(TempMessage)));
            }
            else if (Type == MSG_CHOICE)    //6-17��ӣ������ѡ������Ϣ��ת�����ı����󣬷����ź�
            {
                string Ques;
                string OptionA;
                string OptionB;
                string OptionC;
                string OptionD;

                Message::ToChoice(TempMessage, Ques, OptionA, OptionB, OptionC, OptionD);

                emit pProcess->RecvChoice(QString::fromStdString(Ques), QString::fromStdString(OptionA), QString::fromStdString(OptionB), QString::fromStdString(OptionC), QString::fromStdString(OptionD));
            }

            //�������Ƶ֡��Ϣ�������������Ƶ������
            else if (Type == MSG_AUDIO) {
                qDebug() << "SP: recieved audio frame message " << TempMessage.Size << " bytes";
                pProcess->m_pVoicePlayer->AppendFrameToPlay(Message::ToAudioFrame(TempMessage));
            }
            //�����Jpgͼ����Ϣ�������ˢ��������
            else if (Type == MSG_JPG) {
                char* pJpgData = nullptr;
                unsigned int JpgSize = 0;
                Message::ToJpgData(TempMessage, &pJpgData, &JpgSize);
                QImage qImg;
                qImg.loadFromData((unsigned char*)pJpgData, JpgSize, "jpg");
                qDebug() << "SP: recieved jpg message " << JpgSize << " bytes";
                //2020-05-19 �������߼���֮ǰû���ͷſ��ٵĿռ�
                delete[] pJpgData;
                //�����յ�ͼ���źţ�Ҫ��������
                emit pProcess->RecvScreen(qImg);
            }
            //6-19������Ǽ����¿ε���Ϣ�����ͷ���ע������Ϣ���ź�
            else if (Type == MSG_SOONEXIT)
            {
                emit pProcess->RecvSoonExit();
            }
            //������˳���Ϣ��������Ϣ���մ���ѭ�����൱�˳�����
            else if (Type == MSG_EXIT) {
                pProcess->m_bIsInClass = false;
                qDebug() << "SP: disconnected socket";
                //�����˳������ź�
                emit pProcess->ClassExited();
                break;
            }
        }
    }
    return 0;
}
