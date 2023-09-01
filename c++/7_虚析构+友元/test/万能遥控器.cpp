#include <iostream>
#include <cstring>
using namespace std;

class TV; // 前置声明TV类

// 遥控器类
class Remoter
{
public:
    void setChannel(TV &tv, const char *channel);
    void setVolume(TV &tv, int volume);

    void turnOnLight();
    void turnOffLight();
};

void Remoter::turnOnLight()
{
    cout << "打开灯光" << endl;
}
void Remoter::turnOffLight()
{
    cout << "关闭灯光" << endl;
}
// 电视机类
class TV
{
private:
    char channel[10];
    int volume;

public:
    TV(const char *channel = "CCTV-1", const int volume = 0) : volume(volume)
    {
        strcpy(this->channel, channel);
    }

    void setChannel(const char *channel)
    {
        strcpy(this->channel, channel);
        cout << "电视机：设置频道为 " << channel << endl;
    }

    void setVolume(int volume)
    {
        this->volume = volume;
        cout << "电视机：设置音量为 " << volume << endl;
    }

    // 1. 设置为友元类
    // friend class Remoter; // 声明Remoter类为友元类，使其能够访问TV的私有成员

    // 2. 设置为友元类方法
    friend void Remoter::setChannel(TV &tv, const char *channel);
    friend void Remoter::setVolume(TV &tv, int volume);

    // 3. 设置为友元函数
    friend void mute(TV &tv);

    void state();
};

void TV::state()
{
    cout << "你正在看" << channel << endl;
    cout << "当前音量" << volume << endl;
}

void Remoter::setChannel(TV &tv, const char *channel)
{
    strcpy(tv.channel, channel);
    cout << "电视机：设置频道为 " << tv.channel << endl;
}

void Remoter::setVolume(TV &tv, int volume)
{
    tv.volume = volume;
    cout << "电视机：设置音量为 " << tv.volume << endl;
}

void mute(TV &tv)
{
    tv.volume = 0;
    cout << "电视机：禁音" << endl;
}

int main()
{
    Remoter remoter;
    TV tv("CCTV-6", 10);
    tv.state();

    remoter.setChannel(tv, "bilibili");
    remoter.setVolume(tv, 20);
    tv.state();

    mute(tv);
    tv.state();

    return 0;
}
