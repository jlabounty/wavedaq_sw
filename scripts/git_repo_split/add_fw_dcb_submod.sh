#!/bin/bash

git checkout develop

mkdir library
cd library
#mkdir TCL
mkdir VHDL
mkdir VivadoIp
cd ..

#git submodule add https://github.com/paulscherrerinstitute/PsiSim.git TCL/PsiSim
#git submodule add https://github.com/paulscherrerinstitute/PsiIpPackage.git TCL/PsiIpPackage
git submodule add https://github.com/paulscherrerinstitute/psi_common.git library/VHDL/psi_common
#git submodule add https://github.com/paulscherrerinstitute/psi_tb.git library/VHDL/psi_tb
git submodule add https://github.com/paulscherrerinstitute/vivadoIP_clock_measure.git library/VivadoIp/vivadoIP_clock_measure
git submodule init
git submodule update --recursive

#git add .gitmodules
#git commit -m "Configured submodules"
#git push
