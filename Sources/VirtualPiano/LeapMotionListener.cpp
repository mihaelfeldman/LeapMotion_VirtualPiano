#include "LeapMotionListener.h"

#include "cinder/app/App.h"
#include "LeapMotionListener.h"

using namespace ci;
using namespace ci::app;
using namespace std;


//additional  help sources 
//Snip2Code https://www.snip2code.com/Snippet/518467/Sample-showing-how-to-perform-a-fixed-nu\
//StackOverflow
//cinder forum https://forum.libcinder.org/topic/how-does-timeline-or-any-block-get-access-to-the-update-signal

LeapMotionListener::LeapMotionListener()
{
	newFrame = false;

	mController = new Leap::Controller(*this);

	// this is a colback mechanism to call LeapMotionListener::update authomaticalt before APP update is called 
	App::get()->getSignalUpdate().connect(bind(&LeapMotionListener::update, this)); 

}

LeapMotionListener::~LeapMotionListener()
{
	mController->removeListener(*this);

}

vec3 LeapMotionListener::convertToVec3(const Leap::Vector& v)
{
	return vec3(v.x, v.y, v.z);
}

void LeapMotionListener::onFrame(const Leap::Controller& controller)
{
	lock_guard<mutex> lock(leapMutex);
	if (!newFrame) {
		leapFrame = controller.frame();
		newFrame = true;
	}
}


void LeapMotionListener::registerEventHandler(const function<void(Leap::Frame)>& eventHandler)
{
	mEventHandler = eventHandler;
}

void LeapMotionListener::update()
{
	lock_guard<mutex> lock(leapMutex);
	if (newFrame) {
		mEventHandler(leapFrame);
		newFrame = false;

	}
}

