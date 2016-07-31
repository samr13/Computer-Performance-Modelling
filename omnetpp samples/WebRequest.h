
#ifndef _WebRequest_H_
#define _WebRequest_H_

#include <omnetpp.h>


class WebRequest : public ::cMessage
{
private:
    bool served;
    simtime_t startTime;
    int requestNumber;
    void copy(const WebRequest& other);
  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const WebRequest&);

public:
    WebRequest(const char *name=NULL, int kind=0);
    WebRequest(const WebRequest& other);
    virtual ~WebRequest();
    WebRequest& operator=(const WebRequest& other);
    //virtual WebRequest *dup() const {return new WebRequest(*this);}

    // field getter/setter methods
    virtual bool getServed() const;
    virtual void setServed(bool source);
    virtual simtime_t getStartTime() const;
    virtual void setStartTime(simtime_t destination);
    virtual int getRequestNumber() const;
    virtual void setRequestNumber(int hopCount);
};

#endif