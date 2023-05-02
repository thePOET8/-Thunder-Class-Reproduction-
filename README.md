
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

在这当中，UI模块目测是最简单的部分，一方面我们对于AI的美观没有要求（先实现功能后面考虑UI），如果有过了解的话，可以利用Qt Designer，通过拖拽方式创建用户界面，甚至无需编写代码。

 然而除此之外的对于我们来说就比较陌生了，存储模块可能涉及到数据库，屏幕获取、UDP传输、以及语音模块都相当陌生。那么我们还是先从语音模块说起吧。


## 语音模块
在学习本项目之前，大部分学生似乎也只是写过一些简单程序，写过一些算法的都极少（当时的学生估计也一样），那么面对语音（声音）可以说是一窍不通。

让我们先了解下声音吧，这里可以听一听
【“雷课堂” 大作业小课堂 - 1】

https://www.bilibili.com/video/BV1rt4y127ak?vd_source=e4f2fda4b9410b91ed51e583b06b125e 
中视频选集2中02：03开始的部分。

以及
【计算机数据存储：音频&视频】

https://www.bilibili.com/video/BV1vD4y1j7rm?vd_source=e4f2fda4b9410b91ed51e583b06b125e

来了解一下计算机音频

或者有一定基础的可以看下这篇博客

 [计算机音频基础-PCM简介](https://www.cnblogs.com/TianFang/p/7894630.html)
 
以及可以使用AI工具辅助讲解和理解。


在了解了计算机是如何对声音进行处理/编程之后，由于我们所需实现的功能以录音为基础，加上获取麦克风录音、控制麦克风（这些都是建立在录音功能上）。我们来实现录音功能。
我们该如何处理我们要用到的声音呢？
众所周知音乐文件有很多种格式：mp3/WAV …… ，这里我们就用WAV格式来处理我们的声音。


（原因：1.WAV格式不复杂  2.目前我找到的资料中都是以WAV的编程为主（咳咳））
[WAV格式介绍](http://soundfile.sapp.org/doc/WaveFormat/)


简单了解WAV格式之后，


我们先来学习几篇博客：

[C++ 采集音频流(PCM裸流)实现录音功能](https://blog.csdn.net/weixinhum/article/details/29943973)

[ C++ 采集音频流(PCM裸流)实现录音功能(双缓存版本) 寒潭雁影的博客-CSDN博客](https://blog.csdn.net/weixinhum/article/details/76158998?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522168294470316800222822643%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fblog.%2522%257D&request_id=168294470316800222822643&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~first_rank_ecpm_v1~rank_v31_ecpm-1-76158998-null-null.blog_rank_default&utm_term=%E5%A3%B0%E9%9F%B3&spm=1018.2226.3001.4450)

[C++ 调节PCM音频音量大小 寒潭雁影的博客-CSDN博客](https://blog.csdn.net/weixinhum/article/details/34864625?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522168294470316800222822643%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fblog.%2522%257D&request_id=168294470316800222822643&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~first_rank_ecpm_v1~rank_v31_ecpm-2-34864625-null-null.blog_rank_default&utm_term=%E5%A3%B0%E9%9F%B3&spm=1018.2226.3001.4450)

[C++ pcm音频裸流的压缩和解码__寒潭雁影的博客-CSDN博客](https://blog.csdn.net/weixinhum/article/details/31133459?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522168294470316800222822643%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fblog.%2522%257D&request_id=168294470316800222822643&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~first_rank_ecpm_v1~rank_v31_ecpm-3-31133459-null-null.blog_rank_default&utm_term=%E5%A3%B0%E9%9F%B3&spm=1018.2226.3001.4450)

（感谢各位前辈啊，跪谢）



## 用户界面和UI（Qt Creater实现）
