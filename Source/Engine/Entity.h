
#include "Controller.h"

/*
class Cell
{
    // this is a temp class, for compiling
    int id;
    public:
        Cell() { id = 0; };
        bool operator==(Cell& c) { if (id == c.id) return true; };
};/*

class Entity
{
    private:

        Controller controller;
        vector<Cell> occupiedCells;

    public:

        Entity(Controller);
        ~Entity();
	    void turn();
        Entity move(float, float, bool);
        bool checkCollision( Entity );
        vector<Cell> getCells();
        void onCreate();
        void onDestroy();
        void onUpdate();

        bool operator==(Entity&);
};