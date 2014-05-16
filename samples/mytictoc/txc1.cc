//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <string.h>
#include <omnetpp.h>


class Txc1 : public cSimpleModule
{
  private:
    int counter;  // Note the counter here
    cMessage *event; // pointer to the event object which we'll use for timing
    cMessage *tictocMsg; // variable to remember the message until we send it back
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

// The module class needs to be registered with OMNeT++
Define_Module(Txc1);

void Txc1::initialize()
{
    counter = par("limit");
    WATCH(counter);
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be `tic'.

    // Am I Tic or Toc?
    if (par("sendMsgOnInit").boolValue() == true)
    {
	EV << "Sending initial message\n";
        // create and send first message on gate "out". "tictocMsg" is an
        // arbitrary string which will be the name of the message object.
        cMessage *msg = new cMessage("tictocMsg");
        send(msg, "out");
    }
}

void Txc1::handleMessage(cMessage *msg)
{
   if (counter >= 0) {
    counter--;		
    EV << "Received message `" << msg->getName() << "', sending it out again\n";
    // The handleMessage() method is called whenever a message arrives
    // at the module. Here, we just send it to the other module, through
    // gate `out'. Because both `tic' and `toc' does the same, the message
    // will bounce between the two.
    send(msg, "out");
   } else {
    EV << msg->getName() << "'s counter reached zero\n"; delete msg;
  }
	EV << counter;
}
