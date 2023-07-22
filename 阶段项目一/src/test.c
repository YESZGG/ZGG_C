// #include <stdio.h>
// #include <stdlib.h>

// typedef struct Image {
//     char* filename[20];
//     struct Image* prev;
//     struct Image* next;
// } Image;

// Image* createImage(char* filename) {
//     Image* image = (Image*)malloc(sizeof(Image));
//     image->filename = filename;
//     image->prev = NULL;
//     image->next = NULL;
//     return image;
// }

// void insertImage(Image** start, Image** end, char* filename) {
//     Image* image = createImage(filename);
//     if (*start == NULL) {
//         *start = image;
//         *end = image;
//         (*start)->next = *start;
//         (*start)->prev = *end;
//     } else {
//         image->prev = *end;
//         image->next = *start;
//         (*end)->next = image;
//         (*start)->prev = image;
//         *end = image;
//     }
// }

// void destroyImageList(Image* start) {
//     if (start == NULL) {
//         return;
//     }
//     Image* current = start;
//     Image* next = start->next;
//     while (next != start) {
//         free(current);
//         current = next;
//         next = next->next;
//     }
//     free(current);
// }

// void displayImage(Image* image) {
//     printf("Displaying %s\n", image->filename);
// }

// void automaticPlay(Image* start, Image* end) {
//     Image* current = start;
//     do {
//         displayImage(current);
//         current = current->next;
//     } while (current != start);
//     destroyImageList(start);
// }

// void manualPlay(Image* start, Image* end) {
//     Image* current = start;
//     char choice = ' ';
//     do {
//         displayImage(current);
//         printf("Press 'l' for next image, 'r' for previous image, or 'q' to quit: ");
//         scanf(" %c", &choice);

//         if (choice == 'l') {
//             current = current->next;
//         } else if (choice == 'r') {
//             current = current->prev;
//         }
//     } while (choice != 'q');
//     destroyImageList(start);
// }

// int main() {
//     Image* start_auto = NULL;
//     Image* end_auto = NULL;
//     insertImage(&start_auto, &end_auto, "1.bmp");
//     insertImage(&start_auto, &end_auto, "3.bmp");
//     insertImage(&start_auto, &end_auto, "5.bmp");

//     Image* start_manual = NULL;
//     Image* end_manual = NULL;
//     insertImage(&start_manual, &end_manual, "1.bmp");
//     insertImage(&start_manual, &end_manual, "3.bmp");
//     insertImage(&start_manual, &end_manual, "5.bmp");

//     // 自动播放功能
//     int x_auto = 100;  // 假设点击区域x坐标为100，y坐标为30
//     int y_auto = 30;
//     if (x_auto > 0 && x_auto < 200 && y_auto > 0 && y_auto < 60) {
//         automaticPlay(start_auto, end_auto);
//     }

//     // 手动播放功能
//     int x_manual = 300;  // 假设点击区域x坐标为300，y坐标为30
//     int y_manual = 30;
//     if (x_manual > 200 && x_manual < 400 && y_manual > 0 && y_manual < 60) {
//         manualPlay(start_manual, end_manual);
//     }

//     return 0;
// }
