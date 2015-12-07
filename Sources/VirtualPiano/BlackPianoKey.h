#pragma once
#include "PianoKey.h"
class BlackPianoKey :
	public PianoKey
{
public:
	BlackPianoKey(const vec3& _center, const vec3& _size, int _key) :PianoKey( _center, _size, _key){
		color = Color::black();
	};
	~BlackPianoKey();

	 void draw() override;

};


