// TODO: Need a clock to start once it stops recording
// TODO: Clock needs to be synchronized with the clock gate signal
// TODO: Try counting samples once the next clock tick happens, based on an internal sample counter that should be N * TICKS *
// BARS
// TODO: Each Sample value should have the internal ticks registered
template <typename T> class EventSampler {
  public:
    enum State { PLAYING, WAITING_RECORDING, RECORDING, WAITING_PLAYING };

    EventSampler()
        : state_(PLAYING), waiting_for_next_(false), event_index_(0), ticker_(0), next_event_(0), recording_length_(0),
          trigger_(0) {}
    ~EventSampler(){};

    void Init(float sample_rate) {
        sample_rate_ = sample_rate;
        clock_.Init(sample_rate);
    }

    void TickClock() { clock_.Tick(); }

    void Process() {
        switch (state_) {
        case RECORDING:
            ticker_++;
            break;
        case WAITING_PLAYING:
            ticker_++;
            break;
        case PLAYING:
            if (recording_length_ == 0) return;

            if (ticker_ == next_event_) {
                trigger_ = static_cast<uint_fast16_t>(floor((sample_rate_ / 1000.f) * 10.f));

                event_index_ = (event_index_ + 1) % events_count_;
                next_event_ = events_[event_index_];
            }

            if (trigger_ > 0) {
                dsy_gpio_write(&patch.gate_output, true);
                trigger_ -= 1;
            } else {
                dsy_gpio_write(&patch.gate_output, false);
            }

            ticker_ = (ticker_ + 1) % recording_length_;
        default:
            break;
        }
    }

    void Sample(T data) {
        uint8_t bpm = clock_.GetBPM();

        switch (state_) {
        case WAITING_RECORDING:
            state_ = RECORDING;
            patch.seed.SetLed(true);
        case RECORDING:
            if (state_ == RECORDING) {
                events_[event_index_] = ticker_;
                bucket_[event_index_] = data;

                events_count_++;
                event_index_ = (event_index_ + 1) % MAX_EVENTS;
            }
            break;
        case WAITING_PLAYING:
            next_event_ = 0;
            event_index_ = 0;
            recording_length_ = ticker_;
            ticker_ = 0;
            trigger_ = 0;

            state_ = PLAYING;
        case PLAYING:
            patch.seed.SetLed(false);
            break;
        default:
            break;
        }
    }

    void ToggleRecord() {
        switch (state_) {
        case PLAYING:
            // wait for next event to start recording
            state_ = WAITING_RECORDING;

            ticker_ = 0;
            trigger_ = 0;
            next_event_ = 0;
            events_count_ = 0;
            event_index_ = 0;
            recording_length_ = 0;
            break;
        case RECORDING:
            state_ = WAITING_PLAYING;
            break;
        default:
            state_ = PLAYING;
            break;
        }
    }

    State const GetState() { return state_; }
    string const GetStateStr() {
        switch (state_) {
        case PLAYING:
            return string("Playing");
        case WAITING_RECORDING:
            return string("Waiting Record");
        case RECORDING:
            return string("Recording");
        case WAITING_PLAYING:
            return string("Waiting Play");
        default:
            return string("???");
        }
    }

    string GetTicker() {
        FixedCapStr<20> str("Ticker: ");
        str.AppendInt(ticker_);
        return string(str);
    }

    string GetNextEvent() {
        FixedCapStr<20> str("Next: ");
        str.AppendInt(next_event_);
        return string(str);
    }

    string GetRecordingLength() {
        FixedCapStr<20> str("RecLen: ");
        str.AppendInt(recording_length_);
        return string(str);
    }

    string GetEventsCount() {
        FixedCapStr<20> str("Events: ");
        str.AppendInt(events_count_);
        return string(str);
    }

    string GetEventIndex() {
        FixedCapStr<20> str("EventIdx: ");
        str.AppendInt(event_index_);
        return string(str);
    }

  private:
    State state_;
    bool waiting_for_next_;
    uint_fast16_t event_index_;
    size_t ticker_;
    size_t next_event_;
    size_t recording_length_;
    size_t events_count_;
    uint_fast16_t trigger_;

    float sample_rate_;
    TempoSampler clock_;
    size_t events_[MAX_EVENTS];
    T bucket_[MAX_EVENTS];
};