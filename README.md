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

If you have an Ethernet-based WDB, connect it to your network. Note that it only supports 1GBit
ethernet, so if you have a switch which supports only 100 MBit, it won't work. A slowly blue 
blinking LED after boot means it's acquiring is network IP address through DHCP, and once it
succeeded, the LED will become green. Now you can try to ping the board. If that is successful,
you can start the wds server directly connectin to that board:

```
   $ wds -w wdxxx
```

where 'xxx' is the number of your board. If this is successful, you can connect your browser
to your sever at http://localhost:8080. You can also remotely connect to your server, but 
then you have to make sure that the firewall allows access to port 8080.

The oscilloscope application in the web browser is mainly self-explanatory and modeled after
a 'normal' oscilloscope. The only special thing is the trigger configuration, but it comes
with a dedicated help page.