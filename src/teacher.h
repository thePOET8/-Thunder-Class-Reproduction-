/*************************************************************************
���ļ�����teacher.h
������ģ���Ŀ�ġ���ʦ������
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-10
����Ȩ��Ϣ�������߷�����(fanjingtao@tsinghua.edu.cn)���������κΰ�Ȩ�����κ�ʹ���߿������κ��޸ġ������κ�Ŀ��
�����ļ�¼��2020-5-15 �ɷ���������ע��
*************************************************************************/
#ifndef TEACHER_H
#define TEACHER_H

#include "user.h"

/*************************************************************************
��������Teacher
�����ܡ���ʦ��
���ӿ�˵����
    ���캯��Teacher(const string& Name, const string& Password);
�������߼����ڡ�������(fanjingtao@tsinghua.edu.cn) 2020-5-10
�����ļ�¼��2020-5-15 �ɷ���������ע��
*************************************************************************/
class Teacher : public User
{
public:
    Teacher(const string& Name, const string& Password);
};

#endif // TEACHER_H