//
//  PlayerBall.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 14/11/16.
//
//

#include "PlayerBall.h"
#include "Game.h"
#include "Ball.h"
USING_NS_CC;

PlayerBall* PlayerBall::create() {
	PlayerBall *sprite = new PlayerBall();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool PlayerBall::init() {
    if (!Sprite::init()) {
        return false;
    }
    // 位置初始化在屏幕中心
    position = Vec2(VisiableSize.width/2, VisiableSize.height/2);
    
    // 初始重量
    weight = minWeight*10;
    // 速度(>=1)
    speed = sqrt(Energy/weight);
    // 半径
    radius = sqrt(weight*5/PI);
    
    // 随机颜色
    color = Color4F(255*CCRANDOM_0_1(), 255*CCRANDOM_0_1(), 255*CCRANDOM_0_1(), 1.0);
    // 随机图片
    // initWithFile("CloseNormal.png");
    // isDraw = false;
    
    // 设置位置
    setPosition(position);
    // drawnode
    drawNode = DrawNode::create();
    this->addChild(drawNode);
    
    // 开启安帧更新
    this->scheduleUpdate();
    // 开启定时器
    this->schedule(schedule_selector(PlayerBall::sharedUpdate), Interval);// 继承自父类的更新
    this->schedule(schedule_selector(PlayerBall::thisUpdate), Interval);
    
    return true;
}

/**
 * 安帧更新
 */
void PlayerBall::update(float time) {}

/**
 * 定时更新
 */
void PlayerBall::thisUpdate(float delta) {
    // 移动
    bool isEage = position.x >= maxW-radius || position.x <= radius-maxW || position.y >= maxH-radius || position.y <= radius-maxH;
    if(!isEage) {
        position += direction*speed;
        setPosition(position);// 本地坐标
    }
    
    // 检测更新player状态
    // RUN_NORMAL -> OVER_MAP
    Vec2 dir = Vec2(direction);
    if(Game::sharedGame()->getState() == RUN_NORMAL) {
        if (position.x >= maxW-ScreenWidth/2) {
            if (dir.x > 0) dir.x = 0;
            Game::sharedGame()->setState(OVER_MAP);
        }
        
        if (position.x <= ScreenWidth/2-maxW) {
            if (dir.x < 0) dir.x = 0;
            Game::sharedGame()->setState(OVER_MAP);
        }
        
        if (position.y >= maxH-ScreenHeight/2) {
            if (dir.y > 0) dir.y = 0;
            Game::sharedGame()->setState(OVER_MAP);
        }
        
        if (position.y <= ScreenHeight/2-maxH) {
            if (dir.y < 0) dir.y = 0;
            Game::sharedGame()->setState(OVER_MAP);
        }
        
    }
    // 屏幕跟随
    Game::sharedGame()->gameLayer->setPosition(Game::sharedGame()->getPosition() - dir*speed);
    
    // OVER_MAP -> RUN_NORMAL
    int curState = Game::sharedGame()->getState();
    bool isOverMap = position.x >= maxW-ScreenWidth/2 || position.x <= ScreenWidth/2-maxW || position.y >= maxH-ScreenHeight/2 || position.y <= ScreenHeight/2-maxH;
    if(curState == OVER_MAP && !isOverMap) {
        Game::sharedGame()->setState(RUN_NORMAL);
    }

}

/**
 * 析构函数
 */
PlayerBall::~PlayerBall() {
}
