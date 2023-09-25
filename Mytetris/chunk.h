/*
 * @Author: Guomw
 * @Date: 2023-04-26 11:19:04
 * @LastEditors: Guomw  isguo_mw@163.com
 * @LastEditTime: 2023-09-22 20:51:53
 * @Description: 俄罗斯方块基本方块类
 */
#ifndef CHUNK_H_
#define CHUNK_H_

// Point类表示二维空间点的坐标
// 以左上角为原点(0, 0)
class Point {
private:
    int x;
    int y;
public:
    // 默认构造函数
    // 初始化(x, y)坐标
    Point(const int a = 0, const int b = 0) : x(a), y(b) {};

    // get方法
    int GetX() const { return x; }
    int GetY() const { return y; }
    //set方法
    void SetX(int a) { x = a; }
    void SetY(int b) { y = b; }
    void Set(int a, int b) { x = a, y = b; }
    // 坐标改动1
    void AddX() { x += 1; }
    void SubX() { x -= 1; }
    void AddY() { y += 1; }
    void SubY() { y -= 1; }
};

// 方块的抽象基类
class Abr_Chunk {
private:
    Point position; // 方块左上角的坐标
    Point WandH; // 方块的宽(X轴)和高(Y轴)，从0开始计数，可以理解为右下角的坐标
    Point blocks[4]; // 每一个方块的坐标，每一个俄罗斯方块都是由4个小方块组成
    int color; // 方块颜色
public:
    // 默认构造函数
    Abr_Chunk() : position(), WandH(), blocks(), color(0) {}
    virtual ~Abr_Chunk() {};

    // get方法
    // 目的是返回成员数据（以引用方式返回自定义类型提高效率），但是不允许修改内容
    const Point& GetPos() const { return position; }
    const Point& GetWH() const { return WandH; }
    const Point& GetBlock(int index) const { return blocks[index]; }
    int GetColor() { return color; }
    // set方法
    void SetPos(const Point &pos) { position = pos; }
    // 块左移一格
    void SetPosLeft() { position.SubX(); }
    // 块右移一格
    void SetPosRight() { position.AddX(); }
    // 块下移一格
    void SetPosDown() { position.SubY(); }
    void SetWH(const Point &p) { WandH = p; }
    void SetBlock(int index, const Point &b) { blocks[index] = b; }
    void SetColor(int c) { color = c; }

    // 留给具体的方块类实现（工厂方法模式）
    virtual void Rotate() = 0;
    virtual void Rerotate() = 0;
};


// O型方块定义
// @@
// @@
class O_Chunk final: public Abr_Chunk {
public:
    // 默认构造函数
    O_Chunk();
    ~O_Chunk() {} // 非virtual析构函数，说明此类不准备作为一个基类
    
    // 旋转函数
    virtual void Rotate();
    virtual void Rerotate();
};

// I型定义
// @@@@
class I_Chunk final: public Abr_Chunk {
private:
    int state; // 范围0~1表示I型块只有两种状态
public:
    enum { TypeNum = 2 }; // 状态个数
    I_Chunk(int s);
    ~I_Chunk() {}

    // 根据成员变量state设置块的坐标信息
    void SetShape();

    virtual void Rotate();
    virtual void Rerotate();
};

// S型定义
//  @@
//@@
class S_Chunk final: public Abr_Chunk {
private:
    int state;
public:
    enum { TypeNum = 2 }; // 状态个数
    S_Chunk(int s);
    ~S_Chunk() {}

    void SetShape();
    virtual void Rotate();
    virtual void Rerotate();
};

// Z型定义
// @@
//  @@
class Z_Chunk final: public Abr_Chunk {
private:
    int state;
public:
    enum { TypeNum = 2 }; // 状态个数
    Z_Chunk(int s);
    ~Z_Chunk() {}

    void SetShape();
    virtual void Rotate();
    virtual void Rerotate();
};

// L型定义
// @
// @
// @@
class L_Chunk final: public Abr_Chunk {
private:
    int state;
public:
    enum { TypeNum = 4 }; // 状态类型个数
    L_Chunk(int s);
    ~L_Chunk() {}

    void SetShape();
    virtual void Rotate();
    virtual void Rerotate();
};

// J型定义
//  @
//  @
// @@
class J_Chunk final: public Abr_Chunk {
private:
    int state;
public:
    enum { TypeNum = 4 }; // 状态类型个数 
    J_Chunk(int s);
    void SetShape();
    virtual void Rotate();
    virtual void Rerotate();
};

// T型定义
// @@@
//  @
class T_Chunk final: public Abr_Chunk {
private:
    int state;
public:
    enum { TypeNum = 4 }; // 状态个数
    T_Chunk(int s);
    ~T_Chunk() {}

    void SetShape();
    virtual void Rotate();
    virtual void Rerotate();
};



#endif
