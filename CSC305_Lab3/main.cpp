#include <iostream>
#include <queue>
#include <list>
#include <cassert>
#include <fstream>
#include <string>
#include "Job.h"

using namespace std;


void populateJobsQueue(priority_queue<Job>& targetQueue, ifstream& targetFileStream) {
	//Temporary data holders
	string stringHolder;
	int intHolder[4];
	//0 = Arrival Time
	//1 = Priority
	//2 = Execution Time
	Job jobHolder;

	while (!targetFileStream.eof()) {
		targetFileStream >> stringHolder >> intHolder[0] >> intHolder[1] >> intHolder[2];
		jobHolder = Job(stringHolder, intHolder[0], intHolder[1], intHolder[2]);

		targetQueue.push(jobHolder);
	}
}

/*
void printJobsQueue(priority_queue<pair<int, Job>> targetQueue) {
	while (!targetQueue.empty()) {
		cout << targetQueue.top().first << endl;
		targetQueue.pop();
	}
}

*/

int main() {



	ifstream fin;
	priority_queue<Job> jobsArrivalQueue;
	/*	This jobsQueue contains pair of int and Job.
		the int value of pair is Job's arrivalTime * -1
		In doing this, when jobs are pushed onto queue,
		all jobs will be in order according to arrivalTime
		This is beneficial as it allows circumvention of
		doing a search for a matching arrivalTime value
		every time arrivalTime is updated.
	*/

	fin.open("input_file.txt");
	assert(!fin.fail());


	/*
	1. Take processes from file until end of file
	2. Gradually increment time. Check when time = arrival time of a job.
		When = arrival time of a job, push into working 'X'


		MY CURRENT IDEA...
		1. list jobList with all jobs
		2. priorityQueue push a pair of <int, int> where first int represents arrival time and second int represents linked list position >:D

	*/




	//This is for SJN
	//list<int> arrivedJobs;

	//This is for Priority
	//priority_queue<pair<int,char>> jobsPQueue;

	//This is for FCFS
	//queue<int> jobsQueue;

	


	system("pause");
	return 0;
}


