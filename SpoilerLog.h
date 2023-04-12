#ifndef __SPOILER_LOG_H__
#define __SPOILER_LOG_H__

#include "World.h"
#include "Filler.h"

#define PROGRESSION_LOCATIONS_SIZE 400

using namespace std;
using namespace Filler;

const char* getAreaName(int lairArea);
void createSpoilerLog(WorldMap& theWorld, int progressionLocations[], string& seedText);

#endif // __SPOILER_LOG_H__