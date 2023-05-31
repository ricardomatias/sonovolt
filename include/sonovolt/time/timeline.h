#pragma once
#ifndef SONOVOLT_TRANSPORT_H
#define SONOVOLT_TRANSPORT_H

#include "../types.h"

struct TimelineEvent {

};

class Timeline
{
private:
    u64 playhead = 0;
public:
    Timeline();
    ~Timeline();

    void insertAt();
};

#endif