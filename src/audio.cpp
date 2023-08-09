/*************************************************************************
【文件名】audio.cpp
【功能模块和目的】音频类声明
*************************************************************************/


//类静态成员初始化，表示数据区默认大小10k字节
const unsigned int AudioFrame::BUF_SZIE = 1024 * 10;

//类静态成员初始化，表示录音和播放的音频格式
//请注意，这种结构体作为静态成员的初始化形式比较少见，初始化要加.成员名
const WAVEFORMATEX AudioFrame::FORMAT = {
    .wFormatTag = WAVE_FORMAT_PCM, //FORMAT.wFormatTag, 声音格式为PCM
    .nChannels = 1,                //FORMAT.nChannels, 采样声道数，1声道
    .nSamplesPerSec = 8000,        //FORMAT.nSamplesPerSec, 采样率，8000次/秒
    .nAvgBytesPerSec = 8000,       //FORMAT.nAvgBytesPerSec, 每秒的数据率，就是每秒能采集多少字节的数据
    .nBlockAlign = 1,              //FORMAT.nBlockAlign, 一个块的对齐字节数，采样bit的字节数乘以声道数
    .wBitsPerSample = 8,           //FORMAT.wBitsPerSample, 采样比特，16bits/次
    .cbSize = 0                    //FORMAT.cbSize, 一般为0
};
