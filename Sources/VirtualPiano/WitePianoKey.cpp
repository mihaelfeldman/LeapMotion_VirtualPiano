#include "WitePianoKey.h"

WitePianoKey::~WitePianoKey()
{
}


void WitePianoKey::draw()
{
		vec3 sizeWiteCube = size - vec3(2, 1, 1);
		gl::color(color); //white color
		gl::drawCube(vec3(newPianoKeyCenter.x, newPianoKeyCenter.y + size.y / 2, newPianoKeyCenter.z), vec3(size.x - 1, 1, size.z)); // draws the surface of a key
		gl::color(sideColor);    // 
		gl::drawCube(vec3(newPianoKeyCenter.x + size.x / 2, newPianoKeyCenter.y, newPianoKeyCenter.z), vec3(1, size.y, size.z));
		gl::drawCube(vec3(newPianoKeyCenter.x - size.x / 2, newPianoKeyCenter.y, newPianoKeyCenter.z), vec3(1, size.y, size.z));
		gl::color(frontColor);
		gl::drawCube(vec3(newPianoKeyCenter.x, newPianoKeyCenter.y, newPianoKeyCenter.z + size.z / 2), vec3(size.x, size.y, 1));

	}
