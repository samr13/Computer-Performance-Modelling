#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <deque>
#include <WebRequest.h>
#include <QueueNode.h>

class Proxy :public QueueNode {
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
    Proxy();
    virtual ~Proxy();
    virtual void sendMessageOnItsWay( WebRequest *req );
};

Proxy::Proxy()
{
    event = original = NULL;
    currentlyServing = NULL;
    utilization=0;
    //requestQueue = node->qq;
}

Proxy::~Proxy()
{
    cancelAndDelete(event);
    delete original;
}

Define_Module(Proxy);

void Proxy::initialize() {
     node = new Proxy();
      busyTime = 0;
     //WATCH(busyTime);
     //requestQueue = node->qq;
     /*
     std::string filename = par("OutputFile");
     output.open(filename, std::ofstream::out);
     selfCallEvent = new cMessage("selfCallEvent");
     original=new cMessage("original");
     //selfCallEvent->setServed(false);
     //selfCallEvent->setRequestNumber(1);
     simtime_t when = par("InterarrivalTime");
     EV << "scheduled self call for " << when <<endl;
     scheduleAt(simTime() + when, selfCallEvent);
     
     msg = new WebRequest(...);
     msg -> setServed(false);
     msg -> setStart( simTime() );
     scheduleAt(msg, simTime() + interArrivalTime);
     */
}
/*
void Proxy::handleMessage( cMessage *msg ) {
	  WebRequest *req = check_and_cast <WebRequest *> (msg);
    
    if (req->getServed()) {
       send(req, "client$o");    
    } else {
        if (uniform(0,1) < 0.7) {
         req->setServed(true); 
         send(req, "client$o");
        } else {
    	    send(req, "router$o");
        }
    }
   	  
   	  if (msg==event)
   	  {
        	EV << "Wait period is over, sending back message\n";
        	send(original, "router$o");
        	original = NULL;
      } else {
            simtime_t delay = 0.035;
            event = new cMessage("event");	
            EV << "Message arrived, starting to wait " << delay << " secs...\n";
            original = msg;
            scheduleAt(simTime()+delay, event);      	
      }
      
   
}
*/
void Proxy::sendMessageOnItsWay( WebRequest *req ) {
    //WebRequest *req = check_and_cast <WebRequest *> (msg);
    //std::cout << "inside sendMessageOnItsWay" <<req->getServed() <<endl;
    if (req->getServed()) {
       send(req, "client$o");    
    } else {
        if (uniform(0,1) < 0.7) {
         req->setServed(true); 
         send(req, "client$o");
        } else {
          send(req, "router$o");
        }
    }
}    

void Proxy::handleMessage(cMessage *msg)
{
 WebRequest *req = check_and_cast<WebRequest *>(msg);
 //if (!req->getServed()) {
     if (req == currentlyServing ) {
         // this is a "self message" implementing a delay....
      //std::cout << currentlyServing << " " <<req->getRequestNumber() << " " <<1000*req->getStartTime() << " "<< 1000*((simTime()-req->getStartTime()).dbl())<<endl; 
        //std::cout <<  currentlyServing << " " << busyTime<< " " <<simTime() << " "<< busyTime/simTime() <<endl;
         currentlyServing = NULL;
         simtime_t serviceTime = par("ServiceTime");
         busyTime+=(serviceTime);
         //std::cout << serviceTime << " " <<simTime()-req->getStartTime() <<endl;
         //busyTime+=simTime()-req->getStartTime();
         setUtilization(busyTime);
         //setUtilization( (simTime()-req->getStartTime()).dbl());
         sendMessageOnItsWay( req );
     } else {
        req->setStartTime(simTime());
       // std::cout <<  req->getRequestNumber() << " "  << 1000*simTime() <<endl;
        requestQueue.push_back( req );
     }
 /*} else {
    //double d= getUtilization();
    //std::cout <<  " getutil" <<req << " " <<1000*req->getStartTime()<< " " << 1000*d<<endl;
    sendMessageOnItsWay( req );
 }*/
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