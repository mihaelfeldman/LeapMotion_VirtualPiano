#pragma once
#include "cinder/gl/gl.h"
using namespace ci;

class StaticFingerTip
{
public:
	StaticFingerTip(){ position = vec3(0, 0, 0), pianoKeyID = 0; };
	~StaticFingerTip();

	vec3 position;
	int pianoKeyID;
};

