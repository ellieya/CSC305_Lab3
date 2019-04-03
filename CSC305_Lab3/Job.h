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


	//The following three values are used to circumvent priorityQueue's sorting quirks and ensures that jobs
	//that share the same "key value" will execute based on when they arrived.
	//This is a TERRIBLE workaround since it completely violates OOD principle of durability but I have no time left :(
	int truePriority;
	int trueExecutionTime;
	static int count;
		//count keeps track of total # of jobs

	void calculateTurnaroundTime(int);

public:
	Job();
	Job(std::string jobName, int arrivalTime, int priority, int executionTime);
	std::string getJobName();
	int getArrivalTime();
	int getPriority();
	int getTruePriority();
	int getExecutionTime();
	int getTrueExecutionTime();
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
	trueExecutionTime = executionTime * 1000 + count; //Using add since execution time is working with negative numbers
	truePriority = priority * 1000 - count; //Using subtract since priority is using with positive numbers
	count++;
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

int Job::getTruePriority() {
	return truePriority;
}

int Job::getExecutionTime() {
	return executionTime;
}

int Job::getTrueExecutionTime() {
	return trueExecutionTime;
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

int Job::count = 0;
