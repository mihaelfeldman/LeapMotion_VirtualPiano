#include "Piano.h"
#include "WitePianoKey.h"
#include "BlackPianoKey.h"


Piano::Piano()
{

	//initialize all piano keys 
	char vpiano[26] = { 45,47,48, 50, 52, 53, 55, 57, 59, 60, 62, 64, 65, 67, 69, 71, 72,74,76,77,79,81,83,84,86,88};
	char bpiano[18] = { 46,49, 51, 54, 56, 58, 61, 63, 66, 68, 70,73,75,78,80,82,85,87};
	//numberOfKeys = 14;


	midiOutOpen(&hMidiOut, 0, 0, 0, CALLBACK_NULL); // open sound card

	int keyLenght = 150;
	int bkey = 0;
	int wkey = 0;
	int y = 170;
	int z = -80;
	int startX = -240;

	keys.push_back(new WitePianoKey(vec3(startX, y, z), vec3(20, 20, keyLenght), vpiano[wkey++]));
	startX += 10;
	keys.push_back(new BlackPianoKey(vec3(startX, y + 20, z - 30), vec3(12, 15, 100), bpiano[bkey++]));
	startX += 10;
	keys.push_back(new WitePianoKey(vec3(startX, y, z), vec3(20, 20, keyLenght), vpiano[wkey++]));
	startX += 20;

	for (int i = 0; i < 3; i++)
	{
		keys.push_back(new WitePianoKey(vec3(startX, y, z), vec3(20, 20, keyLenght), vpiano[wkey++]));
		startX += 10;
		keys.push_back(new BlackPianoKey(vec3(startX, y + 20, z - 30), vec3(12, 15, 100),  bpiano[bkey++]));
		startX += 10;
		keys.push_back(new WitePianoKey(vec3(startX, y, z), vec3(20, 20, keyLenght), vpiano[wkey++]));
		startX += 10;
		keys.push_back(new BlackPianoKey(vec3(startX, y + 20, z - 30), vec3(12, 15, 100), bpiano[bkey++]));
		startX += 10;
		keys.push_back(new WitePianoKey(vec3(startX, y, z), vec3(20, 20, keyLenght), vpiano[wkey++]));
		startX += 20;
		keys.push_back(new WitePianoKey(vec3(startX, y, z), vec3(20, 20, keyLenght), vpiano[wkey++]));
		startX += 10;
		keys.push_back(new BlackPianoKey(vec3(startX, y + 20, z - 30), vec3(12, 15, 100), bpiano[bkey++]));
		startX += 10;
		keys.push_back(new WitePianoKey(vec3(startX, y, z), vec3(20, 20, keyLenght), vpiano[wkey++]));
		startX += 10;
		keys.push_back(new BlackPianoKey(vec3(startX, y + 20, z - 30), vec3(12, 15, 100),  bpiano[bkey++]));
		startX += 10;
		keys.push_back(new WitePianoKey(vec3(startX, y, z), vec3(20, 20, keyLenght), vpiano[wkey++]));
		startX += 10;
		keys.push_back(new BlackPianoKey(vec3(startX, y + 20, z - 30), vec3(12, 15, 100), bpiano[bkey++]));
		startX += 10;
		keys.push_back(new WitePianoKey(vec3(startX, y, z), vec3(20, 20, keyLenght), vpiano[wkey++]));
		startX += 20;
	}

	keys.push_back(new WitePianoKey(vec3(startX, y, z), vec3(20, 20, keyLenght), vpiano[wkey++]));
	startX += 10;
	keys.push_back(new BlackPianoKey(vec3(startX, y + 20, z - 30), vec3(12, 15, 100), bpiano[bkey++]));
	startX += 10;
	keys.push_back(new WitePianoKey(vec3(startX, y, z), vec3(20, 20, keyLenght), vpiano[wkey++]));
	startX += 10;
	keys.push_back(new BlackPianoKey(vec3(startX, y + 20, z - 30), vec3(12, 15, 100), bpiano[bkey++]));
	startX += 10;
	keys.push_back(new WitePianoKey(vec3(startX, y, z), vec3(20, 20, keyLenght), vpiano[wkey++]));
	startX += 10;
}



Piano::~Piano()
{
}

void Piano::notaOn(char nota)
{
	Data u;
	u.bData[0] = 0x90;
	u.bData[1] = nota;
	u.bData[2] = 127;
	u.bData[3] = 0;
	midiOutShortMsg(hMidiOut, u.dwData);
}

void Piano::notaOff(char nota)
{
	Data u;
	u.bData[0] = 0x80;
	u.bData[1] = nota;
	u.bData[2] = 0;
	u.bData[3] = 0;
	midiOutShortMsg(hMidiOut, u.dwData);

} 

void Piano::draw(bool useOneHand, vector<DinamicFingerTip>& fingerTipsLeft, std::map<Leap::Finger::Type, StaticFingerTip>& fingerLeftHand, vector<DinamicFingerTip>& fingerTipsRight, std::map<Leap::Finger::Type, StaticFingerTip>& fingerRightHand)
{
	detectCollision(useOneHand,fingerTipsLeft, fingerLeftHand, fingerTipsRight, fingerRightHand);
	std::vector<PianoKey*>::iterator it;// = keys.begin();
	for (it = keys.begin(); it != keys.end(); ++it){
		(*it)->draw();
	}
}

void Piano::detectCollision(bool useOneHand, vector<DinamicFingerTip>& fingerTipsLeft, std::map<Leap::Finger::Type, StaticFingerTip>& fingerLeftHand, vector<DinamicFingerTip>& fingerTipsRight, std::map<Leap::Finger::Type, StaticFingerTip>& fingerRightHand){

	std::vector<PianoKey*>::iterator it;// = keys.begin();
	for (it = keys.begin(); it != keys.end(); ++it){
		(*it)->DetectCollision_(useOneHand,fingerTipsLeft, fingerLeftHand, fingerTipsRight, fingerRightHand);
		if ((*it)->coliSionState == true){
			if ((*it)->soundState == false){
				(*it)->soundState = true;
				notaOn((*it)->key);
			}

		}
		else if ((*it)->soundState){
			(*it)->soundState = false;
			notaOff((*it)->key);
		}
	}

}