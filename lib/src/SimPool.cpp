#include "Sim.hpp"
#include <functional>
#include <iostream>

namespace stochastic
{
    void SimPool::workerThread()
    {
        while (true)
        {
            worker_job_t job;
            {
                std::unique_lock<std::mutex> lock(job_lock);
                job_cv.wait(lock, [&]()
                            { return shutting_down || !jobs.empty(); });

                if (shutting_down && jobs.empty())
                {
                    return;
                }

                job = std::move(jobs.front());
                jobs.pop();
            }

            job();
        }
    }

    void SimPool::repeat_job(int job_count, sim_job_func_t job)
    {
        std::lock_guard<std::mutex> lock(job_lock);
        for (auto job_index = 0; job_index < job_count; job_index++)
        {
            jobs.emplace(std::bind(job, job_index));
        }
        ready = true;
        job_cv.notify_all();
    }

    SimPool::~SimPool()
    {
        {
            std::lock_guard<std::mutex> lock(job_lock);
            shutting_down = true;
            ready = true;
        }
        job_cv.notify_all();

        for (auto &t : workers)
        {
            if (t.joinable())
            {
                t.join();
            }
        }
    }
}
