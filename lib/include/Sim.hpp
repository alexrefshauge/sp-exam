#ifndef STOCHASTIC_SIM_HPP
#define STOCHASTIC_SIM_HPP

#include <cstddef>
#include <functional>
#include <map>
#include <string>
#include <thread>
#include <queue>

namespace stochastic
{
    using VesselState = std::map<std::string, std::size_t>;

    struct StateObserver
    {
        virtual ~StateObserver() = default;
        virtual void observe(const double t, const VesselState &s) = 0;
    };

    typedef std::function<void(int)> sim_job_func_t;
    typedef std::function<void(void)> worker_job_t;

    struct SimPool
    {
        size_t pool_size;
        int running_jobs;
        std::vector<std::thread> workers;
        std::queue<worker_job_t> jobs;

        std::mutex job_lock;

        SimPool() : pool_size(std::thread::hardware_concurrency()), running_jobs(0)
        {
            workers.reserve(pool_size);
        }

        void run_job(int job_index, sim_job_func_t job);
        void repeatJob(int job_count, sim_job_func_t job);

        void workerThread();
        worker_job_t nextJob();
    };
}

#endif
