#ifndef GRAVEDIGGERS_MONITOR_H
#define GRAVEDIGGERS_MONITOR_H


class Monitor {

private:
    int myClock;
    int myChoice;


public:
    void makeSnapshot(int clock, int choice);

};


#endif //GRAVEDIGGERS_MONITOR_H
