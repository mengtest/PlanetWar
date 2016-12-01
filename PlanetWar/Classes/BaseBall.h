//
//  BaseBall.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//  球的虚基类，不用于实例化

#ifndef __PlanetWar__BaseBall__ 
#define __PlanetWar__BaseBall__
USING_NS_CC;

class BaseBall : public Sprite {

/** 重写函数 **/
public:
    // 析构函数
    virtual ~BaseBall();

/** 内部变量和函数 **/
protected:
    // 坐标
    Vec2 position = Vec2::ZERO;
    // 半径
    double radius = 0;
    // 颜色
    Color4F color = Color4F::YELLOW;
    // 重量
    int weight = 1;
    // 是否启动图形绘制
    bool isDraw = true;
    // DrawNode
    DrawNode *drawNode = NULL;
    
/** 对外接口 **/
public:
    // getter
    const Vec2 getPos()const{return position;}
    const float getR()const{return radius;}
    const int getBallWeight()const{return weight;}
    const Color4F getBallColor()const{return color;}
    
    // setter
    
    // 缩放
    virtual void scale(const float scale){}
};

#endif /* defined(__PlanetWar__BaseBall__) */
