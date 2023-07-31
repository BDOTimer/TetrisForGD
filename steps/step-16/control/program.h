#ifndef PROGRAM_H
#define PROGRAM_H

#include "menu.h"

///----------------------------------------------------------------------------|
/// Program.
///-------------------------------------------------------------------- Program:
struct  Program
{       Program()
        {
            ResurcesHolder::create();
            Menu menu;
            ResurcesHolder::del();
        }

private:

};

#endif // PROGRAM_H
