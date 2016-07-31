#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <fstream>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <WebRequest.h>
#include <queue>
#include <QueueNode.h>
#include <string> 

using namespace std;


class ClientClosed :  public QueueNode {
private:
    int numMsg;
    cMessage *selfCallEvent;
    cMessage *original;
    ofstream output;
     
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  public:
    ClientClosed();
    virtual ~ClientClosed();
    virtual double getUtil(const char *node);
};

ClientClosed::ClientClosed()
{
     selfCallEvent = original = NULL;
     numMsg=1;
}

ClientClosed::~ClientClosed()
{
    cancelAndDelete(selfCallEvent);
    delete original;
}

Define_Module(ClientClosed);

double ClientClosed::getUtil(const char *node) { 
  //cout << "\n"<<getModuleByPath(node)<< endl;
 return check_and_cast<QueueNode *>(getModuleByPath(node)) -> getUtilization() /simTime(); 
 //cout<<getModuleByPath(node);
 }

void ClientClosed::initialize() {

     std::string filename = par("OutputFile");
     output.open(filename, std::ofstream::out);
/*
     selfCallEvent = new cMessage("selfCallEvent");
     original=new cMessage("original");
     //selfCallEvent->setServed(false);
     //selfCallEvent->setRequestNumber(1);
     simtime_t when = par("InterarrivalTime");
     EV << "scheduled self call for " << when <<endl;
     scheduleAt(simTime() + when, selfCallEvent);
*/
     int N=par("NumJobs");
     WebRequest *messages[N];
    for (int i = 0; i < N; i++) {
     messages[i] = new WebRequest(to_string(numMsg).c_str());
     messages[i]->setRequestNumber(numMsg++);
     messages[i]->setServed(false);
     messages[i]->setStartTime( simTime() );
     send( messages[i], "proxy$o" );
   }

}

void ClientClosed::handleMessage( cMessage *msg ) {
   //cout << "message: "<<msg <<endl;
  WebRequest *req = check_and_cast <WebRequest *> (msg);
   if (!req->getServed()) {
         
          //WebRequest *req = check_and_cast <WebRequest *> (msg);
          req->setServed(false);
          req->setStartTime( simTime() );
          send(req, "proxy$o");
          //delete(selfCallEvent);
          //selfCallEvent = new cMessage("selfCallEvent");


   } else {   
   // cout <<"else" <<endl;
         //WebRequest *req = check_and_cast <WebRequest *> (msg);
         assert (req-> getServed());

         simtime_t responseTime = simTime() - req->getStartTime();
         
         delete(msg);
          output << simTime() << ", " << responseTime; 
          output << ", " << getUtil("^.proxy"); 
          output << ", " << getUtil("^.router"); 
          output << ", " << getUtil("^.originA"); 
          output << ", " << getUtil("^.originB"); 
          output << endl;
         
         WebRequest *req = new WebRequest(to_string(numMsg).c_str());
         req->setRequestNumber(numMsg++);
         req ->setServed(false);
         simtime_t when = par("ThinkTime");
         scheduleAt(simTime() + when, req);         
    
  }   

}

