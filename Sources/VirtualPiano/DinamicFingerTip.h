#pragma once

#include "cinder/app/App.h"
#include "cinder/Camera.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "LeapMotionListener.h"
#include "cinder/app/RendererGl.h"
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"
#include <map>

using namespace ci;
using namespace ci::app;
using namespace std;

class DinamicFingerTip
{
public:
	DinamicFingerTip(Leap::Finger::Type key, vec3 cordinateVector){ this->key = key; this->cordinateVector = cordinateVector; };
	~DinamicFingerTip();
	Leap::Finger::Type key;
	vec3 cordinateVector;
};

