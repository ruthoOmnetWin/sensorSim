package sensor;
//import org.mixim.base.connectionManager.NicEntry;

simple dataVector //extends Nic
{
    parameters:
        //postion of the data
        int posX;
        int posY;
        //type of the data
        string type;
        //value of the data
        int value;
	gates: 
	    output out; 
	    input in;  
}