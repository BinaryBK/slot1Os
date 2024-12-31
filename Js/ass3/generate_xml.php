<?php
// Set the content type to XML
header('Content-Type: application/xml; charset=ISO-8859-1');

// Create a new XML document
$xml = new SimpleXMLElement('<?xml version="1.0" encoding="ISO-8859-1"?><CDStore></CDStore>');

// Add movies to the XML
$movies = [
    ['Title' => 'Mr. India', 'Release Year' => '1987'],
    ['Title' => 'Holiday', 'Release Year' => '2014'],
    ['Title' => 'LOC', 'Release Year' => '2003'],
];

foreach ($movies as $movie) {
    $movieElement = $xml->addChild('Movie');
    $movieElement->addChild('Title', $movie['Title']);
    $movieElement->addChild('ReleaseYear', $movie['Release Year']);
}

// Output the XML
echo $xml->asXML();
?>