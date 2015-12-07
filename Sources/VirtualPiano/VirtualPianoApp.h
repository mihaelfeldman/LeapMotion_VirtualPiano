#pragma once

#include "StaticFingerTip.h"
#include "LeapMotionListener.h"

class VirtualPianoApp : public ci::app::App
{
public:
	VirtualPianoApp();
	void	draw() override;
	void	setup() override;
	void	update() override;
private:
	LeapMotionListener* leapMotionDevice;
	Leap::Frame leapFrame;
	Leap::Frame	currentFrame;
	Leap::Frame	previousFrame;

	ci::CameraPersp	virtualCamera;
	float	leapFrameRate;
	bool	leapFullScreen;

	bool	FINGERS;
	bool	HANDS;

	const Color sphereColor = Color(172.0f / 255.0f, 172.0f / 255.0f, 255.0f / 255.0f);
	const Color yellow = Color(1.0f, 1.0f, 0.0f);
	const vec3 shadowCubeSize;
	const vec3 cubeSize;
	ci::params::InterfaceGlRef	mParams;

	void	updateFingers();
	Piano piano;
	int distansOfCPianoCenter_y;
	int pianoKeyHeight;

	std::map<Leap::Finger::Type, StaticFingerTip> fingerTipRightHand_;
	std::map<Leap::Finger::Type, StaticFingerTip> fingerTipLeftHand_;

	void updateStaticFingerTips(const Leap::Hand& hand, std::map<Leap::Finger::Type, StaticFingerTip>& Tips);
	void updateDynamicFingertips(vector<DinamicFingerTip>& fingerTips, const Leap::Hand& hand); // exstracts finger tips for every incomming frame
	void initializeStaticFingerTips();
	void drawFingerTip(vec3 tipVector);
	
};
