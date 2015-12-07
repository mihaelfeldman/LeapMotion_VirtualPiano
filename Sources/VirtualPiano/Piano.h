#pragma once
#include <iostream>
#include <vector>
#include "PianoKey.h"
#include "DinamicFingerTip.h"
class Piano
{
public:
	Piano();
	~Piano();

	union Data { DWORD dwData; UCHAR bData[4]; }; // specific type
	HMIDIOUT hMidiOut; //sound card

	std::vector<PianoKey*> keys;
	//std::vector<PianoKey*> workingKeys;


	void notaOn(char nota); // start playing sound
	void notaOff(char nota); //stop playing sound
//	void detectCollision( vector<FingerTypeVectorPair>& fingerTips, std::map<Leap::Finger::Type, vec3> fingerTipRightHand);

	//void detectCollision(vector<FingerTypeVectorPair>& fingerTips, std::map<Leap::Finger::Type, PinoKeyFTipRelationship>& fingerOneHand);
	void detectCollision(bool useOneHand, vector<DinamicFingerTip>& fingerTipsLeft, std::map<Leap::Finger::Type, StaticFingerTip>& fingerLeftHand, vector<DinamicFingerTip>& fingerTipsRight, std::map<Leap::Finger::Type, StaticFingerTip>& fingerRightHand);
	int numberOfKeys;
//	void draw(vector<FingerTypeVectorPair>& fingerTips, std::map<Leap::Finger::Type, PinoKeyFTipRelationship>& fingerOneHand_);

	void draw(bool useOneHand, vector<DinamicFingerTip>& fingerTipsLeft, std::map<Leap::Finger::Type, StaticFingerTip>& fingerLeftHand, vector<DinamicFingerTip>& fingerTipsRight, std::map<Leap::Finger::Type, StaticFingerTip>& fingerRightHand);



};

