#include "BlackPianoKey.h"


BlackPianoKey::~BlackPianoKey()
{
}

void BlackPianoKey::draw()
{
//	gl::enableAlphaBlending();
		gl::color(color);
		gl::drawCube(newPianoKeyCenter, size); // full cube

		gl::color(Color::black());
		gl::drawStrokedCube(newPianoKeyCenter, size); // anly the lines of cube

		gl::color(Color::white());
		gl::drawStrokedCube(newPianoKeyCenter, size); // anly the lines of cube
	
}
