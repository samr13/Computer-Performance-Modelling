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


class ClientOpen :  public QueueNode {
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
    ClientOpen();
    virtual ~ClientOpen();
    virtual double getUtil(const char *node);
};

ClientOpen::ClientOpen()
{
     selfCallEvent = original = NULL;
     numMsg=1;
}

ClientOpen::~ClientOpen()
{
    cancelAndDelete(selfCallEvent);
    delete original;
}

Define_Module(ClientOpen);

double ClientOpen::getUtil(const char *node) { 
  //cout << "\n"<<getModuleByPath(node)<< endl;
 return check_and_cast<QueueNode *>(getModuleByPath(node)) -> getUtilization() /simTime(); 
 //cout<<getModuleByPath(node);
 }

void ClientOpen::initialize() {

     std::string filename = par("OutputFile");
     output.open(filename, std::ofstream::out);
     selfCallEvent = new cMessage("selfCallEvent");
     original=new cMessage("original");
     //selfCallEvent->setServed(false);
     //selfCallEvent->setRequestNumber(1);
     simtime_t when = par("InterarrivalTime");
     EV << "scheduled self call for " << when <<endl;
     scheduleAt(simTime() + when, selfCallEvent);
     /*
     msg = new WebRequest(...);
     msg -> setServed(false);
     msg -> setStart( simTime() );
     scheduleAt(msg, simTime() + interArrivalTime);
     */
}

void ClientOpen::handleMessage( cMessage *msg ) {
   //cout << "message: "<<msg <<endl;
   if (msg == selfCallEvent) {
          //cout << "Wait period is over, sending back message"<< numMsg<<" "<<simTime() <<" \n";
          
          //WebRequest *req = check_and_cast <WebRequest *> (msg);
          WebRequest *req = new WebRequest(to_string(numMsg).c_str());
          req->setRequestNumber(numMsg++);
          req->setServed(false);
          req->setStartTime( simTime() );
          send(req, "proxy$o");
          //original = NULL;      
          delete(selfCallEvent);
          selfCallEvent = new cMessage("selfCallEvent");
          simtime_t when = par("InterarrivalTime");
          //cout << "Message arrived after " << responseTime << " at"<<simTime()<< "  next msg at "<<simTime()+when <<endl;
          //cout << "scheduled self call for " << simTime() << " " <<when <<endl;
          scheduleAt(simTime() + when, selfCallEvent);
          /*
             WebRequest *req = new WebRequest();
             //req->setServed(false);
             req->setStartTime(simTime());
             send(req, "ClientOpen$o");
    
         simtime_t when = par ("InterarrivalTime");
         EV << "scheduled self call for " << when <<"seconds\n";
         WebRequest *selfCallEvent = new WebRequest();
         selfCallEvent->setRequestNumber(this->numMsg++);
         scheduleAt(simTime() + when, selfCallEvent);
          */
   } else {   
   // cout <<"else" <<endl;
         WebRequest *req = check_and_cast <WebRequest *> (msg);
         assert (req-> getServed());
         simtime_t responseTime = simTime() - req->getStartTime();
         
         delete(msg);
          output << simTime() << ", " << responseTime; 
          output << ", " << getUtil("^.proxy"); 
          output << ", " << getUtil("^.router"); 
          output << ", " << getUtil("^.originA"); 
          output << ", " << getUtil("^.originB"); 
          output << endl;
          //cout << "nessage receievd\n" <<endl;
          /*
          selfCallEvent = new cMessage("selfCallEvent");
          simtime_t when = par("InterarrivalTime");
         cout << "Message arrived after " << responseTime << " at"<<simTime()<< "  next msg at "<<simTime()+when <<endl;
          //cout << "scheduled self call for " << simTime() << " " <<when <<endl;
          scheduleAt(simTime() + when, selfCallEvent);
         //WebRequest *req = new WebRequest();
         //req->setRequestNumber(this->numMsg++);
         //req->setServed(false);
         //req->setStartTime(simTime());
         //send(req, "ClientOpen$o");
         */
  }   

/*
   if ( msg -> getServed() ) {
     // it's a request that's finally been satisfied...
     ...record some performance statistics....
     delete(msg);
   } else {

      delete(msg); // could probably re-use this
    
      // this must be a "self message, so time to send out a request...
      //msg = new WebRequest(...); // generate messages for ClientOpen...
      msg -> setServed( false );
      msg -> setStart( simTime() );
      sendMessageToClientOpen( msg );

      // now, send myself another "self message" to send next request
      msg = new WebRequest(...);
      msg -> setServed( false );
      scheduleAt(msg, simTime() + interArrivalTime);
   }
*/
}

