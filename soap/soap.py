import zeep

wsdl = 'http://192.168.1.42:5000/soap/someservice?wsdl'
client = zeep.Client(wsdl=wsdl)
print(wsdl)
print(client.service.echo('Pat'))
