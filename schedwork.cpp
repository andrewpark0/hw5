#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool findSchedule(size_t dayIndex, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, map<Worker_T, size_t>& shiftsCounter);
bool tryScheduleDay(size_t dayIndex, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, map<Worker_T, size_t>& shiftsCounter, vector<Worker_T>& todaysCandidates, size_t startID, size_t workersAdded);
// Add your implementation of schedule() and other helper functions here
bool findSchedule(size_t dayIndex, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, map<Worker_T, size_t>& shiftsCounter){
    if(dayIndex == avail.size()){ //base case: all days have been successfully scheduled
        return true;
    }

    vector<Worker_T> todaysCandidates;
    
    for(size_t worker = 0; worker < avail[dayIndex].size(); ++worker){
        if(avail[dayIndex][worker]){
            todaysCandidates.push_back(worker);
        }
    }
    //try to find valid combo of workers for today
    return tryScheduleDay(dayIndex, avail, dailyNeed, maxShifts, sched, shiftsCounter, todaysCandidates, 0, 0);
}


bool tryScheduleDay(size_t dayIndex, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, map<Worker_T, size_t>& shiftsCounter, vector<Worker_T>& todaysCandidates, size_t startID, size_t workersAdded){
    if(workersAdded == dailyNeed){ //base case: enough workers added for today
        return findSchedule(dayIndex + 1, avail, dailyNeed, maxShifts, sched, shiftsCounter);
    }

    for(size_t i = startID; i < todaysCandidates.size(); ++i){
        Worker_T worker = todaysCandidates[i];
        //add worker if available and still under max shifts
        if(avail[dayIndex][worker] && shiftsCounter[worker] < maxShifts){
            sched[dayIndex].push_back(worker);
            shiftsCounter[worker]++;
            if(tryScheduleDay(dayIndex, avail, dailyNeed, maxShifts, sched, shiftsCounter, todaysCandidates, i+1, workersAdded+1)){
                return true;
            }
            //backtrack
            shiftsCounter[worker]--;
            sched[dayIndex].pop_back();
        }
    }

    return false; //no valid schedule found for this day
}


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    sched.resize(avail.size());
    
    map<Worker_T, size_t> shiftsCounter;

    for(size_t worker = 0; worker < avail[0].size(); ++worker){
        shiftsCounter[worker] = 0;
    }


    return findSchedule(0, avail, dailyNeed, maxShifts, sched, shiftsCounter);
}

