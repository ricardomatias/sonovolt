#pragma once
#ifndef SONOVOLT_TIMELINE_H
#define SONOVOLT_TIMELINE_H

#include "../types.h"
#include <array>
#include <stdio.h>

namespace sonovolt {

template <typename T> struct TimelineEvent {
    u64 start;
    u64 end;
    T data_on;
    T data_off;
};

template <size_t C, typename T> class Timeline {
  private:
    typedef void (*Callback)(u64 ticker);
    u32 playhead_ = 0;
    u32 loop_end_ = UINT32_MAX;
    u8 event_count_ = 0;

    bool has_on_event_cb_ = false;
    Callback on_event_cb_;

  public:
    std::array<TimelineEvent<T>, C> events;

    Timeline() {}
    ~Timeline() {}

    void insert(TimelineEvent<T> event);
    void tick(u64 time);

    u16 getEventCount() { return event_count_; }

    u64 current(u64 ticker) { return ticker % loop_end_; }
    void setLoopEnd(u32 end) { loop_end_ = end; }

    void onEvent(Callback &&callback);

    void logEvents();
};

template <size_t C, typename T> inline void Timeline<C, T>::insert(TimelineEvent<T> event) {
    events[event_count_] = event;
    event_count_ += 1;
}

template <size_t C, typename T> inline void Timeline<C, T>::onEvent(Timeline<C, T>::Callback &&callback) {
    on_event_cb_ = std::move(callback);
    has_on_event_cb_ = true;
};

template <size_t C, typename T> inline void Timeline<C, T>::tick(u64 time) {
    if (has_on_event_cb_) {
        TimelineEvent<T> event = events[playhead_];

        // printf("ticks: %llu, start: %llu, data: %u, playhead: %u\n", time, event.start, event.data, playhead_);
        if (event.start == time) {
            on_event_cb_(&event);
            playhead_ += 1;
        }
    }
}

template <size_t C, typename T> inline void Timeline<C, T>::logEvents() {
    printf("events: [");

    for (size_t i = 0; i < event_count_; i++) {
        auto event = events[i];
        printf("{start: %llu, end: %llu, data_on: %u, data_off: %u}\n", event.start, event.end, event.data_on, event.data_off);
    }

    printf("]\n");
}

}; // namespace sonovolt

#endif