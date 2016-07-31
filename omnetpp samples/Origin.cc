#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <WebRequest.h>
#include <QueueNode.h>

class Origin :  public QueueNode {
  private:
  	cMessage *event;
    cMessage *currentlyServing;
  	cMessage *original;
    QueueNode *node;
    std::deque<WebRequest*> requestQueue;

  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  public:
    Origin();
    virtual ~Origin();

};

Origin::Origin()
{
    event = original = NULL;    
    currentlyServing = NULL;
    utilization=0;
}

Origin::~Origin()
{
    cancelAndDelete(event);
    delete original;
}


Define_Module(Origin);


void Origin::initialize() {
     node = new Origin();
           busyTime = 0;
     //WATCH(busyTime);
}



void Origin::handleMessage(cMessage *msg)
{
 WebRequest *req = check_and_cast<WebRequest *>(msg);

     if (req == currentlyServing ) {
         // this is a "self message" implementing a delay....
         currentlyServing = NULL;
                  simtime_t serviceTime = par("ServiceTime");
         busyTime+=(serviceTime);
         setUtilization(busyTime);
         //setUtilization((simTime()-req->getStartTime()).dbl());
         //std::cout << "Origin stop time" << simTime() << " " <<req->getStartTime()<<endl;
         req->setServed(true);
         send(req, "router$o");
     } else {
     	//std::cout << "Origin set time" << simTime() <<endl;
     	req->setStartTime(simTime());
        requestQueue.push_back( req );
     }
  
 //
 // If not currently serving/processing a request
 // pull one from the queue and start serving it..
 //
 if ( ! requestQueue.empty() && currentlyServing == NULL) {
    currentlyServing = requestQueue.front();
    requestQueue.pop_front();
    //std::cout << "serving: "<<currentlyServing << "  " << req->getServed()<<endl;
    scheduleAt(simTime() + par("ServiceTime"), currentlyServing);
 }
}
/*
void Origin::handleMessage(cMessage *msg) {
	
	if (msg==event)
   	  {
   	  		WebRequest *req = check_and_cast <WebRequest *> (original);
   	  		req->setServed(true);
        	EV << "Wait period is over, sending back message\n";
        	setUtilization((simTime()-req->getStartTime()).dbl());
        	std::cout << "Origin stop time" << simTime() <<endl;
        	send(req, "Origin$o");
        	original = NULL;
      } else {      	
      		WebRequest *req = check_and_cast <WebRequest *> (msg);
      		req->setStartTime(simTime());
      		std::cout << "Origin set time" << simTime() <<endl;
            simtime_t delay = par("ServiceTime");
            event = new cMessage("event");	
            EV << "Message arrived, starting to wait " << delay << " secs...\n";
            original = msg;
            scheduleAt(simTime()+delay, event);      	
      }
}
*/