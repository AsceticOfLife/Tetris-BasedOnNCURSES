#include "mytetris.h"


Mytetris::Mytetris() {
    for (int y = 0; y < 20; y++) memset(board[y], 0, 10 * sizeof(int));
    // 测试
    // memset(&board[0][0], 1, sizeof(int));
    // memset(&board[1][4], 3, sizeof(int));
    // memset(board[10], 2, 10 * sizeof(int));
    score = 0;
}

/**
 * @description: 初始化屏幕
 * @return {*}
 */
void Mytetris::init_frame() {
    // 种子初始化
    srand(time(0));
    // 屏幕初始化
    initscr();
    noecho();
    raw();
    // 设置屏幕大小以及显示边界
    resize_term(22, 22);
    timeout(0);
    box(stdscr, 0, 0);
    // 颜色初始化
    start_color();
    for (int i = 1; i < 8; i++) {
        init_pair(i, i, 0);
    }
}

/**
 * @description: 创建一个在第一行随机位置的随机状态的块并返回
 * @return {Abr_Chunk *}: 新块指针
 */
Abr_Chunk * Mytetris::new_chunk() {
    // 首先创建一个左上角位置为(0, 0)的块
    int type = rand() % 7;
    int state;
    Abr_Chunk * chunk;
    switch (type) {
    case 0:
        chunk = new O_Chunk(); break;
    case 1:
        state = rand() % 2;
        chunk = new I_Chunk(state); break;
    case 2:
        state = rand() % 2;
        chunk = new S_Chunk(state); break;
    case 3:
        state = rand() % 2;
        chunk = new Z_Chunk(state); break;
    case 4:
        state = rand() % 4;
        chunk = new L_Chunk(state); break;
    case 5:
        state = rand() % 4;
        chunk = new J_Chunk(state); break;
    case 6:
        state = rand() % 4;
        chunk = new T_Chunk(state); break;
    default:
        exit(EXIT_FAILURE);
    }
    // 已经创建一个随机状态的块
    // 下面需要随机第一行出现的位置
    int p = rand() % (COL - chunk->GetWH().GetX());
    chunk->SetPos(Point(p, 0));

    // 随机化这个块的颜色
    chunk->SetColor(rand() % 7 + 1);

    return chunk;
}

/**
 * @description: 检测如果块的左上角位置为(x, y)是否会发生碰撞
 * @param {int} y
 * @param {int} x
 * @return {*}
 */
bool Mytetris::check_hit(Abr_Chunk *chunk, int y, int x) {
    // 判断xy点所在位置是否合法
    if (y >= ROW || x < 0 || x >= COL) return true;
    // 判断是否碰到边界
    int w = chunk->GetWH().GetX();
    int h = chunk->GetWH().GetY();
    if (y + h >= ROW || x + w >= COL) return true;
    // 首先消除在块在当前位置覆盖的背景板的值
    update_board(chunk, 0);
    // 检测如果以当前xy作为块的起点位置是否会覆盖已经有值的背景板
    int temp_x, temp_y; // 每一个正方形的相对于起点的下标
    for (int i = 0; i < 4; i++) {
        temp_x = chunk->GetBlock(i).GetX();
        temp_y = chunk->GetBlock(i).GetY();
        if (board[y + temp_y][x + temp_x] != 0) return true;
    }

    return false;
}

/**
 * @description: 如果存在某一行满，就把这一行删除，并把上面全部下移动
 * @return {*}
 */
void Mytetris::remove_line() {
    int count;
    for (int y = 0; y < ROW; y++) {
        count = 0;
        for (int x = 0; x < COL; x++) {
            if (board[y][x] != 0) count++;
        }

        // 如果这一行全都是非0值则消除行
        if (count == COL) {
            for (int r = y - 1; r >= 0; r--) 
                memcpy(board[r + 1], board[r], COL * sizeof(int));
            memset(board[0], 0, COL * sizeof(int));
            score++;
        } else continue;

    }
}

/**
 * @description: 如果在向下移动就会发生碰撞就消除并返回true，否则下降一行返回false
 * @param {Abr_Chunk} *chunk
 * @return {*}
 */
bool Mytetris::fall_chunk(Abr_Chunk *chunk) {
    // 如果没有发生碰撞就下移动
    if (!check_hit(chunk, chunk->GetPos().GetY() + 1, chunk->GetPos().GetX())) {
        update_board(chunk, 0); // 将当前覆盖背景的值设为0
        // 更新块的起点坐标
        chunk->SetPos(Point(chunk->GetPos().GetX(), chunk->GetPos().GetY() + 1));
        update_board(chunk, chunk->GetColor()); // 设置背景板颜色为块的颜色
        return false;
    } else {
        update_board(chunk, chunk->GetColor());
        // 发生碰撞之后先消除行
        remove_line();
        return true;
    }
}

/**
 * @description: 将块覆盖的背景板的值设置为p
 * @param {Abr_Chunk} &chunk
 * @return {*}
 */
void Mytetris::update_board(Abr_Chunk *chunk, int color) {
    // 获得块的左上角位置
    Point pos = chunk->GetPos();
    int originX = pos.GetX();
    int originY = pos.GetY();

    Point block;
    // 一个块有四个正方形组成
    for (int i = 0; i < 4; i++) {
        block = chunk->GetBlock(i);
        board[originY + block.GetY()][originX + block.GetX()] = color;
    }

}

/**
 * @description: 将board背景板的内容刷新到屏幕上
 * @return {*}
 */
void Mytetris::refresh_frame() {
    for (int y = 0; y < 20; y++) {
        // 移动光标，第0行和第0列是边界线不能写
        move(1 + y, 1);
        for (int x = 0; x < 10; x++) {
            if (board[y][x] != 0) attron(A_REVERSE | board[y][x] << 8);
            printw("  ");
            attroff(A_REVERSE | board[y][x] << 8);
        }
    }

    move(21, 1);
    printw(" score:%d  ", score);
    refresh();
}

/**
 * @description: 主循环运行函数
 * @return {*}
 */
void Mytetris::main_loop() {
    refresh_frame();
    Abr_Chunk *c = new_chunk();
    int tick = 0;


    update_board(c, c->GetColor());
    refresh_frame();

    
    while (!check_hit(c, c->GetPos().GetY() + 1, c->GetPos().GetX()) || c->GetPos().GetY() > 0) {
        usleep(10000);
        if (++tick > 30) {
            tick = 0;
            if (fall_chunk(c)) {
                delete c;
                c = new_chunk();
            };
        }

        // 改变状态
        char ch = getch();
        if (ch == 'q') {
            delete c;
            return ;
        }

        if (ch == 'a') {
            int originX = c->GetPos().GetX();
            int originY = c->GetPos().GetY();
            if (!check_hit(c, originY, originX - 1)) 
                c->SetPos(Point(originX - 1, originY));
        }

        if (ch == 'd') {
            int originX = c->GetPos().GetX();
            int originY = c->GetPos().GetY();
            if (!check_hit(c, originY, originX + 1)) 
                c->SetPos(Point(originX + 1, originY));
        }

        if (ch == 's') {
            while (!fall_chunk(c)) continue;
            delete c;
            c = new_chunk();
        }
        
        if (ch == 'w') {
            update_board(c, 0);
            c->Rotate();
            int originX = c->GetPos().GetX();
            int originY = c->GetPos().GetY();

            while (c->GetPos().GetX() + c->GetWH().GetX() >= COL) 
                c->SetPos(Point(c->GetPos().GetX() - 1, c->GetPos().GetY()));
            
            if (check_hit(c, c->GetPos().GetY(), c->GetPos().GetX())) {
                // 恢复原状
                c->Rerotate();
                c->SetPos(Point(originX, originY));
            }
        }

        update_board(c, c->GetColor());
        refresh_frame();
    }

    update_board(c, c->GetColor());   
    refresh_frame();
    usleep(100000);
    delete c;
}





void Mytetris::Play() {
    init_frame();
    main_loop();
    
    getch();
    endwin();
}


// int Mytetris::main_loop() {
//     new_piece();
//     // 每0.01s检查一次输入和刷新屏幕
//     // 每0.3s下落一格
//     while (碰撞没有发生在第一层) {

//         if (++flag > 30) fall_piece();

//         usleep(10000);  // sleep for 0.01s
//         change_piece(); // 接受输入改变k块状态
//         update_board(); // 更新背景板
//         frame();    // 可视化

//     }
// }