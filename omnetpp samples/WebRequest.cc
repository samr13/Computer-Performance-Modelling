#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <fstream>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <WebRequest.h>

using namespace std;

Register_Class(WebRequest);

WebRequest::WebRequest(const char *name, int kind) : ::cMessage(name,kind)
{
    this->served = 0;
    this->startTime = 0;
    this->requestNumber = 0;
}

WebRequest::WebRequest(const WebRequest& other) : ::cMessage(other)
{
    copy(other);
}

WebRequest::~WebRequest()
{
}

WebRequest& WebRequest::operator=(const WebRequest& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void WebRequest::copy(const WebRequest& other)
{
    this->served = other.served;
    this->startTime = other.startTime;
    this->requestNumber = other.requestNumber;
}


bool WebRequest::getServed() const
{
    return served;
}

void WebRequest::setServed(bool served)
{
    this->served = served;
}

simtime_t WebRequest::getStartTime() const
{
    return startTime;
}

void WebRequest::setStartTime(simtime_t startTime)
{
    this->startTime = startTime;
}

int WebRequest::getRequestNumber() const
{
    return requestNumber;
}

void WebRequest::setRequestNumber(int requestNumber)
{
    this->requestNumber = requestNumber;
}
