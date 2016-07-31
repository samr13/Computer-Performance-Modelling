#include <omnetpp.h>
#include <queue>
#include <QueueNode.h>
#include <deque>
#include <WebRequest.h>

void QueueNode::setUtilization(simtime_t ut) {
// /	std::cout << "\n"<<getModuleByPath(this)<< endl;
	this->utilization=ut;
	//std::cout << " setUtilization " <<this <<" " << this->utilization <<endl;
}


simtime_t QueueNode::getUtilization() {
	//std::cout << "utilization of "<< this << " is " << this->utilization <<endl;
	return this->utilization;
	//return this->busyTime;
}
