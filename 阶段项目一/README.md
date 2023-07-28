编译方法：
    make
清除之前的二进制文件
    make clean

GitHub： https://github.com/YESZGG/ZGG_C.git

------------------------------------------------------------------------------
智能家居（假的） ------ 基于粤嵌GEC6818开发板的各种小功能

显示了开机动画之后显示desktop.bmp 桌面

点击  x > 0 && x < 200 && y > 0 && y < 60
实现自动播放功能    √
1.bmp格式3张（1.bmp,3.bmp,5.bmp）
2.jpg格式3张(2.jpg,3.jpg,6.jpg)
3.bmp图片实现百叶窗、左进、右进等三种效果
4.所有的图片要用：双向循环链表来存储
5.循环播放后自动结束

点击 x > 200 && x < 400 && y > 0 && y < 60
实现手动播放功能    √
1.bmp格式3张（1.bmp,3.bmp,5.bmp)
2.jpg格式3张(2.jpg,4jpg,6.jpg)
3.所有的图片要用：双向循环链表来存储（图片的存储顺序为1.bmp,2.jpg,3.bmp,4jpg,5.bmp,6.jpg）
4.向右滑动显示上一张，向左滑动显示下一张

其中，自动播放功能和手动播放功能的存储图片所用的结构体是相同的


MP3功能     √
处于主菜单界面时， 点击 x > 0 && x < 200 && y > 420 && y < 480
跳转到MP3界面,显示MP3_start.bmp
在MP3界面中，点击 x > 200 && x < 400 && y > 420 &&  y < 480,播放MP3
播放：system("madplay 1.mp3 &"); 
播放成功，同时更换MP3界面，显示MP3_stop.bmp
再次点击 x > 200 && x < 400 && y > 420 &&  y < 480,赞同播放MP3
暂停：system("killall -SIGSTOP madplay");
暂停成功，同时更换MP3界面，显示MP3_start.bmp
再次点击 x > 200 && x < 400 && y > 420 &&  y < 480,继续播放当首MP3
播放成功，同时更换MP3界面，显示MP3_stop.bmp

可以下载歌曲的方法:
http://music.163.com/song/media/outer/url?id=1824020871.mp3

将下方的id= xxxx  复制 更换到上面的id 再打开新页面链接

https://music.163.com/song?id=1917549208&userid=537429233
https://music.163.com/song?id=2036445126&userid=537429233
https://music.163.com/song?id=1824020871&userid=537429233

开灯功能    √
处于主菜单界面时，点击 x > 200 && x < 400 && y > 420 && y < 480
小灯依次打开,每个小灯亮灯之间有0.05秒延迟

关灯功能    √
处于主菜单界面时，点击 x > 400 && x < 600 && y > 420 && y < 480
小灯依次灭灯,每个小灯灭灯之间有0.05秒延迟

------------------------------------------------------------------------------


工程目录：
.
├── admin    // 管理员信息
│   ├── 1.txt
│   ├── 2.txt
│   └── 3.txt
├── bin      // 二进制可执行程序
│   └── main
├── image    // 图片素材
│   ├── 1.bmp
│   ├── 2.jpg
│   ├── 3.bmp
│   ├── 4.jpg
│   ├── 5.bmp
│   ├── 6.jpg
│   ├── 7.bmp
│   ├── 8.bmp
│   ├── 9.bmp
│   ├── Admin.bmp
│   ├── Angelababy.bmp
│   ├── Auto_play.bmp
│   ├── desktop.bmp
│   ├── Exit.bmp
│   ├── kun.bmp
│   ├── Manual_play.bmp
│   ├── MP3_continue.bmp
│   ├── MP3_start.bmp
│   ├── MP3_stop.bmp
│   ├── start1.bmp
│   ├── start2.bmp
│   ├── start3.bmp
│   └── zhangsan.bmp
├── include     // 头文件
│   ├── admin.h       // 管理员头文件
│   ├── autoplay.h    // 自动播放头文件
│   ├── font.h        // 字库头文件
│   ├── lcdjpg.h      // jpg头文件
│   ├── led_control.h
│   ├── linkedlist.h
│   ├── menu.h
│   ├── mp3.h
│   ├── open_file.h
│   └── slideshow.h
├── led         // 小灯驱动程序
│   └── led.ko
├── lib         // 字库
│   ├── font
│   └── libfont.a
├── libjpeg     // JPG库
│   ├── jconfig.h
│   ├── jerror.h
│   ├── jmorecfg.h
│   ├── jpeglib.h
│   ├── libjpeg.a
│   ├── libjpeg.la
│   ├── libjpeg.so
│   ├── libjpeg.so.9
│   └── libjpeg.so.9.1.0
├── main        // 主程序
│   └── main.c
├── makefile    // Makefile文件
├── mp3         // MP3
│   ├── 都落ち.mp3
│   └── Love_Story.mp3
├── README.md
└── src         // .c编译
    ├── admin.c      // 管理员
    ├── autoplay.c   // 自动播放
    ├── lcdjpg.c     // jpg 进行修改过添加使jpg居中显示
    ├── led.c        // 小灯控制
    ├── linkedlist.c // 图片结构体
    ├── menu.c       // 界面跳转
    ├── mp3.c        // MP3播放、暂停、继续、结束
    ├── open_file.c  // open fd_lcd
    └── slideshow.c  // 手动播放

10 directories, 64 files

------------------------------------------------------------------------------

