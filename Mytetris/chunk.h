/*
 * @Author: Guomw
 * @Date: 2023-04-26 11:19:04
 * @LastEditors: Guomw  isguo_mw@163.com
 * @LastEditTime: 2023-04-27 21:49:44
 * @Description: 俄罗斯方块基本方块类
 */
#ifndef CHUNK_H_
#define CHUNK_H_

class Point {
private:
    int x;
    int y;
public:
    Point(int a = 0, int b = 0) : x(a), y(b) {};

    int GetX() const { return x; }
    int GetY() const { return y; }
    void SetX(int a) { x = a; }
    void SetY(int b) { y = b; }
    void Set(int a, int b) { x = a, y = b; }
};


class Abr_Chunk {
private:
    Point position;
    Point WandH;
    Point blocks[4];
    int color;
public:
    virtual ~Abr_Chunk() {};

    Point GetPos() const { return position; }
    Point GetWH() const { return WandH; }
    Point GetBlock(int index) const { return blocks[index]; }
    int GetColor() { return color; }
    void SetPos(Point pos) { position = pos; }
    void SetWH(const Point &p) { WandH = p; }
    void SetBlock(int index, const Point &b) { blocks[index] = b; }
    void SetColor(int c) { color = c; }

    virtual void Rotate() = 0;
    virtual void Rerotate() = 0;
};


// O型定义
// @@
// @@
class O_Chunk : public Abr_Chunk {
public:
    O_Chunk();
    
    virtual void Rotate();
    virtual void Rerotate();
};

// I型定义
// @@@@
class I_Chunk : public Abr_Chunk {
private:
    int state; // 范围0~1表示I型块只有两种状态
public:
    I_Chunk(int s);

    void SetShape();
    virtual void Rotate();
    virtual void Rerotate();
};

// S型定义
//  @@
//@@
class S_Chunk : public Abr_Chunk {
private:
    int state;
public:
    S_Chunk(int s);

    void SetShape();
    virtual void Rotate();
    virtual void Rerotate();
};

// Z型定义
// @@
//  @@
class Z_Chunk : public Abr_Chunk {
private:
    int state;
public:
    Z_Chunk(int s);

    void SetShape();
    virtual void Rotate();
    virtual void Rerotate();
};

// L型定义
// @
// @
// @@
class L_Chunk : public Abr_Chunk {
private:
    int state;
public:
    L_Chunk(int s);

    void SetShape();
    virtual void Rotate();
    virtual void Rerotate();
};

// J型定义
//  @
//  @
// @@
class J_Chunk : public Abr_Chunk {
private:
    int state;
public:
    J_Chunk(int s);
    void SetShape();
    virtual void Rotate();
    virtual void Rerotate();
};

// T型定义
// @@@
//  @
class T_Chunk : public Abr_Chunk {
private:
    int state;
public:
    T_Chunk(int s);

    void SetShape();
    virtual void Rotate();
    virtual void Rerotate();
};



#endif
