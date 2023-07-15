arm-linux-gcc move_taiChi.c -o move

rx move
chmod 777 move
./move

关键性代码：
int dx = 1; // 水平方向速度
int dy = 1; // 垂直方向速度
// 更新位置
center_x += dx;
center_y += dy;

// 检测碰撞屏幕边界
if (center_x - radius <= 0 || center_x + radius >= 800)
{
    dx = -dx; // 水平方向取反
}

if (center_y - radius <= 0 || center_y + radius >= 480)
{
    dy = -dy; // 垂直方向取反
}


图形旋转
arm-linux-gcc roate.c -o roate -lm
-lm 链接math.h库

rx roate
chmod 777 roate
./roate


关键代码
int angle = 0;
// 根据旋转角度计算对应位置
double radians = angle * M_PI / 180; // 将角度转换为弧度
int rotate_x = (x - center_x) * cos(radians) - (y - center_y) * sin(radians) + center_x;
int rotate_y = (x - center_x) * sin(radians) + (y - center_y) * cos(radians) + center_y;
// 增加旋转角度
angle += 5; // 每次增加1度
if (angle >= 360)
    angle = 0; // 重置角度为0，重新开始旋转