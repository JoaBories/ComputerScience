#pragma once

#include <chrono>
#include <iostream>
#include <string>

namespace Benchmark
{
    using namespace std::chrono;
    
    enum class TimePrecision : uint8_t
    {
        None = 0,
        NanoSeconds,
        MicroSeconds,
        MilliSeconds,
        Seconds,
        Minutes,
        Hours,
    };

    inline uint64_t durationCast(const time_point<steady_clock> start, const time_point<steady_clock> end,
                                 const TimePrecision precision = TimePrecision::MicroSeconds)
    {
        switch (precision)
        {
            case TimePrecision::NanoSeconds: 
                return duration_cast<nanoseconds>(end - start).count();
            case TimePrecision::MicroSeconds:
                return duration_cast<microseconds>(end - start).count();
            case TimePrecision::MilliSeconds:
                return duration_cast<milliseconds>(end - start).count();
            case TimePrecision::Seconds:
                return duration_cast<seconds>(end - start).count();
            case TimePrecision::Minutes:
                return duration_cast<minutes>(end - start).count();
            case TimePrecision::Hours:
                return duration_cast<hours>(end - start).count();
            default:
                return 0;
        }
    }
    
    inline std::string toString(const TimePrecision precision, const bool shortFormat = true)
    {
        switch (precision)
        {
            case TimePrecision::NanoSeconds: return shortFormat ? "ns" : "nano seconds";
            case TimePrecision::MicroSeconds: return shortFormat ? "us" : "microseconds";
            case TimePrecision::MilliSeconds: return shortFormat ? "ms" : "milliseconds";
            case TimePrecision::Seconds: return shortFormat ? "s" : "seconds";
            case TimePrecision::Minutes: return shortFormat ? "m" : "minutes";
            case TimePrecision::Hours: return shortFormat ? "h" : "hours";
            default: return shortFormat ? "nan" : "unknown time precision";
        }
    }

    template<typename F>
    inline uint64_t bench(const F& func, const TimePrecision precision = TimePrecision::MicroSeconds)
    {
        const auto start = high_resolution_clock::now();
        func();
        const auto end = high_resolution_clock::now();

        const uint64_t time = durationCast(start, end, precision);
        return time;
    }
    
    template<typename F>
    inline void benchPrint(const F& func, const std::string& testName, const TimePrecision precision = TimePrecision::MicroSeconds, 
        const bool print = true, const bool shortFormat = true)
    {
        if (print) std::cout << testName << ": ";
        const auto start = high_resolution_clock::now();
        func();
        const auto end = high_resolution_clock::now();

        const uint64_t time = durationCast(start, end, precision);
        if (print) std::cout << time << toString(precision, shortFormat) << '\n';
    }
}
