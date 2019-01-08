// Copyright (c) 2016 The Zcash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uint256.h"

#include <atomic>
#include <mutex>
#include <string>

struct AtomicCounter {
    std::atomic<uint64_t> value;

    AtomicCounter() : value {0} { }

    void increment(){
        ++value;
    }

    void decrement(){
        --value;
    }

    int get() const {
        return value.load();
    }
};

class AtomicTimer {
private:
    std::mutex mtx;
    uint64_t threads;
    int64_t start_time;
    int64_t total_time;

public:
    AtomicTimer() : threads(0), start_time(0), total_time(0) {}

    /**
     * Starts timing on first call, and counts the number of calls.
     */
    void start();

    /**
     * Counts number of calls, and stops timing after it has been called as
     * many times as start().
     */
    void stop();

    bool running();

    uint64_t threadCount();

    double rate(const AtomicCounter& count);
};

extern AtomicCounter transactionsValidated;
extern AtomicCounter ehSolverRuns;
extern AtomicCounter solutionTargetChecks;
extern AtomicTimer miningTimer;

void TrackMinedBlock(uint256 hash);

void MarkStartTime();
double GetLocalSolPS();
int EstimateNetHeightInner(int height, int64_t tipmediantime,
                           int heightLastCheckpoint, int64_t timeLastCheckpoint,
                           int64_t genesisTime, int64_t targetSpacing);

void TriggerRefresh();

void ConnectMetricsScreen();
void ThreadShowMetricsScreen();

const std::string METRICS_ART =
"\e[0m     \e[38;5;1m\e[48;5;15m   ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐   \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐\e[38;5;0m                   ███████████████████   \e[38;5;1m┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘\e[38;5;0m                   ██          ██████    \e[38;5;1m└─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐\e[38;5;0m                   █          ██████     \e[38;5;1m┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘\e[38;5;0m                             ██████      \e[38;5;1m└─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐\e[38;5;0m                            ██████       \e[38;5;1m┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘\e[38;5;0m                           ██████        \e[38;5;1m└─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐\e[38;5;0m                          ██████         \e[38;5;1m┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘\e[38;5;0m               \e[38;5;7m███\e[38;5;0m       ██████          \e[38;5;1m└─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐\e[38;5;0m                 \e[38;5;7m███\e[38;5;0m    ██████           \e[38;5;1m┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘\e[38;5;0m                   \e[38;5;8m███\e[38;5;0m ██████            \e[38;5;1m└─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐\e[38;5;0m                     \e[38;5;8m██\e[38;5;0m█████             \e[38;5;1m┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘\e[38;5;0m                       \e[38;5;8m██\e[38;5;0m██          █   \e[38;5;1m└─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐\e[38;5;0m                         \e[38;5;8m███\e[38;5;0m        ██   \e[38;5;1m┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘\e[38;5;4m █████ █████ ████   ███    \e[38;5;8m██\e[38;5;0m█████████   \e[38;5;1m└─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐\e[38;5;4m    █  █     █   █ █   █     \e[38;5;8m███\e[38;5;0m         \e[38;5;1m┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘\e[38;5;4m   █   ███   ████  █   █       \e[38;5;7m███\e[38;5;0m       \e[38;5;1m└─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐\e[38;5;4m  █    █     █  █  █   █         \e[38;5;7m███\e[38;5;0m     \e[38;5;1m┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘\e[38;5;4m █████ █████ █   █  ███                  \e[38;5;1m└─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐\e[38;5;0m                                         \e[38;5;1m┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘\e[38;5;6m  ███  █       █    ████  ████ █  ███    \e[38;5;1m└─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐\e[38;5;6m █   █ █      █ █  █     █     █ █   █   \e[38;5;1m┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘\e[38;5;6m █     █     █   █  ███   ███  █ █       \e[38;5;1m└─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐\e[38;5;6m █   █ █     █████     █     █ █ █   █   \e[38;5;1m┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m ┌─┘\e[38;5;6m  ███  █████ █   █ ████  ████  █  ███    \e[38;5;1m└─┐ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m └─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┘ \e[0m \n"
"\e[0m     \e[38;5;1m\e[48;5;15m   └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘   \e[0m \n";






