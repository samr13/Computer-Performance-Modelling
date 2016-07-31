#include <omnetpp.h>
#include <queue>
#include <WebRequest.h>
#include <deque>


class QueueNode  : public cSimpleModule
{
public:
	simtime_t busyTime;
	simtime_t utilization;
	std::deque<WebRequest*> qq;
	virtual void setUtilization(simtime_t ut);
	virtual simtime_t getUtilization();
};