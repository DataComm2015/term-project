#ifndef TRAINING_DUMMY_H
#define TRAINING_DUMMY_H

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

// The current status effect on the dummy
enum Status {NONE, HEAL, OVERTIME_DAMAGE, REDUCE_DAMAGE, INCREASE_DAMAGE};

class TrainingDummy
{
    public:
        TrainingDummy();
        void hitTaken();
        void afflicted(Status cast);
        bool timeElapsed();

        friend std::ostream& operator<< (std::ostream &os, const TrainingDummy& td);

    private:
        int health;
        int duration;
        Status effect;

        std::string stringEffect() const;
        std::string stringOutput() const;
};

#endif
