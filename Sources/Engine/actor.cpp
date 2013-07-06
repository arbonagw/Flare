/**
* This work is distributed under the General Public License,
* see LICENSE for details
*
* @author Gwenna�l ARBONA
**/

#include "Engine/actor.hpp"
#include "Engine/world.hpp"


/*----------------------------------------------
	Constructor & destructor
----------------------------------------------*/

Actor::Actor(World* w, String name)
	: mMesh(NULL)
{
	mNode = w->createWorldNode(name);
}


Actor::Actor(World* w, String name, String file)
{
	mNode = w->createWorldNode(name);
	mMesh = w->createWorldEntity(name, file);
	mNode->attachObject(mMesh);
	mMesh->setCastShadows(true);
}


Actor::Actor(World* w, String name, String file, String material)
{
	mNode = w->createWorldNode(name);
	mMesh = w->createWorldEntity(name, file);
	mNode->attachObject(mMesh);
	mMesh->setCastShadows(true);
	setMaterial(material);
}


Actor::~Actor()
{
}


/*----------------------------------------------
	Methods
----------------------------------------------*/

Vector3 Actor::speed()
{
	return mSpeed;
}


void Actor::attachObject(MovableObject* obj)
{
	mNode->attachObject(obj);
}


void Actor::setLocation(Vector3 newPos)
{
	mNode->setPosition(newPos);
}


void Actor::translate(Vector3 offset, bool bRelative)
{
	mNode->translate(offset[0], offset[1], offset[2], bRelative ? Node::TS_LOCAL : Node::TS_WORLD);
}


void Actor::rotate(Vector3 rotator)
{
	mNode->pitch(Degree(rotator[0]));
	mNode->yaw(Degree(rotator[1]));
	mNode->roll(Degree(rotator[2]));
}


void Actor::setMaterial(String name)
{
	mMesh->setMaterialName(name);
}
