#include "TrainingDummy.h"
#include "CastAbility.h"

using std::map;
using std::string;
using std::cout;
using std::endl;
using std::cin;

map<Aspect, Ability> aspects;
map<Ability, Status> abilities;

int main()
{
    Aspect first;
    Aspect second;

    initAspects();

    displayAspects(first, second);

    testBed(first, second);

    return 0;
}

void testBed(Aspect first, Aspect second)
{
    TrainingDummy td;
    Ability chosenCast;

    while(cin.good())
    {
        cout << endl;
        cout << "1. " << aspects[first]<< endl;
        cout << "2. " << aspects[second] << endl;
        cin >> chosenCast;

        if(chosenCast == "quit")
        {
            break;
        }

        cout << "Deity casts " << chosenCast << " on the training dummy" << endl;
        td.afflicted(abilities[chosenCast]);
        cout << "Training dummy hit with pointed stick" << endl;
        td.hitTaken();

        cout << endl << td << endl;

        if(td.timeElapsed())
        {
            cout << "Effect ended" << endl;
        }
    }

    cout << "Exited" << endl;
}

void initAspects()
{
    aspects["Life"] = "Heal";
    aspects["Death"] = "Ove_Dam";
    aspects["Augmentor"] = "Inc_Dam";
    aspects["Debilitator"] = "Red_Dam";

    abilities["Heal"] = HEAL;
    abilities["Ove_Dam"] = OVERTIME_DAMAGE;
    abilities["Inc_Dam"] = REDUCE_DAMAGE;
    abilities["Red_Dam"] = INCREASE_DAMAGE;
}

void displayAspects(Aspect& first, Aspect& second)
{
    cout << "Aspects     | Abilities" << endl;
    cout << "=======================" << endl;
    cout << "Life        | Heal Target" << endl;
    cout << "Death       | Damage Over Time" << endl;
    cout << "Augmentor   | Increase Damage Taken" << endl;
    cout << "Debilitator | Decrease Damage Taken" << endl;
    cout << "Choose two Aspects: ";

    cin >> first >> second;

    cout << endl;
}
