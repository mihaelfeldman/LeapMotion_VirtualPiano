#pragma once

#include "cinder/app/App.h"
#include "cinder/Camera.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "LeapMotionListener.h"
#include "cinder/Objloader.h"

#include <Windows.h>
#include <Mmsystem.h>

#include "cinder/app/RendererGl.h"
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"
#include "DinamicFingerTip.h"
#include "StaticFingerTip.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class PianoKey
{
public:

	PianoKey(const vec3& _center, const vec3& _size, int _key) :
		center(_center), size(_size), newPianoKeyCenter(_center), key(_key), tick(0)
	{
		coliSionState = false;
		soundState = false;
		colite = false;
	}
	~PianoKey();

	//----------------------
	bool coliSionState;
	bool soundState;
	vec3 center; // center of a piano key 
	vec3 size; // size of a key

	Color color; // color could be wite or black
	vec3 newPianoKeyCenter; // position after colition detection with finger

	int tick;
	int key; // interger value of a given piano key that decides sound
	bool colite ;

	virtual void draw() = 0;

	void DetectCollision_(bool useOneHand, vector<DinamicFingerTip>& fingerTipsLeft, std::map<Leap::Finger::Type, StaticFingerTip>& fingerLeftHand, vector<DinamicFingerTip>& fingerTipsRight, std::map<Leap::Finger::Type, StaticFingerTip>& fingerRightHand);
	void isColite(vector<DinamicFingerTip>& fingerTips, map<Leap::Finger::Type, StaticFingerTip>& fingerOneHand);
};

