#pragma once
#include "PianoKey.h"
class WitePianoKey :
	public PianoKey
{
public:
	WitePianoKey(const vec3& _center, const vec3& _size, int _key) :PianoKey(_center, _size, _key){
		color = Color::white();
		size.x = size.x - 1;
	};
	~WitePianoKey();

	void draw() override;
private:

	const Color sideColor = Color(149.0f / 255.0f, 150.0f / 255.0f, 151.0f / 255.0f);
	const Color frontColor = Color(169.0f / 255.0f, 170.0f / 255.0f, 171.0f / 255.0f);
};


