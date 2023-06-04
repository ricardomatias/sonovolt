#pragma once
#ifndef SONOVOLT_TIMELINE_H
#define SONOVOLT_TIMELINE_H

#include "../types.h"
#include <stdio.h>
#include <array>

namespace sonovolt {

template <typename T> struct TimelineEvent {
    u64 start;
    u64 end;
    T data;
};

template <typename T> class Timeline {
  private:
    typedef void (*Callback)(TimelineEvent<T>*);
    u8 playhead_ = 0;
    u8 event_count_ = 0;
    std::array<TimelineEvent<T>, 64> events_;

    bool has_on_event_cb_ = false;
    Callback on_event_cb_;

  public:
    Timeline() {}
    ~Timeline() {}

    void insert(TimelineEvent<T> event);
    void tick(u64 time);

    void logEvents();

    void onEvent(Callback &&callback);
};

template <typename T> inline void Timeline<T>::insert(TimelineEvent<T> event) { 
    events_[event_count_] = event;
    event_count_ += 1;
 }

template <typename T> inline void Timeline<T>::onEvent(Timeline<T>::Callback &&callback) {
    on_event_cb_ = std::move(callback);
    has_on_event_cb_ = true;
};

template <typename T> inline void Timeline<T>::tick(u64 time) {
    if (has_on_event_cb_) {
        TimelineEvent<T> event = events_[playhead_];

        // printf("ticks: %llu, start: %llu, data: %u, playhead: %u\n", time, event.start, event.data, playhead_);

        if (event.start == time) {
            on_event_cb_(&event);
            playhead_ += 1;
        }
    }
}

template <typename T> inline void Timeline<T>::logEvents() {
    printf("events: [");

    for (size_t i = 0; i < event_count_; i++) {
        auto event = events_[i];
        printf("{start: %llu, end: %llu, data: %u}\n", event.start, event.end, event.data);
    }

    printf("]\n");
}

}; // namespace sonovolt

#endif