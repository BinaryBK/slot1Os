<?php
// Set the content type to plain text
header('Content-Type: text/plain');

// Read the contents of the text file
$filename = 'sample.txt';
if (file_exists($filename)) {
    echo file_get_contents($filename);
} else {
    echo "File not found.";
}
?>