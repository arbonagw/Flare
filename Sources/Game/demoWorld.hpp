/**
* This work is distributed under the General Public License,
* see LICENSE for details
*
* @author Gwenna�l ARBONA
**/

#ifndef __DEMOWORLD_H_
#define __DEMOWORLD_H_

#include "Engine/game.hpp"
#include "Engine/actor.hpp"
#include "Engine/player.hpp"


/*----------------------------------------------
Class definitions
----------------------------------------------*/

class DemoWorld : public Game
{

public:
	
	void construct()
	{
		Actor* act = new Actor(this, "DemoMesh", "Airlock.mesh", "MI_Airlock");
		act->translate(Vector3(0,0,-200));

		
		Plane plane(Vector3::UNIT_Y, 0);
		MeshManager::getSingleton().createPlane("ground", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 512, 512, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
		Entity* entGround = mScene->createEntity("GroundEntity", "ground");
		SceneNode* groundNode = mScene->getRootSceneNode()->createChildSceneNode();
		groundNode->attachObject(entGround);
		groundNode->setPosition(0, -128, 0);
		
		Plane plane2(Vector3::UNIT_Z, 0);
		MeshManager::getSingleton().createPlane("wall", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane2, 512, 512, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
		Entity* entWall = mScene->createEntity("WallEntity", "wall");
		SceneNode* wallNode = mScene->getRootSceneNode()->createChildSceneNode();
		wallNode->attachObject(entWall);
		wallNode->setPosition(0, 0, -128);
		
		Light *light = mScene->createLight("light");
		light->setDiffuseColour(1.0, 1.0, 1.0);
		light->setSpecularColour(1.0, 1.0, 1.0);
		light->setType(Light::LT_POINT);
		light->setAttenuation(500, 0.1, 0.007, 0);
		light->setCastShadows(true);
		
		mPlayer->attachObject(light);
	}

	void destruct(){}
	
};


#endif /* __DEMOWORLD_H_ */
