#pragma once

#include "Leap.h"
#include "cinder/Channel.h"
#include "cinder/Matrix.h"
#include "cinder/Thread.h"
#include "cinder/Vector.h"
#include <functional>



class LeapMotionListener :	public Leap::Listener
{
public:
	LeapMotionListener();
	~LeapMotionListener();
 ci::vec3 convertToVec3(const Leap::Vector& v);
 void	registerEventHandler(const std::function<void(Leap::Frame)>& eventHandler);

protected:

	virtual void onFrame(const Leap::Controller& controller);
	virtual void update();
	volatile bool newFrame;
	Leap::Controller*	mController;
	std::mutex	leapMutex;
	Leap::Frame	leapFrame;
	std::function<void(Leap::Frame)> mEventHandler;





};

