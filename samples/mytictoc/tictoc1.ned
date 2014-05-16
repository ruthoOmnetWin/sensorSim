//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


simple Txc1
{
    parameters:
        bool sendMsgOnInit = default(false); // whether the module should send out a message on initialization
        int limit = default(2);   // another parameter with a default value
        @display("i=block/routing"); // add a default icon
    gates:
        input in;
        output out;
}

simple Tic extends Txc1
{
    parameters:
        sendMsgOnInit = true;
        @display("i=,cyan"); // do not change the icon (first arg of i=) just colorize it
}

simple Toc extends Txc1
{
    parameters:
        sendMsgOnInit = false;
        @display("i=,gold"); // do not change the icon (first arg of i=) just colorize it
           
}

//
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.
//
network Tictoc1
{
    submodules:
        tic: Tic;
        toc: Toc;
    connections:
        tic.out --> {  delay = 100ms; } --> toc.in;
        tic.in <-- {  delay = 100ms; } <-- toc.out;
}
