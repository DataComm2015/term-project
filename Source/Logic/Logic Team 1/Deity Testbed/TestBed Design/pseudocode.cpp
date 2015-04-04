Deity Ability Testbed
=====================
The pseudocode and flow of the Ability Testbed.

Flow
----
Program:    Display aspect choices

User:       Choose two aspects

Program:    Display abilities to use for chosen aspects

User:       Choose ability to cast

Program:    Display ability that was cast
Program:    Start cooldown timer for ability

Pseudocode
----------
map of aspects

function Main ()
{
    Call InitAspects function

    Call DisplayAspects function

    Run TestBed function with chosen aspects
}

function TestBed ()
{
    while user does not quit do
    {
        Display abilities to cast
        Cast user-chosen ability on Training Dummy

        Begin duration timer for ability
        Display cast ability and effect

        if duration on ability ends
        {
            Display status
        }
    }
}

function InitAspects ()
{
    Initialize aspects
    Initialize abilities
}

function DisplayAspects ()
{
    Display aspect choices
    Store user-chosen aspects
}

class TrainingDummy
{
    variables:
        health
        duration
        status effect

    functions:
        function HitTaken ()
        {
            Lower health by attack value
        }

        function Afflicted ()
        {
            Take afflicted status effect
        }

        function TimeElapsed ()
        {
            Check duration timer

            if duration is zero
            {
                Set status effect to NONE

            }
        }
}
