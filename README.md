# -Thunder-Class-Reproduction-
对于当时的网红大作业“雷课堂”的复刻
---------------------------------
 ## 前言
    对于初学者而言，这是一个很好的i+1（笑）锻炼自己的项目，要知道，当时的学生也只是大一而已，而且现在Github上也可以找到其他人对于本项目的复刻，拥有如此充分的学习资料，让难度再次降低。

    初学者看到这样一个庞大的项目，对比之前课上练习的简短的命令行以及类似学生管理系统之类，本项目的要求更高，不过不用担心，稍微加上一些难度才是正确的锻炼之道。



项目要求的pdf文件可以在知乎上的这个问题描述中找到，这里就不放了。
https://www.zhihu.com/question/389457315

## 学前须知
		对于开发者（学习者）需求：
			基本需求：C++基础（因为是给大一自动化专业学生的C++程序设计大作业）
			刚需：学习能力、学习热情、自学能力（对于本项目中的很多功能的实现都是需要这些能力）

## 学习借鉴和资料搜集

【“雷课堂” 大作业小课堂 - 1】
https://www.bilibili.com/video/BV1rt4y127ak?vd_source=e4f2fda4b9410b91ed51e583b06b125e

如何看待清华大学自动化系2020年大一c++大作业是写一个功能更强大的雨课堂（雷课堂）?
https://www.zhihu.com/question/389457315

以及GitHub上也有已经完成的项目以及在进行中的复刻项目可以带来启发

以及ChatGPT和New Bing等AI工具辅助学习

## 项目分析
1. 基本要求
 1.1 用户登录
 1.2 语音设备
 1.3 共享屏幕
 1.4 语音直播
 1.5 随机语音提问
 1.6～1.7 在线做题
  1.8 学生签到
    1.9 注意力
      1.10 上下课
     1.11 进出课堂
       1.12 麦克风管制
   
 2. 系统设计要求
    2.1 系统设计要求
    2.2 private
	2.3 类分离
   2.4 API 封装
    2.5 调库
    


对于初学者来说，对于雷课堂这样功能众多且复杂的项目，一时间会很难下手，从0开始构建，以及各个功能该如何实现，这些都是我们需要考虑的问题，让我们来看看，当时的学生是怎么储备实现这些的知识的：
		
	
  [大作业习题课讲解实录]
  https://www.zhihu.com/question/389457315/answer/1169611271

	1.讲解winsock 的使用
	（从 CSDN 上找到一段能运行的 socket 代码并复制到自己的工程里，然后在把 server 部署在了自己的公网 IP 上（注：清华校园网有公网 IP），并且用清华网盘把客户端传给大家，让大家连到 server 并发送信息）

	2.完善socket程序
	为上次的 socket 程序完成类设计，配置图形界面，以及封装成类。最初的类设计不多说，范老师用他严格的规范要求改了命名、接口、类结构等等（提及了用C++Builder写图形界面)（不过就现在而言更建议学学Qt Creator）

	…………………………

## 我的分析过程
将大致的功能分类，可以得到大概如下分类。

![图片](https://github.com/thePOET8/-Thunder-Class-Reproduction-/blob/main/1682942419057.png)

