#include "Sim.hpp"
#include <functional>
#include <iostream>

namespace stochastic
{
    void SimPool::workerThread()
    {
        worker_job_t job;
        while (true)
        {
            job_lock.lock(); // Claim next job in queue
            if (jobs.empty())
            {
                job_lock.unlock();
                return;
            }
            job = std::move(jobs.front());
            jobs.pop();
            job_lock.unlock(); // Unlock job queue for other workers

            job(); // Run job
        }
    }

    void SimPool::repeat_job(int job_count, sim_job_func_t job)
    {
        auto job_index = 0;
        job_lock.lock();
        for (auto job_index = 0; job_index < job_count; job_index++)
        {
            jobs.emplace(std::bind(job, job_index));
        }

        job_lock.unlock();
    }
}
