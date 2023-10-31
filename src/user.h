/**
�����û��������
**/

#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>
#include <vector>
#include "Message.h"
using namespace std;


/*************************************************************************
��������User
�����ܡ����ڲ����û�
���ӿ�˵����
    ����������~User(); 
    �������캯��User(const User& anUser);
    ��ֵ�����User& operator=(const User& anUser);
    ����GetName��������;
    ����ToMessage���û���Ϣ���Ϊһ����Ϣ
    ����TestPassword���ڲ��Ը��������Ƿ�Ϊ�û�����
    ��̬����LoadFromFile���ļ�����һ���û�
    ��̬����SaveToFile��ȫ���û���Ϣ�����ļ�
    ��̬����GetUser(const string& Name, const string& Password)���û������������û�
    ��̬����GetUser(const string& Name)���û��������û�
    ��̬����GetLoginedUser������һ�ε�¼���û�ָ��
    ��̬����OfflineAllStudentsʹ������ѧ���û���������
    ��̬������UserCount��ʾ�û��ܸ���
    ������Type��ʾ�û������ִ�
    *************************************************************************/
class User {
public:
    //����������~User();//2020-05-23 �޸�Ϊ����������
    virtual ~User();//2020-05-23 �޸�Ϊ����������
    //�������캯��User(const User& anUser);
    User(const User& anUser);
    //��ֵ�����User& operator=(const User& anUser);
    User& operator=(const User& anUser);
    //����GetName�����û���;
    string GetName() const;
    //����ToMessage���û���Ϣ���Ϊһ����Ϣ
    Message ToMessage() const;
    //����TestPassword���ڲ��Ը��������Ƿ�Ϊ�û�����
    bool TestPassword(const string& Password) const;
    //��̬����LoadFromFile���ļ�����һ���û�
    static void LoadFromFile(const string& FileName);
    //��̬����SaveToFile��ȫ���û���Ϣ�����ļ�
    static void SaveToFile(const string& FileName);
    //��̬����GetUser(const string& Name, const string& Password)���û������������û�
    static const User* GetUser(const string& Name, const string& Password);
    //��̬����GetUser(const string& Name)���û��������û�
    static const User* GetUser(const string& Name);
    //��̬����GetLoginedUser������һ�ε�¼���û�ָ��
    static User* GetLoginedUser();
    //��̬����OfflineAllStudentsʹ������ѧ���û���������
    static void OfflineAllStudents();

    //6-15�������û���Ϣ������������ʽ
    static bool GetNthUserInfo(unsigned int n, string& Name, string& Password, string& Type);

    //��̬������UserCount��ʾ�û��ܸ���
    static const unsigned int& UserCount;
    //������Type��ʾ�û������ִ�
    const string& Type;
protected:
    //���캯��
    User(const string& Name, const string& Password, const string& Type);
    //���캯��
    User(ifstream& inFile);
    virtual bool AddUser(const string& Name, const string& Password, const string& Type);
    //6-14,ɾ��һ���û�
    virtual bool DeleteUser(const string& Name);
private:
    //���浽�ļ���
    void SaveToFileStream(ofstream& OutFile) const;
    //�û������ܸ���
    static unsigned int m_uUserCount;
    //ȫ���û���ָ������
    static vector<User*> m_UserList;
    //���һ���ӵ�¼���û�ָ��
    static User* m_LoginedUser;
    string m_sName;
    string m_sPassword;
    string m_sType;
};

#endif // USER_H
