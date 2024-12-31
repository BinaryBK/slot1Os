<?php
// Create a new XML document
$xml = new SimpleXMLElement('<?xml version="1.0" encoding="UTF-8"?><CricketTeam></CricketTeam>');

// Add India as a country
$india = $xml->addChild('Country');
$india->addAttribute('name', 'India');

// Add players for India
$player1 = $india->addChild('PlayerName', 'Virat Kohli');
$player1->addChild('Wickets', '0');
$player1->addChild('Runs', '12000');

$player2 = $india->addChild('PlayerName', 'Jasprit Bumrah');
$player2->addChild('Wickets', '120');
$player2->addChild('Runs', '0');

// Add England as a country
$england = $xml->addChild('Country');
$england->addAttribute('name', 'England');

// Add players for England
$player3 = $england->addChild('PlayerName', 'Ben Stokes');
$player3->addChild('Wickets', '70');
$player3->addChild('Runs', '4000');

$player4 = $england->addChild('PlayerName', 'Joe Root');
$player4->addChild('Wickets', '0');
$player4->addChild('Runs', '8000');

// Save the XML to a file
$xml->asXML('cricket.xml');

// Output success message
echo "cricket.xml file has been created successfully.";
?>