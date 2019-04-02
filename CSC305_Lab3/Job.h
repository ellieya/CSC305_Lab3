#pragma once
#include <string>

class Job {
	std::string jobName;
	int arrivalTime;
	int priority;
	int executionTime;
	int remainingExecutionTime;
	bool jobComplete; //1 = job completed, 0 = need to execute

	int turnaroundTime;

	void calculateTurnaroundTime(int);

public:
	Job();
	Job(std::string jobName, int arrivalTime, int priority, int executionTime);
	std::string getJobName();
	int getArrivalTime();
	int getPriority();
	int getExecutionTime();
	int getRemainingExecutionTime();
	void decrRemainingExecutionTime(int);
	//Method must take int variable which is assumed to be clock. In this way, we will have process termination time.
	//POST: remainingExecutionTime -= 1. If remainingExecutionTime = 0, jobComplete flag = true. Additionally, calculates TA time.

	int getTurnaroundTime();
	bool isJobComplete();
};

void Job::calculateTurnaroundTime(int terminationTime) {
	turnaroundTime = terminationTime - arrivalTime;
}

Job::Job() {
	//Intentionally blank
}

Job::Job(std::string jobName, int arrivalTime, int priority, int executionTime)
	:jobName(jobName), arrivalTime(arrivalTime), priority(priority), executionTime(executionTime), remainingExecutionTime(executionTime)
{
	jobComplete = false;
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

void Job::decrRemainingExecutionTime(int currentTime) {
	remainingExecutionTime--;

	if (remainingExecutionTime == 0) {
		jobComplete = true;
		calculateTurnaroundTime(currentTime+1); //Sending over termination time. Must be fixed by + 1 because that is true termination time.
	}
}

int Job::getTurnaroundTime() {
	return turnaroundTime;
}

bool Job::isJobComplete() {
	return jobComplete;
}



