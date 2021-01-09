#include "JobCore.h"

/*

namespace JobSystem
{
	uint32_t numThreads = 0;
	ThreadSafeRingBuffer<std::function<void()>, 256> jobPool;
	std::condition_variable wakeCondition;
	std::mutex wakeMutex;
	uint64_t currentLabel = 0;
	std::atomic<uint64_t> finishedLabel;

	void Initialize()
	{
		finishedLabel.store(0);
		auto numCores = std::thread::hardware_concurrency();
		numThreads = std::max(1u, numCores);

		for (uint32_t threadID = 0; threadID < numThreads; ++threadID) {
			std::thread worker([] {
				std::function<void()> job;

				while (true)
				{
					if (jobPool.pop_front(job))
					{
						job();
						finishedLabel.fetch_add(1);
					}
					else
					{
						std::unique_lock<std::mutex> lock(wakeMutex);
						wakeCondition.wait(lock);
					}
				}
			});

			worker.detach();
		}
	}

	inline void poll() {
		wakeCondition.notify_one();
		std::this_thread::yield();
	}

	void Execute(const std::function<void()>& job) {
		currentLabel += 1;
		while (!jobPool.push_back(job)) { poll(); }
		wakeCondition.notify_one();
	}

	bool IsBusy() { return finishedLabel.load() < currentLabel; }

	void Wait() { while (IsBusy()) { poll(); } }

	void Dispatch(uint32_t jobCount, uint32_t groupSize, const std::function<void(JobDispatchArgs)>& job)
	{
		if (jobCount == 0 || groupSize == 0)
		{
			return;
		}

		const uint32_t groupCount = (jobCount + groupSize - 1) / groupSize;
		currentLabel += groupCount;

		for (uint32_t groupIndex = 0; groupIndex < groupCount; ++groupIndex)
		{
			auto& jobGroup = [jobCount, groupSize, job, groupIndex]() {

				const uint32_t groupJobOffset = groupIndex * groupSize;
				const uint32_t groupJobEnd = std::min(groupJobOffset + groupSize, jobCount);

				JobDispatchArgs args;
				args.groupIndex = groupIndex;

				for (uint32_t i = groupJobOffset; i < groupJobEnd; ++i)
				{
					args.jobIndex = i;
					job(args);
				}
			};

			while (!jobPool.push_back(jobGroup)) { poll(); }

			wakeCondition.notify_one(); // wake one thread
		}
	}
}

*/