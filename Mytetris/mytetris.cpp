#include "mytetris.h"


Mytetris::Mytetris() {
    // 初始化每一行背景板颜色为0
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
 * @description: 将board背景板的内容刷新到屏幕上
 * @return {*}
 */
void Mytetris::refresh_frame() {
    for (int y = 0; y < 20; y++) {
        // 移动光标，第0行和第0列是边界线不能写
        move(1 + y, 1);
        for (int x = 0; x < 10; x++) {
            if (board[y][x] != 0) attron(A_REVERSE | board[y][x] << 8);
            printw("  "); // 以两个空格作为屏幕上一个方块
            attroff(A_REVERSE | board[y][x] << 8);
        }
    }

    move(21, 1); // 移动光标到最后一行
    printw(" score:%d  ", score);
    refresh(); // 刷新
}

/**
 * @description: 创建一个在第一行随机位置的随机状态的块并返回
 * @return {Abr_Chunk *}: 新块指针
 */
void Mytetris::new_chunk() {
    // 首先创建一个左上角位置为(0, 0)的块
    int type = rand() %  ChunkTypeNum; // 随机选择一个类型的方块
    int state;

    // 根绝type值确定创建的块类型
    switch (type) {
    case 0:
        chunk = new O_Chunk(); break;
    case 1:
        state = rand() % I_Chunk::TypeNum; // 确定块的状态类型
        chunk = new I_Chunk(state); break;
    case 2:
        state = rand() % S_Chunk::TypeNum;
        chunk = new S_Chunk(state); break;
    case 3:
        state = rand() % Z_Chunk::TypeNum;
        chunk = new Z_Chunk(state); break;
    case 4:
        state = rand() % L_Chunk::TypeNum;
        chunk = new L_Chunk(state); break;
    case 5:
        state = rand() % J_Chunk::TypeNum;
        chunk = new J_Chunk(state); break;
    case 6:
        state = rand() % T_Chunk::TypeNum;
        chunk = new T_Chunk(state); break;
    default:
        exit(EXIT_FAILURE);
    }

    // 随机化块在第一行中的位置
    int p = rand() % (COL - chunk->GetWH().GetX());
    chunk->SetPos(Point(p, 0));

    // 随机化这个块的颜色
    // 范围是[1, 8]
    chunk->SetColor(rand() % ChunkTypeNum + 1);
}

/**
 * @description: 修改被方块覆盖的背景板的颜色
 * @param {Abr_Chunk} *chunk: 方块
 * @param {int} color: default 0, 默认设置为黑色
 * @return {*}
 */

void Mytetris::update_board(int color) {
    // 获得块的左上角位置
    Point pos = chunk->GetPos();
    int originX = pos.GetX();
    int originY = pos.GetY();

    Point block;
    // 一个块有四个正方形组成
    for (int i = 0; i < 4; i++) {
        block = chunk->GetBlock(i); // 获取第i个正方形相对于pos的坐标
        board[originY + block.GetY()][originX + block.GetX()] = color;
    }

}

/**
 * @description: 检测如果块的左上角位置为(x, y)是否会发生碰撞
 * @param {int} y
 * @param {int} x
 * @return {*}
 */
bool Mytetris::check_hit(MoveDest md) {
    int y, x; // 表示方块下一步的位置
    switch (md) {
    case NONE:
        y = chunk->GetPos().GetY();
        x = chunk->GetPos().GetX();
        break;
    case DOWN:
        y = chunk->GetPos().GetY() + 1;
        x = chunk->GetPos().GetX();
        break;
    case LEFT:
        y = chunk->GetPos().GetY();
        x = chunk->GetPos().GetX() - 1;
        break;
    case RIGHT:
        y = chunk->GetPos().GetY();
        x = chunk->GetPos().GetX() + 1;
        break;
    default:
        exit(EXIT_FAILURE);
    }

    // 判断xy点所在位置是否合法
    if (y >= ROW || x < 0 || x >= COL) return true;
    // 判断是否碰到边界
    int w = chunk->GetWH().GetX();
    int h = chunk->GetWH().GetY();
    if (y + h >= ROW || x + w >= COL) return true;
    // 首先消除在块在当前位置覆盖的背景板的值
    update_board();
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
    int count; // 统计一行中有颜色的方格数目
    for (int y = 0; y < ROW; y++) {
        count = 0;
        // 遍历每一列统计有颜色方格数目
        for (int x = 0; x < COL; x++) {
            if (board[y][x] != 0) count++;
        }

        // 如果这一行全都是非0值则消除行
        if (count == COL) {
            // 从上一行开始均向下移动一行
            for (int r = y - 1; r >= 0; r--) 
                memcpy(board[r + 1], board[r], COL * sizeof(int));
            memset(board[0], 0, COL * sizeof(int)); // 第一行无颜色
            score++; // 消除一行得一分
        } else continue;

    }
}

/**
 * @description: 如果在向下移动就会发生碰撞就消除并返回true，否则下降一行返回false
 * @param {Abr_Chunk} *chunk
 * @return {*}
 */
bool Mytetris::fall_chunk() {
    // 如果向下移动一行不会发生碰撞就下移动一行
    if (!check_hit(DOWN)) {
        update_board(); // 将当前覆盖背景的值设为0
        // 更新块的起点坐标
        chunk->SetPos(Point(chunk->GetPos().GetX(), chunk->GetPos().GetY() + 1));
        update_board(chunk->GetColor()); // 设置背景板颜色为块的颜色
        return false;
    } else {
        // 向下移动一行会发生碰撞
        // 那么这个方块就停留在这里
        // 更新背景板
        update_board(chunk->GetColor());
        // 尝试消除满行
        remove_line();
        return true;
    }
}


/**
 * @description: 主循环运行函数
 * @return {*}
 */
void Mytetris::main_loop() {
    refresh_frame(); // 根据背景板刷新屏幕
    new_chunk(); // 在第一行随机创建一个方块
    int tick = 0;


    update_board(chunk->GetColor()); // 更新方块覆盖的背景板
    refresh_frame(); // 更新背景板之后就刷新屏幕

    // 方块（在第一行）且（向下移动会发生碰撞）说明游戏应该结束
    while (!check_hit(DOWN) || chunk->GetPos().GetY() > 0) {
        usleep(10000);
        // tick30次才会令方块下降一格
        // 也就是30次循环的时间里都可以改变方块状态
        if (++tick > 30) {
            tick = 0;
            if (fall_chunk() == true) {
                // 方块已经向下移动完成
                delete chunk;
                new_chunk(); // 重新创建一个块
            };
        }

        // 改变状态
        char ch = getch(); // 获取键盘输入
        if (ch == 'q') {
            delete chunk; // 删除块
            return ; // 退出循环
        }

        // 向左移动
        if (ch == 'a') {
            if (!check_hit(LEFT)) 
                chunk->SetPosLeft();
        }

        // 向右移动
        if (ch == 'd') {
            if (!check_hit(RIGHT)) 
                chunk->SetPosRight();
        }

        // 向下移动到不能移动为止
        if (ch == 's') {
            while (!fall_chunk()) continue;
            delete chunk;
            new_chunk(); // 重新创建一个块
        }
        
        // 旋转块
        if (ch == 'w') {
            update_board(); // 清除块当前覆盖位置颜色
            chunk->Rotate(); // 顺时针旋转块，旋转不会改变左上角位置坐标
            int originX = chunk->GetPos().GetX();
            int originY = chunk->GetPos().GetY();

            // 旋转不会改变改变左上角位置坐标
            // 如果旋转之后超出右边界
            // 需要向左移动
            while (chunk->GetPos().GetX() + chunk->GetWH().GetX() >= COL) 
                chunk->SetPosLeft();
            
            // 如果旋转之后的状态会导致发生碰撞
            if (check_hit(NONE)) {
                // 恢复原状
                chunk->Rerotate();
                chunk->SetPos(Point(originX, originY));
            }
        }

        update_board(chunk->GetColor());
        refresh_frame();
    }

    update_board(chunk->GetColor());   
    refresh_frame();
    usleep(2000000);
    
}


void Mytetris::Play() {
    init_frame(); // 初始化屏幕

    main_loop();  // 进入游戏循环
    
    char ch = getch(); // 等待用户输入字符

    endwin(); // 关闭屏幕
}
