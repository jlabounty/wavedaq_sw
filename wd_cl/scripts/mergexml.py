#!/usr/bin/env python
import xml.etree.ElementTree as ET
import copy
import sys

#board processing logic
def doBoard(xmlElement, output, crateName):
    print("processing board " + xmlElement.attrib["Name"]);
    #print("./Crate[@Name=\"%s\"]/%s[@Name=\"%s\"]" % (crateName, xmlElement.tag, xmlElement.attrib["Name"]))
    for wdb in output.findall("./Crate[@Name=\"%s\"]/%s[@Name=\"%s\"]" % (crateName, xmlElement.tag, xmlElement.attrib["Name"])):
        print("\tfound")
        for el in xmlElement:
            tag = wdb.find(el.tag)
            if tag is None:
                #copy over
                print("\tcreate new tag "+el.tag)
                copiedElement = copy.deepcopy(el)
                wdb.append(copiedElement)
            else :
                #update
                print("\tupdating tag "+ tag.tag)
                tag.text = el.text

#custom output
def indent(elem, level=0, hor='   ', ver='\n'):
    i = ver + level * hor
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + hor
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
        for elem in elem:
            indent(elem, level + 1, hor, ver)
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
    else:
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i

if len(sys.argv) != 4:
    print("usage mergexml.py original.xml mod.xml output.xml")
    sys.exit()

try:
    inputTree = ET.parse(sys.argv[1])
except ET.ParseError:
    print("cannot parse input file " + sys.argv[1])
    sys.exit()

inputRoot = inputTree.getroot()

try:
    modTree = ET.parse(sys.argv[2])
except ET.ParseError:
    print("cannot parse modification file " + sys.argv[1])
    sys.exit()

modRoot = modTree.getroot()

for crate in modRoot.findall('Crate'):
    for board in crate:
        doBoard(board, inputRoot, crate.attrib["Name"])

#ET.indent(inputRoot)
indent(inputRoot)
inputTree.write(sys.argv[3])
