#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <WebRequest.h>
#include <QueueNode.h>
#include <deque>

class Router :  public QueueNode {
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
    Router();
    virtual ~Router();
    virtual void sendMessageOnItsWay( WebRequest *req );
};

Router::Router()
{
    event = original = NULL;
    currentlyServing = NULL;
    utilization=0;
    //requestQueue = node->qq;
}

Router::~Router()
{
    cancelAndDelete(event);
    delete original;
}

Define_Module(Router);

void Router::initialize() {
     node = new Router();
           busyTime = 0;
     //WATCH(busyTime);
}

void Router::sendMessageOnItsWay( WebRequest *req ) {
	//WebRequest *req = check_and_cast <WebRequest *> (msg);
   if (req->getServed()) {
      send(req, "proxy$o");     
   } else {
   	  if (req->getRequestNumber()%2)
      	send(req, "origin$o",0);
      else
      	send(req, "origin$o",1);
   }

}

void Router::handleMessage(cMessage *msg)
{
 WebRequest *req = check_and_cast<WebRequest *>(msg);
 if (!req->getServed()) {
     if (req == currentlyServing ) {
         // this is a "self message" implementing a delay....
         currentlyServing = NULL;
                  simtime_t serviceTime = par("ServiceTime");
         busyTime+=(serviceTime);
         setUtilization(busyTime);
         //setUtilization((simTime()-req->getStartTime()).dbl());
         //std::cout << "Router stop time" << simTime() <<endl;
         sendMessageOnItsWay( req );
     } else {
     	//std::cout << "Router set time" << simTime() <<endl;
     	req->setStartTime(simTime());
        requestQueue.push_back( req );
     }
 } else {
    sendMessageOnItsWay( req );
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
void Router::handleMessage(cMessage *msg)
{
 WebRequest *req = check_and_cast<WebRequest *>(msg);
 if (req == currentlyServing ) {
     // this is a "self message" implementing a delay....
     currentlyServing = NULL;
     sendMessageOnItsWay( req );
 } else {
    requestQueue.push_back( req );
 }
 //
 // If not currently serving/processing a request
 // pull one from the queue and start serving it..
 //
 if ( ! reqeuestQueue.empty() && currentlyServing == NULL) {
    currentlyServing = requestQueue.pop_front();
    scheduleAt(simTime() + par("delay"), currentlyServing);
 }
}
*/