# Sensor Simulation for Omnet++

> a Codedocumentation can be found inside CodeDocu.html

## Installation of a Network using Sensors

> you can have a look inside the examples/ folder or even copy the BasicExample inside it

* you will need to import the MiXiM Framework inside your project
* import the SensorTechnology project inside your project
* create the following files inside your project
 * config.xml - Options for MiXiM
 * omnetpp.ini - set Parameters for the Simulation
  * you can also set the values inside the ned-files
 * create an folder data/ with the following files inside
 * alternatively you can just start the simulation and the world model will create these files itself, but the simulation will need to be restarted before you can use it (it will throw an runtimeException)
 * the files to be created:
  * humidity.xml
  * light.xml
  * pressure.xml
  * temperature.xml
  * initialise these files with the following content: 

<?xml version="1.0" encoding="UTF-8"?>
<type>
</type>

for example:

<?xml version="1.0" encoding="UTF-8"?>
<humidity>
</humidity>

## usage

> again you can just take a look inside the BasicExample
> all of the needed parameters are there set as an example

* if you want you can use sensortechnology.src.SensorNetworkInterface.BasicWSN
* let your network inherit from it and the most initialisation is done

* left to do:
 * set numHosts to the amount of sensor nodes
 * create as many sensor nodes as you want
 * set numHosts for each of the sensor modules (needed by MiXiMs wireless communication)
* if you to define the sensors use the following booleans: (default is false)
 * hasTemperatureSensor
 * hasPressureSensor
 * hasHumiditySensor
 * hasLightSensor
* allow unconnected connections, so that the MiXiM radioIn can be used

### relevant parameters

> you can again just have a look inside BasicExamples omnetpp.ini

#### Energy consumption

* currentConsumption - integer (in mA): consumption per time
* energyConsumption - integer (in mWs): consumption of a single operation
* battery.nominal - double (in mAh): battery storage

#### Energy consumption of the Processor modes 

* currentConsumptionNormal - integer (in mA)
* energyConsumptionNormal - integer (in mWs)
* currentConsumptionPowerSaving - integer (in mA)
* energyConsumptionPowerSaving - integer (in mWs)
* currentConsumptionHighPerformance - integer (in mA)
* energyConsumptionHighPerformance - integer (in mWs)

#### Energy consumption for the periphery by processor mode

> influences the periphery modules energy consumption over time and per operation by the active power mode

* normalRatio - double
* powerSavingRatio - double
* highPerformanceRatio - double

#### Events etc.

* dataGranularity - integer: defines how coarse the sensor data is generated; the value defines the size of the cubes which uses one sensor value
* sensingIntervall - integer (in s): time intervalls for sensing
* shiftProcessorModeNormalIntervall - integer (in s): how long to stay inside normal mode before switching to next mode
* shiftProcessorModePowerSavingIntervall - integer (in s): how long to stay inside power saving mode
* shiftProcessorModeHighPerformanceIntervall - integer (in s): how long to stay inside high perfomance mode
* collectStatisticsIntervall - integer (in s): time intervall for collecting statistics
* readAndClearStorageIntervall - integer (in s): time intervall for reading and clearing the memory
* dataRecreationIntervall - integer (in s): time intervall for recreation of new sensing data

#### Netzwerkparameter
* createData - boolean: if true, new data will be created on start
* numHosts - integer: amount of nodes inside the network
* noisyWorld - boolean: for debugging, if true, the world will output informations about status and actions
* noisy - boolean: same like noisyWorld, but for the sensorNode
* playgroundSizeX - integer (in m): size of the X-dimension
* playgroundSizeY - integer (in m): size of the Y-dimension
* playgroundSizeZ - integer (in m): size of the Z-dimension

#### Sensorknoten
* dataBandwidth - double (in bps): bandwidth of the channels called data (f.e. from transducer -> processor)
* controlBandwidth - double (in bps): bandwidth of the channels called control (f.e. from processor -> sensing unit)
* Memory.storageSize - integer: amount of datasets that the memory can store
