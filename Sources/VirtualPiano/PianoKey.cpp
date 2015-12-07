#include "PianoKey.h"
#include "DinamicFingerTip.h"


PianoKey::~PianoKey()
{
}


// takes the coordinates of every finger tip
// checkes with the position of a key to deteced if the colosion happened 



void PianoKey::DetectCollision_(bool useOneHand, vector<DinamicFingerTip>& fingerTipsLeft, std::map<Leap::Finger::Type, StaticFingerTip>& fingerLeftHand, vector<DinamicFingerTip>& fingerTipsRight, std::map<Leap::Finger::Type, StaticFingerTip>& fingerRightHand)
{

	if (!useOneHand)
	isColite(fingerTipsLeft, fingerLeftHand);
	isColite(fingerTipsRight, fingerRightHand);

if (colite)
	{
		if (tick == 0)  // is not 0 when key starts making sound
		{
			tick = GetTickCount();
			coliSionState = true; // colisi on is detected
		}
	}
	else
	{
		coliSionState = false; // no colision
		tick = 0;
		newPianoKeyCenter = center;
	}  

}


void PianoKey::isColite(vector<DinamicFingerTip>& fingerTips, map<Leap::Finger::Type, StaticFingerTip>& fingerOneHand){

	int fingerSize = fingerTips.size();
	for (int i = 0; i < fingerSize; i++)
	{
		vec3 tip = fingerTips[i].cordinateVector;

		vec3 prevFingerPosition = fingerOneHand[fingerTips[i].key].position;
		int& pianoKeyID = fingerOneHand[fingerTips[i].key].pianoKeyID;

		if (tip.y >= center.y + 15 && pianoKeyID == key){
			colite = false;
			pianoKeyID = 0;
		}
		else{

			if (pianoKeyID == 0 &&
				prevFingerPosition.x >= center.x - size.x / 2 - 1 && prevFingerPosition.x <= center.x + size.x / 2 + 1 &&
				tip.x >= center.x - size.x / 2 - 1 && tip.x <= center.x + size.x / 2 + 1 &&
				prevFingerPosition.y >= center.y + size.y / 2 && tip.y <= center.y + size.y / 2 &&
				prevFingerPosition.z > center.z - size.z / 2 && prevFingerPosition.z < center.z + size.z / 2 &&
				tip.z > center.z - size.z / 2 && tip.z < center.z + size.z / 2)

			{

				pianoKeyID = key;
				colite = true;

				float pushDeep = center.y + size.y / 2 - tip.y;
				if (pushDeep > size.y) // if true, the key can not go down anymore
					newPianoKeyCenter.y = center.y - size.y;
				else // the key stil has some space to go down
					newPianoKeyCenter.y = center.y - pushDeep;

				break;

			}

		}

		if (pianoKeyID == key && tip.y < center.y + size.y / 2)
		{
			float pushDeep = center.y + size.y / 2 - tip.y;
			if (pushDeep > size.y) // if true, the key can not go down anymore
				newPianoKeyCenter.y = center.y - size.y;
			else // the key stil has some space to go down
				newPianoKeyCenter.y = center.y - pushDeep;

			break;

		}
	}

}
