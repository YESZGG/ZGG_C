#include <iostream>
using namespace std;

class TV;

// 万能遥控
class Remoter
{
public:
    void setTV_channel(TV &tv, int channel);

    void setTV_volume(TV &tv, int volume);

    void LightUp()
    {
    }

    void LightDown()
    {
    }

    void setConditioner(int t)
    {
    }
};

// 设计一台电视机类
class TV
{
public:
    void setcannel(int channel)
    {
        this->channel = channel;
        cout << "设置频道为：" << channel << endl;
    }

    void setvolume(int volume)
    {
        this->volume = volume;
        cout << "设置音量为：" << volume << endl;
    }

private:
    int volume = 0;  // 音量
    int channel = 0; // 频道

    // 声明类的成员函数作为当前 TV 类的友元
    friend void Remoter::setTV_channel(TV &tv, int channel);
    friend void Remoter::setTV_volume(TV &tv, int volume);
};

// 在电视类定义后才定义函数
void Remoter::setTV_channel(TV &tv, int channel)
{
    tv.channel = channel;
    cout << "设置频道为：" << channel << endl;
}

void Remoter::setTV_volume(TV &tv, int volume)
{
    tv.volume = volume;
    cout << "设置音量为：" << volume << endl;
}

int main()
{
    // 定义一台电视对象
    TV tv;

    // 定义万能遥控对象
    Remoter rem;

    // 利用遥控器，控制电视
    rem.setTV_channel(tv, 1);
    rem.setTV_volume(tv, 50);
}