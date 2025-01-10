#include <iostream>
#include "Game.h"
#include "MouseEvents.h"
#include <thread>
//#include <windows.h>

int main(int argc, char* argv[])
{
    /*std::thread mouse([] () {
        MouseEvents m;
        m.work();
        });

    mouse.detach();


    while (true) {

    }*/

    MouseEvents mouse;
    mouse.work2();
}