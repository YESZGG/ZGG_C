#ifndef IMAGE_H_
#define IMAGE_H_

class IFM
{
public:
    IFM(const char *path = "./");

    char *get_index(int n);
    int get_count();

private:
    char image_path[1024][1024];
    int count = 0;
};

#endif
