Elmar Schmid [elmar.schmid@psi.ch]

## Authors
Stefan Ritt [stefan.ritt@psi.ch]
Elmar Schmid [elmar.schmid@psi.ch]
Luca Galli [luca.galli@pi.infn.it]
Marco Francesconi [marco.francesconi@pi.infn.it]

# Origin
This repository was originally part of a larger repository that is now available here:
https://bitbucket.org/twavedaq/wavedaq_old.git

There is a main repository containing all WaveDAQ repositories as submodules:
https://bitbucket.org/twavedaq/wavedaq_main.git

Note that the major part of the history was preserved when splitting the repository.

# Description
This repository contains files for the WaveDAQ software running on various parts in the system:

  * The WaveDREAM Server (wds) runs on a PC, connects to WaveDREAM boards and has a web server to display oscilloscope-like waveforms
  * The Data Concentrator Board Server (dcbs) runs on a Data Concentrator Board (DCB)
	
# Installation of WDS
The WaveDREAM Server (wds) can be installed standalone to connect to a Ethernet-based WaveDREAM board.
To do so, follow these steps:

  * Clone the develop branch of the repository: 
  
  ```  
  $ git clone https://bitbucket.org/twavedaq/wavedaq_sw.git
  $ cd wavedaq_sw
  $ git checkout develop
  $ git submodule update --init
  ```
    
  * Compile the wds server:

   ```
   $ mkdir build; cd build
   $ cmake ..
   $ make
   ```
      
  * Run the server:
 
 ```
   $ wds/wds
 ```

Now you can connect to your server via http://<servername>:8080 and choose a WDB to connect to.