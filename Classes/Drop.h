
#ifndef __PINGANY_DROP_H__
#define __PINGANY_DROP_H__

class Drop : public CCSprite
{
public:
    class Listener
    {
	public:
        virtual void onDropBump(Drop*) = 0;
    };
private:
    int water;
    Listener* listener;

    void updateImage();
public:
    Drop(): water(0),
        listener(NULL)
    {}
    bool init(int water, Listener* listener);

    CCRect getRect() { return CocosUtils::getSpriteRect(this); }

    void addWater();
};

#endif
