
#ifndef __ACTION_CCMOVEBY_SINGLE_DIRECTION_H__
#define __ACTION_CCMOVEBY_SINGLE_DIRECTION_H__

NS_CC_BEGIN

#include "base_nodes/CCNode.h"
#include "actions/CCActionInterval.h"

/** @brief Moves a CCNode object to the position x,y. x and y are absolute coordinates by modifying it's position attribute.
*/
class /*CC_DLL*/ CCMoveBySingleDirection : public CCMoveBy
{
    int m_direction;
public:
    enum
    {
        DIRECTION_X,
        DIRECTION_Y
    };
    /** initializes the action */
    bool initWithDuration(float duration, float position, int direction);

    virtual void update(float time);
    virtual CCActionInterval* reverse();

public:
    static CCMoveBySingleDirection* create(float duration, float position, int direction);

	// override
	CCObject* copyWithZone(CCZone *pZone);
};

NS_CC_END

#endif