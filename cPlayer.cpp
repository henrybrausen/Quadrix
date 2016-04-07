#include "cPlayer.h"
#include "cSoundManager.h"
#include "cGlobals.h"

double sign(double in) {
	return (in >= 0.0)?(1.0):(-1.0);
}

void cPlayer::on_collide(cSprite *sp)
{
	//this->kill();
	//cSoundManager::play_sound("zap");
	double vX1 = get_x_vel();
	double vY1 = get_y_vel();
	double m1 = 1;
	double vX2 = sp->get_x_vel();
	double vY2 = sp->get_y_vel();
	double m2 = 5;
	set_vel((m2*(vX2-vX1) + m1*vX1 + m2*vX2)/(m1+m2), (m2*(vY2-vY1) + m1*vY1 + m2*vY2)/(m1+m2));
	sp->set_vel((m1*(vX1-vX2) + m1*vX1 + m2*vX2)/(m1+m2), (m1*(vY1-vY2) + m1*vY1 + m2*vY2)/(m1+m2));
}

void cPlayer::myprocess()
{
	if(cKeyStateManager::is_pressed(SDLK_UP)) set_y_accel(-1000);
	else if(cKeyStateManager::is_pressed(SDLK_DOWN)) set_y_accel(1000);
	else set_y_accel(0);
	if(cKeyStateManager::is_pressed(SDLK_LEFT)) set_x_accel(-1000);
	else if(cKeyStateManager::is_pressed(SDLK_RIGHT)) set_x_accel(1000);
	else set_x_accel(0);

	cGlobals::doubles["p1x"] = get_x();
	cGlobals::doubles["p1y"] = get_y();
}
