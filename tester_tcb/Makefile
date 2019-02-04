ROOTCFLAGS:= `root-config --cflags`
ROOTLFLAGS:= `root-config --glibs`

FLAGS         = -g -DOS_LINUX -Wall
FLAGS += -I $(MEG2SYS)/common/include
FLAGS += -I $(WDBSYS)/software/tcb -I $(WDBSYS)/../mscb/include

TESTER_OBJECTS=  TCBTester.o TCBTesterWaveform.o
WFM_OBJECTS   =  MEGFADCWaveform.o MEGDiscrWaveform.o 
TCB_OBJECTS   =  TCBLib.o 
MSCB_OBJECTS  =  mscb.o
OBJECTS       =  main.o myDict.o
OUTNAME	      =  tester

$(OUTNAME): $(OBJECTS) $(WFM_OBJECTS) $(TESTER_OBJECTS) $(TCB_OBJECTS) $(MSCB_OBJECTS)
	$(LINK.cc) $(FLAGS) $(ROOTCFLAGS) $^ -o $@ $(ROOTLFLAGS)
$(OBJECTS): %.o: %.cpp
	$(LINK.cc) $(FLAGS) $(ROOTCFLAGS) -c $< -o $@
$(WFM_OBJECTS): %.o: $(MEG2SYS)/common/src/waveform/%.cpp
	$(LINK.cc) $(FLAGS) $(ROOTCFLAGS) -c $< -o $@
$(TESTER_OBJECTS): %.o: %.cpp
	$(LINK.cc) $(FLAGS) $(ROOTCFLAGS) -c $< -o $@
$(TCB_OBJECTS): %.o: $(WDBSYS)/software/tcb/%.cpp
	$(LINK.cc) $(FLAGS) -c $< -o $@
$(MSCB_OBJECTS): %.o: $(WDBSYS)/../mscb/src/%.c
	$(LINK.c) $(FLAGS) -c $< -o $@

myDict.cpp: 
	rootcint -f myDict.cpp -c $(MEG2SYS)/common/include/waveform/MEGFADCWaveform.h $(MEG2SYS)/common/include/waveform/MEGDiscrWaveform.h

clean: 
	rm *.o myDict.cpp *.pcm $(OUTNAME)
