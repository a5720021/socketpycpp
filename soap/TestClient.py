from suds.client import Client as SudsClient

url = 'http://192.168.1.42:5000/soap/someservice?wsdl'
client = SudsClient(url=url, cache=None)
r = client.service.echo('hello world')
print r

