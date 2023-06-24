/*************************************************************************
【文件名】audio.h
【功能模块和目的】音频类声明
【开发者及日期】范静涛(fanjingtao@tsinghua.edu.cn) 2020-5-5
【版权信息】以下代码来源于对CSDN为博主"_寒潭雁影"2篇原创文章源码的修改和封装
    原版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
    原文连接1：https://blog.csdn.net/oHanTanYanYing/article/details/31155985
    原文连接2：https://blog.csdn.net/oHanTanYanYing/article/details/29943973
    开发者范静涛(fanjingtao@tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2020-05-07 由范静涛做了命名规范化修改
    2020-05-15 由范静涛增加注释
*************************************************************************/


#ifndef AUDIOFRAME_H
#define AUDIOFRAME_H

#include <Windows.h>
//Windows API

#pragma comment(lib, "winmm.lib")