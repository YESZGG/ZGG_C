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