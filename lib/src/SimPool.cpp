#include "Sim.hpp"
#include <functional>
#include <iostream>

namespace stochastic
{
    void SimPool::run_job(int job_index, sim_job_t job)
    {
        running_jobs++;
        std::cout << "running job #" << job_index << std::endl;
        std::thread t(job, job_index);
        running_jobs--;
    }

    void SimPool::workerThread()
    {
        worker_job_t job;
        while (true)
        {
            job_lock.lock();
            if (jobs.empty())
            {
                return;
            }
            job_lock.unlock();

            job();
        }
    }

    worker_job_t SimPool::nextJob()
    {
    }

    void SimPool::repeatJob(int job_count, sim_job_t job)
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
