import xml.etree.ElementTree as ET
from xml.etree.ElementTree import SubElement

tree = ET.parse('XMLPetoon.xml')
root = tree.getroot()


albums =  root.findall("album")
for album in albums:
    print(album.attrib)
add = SubElement(albums[0],'test',name="mung")
print("After Romoved")
for album in albums:
    print(album.attrib)


##print(root.tag)
##print(root.attrib)
##
##for node in root.findall("album"):
##    print(node.tag,node.attrib)
