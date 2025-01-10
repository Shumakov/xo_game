#pragma once
#include <windows.h>
#include <iostream>

class MouseEvents
{

public:
	void work() {
        HWND console_wnd = GetConsoleWindow();
        POINT cursor_pos;

        while (true) {
            if (GetCursorPos(&cursor_pos))
            {
                if (console_wnd && ScreenToClient(console_wnd, &cursor_pos))
                {
                    std::cout << '(' << cursor_pos.x << ", " << cursor_pos.y << ")\n";

                }
            }
        }
	}

    void work2() {
        INPUT_RECORD ir[128];
        HANDLE       hStdInput = NULL;
        HANDLE       hStdOutput = NULL;
        HANDLE       hEvent = NULL;
        DWORD        nRead;
        COORD        xy;

        hStdInput = GetStdHandle(STD_INPUT_HANDLE);
        hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        cls(hStdOutput);
        SetConsoleMode(hStdInput, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
        FlushConsoleInputBuffer(hStdInput);
        hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);                   //Event is created non-signaled (3rd param).
        HANDLE handles[2] = { hEvent, hStdInput };                     //Program loops monitoring two handles.  The
        while (WaitForMultipleObjects(2, handles, FALSE, INFINITE))      //1st handle ( handles(0) ) is an event which
        {                                                            //is initially set to non-signaled.  The 2nd
            ReadConsoleInput(hStdInput, ir, 128, &nRead);                 //handle monitored by WaitForMultipleObjects()
            for (size_t i = 0; i < nRead; i++)                                //is the standard input handle set up to
            {                                                          //allow access to mouse/keyboard input.  As
                switch (ir[i].EventType)                                //long as neither handle is in a signaled
                {                                                      //state, WaitForMultipleObjects() will block
                case KEY_EVENT:                                       //in an efficient wait state.  If any keypress
                    if (ir[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) //or mouse movement occurs, WaitForMultiple
                        SetEvent(hEvent);                                //Objects will return TRUE and the input will
                    else                                                //be read by ReadConsolInput().  If the [ESCAPE]
                    {                                                   //key is pressed the event object represented
                        xy.X = 0; xy.Y = 0;                                   //by hEvent will be set to a signaled state by
                        SetConsoleCursorPosition(hStdOutput, xy);         //the SetEvent() Api function.  This will be
                        printf                                           //picked up by the next WaitForMultipleObjects()
                        (                                                //call, and the function will return FALSE and
                            "AsciiCode = %d: symbol = %c\n",                //execution will drop out of the while loop
                            ir[i].Event.KeyEvent.uChar.AsciiChar,           //and program termination will occur.
                            ir[i].Event.KeyEvent.uChar.AsciiChar            //It is important to note that if the 3rd
                        );                                               //parameter to WaitForMultipleObjects() is
                    }                                                   //set to FALSE, the function will return if
                    break;                                              //either of the handles in the HANDLE array
                case MOUSE_EVENT:                                     //represented by handles is signaled.
                    xy.X = 0, xy.Y = 1;
                    SetConsoleCursorPosition(hStdOutput, xy);
                    printf
                    (
                        "%.3d\t%.3d\t%.3d",
                        ir[i].Event.MouseEvent.dwMousePosition.X,
                        ir[i].Event.MouseEvent.dwMousePosition.Y,
                        (int)ir[i].Event.MouseEvent.dwButtonState & 0x07   //mask out scroll wheel, which screws up//output
                    );
                    break;
                }
            }
        };
    }


    void cls(HANDLE hStdOut)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        COORD coordScreen = { 0,0 };
        DWORD cCharsWritten;
        DWORD dwConSize;

        GetConsoleScreenBufferInfo(hStdOut, &csbi);
        dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
        GetConsoleScreenBufferInfo(hStdOut, &csbi);
        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
        SetConsoleCursorPosition(hStdOut, coordScreen);

        return;
    }

};

