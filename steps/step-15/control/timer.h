#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <chrono>

///---------|
/// my lib  |
///---------:
namespace myl
{
    using namespace std::chrono;

    ///------------------------------------------------------------------------|
    /// TimerBase.
    ///-------------------------------------------------------------- TimerBase:
    struct      TimerBase{
    protected:  TimerBase(double s) :   beg   (high_resolution_clock::now()),
                                        period(s)
                {}

        void start(double s)
        {    beg    = high_resolution_clock::now();
             period = s;
        }

        bool is_ready()
        {   auto duration =  double(duration_cast<milliseconds>
                            (high_resolution_clock::now() - beg).count())/1000;

            bool   b      = duration > period;
            if    (b) beg = high_resolution_clock::now();
            return b;
        }

        void set_period(double per)
        {   period = per;
        }

        time_point<std::chrono::high_resolution_clock> beg;
        double                                      period;
    };

    ///------------------------------------------------------------------------|
    /// TimerGame.
    ///-------------------------------------------------------------- TimerGame:
    struct  TimerGame : protected TimerBase
    {       TimerGame(double s) : TimerBase(s)
            {
            }

        bool     is_ready (          ) { return   TimerBase::is_ready(); }
        double& get_period(          ) { return                 period ; }
        double& set_period(double per) { period = per; return   period ; }
    };

    #include <stdio.h>
    ///-----------------------------|
    /// Tect.                       |
    ///-----------------------------:
    inline void testclass_TimerGame()
    {
        myl::TimerGame timer1(10.0);
        myl::TimerGame timer2( 1.0);

        printf("timer.period: %.1f sec.\n", timer1.get_period());

        int ticks = 0;
        printf("ticks: %i    ", ticks);

        while(true)
        {
            if(timer1.is_ready())
            {   printf("\rticks: %i        ",   ++ticks);
                printf("\ntimer.is_ready() == true\n\n");
                break;
            }

            if(timer2.is_ready())
            {   printf("\rticks: %i sec.    ",  ++ticks);
            }
        }
    }
}

#endif // TIMER_H
