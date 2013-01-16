
#include "pch.h"
#include "CCMoveBySingleDirection.h"

NS_CC_BEGIN

CCMoveBySingleDirection* CCMoveBySingleDirection::create(float duration, float position, int direction)
{
    CCMoveBySingleDirection *pMoveBy = new CCMoveBySingleDirection();
    pMoveBy->initWithDuration(duration, position, direction);
    pMoveBy->autorelease();

    return pMoveBy;
}

bool CCMoveBySingleDirection::initWithDuration(float duration, float position, int direction)
{
    CCAssert(direction == DIRECTION_Y || direction == DIRECTION_X,
        "direction must be DIRECTION_X or DIRECTION_Y");
    if (CCMoveBy::initWithDuration(duration,
        direction == DIRECTION_X ? ccp(position, 0) : ccp(0, position)))
    {
        m_direction = direction;
        return true;
    }

    return false;
}

void CCMoveBySingleDirection::update(float time)
{
    if (m_pTarget)
    {
        if (m_direction == DIRECTION_Y)
            m_pTarget->setPositionX(m_startPosition.x + m_delta.x * time);
        else
            m_pTarget->setPositionY(m_startPosition.y + m_delta.y * time);
    }
}

CCActionInterval* CCMoveBySingleDirection::reverse(void)
{
    return CCMoveBySingleDirection::create(m_fDuration,
        -(m_direction == DIRECTION_X ? m_delta.x : m_delta.y), m_direction);
}

CCObject* CCMoveBySingleDirection::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCMoveBySingleDirection* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCMoveBySingleDirection*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCMoveBySingleDirection();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCMoveBy::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, (m_direction == DIRECTION_X ? m_delta.x : m_delta.y), m_direction);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

NS_CC_END