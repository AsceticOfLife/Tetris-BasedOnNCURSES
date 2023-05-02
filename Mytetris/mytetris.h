/*
 * @Author: Guomw
 * @Date: 2023-04-25 15:37:13
 * @LastEditors: Guomw  isguo_mw@163.com
 * @LastEditTime: 2023-04-27 21:51:21
 * @Description: class Mytetris clarification
 */

#ifndef MYTETRIS_H_
#define MYTETRIS_H_
#include "../ncursesw/curses.h"
#include "chunk.h"
#include <string.h> // for memset()
#include <random>   // for srand(), rand()
#include <ctime>    // for time()
#include <unistd.h> // for usleep()

class Mytetris {
private:
    // 背景板大小为20row 10col
    enum {ROW = 20, COL = 10};
    int board[ROW][COL];
    int score;
public:
    Mytetris();
    void init_frame();
    Abr_Chunk * new_chunk();
    bool check_hit(Abr_Chunk *chunk, int y, int x);
    void remove_line();
    bool fall_chunk(Abr_Chunk *chunk);
    void update_board(Abr_Chunk *chunk, int color);
    void refresh_frame();
    void main_loop();
    void Play();
};



#endif 