#include "TrainingDummy.h"

using std::ostream;
using std::stringstream;
using std::string;

TrainingDummy::TrainingDummy()
{
    health = 1000;
    duration = 0;
    effect = NONE;
}

void TrainingDummy::hitTaken()
{
    if(effect == REDUCE_DAMAGE)
    {
        health -= 20;
    }
    else if(effect == INCREASE_DAMAGE)
    {
        health -= 70;
    }
    else
    {
        health -= 50;
    }
}

void TrainingDummy::afflicted(Status cast)
{
    effect = cast;
}

bool TrainingDummy::timeElapsed()
{
    if((duration - 1) < 0)
    {
        effect = NONE;
        return true;
    }
    duration--;

    return false;
}

string TrainingDummy::stringEffect() const
{
    switch(effect)
    {
        case NONE:
            return "None";
        break;
        case HEAL:
            return "Heal";
        break;
        case OVERTIME_DAMAGE:
            return "Overtime Damage";
        break;
        case REDUCE_DAMAGE:
            return "Reduce Damage";
        break;
        case INCREASE_DAMAGE:
            return "Increase Damage";
        break;
    }

    return "Unknown";
}

string TrainingDummy::stringOutput() const
{
    stringstream sstr;

    sstr << "\nTraining Dummy Stats";
    sstr << "\n====================";
    sstr << "\nHealth: " << health;
    sstr << "\nEffect: " << stringEffect();
    sstr << "\nDuration: " << duration;
    sstr << "\n";

    return sstr.str();
}

ostream& operator<< (ostream &os, const TrainingDummy& td)
{
    return os << td.stringOutput();
}
