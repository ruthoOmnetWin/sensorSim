//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <CustomLinearMobility.h>

CustomLinearMobility::CustomLinearMobility()
{
    hasMaxSpeed = false;
    //rand() % 100 = 0-99
    //maxSpeed = 0-20
}

Coord CustomLinearMobility::getCurrentPosition()
{
    return lastPosition;
}

void CustomLinearMobility::initialize(int stage)
{
    LinearMobility::initialize(stage);
    double globalMaxSpeed = par("maxSpeed");
    if (globalMaxSpeed != 0) {
        int x = 100/globalMaxSpeed;
        maxSpeed = (rand() % 100)/x;
    } else {
        maxSpeed = 0;
    }
}

void CustomLinearMobility::move()
{
    //EV << "Position letzte Runde " << lastPosition.x << endl;
    double rad = PI * angle / 180;
    Coord direction(cos(rad), sin(rad));
    lastSpeed = direction * speed;
    double elapsedTime = (simTime() - lastUpdate).dbl();
    lastPosition += lastSpeed * elapsedTime;

    // do something if we reach the wall
    Coord dummy;
    handleIfOutside(REFLECT, dummy, dummy, angle);
    //Coord curr = getCurrentPosition();
    // accelerate
    if (!hasMaxSpeed) {
        double newSpeed = speed;
        newSpeed += acceleration * elapsedTime;
        if (newSpeed > maxSpeed) {
            speed = maxSpeed;
            hasMaxSpeed = true;
        } else {
            speed = newSpeed;
            if (speed <= 0) {
                speed = 0;
                stationary = true;
            }
        }
    }
    EV << maxSpeed << endl;
    EV << " t= " << SIMTIME_STR(simTime()) << " xpos= " << lastPosition.x << " ypos=" << lastPosition.y << " speed=" << speed << endl;
    //EV << "Position diese Runde " << lastPosition.x << endl;
}
