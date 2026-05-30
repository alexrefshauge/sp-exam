#ifndef STOCHASTIC_SIM_HPP
#define STOCHASTIC_SIM_HPP

#include <cstddef>
#include <functional>
#include <unordered_map>
#include <string>
#include <thread>
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>

namespace stochastic
{
    using VesselState = std::unordered_map<std::string, std::size_t>;

    struct StateObserver
    {
        virtual ~StateObserver() = default;
        virtual void observe(const int seed, const double t, const VesselState &s) = 0;
    };

    typedef std::function<void(int)> sim_job_func_t;
    typedef std::function<void(void)> worker_job_t;

    struct SimPool
    {
        size_t pool_size;
        int running_jobs;
        std::vector<std::thread> workers;
        std::queue<worker_job_t> jobs;
        bool ready;
        bool shutting_down;

        std::mutex job_lock;
        std::condition_variable job_cv;

        SimPool() : pool_size(std::thread::hardware_concurrency()), running_jobs(0), ready(false), shutting_down(false)
        {
            workers.reserve(pool_size);
            for (auto i = 0; i < pool_size; i++)
            {
                workers.emplace_back(std::bind(&SimPool::workerThread, this));
            }
        }

        ~SimPool();

        SimPool(const SimPool &) = delete;
        SimPool &operator=(const SimPool &) = delete;
        SimPool(SimPool &&) = delete;
        SimPool &operator=(SimPool &&) = delete;

        void repeat_job(int job_count, sim_job_func_t job);

        void workerThread();
    };
}

#endif
