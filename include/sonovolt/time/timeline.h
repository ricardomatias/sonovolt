#pragma once
#ifndef SONOVOLT_TIMELINE_H
#define SONOVOLT_TIMELINE_H

#include "../types.h"
#include <array>

namespace sonovolt
{

template <typename T>
struct TimelineEvent
{
    u64 start;
    u64 end;
    T data_on;
    T data_off;
};

template <size_t C, typename T>
class Timeline
{
private:
    std::array<TimelineEvent<T>, C> events_;
    typedef void (*Callback)(const TimelineEvent<T> &event);
    u32 playhead_ = 0;
    u32 playhead_loop_ = C;
    u32 loop_end_ = UINT32_MAX;
    u8 event_count_ = 0;

    bool has_on_event_cb_ = false;
    Callback on_event_cb_;

public:
    Timeline() = default;
    ~Timeline() = default;
    Timeline(const Timeline &) = delete;
    Timeline(Timeline &&) = delete;
    Timeline &operator=(const Timeline &) = delete;
    Timeline &operator=(Timeline &&) = delete;

    void insert(TimelineEvent<T> event);
    void tick(u64 time);
    void advance();
    u32 playhead() { return playhead_; }

    std::array<TimelineEvent<T>, C> const &events() { return events_; }

    inline u16 getEventCount() { return event_count_; }
    size_t size() { return C; }

    inline u64 current(u64 ticker) { return ticker % loop_end_; }
    void setLoopEnd(u32 end) { loop_end_ = end; }
    void setPlayheadLoop(u32 loopPoint) { playhead_loop_ = loopPoint; }

    void onEvent(Callback &&callback);

    void logEvents();
};

template <size_t C, typename T>
inline void Timeline<C, T>::insert(TimelineEvent<T> event)
{
    events_[event_count_] = event;
    event_count_ += 1;
}

template <size_t C, typename T>
inline void Timeline<C, T>::onEvent(Timeline<C, T>::Callback &&callback)
{
    on_event_cb_ = std::move(callback);
    has_on_event_cb_ = true;
};

template <size_t C, typename T>
inline void Timeline<C, T>::tick(u64 time)
{
    if(has_on_event_cb_)
    {
        auto &event = events_[playhead_];

        // printf("ticks: %llu, start: %llu, data: %u, playhead: %u\n", time, event.start, event.data, playhead_);
        if(event.start == time)
        {
            on_event_cb_(event);
            playhead_ += 1;
        }
    }
}

template <size_t C, typename T>
inline void Timeline<C, T>::advance()
{
    if(has_on_event_cb_)
    {
        auto &event = events_[playhead_];

        // printf("ticks: %llu, start: %llu, data: %u, playhead: %u\n", time, event.start, event.data, playhead_);
        on_event_cb_(event);
    }

    playhead_ = (playhead_ + 1) % playhead_loop_;
}

template <size_t C, typename T>
inline void Timeline<C, T>::logEvents()
{
    printf("events: [");

    for(size_t i = 0; i < event_count_; i++)
    {
        auto event = events_[i];
        printf("{start: %llu, end: %llu, data_on: %u, data_off: %u}\n",
               event.start,
               event.end,
               event.data_on,
               event.data_off);
    }

    printf("]\n");
}

}; // namespace sonovolt

#endif