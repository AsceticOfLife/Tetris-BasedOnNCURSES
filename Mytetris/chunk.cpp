#include "chunk.h"


/**
 * @description: 初始化一个O型块
 * @return {*}
 */
O_Chunk::O_Chunk() : Abr_Chunk() {
    SetWH(Point(1, 1));
    SetBlock(0, Point(0, 0));
    SetBlock(1, Point(0, 1));
    SetBlock(2, Point(1, 0));
    SetBlock(3, Point(1, 1));   
}

void O_Chunk::Rotate() {
    // 由于O型块旋转四种状态是一样的故不做任何操作
}

void O_Chunk::Rerotate() {
    // 同rotate
}


/**
 * @description: 以状态s初始化一个I型块
 * @param {int} s: 0或者1，表示I型只有两种状态
 * @return {*}
 */
I_Chunk::I_Chunk(int s) : Abr_Chunk(), state(s) {
    SetShape();
}

void I_Chunk::SetShape() {
    if (state == 0) {
        // 状态形如
        // 0
        // 0
        // 0
        // 0
        SetWH(Point(0, 3));
        SetBlock(0, Point(0, 0));
        SetBlock(1, Point(0, 1));
        SetBlock(2, Point(0, 2));
        SetBlock(3, Point(0, 3)); 
    } else {
        // 状态形如 0000
        SetWH(Point(3, 0));
        SetBlock(0, Point(0, 0));
        SetBlock(1, Point(1, 0));
        SetBlock(2, Point(2, 0));
        SetBlock(3, Point(3, 0));         
    }
}

void I_Chunk::Rotate() {
    state = (state + 1) % TypeNum;
    SetShape();
}

void I_Chunk::Rerotate() {
    state = (state - 1) % TypeNum;
    SetShape();
}


/**
 * @description: 以状态s初始化一个S型块
 * @param {int} s
 * @return {*}
 */
S_Chunk::S_Chunk(int s) : Abr_Chunk(), state(s) {
    SetShape();
}

void S_Chunk::SetShape() {
    if (state == 0) {
        // @@
        //@@
        SetWH(Point(2, 1));
        SetBlock(0, Point(1, 0));
        SetBlock(1, Point(2, 0));
        SetBlock(2, Point(0, 1));
        SetBlock(3, Point(1, 1));  
    } else {
        // @
        // @@
        //  @
        SetWH(Point(1, 2));
        SetBlock(0, Point(0, 0));
        SetBlock(1, Point(0, 1));
        SetBlock(2, Point(1, 1));
        SetBlock(3, Point(1, 2)); 
    }
}

void S_Chunk::Rotate() {
    state = (state + 1) % TypeNum;
    SetShape();
}

void S_Chunk::Rerotate() {
    state = (state - 1) % TypeNum;
    SetShape();
}


/**
 * @description: 以状态s初始化一个Z型块
 * @param {int} s
 * @return {*}
 */
Z_Chunk::Z_Chunk(int s) : Abr_Chunk(), state(s) {
    SetShape();
}

void Z_Chunk::SetShape() {
    if (state == 0) {
        // @@
        //  @@
        SetWH(Point(2, 1));
        SetBlock(0, Point(0, 0));
        SetBlock(1, Point(1, 0));
        SetBlock(2, Point(1, 1));
        SetBlock(3, Point(2, 1));          
    } else {
        //  @
        // @@
        // @
        SetWH(Point(1, 2));
        SetBlock(0, Point(1, 0));
        SetBlock(1, Point(0, 1));
        SetBlock(2, Point(1, 1));
        SetBlock(3, Point(0, 2));  
    }
}

void Z_Chunk::Rotate() {
    state = (state + 1) % TypeNum;
    SetShape();
}

void Z_Chunk::Rerotate() {
    state = (state - 1) % TypeNum;
    SetShape();
}


/**
 * @description: 以状态s初始化一个L型块
 * @param {int} s
 * @return {*}
 */
L_Chunk::L_Chunk(int s) : Abr_Chunk(), state(s) {
    SetShape();
}

void L_Chunk::SetShape() {
    if (state == 0) {
        // @
        // @
        // @@
        SetWH(Point(1, 2));
        SetBlock(0, Point(0, 0));
        SetBlock(1, Point(0, 1));
        SetBlock(2, Point(0, 2));
        SetBlock(3, Point(1, 2));           
    } else if (state == 1) {
        // @@@
        // @
        SetWH(Point(2, 1));
        SetBlock(0, Point(0, 0));
        SetBlock(1, Point(1, 0));
        SetBlock(2, Point(2, 0));
        SetBlock(3, Point(0, 1));   
    } else if (state == 2) {
        // @@
        //  @
        //  @
        SetWH(Point(1, 2));
        SetBlock(0, Point(0, 0));
        SetBlock(1, Point(1, 0));
        SetBlock(2, Point(1, 1));
        SetBlock(3, Point(1, 2));   
    } else {
        //   @
        // @@@
        SetWH(Point(2, 1));
        SetBlock(0, Point(2, 0));
        SetBlock(1, Point(0, 1));
        SetBlock(2, Point(1, 1));
        SetBlock(3, Point(2, 1));   
    }
}

void L_Chunk::Rotate() {
    state = (state + 1) % TypeNum;
    SetShape();
}

void L_Chunk::Rerotate() {
    state = (state - 1) % TypeNum;
    SetShape();
}

// J型方块构造函数
J_Chunk::J_Chunk(int s) : Abr_Chunk(), state(s) {
    SetShape();
}

void J_Chunk::SetShape() {
    if (state == 0) {
        //  @
        //  @
        // @@
        SetWH(Point(1, 2));
        SetBlock(0, Point(1, 0));
        SetBlock(1, Point(1, 1));
        SetBlock(2, Point(1, 2));
        SetBlock(3, Point(0, 2)); 
    } else if (state == 1) {
        // @
        // @@@
        SetWH(Point(2, 1));
        SetBlock(0, Point(0, 0));
        SetBlock(1, Point(0, 1));
        SetBlock(2, Point(1, 1));
        SetBlock(3, Point(2, 1)); 
    } else if (state == 2) {
        // @@
        // @
        // @
        SetWH(Point(1, 2));
        SetBlock(0, Point(0, 0));
        SetBlock(1, Point(1, 0));
        SetBlock(2, Point(0, 1));
        SetBlock(3, Point(0, 2)); 
    } else {
        // @@@
        //   @
        SetWH(Point(2, 1));
        SetBlock(0, Point(0, 0));
        SetBlock(1, Point(1, 0));
        SetBlock(2, Point(2, 0));
        SetBlock(3, Point(2, 1)); 
    }
}

void J_Chunk::Rotate() {
    state = (state + 1) % TypeNum;
    SetShape();
}

void J_Chunk::Rerotate() {
    state = (state - 1) % TypeNum;
    SetShape();
}

/**
 * @description: 以状态s创建一个T型块
 * @param {int} s
 * @return {*}
 */
T_Chunk::T_Chunk(int s) : state(s) {
    SetShape();
}

void T_Chunk::SetShape() {
    if (state == 0) {
        // @@@
        //  @
        SetWH(Point(2, 1));
        SetBlock(0, Point(0, 0));
        SetBlock(1, Point(1, 0));
        SetBlock(2, Point(2, 0));
        SetBlock(3, Point(1, 1));  
    } else if (state == 1) {
        //  @
        // @@
        //  @
        SetWH(Point(1, 2));
        SetBlock(0, Point(1, 0));
        SetBlock(1, Point(0, 1));
        SetBlock(2, Point(1, 1));
        SetBlock(3, Point(1, 2));
    } else if (state == 3) {
        //  @
        // @@@
        SetWH(Point(2, 1));
        SetBlock(0, Point(1, 0));
        SetBlock(1, Point(0, 1));
        SetBlock(2, Point(1, 1));
        SetBlock(3, Point(2, 1));
    } else {
        // @
        // @@
        // @
        SetWH(Point(1, 2));
        SetBlock(0, Point(0, 0));
        SetBlock(1, Point(0, 1));
        SetBlock(2, Point(1, 1));
        SetBlock(3, Point(0, 2));
    }
}

void T_Chunk::Rotate() {
    state = (state + 1) % TypeNum;
    SetShape();
}

void T_Chunk::Rerotate() {
    state = (state - 1) % TypeNum;
    SetShape();
}
