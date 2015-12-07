#include "cinder/app/App.h"
#include "cinder/Camera.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "cinder/app/RendererGl.h"
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"
#include "LeapMotionListener.h"
#include "Piano.h"
#include "VirtualPianoApp.h"
#include "DinamicFingerTip.h"

#include <map>

using namespace ci;
using namespace ci::app;
using namespace std;


#include <iostream>
#include <fstream>
#include <string>

using namespace std;


//additional  help sources 
//Snip2Code https://www.snip2code.com/Snippet/518467/Sample-showing-how-to-perform-a-fixed-nu\
//StackOverflow
//cinder forum https://forum.libcinder.org/topic/how-does-timeline-or-any-block-get-access-to-the-update-signal

VirtualPianoApp::VirtualPianoApp() : shadowCubeSize(10, 1, 10), cubeSize(12, 12, 12) {

	initializeStaticFingerTips();
}


void VirtualPianoApp::initializeStaticFingerTips(){

	fingerTipRightHand_.insert(std::pair<Leap::Finger::Type, StaticFingerTip>(Leap::Finger::Type::TYPE_THUMB, StaticFingerTip()));
	fingerTipRightHand_.insert(std::pair<Leap::Finger::Type, StaticFingerTip>(Leap::Finger::Type::TYPE_INDEX, StaticFingerTip()));
	fingerTipRightHand_.insert(std::pair<Leap::Finger::Type, StaticFingerTip>(Leap::Finger::Type::TYPE_MIDDLE, StaticFingerTip()));
	fingerTipRightHand_.insert(std::pair<Leap::Finger::Type, StaticFingerTip>(Leap::Finger::Type::TYPE_RING, StaticFingerTip()));
	fingerTipRightHand_.insert(std::pair<Leap::Finger::Type, StaticFingerTip>(Leap::Finger::Type::TYPE_PINKY, StaticFingerTip()));



	fingerTipLeftHand_.insert(std::pair<Leap::Finger::Type, StaticFingerTip>(Leap::Finger::Type::TYPE_THUMB, StaticFingerTip()));
	fingerTipLeftHand_.insert(std::pair<Leap::Finger::Type, StaticFingerTip>(Leap::Finger::Type::TYPE_INDEX, StaticFingerTip()));
	fingerTipLeftHand_.insert(std::pair<Leap::Finger::Type, StaticFingerTip>(Leap::Finger::Type::TYPE_MIDDLE, StaticFingerTip()));
	fingerTipLeftHand_.insert(std::pair<Leap::Finger::Type, StaticFingerTip>(Leap::Finger::Type::TYPE_RING, StaticFingerTip()));
	fingerTipLeftHand_.insert(std::pair<Leap::Finger::Type, StaticFingerTip>(Leap::Finger::Type::TYPE_PINKY, StaticFingerTip()));


}


// befor a new finger tip positions are calculated, the current ones  are saved 
void VirtualPianoApp::updateStaticFingerTips(const Leap::Hand& hand, std::map<Leap::Finger::Type, StaticFingerTip>& Tips){

	vec3 center;
	Leap::FingerList fingers = hand.fingers();

	for (int i = 0; i < fingers.count(); i++){

		const Leap::Bone& bone = fingers[i].bone((Leap::Bone::Type)3);
		center = leapMotionDevice->convertToVec3(bone.center());
		vec3 direction = leapMotionDevice->convertToVec3(bone.direction());
		vec3 start = center - direction * bone.length() * 0.5f;

		Tips[fingers[i].type()].position = start;
	}
}


void VirtualPianoApp::draw()
{
	gl::viewport(getWindowSize());

//gl::clear(Colorf(113.0 / 255.0, 70.0 / 255.0, 47.0 / 255.0));
gl::clear(Colorf(137.0f / 255.0f, 85.0f / 255.0f, 56.0f / 255.0f));
//	gl::clear(Colorf(219.0 / 255.0, 183.0 / 255.0, 183.0 / 255.0));
	gl::setMatrices(virtualCamera); 

	gl::enableAlphaBlending();
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::color(ColorAf::black());

	vec3 center;

	vector<DinamicFingerTip> rightFingerTipsDynamic;
	vector<DinamicFingerTip> leftFingerTipsDynamic;


	bool t = true;
	//if (leapFrame.isValid())
	{

		const Leap::Hand& leftHand = leapFrame.hands().leftmost();
		const Leap::Hand& rightHand = leapFrame.hands().rightmost();

		if (!HANDS)
			updateDynamicFingertips(leftFingerTipsDynamic, leftHand);
		updateDynamicFingertips(rightFingerTipsDynamic, rightHand);
		
		piano.draw(HANDS,leftFingerTipsDynamic, fingerTipLeftHand_, rightFingerTipsDynamic, fingerTipRightHand_);

		if (!HANDS)
			updateStaticFingerTips(leftHand, fingerTipLeftHand_);  // update finger tip map for a new frame
					
		updateStaticFingerTips(rightHand, fingerTipRightHand_);  // keep previous state of finger tips before a new frame is received
	}

	mParams->draw();
}


// when a new frame is received, this method is used to extract the new position for every finger participatin in the playing 
void  VirtualPianoApp::updateDynamicFingertips(vector<DinamicFingerTip>& fingerTips, const Leap::Hand& hand){

	vec3 distalBoneCenter;
	Leap::FingerList fingers; //= hand.fingers();

	if (FINGERS) // if theis parameter is true only INDEX finger is needed
		fingers.append(hand.fingers().fingerType(Leap::Finger::TYPE_INDEX));
	else
		fingers = hand.fingers();

//	if (FINGERS || fingers.count() == 5 ){
		for (int i = 0; i < fingers.count(); i++)
		{

			const Leap::Bone& distalBone = fingers[i].bone(Leap::Bone::Type::TYPE_DISTAL);
			distalBoneCenter = leapMotionDevice->convertToVec3(distalBone.center());
			vec3 fingerDirection = leapMotionDevice->convertToVec3(distalBone.direction());  // unit lenght
			vec3 tipPosition = distalBoneCenter - fingerDirection * distalBone.length() * 0.5f;

			drawFingerTip(tipPosition);  // computes a current position and draws finger tips


			fingerTips.push_back(DinamicFingerTip(fingers[i].type(), tipPosition));
		}

}

// draws finger tips and the shadow connecting key and tip. this is done to have a betetr visualization feedback
void VirtualPianoApp::drawFingerTip(vec3 tipPosition){

	gl::color(sphereColor);
	//	gl::clear(Colorf(219.0 / 255.0, 183.0 / 255.0, 183.0 / 255.0));
	Color color = Colorf(255.0f / 255.0f, 218.0f / 255.0f, 176.0f / 255.0f);
	gl::color(color);
	gl::drawCube(tipPosition, cubeSize);
	//gl::drawCube(tipPosition, shadowCubeSize);
	int val = distansOfCPianoCenter_y + pianoKeyHeight / 2;
	vec3 shadowCenter(tipPosition.x, val, tipPosition.z);

	// draws finger-piano connecting line. if a finger is abbove a key surface, only the finger is drawn
	if (tipPosition.y > val){ 
		gl::color(0, 0, 0); // black
		gl::drawVector(tipPosition, shadowCenter);

		gl::color(128, 0, 0);  // color = red
		gl::drawCube(shadowCenter, vec3(6, 3, 6));
		gl::color(0, 0, 0);
	}

}



// this method is inherited from cinder
// it is called only once when VirtualPianoApp is created 
void VirtualPianoApp::setup()
{
	virtualCamera = CameraPersp(getWindowWidth(), getWindowHeight(), 60.0f, 1.0f, 500.0f); // set up virtual camera
	virtualCamera.lookAt(vec3(0.0f, 310.0f, 310.0f), vec3(0.0f, 250.0f, 0.0f)); // set up eye point

//	virtualCamera = CameraPersp();
//	virtualCamera.lookAt(vec3(0.0f, 300.0f, 300.0f), vec3(0.0f, 250.0f, 0.0f));
	
	leapMotionDevice = new LeapMotionListener();
	leapMotionDevice->registerEventHandler([&](Leap::Frame frame)
	{
		leapFrame = frame;
	});

	bool k = false;
	leapFrameRate = 0.0f;
	leapFullScreen = false;
	mParams = params::InterfaceGl::create("Params", ivec2(200, 200));
	mParams->addParam("Frame rate", &leapFrameRate, "", true);
	mParams->addParam("Full screen", &leapFullScreen).key("f");
	mParams->addParam("Use One Finger", &FINGERS, "", false);
	mParams->addParam("Use One Hand", &HANDS, "", false);

	mParams->addButton("Quit", [&]() { quit(); }, "key=q");

	distansOfCPianoCenter_y = 170;//120;
	pianoKeyHeight = 20;

}


// is inherited from Cinder
// is called for every frame
void VirtualPianoApp::update()
{
	leapFrameRate = getAverageFps();

	if (leapFullScreen != isFullScreen()) {
		setFullScreen(leapFullScreen);
	}

}

CINDER_APP(VirtualPianoApp, RendererGl, [](App::Settings* settings)
{
	settings->setWindowSize(1024, 768);
	settings->setFrameRate(40.0f);
})
