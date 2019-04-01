#pragma once
#include <string>

class Job {
	std::string jobName;
	int arrivalTime;
	int priority;
	int executionTime;
	int remainingExecutionTime;
	bool jobComplete; //1 = job completed, 0 = need to execute

	int terminationTime;

public:
	Job();
	Job(std::string jobName, int arrivalTime, int priority, int executionTime);
	std::string getJobName();
	int getArrivalTime();
	int getPriority();
	int getExecutionTime();
	int getRemainingExecutionTime();
	void decrRemainingExecutionTime();
	//POST: remainingExecutionTime -= 1. If remainingExecutionTime = 0, jobComplete flag = true.

	int getTerminationTime();
	bool isJobComplete();

	bool operator <(const Job&);
};

Job::Job() {
	//Intentionally blank
}

Job::Job(std::string jobName, int arrivalTime, int priority, int executionTime)
	:jobName(jobName), arrivalTime(arrivalTime), priority(priority), executionTime(executionTime), remainingExecutionTime(executionTime)
{
}

std::string Job::getJobName() {
	return jobName;
}


int Job::getArrivalTime() {
	return arrivalTime;
}

int Job::getPriority() {
	return priority;
}
int Job::getExecutionTime() {
	return executionTime;
}

int Job::getRemainingExecutionTime() {
	return remainingExecutionTime;
}

void Job::decrRemainingExecutionTime() {
	remainingExecutionTime--;

	if (remainingExecutionTime == 0)
		jobComplete = true;
}

int Job::getTerminationTime() {
	return terminationTime;
}

bool Job::isJobComplete() {
	return jobComplete;
}



