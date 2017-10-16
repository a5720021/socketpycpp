<?php
require_once "nusoap.php";
/** @test */

$client = new SoapClient("http://192.168.1.42:5000/soap/someservice?wsdl",true);

$error = $client->getError();
if ($error) {
    echo "<h2>Constructor error</h2><pre>" . $error . "</pre>";
}

$params = array("text"=>"Pathompat");
$result = $client->call("echo",$params);

if ($client->fault) {
    echo "<h2>Fault</h2><pre>";
    print_r($result);
    echo "</pre>";
}
else {
    $error = $client->getError();
    if ($error) {
        echo "<h2>Error</h2><pre>" . $error . "</pre>";
    }
    else {
        echo "<h2>Test</h2><pre>";
        echo $result;
        echo "</pre>";
    }
}

$client -> setEndpoint('http://localhost/index.php');
