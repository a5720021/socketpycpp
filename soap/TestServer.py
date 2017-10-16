from flask import Flask
from flask.ext.spyne import Spyne
from spyne.protocol.soap import Soap11
from spyne.model.primitive import Unicode, Integer
from spyne.model.complex import Iterable, ComplexModel

app = Flask(__name__)
spyne = Spyne(app)
    
class SomeSoapService(spyne.Service):
    __service_url_path__ = '/soap/someservice'
    __in_protocol__ = Soap11(validator='lxml')
    __out_protocol__ = Soap11()

    @spyne.srpc(Unicode, _returns=Iterable(Unicode))
    def echo(text):
        for i in range(cnt):
            yield text

if __name__ == '__main__':
    app.run(host = '192.168.1.42')
