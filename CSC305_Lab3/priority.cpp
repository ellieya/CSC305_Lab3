#include <iostream>
#include <queue>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include "Job.h"

using namespace std;

void populateJobVectorAndQueueFromFile(vector<Job>& jobVector, priority_queue<pair<int,int>>& jobArrivalQueue);

//For debugging
void printJobVector(vector<Job> jobVector);
void printPriorityQueue(priority_queue<pair<int, int>> jobArrivalQueue, vector<Job> jobVector);

//Final outputs
void printJobDataTable(vector<Job> jobVector);
void printJobOrder(queue<string> jobOrder);


int main() {

	int clock = 0;

	vector<Job> jobVector;
	priority_queue<pair<int, int>> jobArrivalQueue;
	//first int - Represents negated arrival time
	//second int - Represents job list position

	priority_queue<pair<int, int>> waitingJobsQueue;
	//first int - Represents priority
	//second int - Represents job list position
	//All items will be auto-sorted based on priority

	queue<string> jobOrder;
	//A queue of job names, pushed in the order they were processed.

	bool done = false;
	bool workingJob = false;
	Job currentWorkingJob;
	int currentWorkingJobIndex;

	populateJobVectorAndQueueFromFile(jobVector, jobArrivalQueue);

	//When -arrivalTime = jobArrivalQueue.second, push onto priorityqueue
	while (!done) {

		/* DEBUGGING */
		//cout << "Clock: " << clock << ". ";
		//if (workingJob) {
		//	cout << "Current Job: " << currentWorkingJob.getJobName() << ". Time left: " << currentWorkingJob.getRemainingExecutionTime() << ".";
		//}
		//cout << endl;

		/* ARRIVAL */
		//Check if queue is empty to avoid error trying to get front
		if (!jobArrivalQueue.empty()) {
			//Is there an arrival?
			if (jobArrivalQueue.top().first == (-clock)) {
				//Push priority value and list position into priorityJobsQueue
				waitingJobsQueue.push({ jobVector[jobArrivalQueue.top().second].getPriority(), jobArrivalQueue.top().second });
				//Pop from jobArrivalQueue
				jobArrivalQueue.pop();
			}
		}

		//Is there any working job?
		if (!workingJob) {
			//If there is no working job, then make currentWorkingJob equal to waitingJobsQueue's top and pop it from queue
			currentWorkingJobIndex = waitingJobsQueue.top().second;
			currentWorkingJob = jobVector[currentWorkingJobIndex];
			workingJob = true;
			waitingJobsQueue.pop();
			//Update string queue...
			jobOrder.push(currentWorkingJob.getJobName());
		} //Otherwise, there is a working job...
		else {
			//Check if queue is empty to avoid error trying to get front
			if (!waitingJobsQueue.empty()) {
				//Is there an item in the queue with a higher priority value?
				if (currentWorkingJob.getPriority() < waitingJobsQueue.top().first) {
					//...then update the currentWorkingJob in the vector, push "currentWorkingJob" back onto the queue, and replace current job with the higher priority job.
					jobVector[currentWorkingJobIndex] = currentWorkingJob;
					waitingJobsQueue.push({ currentWorkingJob.getPriority(), currentWorkingJobIndex });
					currentWorkingJobIndex = waitingJobsQueue.top().second;
					currentWorkingJob = jobVector[currentWorkingJobIndex];
					waitingJobsQueue.pop();
					//Update string queue...
					jobOrder.push(currentWorkingJob.getJobName());
				}
			}
		}

		//Work on current job
		currentWorkingJob.decrRemainingExecutionTime(clock);

		//Is existing job done executing?
		if (currentWorkingJob.isJobComplete()) {
			workingJob = false;
			//Update the job's information in the vector
			jobVector[currentWorkingJobIndex] = currentWorkingJob;
		}

		//Increment clock
		clock++;

		//Check if it's time to stop: waitingJobsQueue must be empty, and there must be no workingJob present.
		if (waitingJobsQueue.empty() && (!workingJob))
			done = true;
	}

	cout << "PRIORITY ALGORITHM" << endl;
	printJobDataTable(jobVector);
	cout << endl;
	printJobOrder(jobOrder);


	system("pause");
	return 0;
}

void populateJobVectorAndQueueFromFile(vector<Job>& jobVector, priority_queue<pair<int, int>>& jobArrivalQueue)
{
	ifstream fin;
	fin.open("input_file.txt");
	assert(!fin.fail());

	int intHolder[4];
	//0 = Arrival time
	//1 = Priority
	//2 = Execution Time
	//3 = Negative version of arrival time
	string stringHolder;
	Job jobHolder;
	int i = 0;

	while (!fin.eof()) {
		fin >> stringHolder >> intHolder[0] >> intHolder[1] >> intHolder[2];
		jobHolder = Job(stringHolder, intHolder[0], intHolder[1], intHolder[2]);
		jobVector.push_back(jobHolder);
		intHolder[3] = -intHolder[0];

		//Push negative version of arrival time and vector position into jobArrival Queue
		jobArrivalQueue.push({ intHolder[3], i });
		i++;
	}
}

void printJobVector(vector<Job> jobList)
{
	for (int i = 0; i < jobList.size(); i++) {
		cout << jobList[i].getJobName() << endl;
	}
}

void printPriorityQueue(priority_queue<pair<int, int>> jobArrivalQueue, vector<Job> jobVector)
{
	while (!jobArrivalQueue.empty()) {
		cout << jobArrivalQueue.top().first << " " << jobVector[jobArrivalQueue.top().second].getJobName() << endl;
		jobArrivalQueue.pop();
	}
}

void printJobDataTable(vector<Job> jobVector) {
	int sum = 0;
	cout << "NAME\tTA" << endl;
	for (int i = 0; i < jobVector.size(); i++) {
		cout << jobVector[i].getJobName() << "\t" << jobVector[i].getTurnaroundTime() << endl;
		sum += jobVector[i].getTurnaroundTime();
	}

	cout << "\nAVERAGE TA: " << static_cast<double>(sum) / jobVector.size() << endl;
}

void printJobOrder(queue<string> jobOrder) {
	cout << "Job Order: ";
	while (!jobOrder.empty()) {
		cout << jobOrder.front() << " ";
		jobOrder.pop();
	}
	cout << endl;
}