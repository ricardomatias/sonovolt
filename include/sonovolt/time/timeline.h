#pragma once
#ifndef SONOVOLT_TRANSPORT_H
#define SONOVOLT_TRANSPORT_H

#include "../types.h"

class Timeline
{
private:
    u64 playhead = 0;
public:
    Timeline(/* args */);
    ~Timeline();

    void insertAt();
};

#endif