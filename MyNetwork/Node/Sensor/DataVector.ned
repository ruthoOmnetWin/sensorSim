package mynetwork.Node.Sensor;

simple DataVector 
{
    parameters:
        //postion of the data
        int posX;
        int posY;
        //type of the data
        int type;
        //value of the data
        int value;
	gates: 
	    output out; 
	    input in;  
}