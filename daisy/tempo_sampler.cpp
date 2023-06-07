#include <cstdint>
#include <array>
#include <cmath>

constexpr static uint8_t MAX_TEMPO_TICKS = 4;

extern uint64_t global_elapsed_samples;

class TempoSampler {
  public:
    TempoSampler() : tick_(0), last_elapsed_ticks_(0) { std::fill_n(ticks_, MAX_TEMPO_TICKS, 0); }
    ~TempoSampler(){};

    void Init(float sample_rate) { sample_rate_ = sample_rate; }

    void Tick() {
        if (tick_ == 0) {
            uint8_t count = 0;

            for (uint8_t i = 1; i < MAX_TEMPO_TICKS; i++) {
                count += ticks_[i] - ticks_[i - 1];
            }

            last_elapsed_ticks_ = count / (MAX_TEMPO_TICKS - 1);
        }

        ticks_[tick_] = global_elapsed_samples;
        tick_ = (tick_ + 1) % MAX_TEMPO_TICKS;
    }

    uint8_t GetBPM() { return static_cast<uint8_t>(roundf((60.f * sample_rate_) / static_cast<float>(last_elapsed_ticks_))); }

    uint32_t GetInterval() { return last_elapsed_ticks_; }

  private:
    uint_fast8_t tick_;
    uint32_t ticks_[MAX_TEMPO_TICKS];
    uint32_t last_elapsed_ticks_;
    float sample_rate_;
};

