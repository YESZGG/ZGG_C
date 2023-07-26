编译方法：
    make
清除之前的二进制文件
    make clean

GitHub： https://github.com/YESZGG/ZGG_C.git


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