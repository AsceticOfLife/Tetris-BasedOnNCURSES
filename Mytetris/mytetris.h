/*
 * @Author: Guomw
 * @Date: 2023-04-25 15:37:13
 * @LastEditors: Guomw  isguo_mw@163.com
 * @LastEditTime: 2023-09-25 08:48:27
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

class Mytetris final {
private:
    enum MoveDest { NONE, DOWN, LEFT, RIGHT }; // 方块移动方向
    enum { ROW = 20, COL = 10, ChunkTypeNum = 7 }; // 背景板行和列大小
    int board[ROW][COL]; // 二维空间背景板，值表示颜色
    int score; // 得分
    Abr_Chunk *chunk; // 方块
public:
    // 默认构造函数
    Mytetris();
    ~Mytetris() { delete chunk; }
    
    // 初始化屏幕
    void init_frame(); 
    // 将背景板上的颜色内容刷新到屏幕上
    void refresh_frame(); 


    // 在第一行随机创建一个方块
    void new_chunk(); 
    // 使用color颜色修改被方块覆盖的位置的颜色
    // 如果不提供第二个参数则默认为黑色
    void update_board(int color = 0); 
    // 检测方块向某一个方向移动一行是否会发生碰撞
    bool check_hit(MoveDest md);
    // 对背景板上满行进行消除
    void remove_line();
    // 令方块下降一行，如果可以下降就下降一行
    // 如果不能下降说明块已经到了停止的位置
    // 更新方块覆盖的背景板
    // 删除旧方块并创建新的方块
    bool fall_chunk();
    
    // 主循环
    void main_loop();
    // 对外接口
    void Play();
};

#endif 