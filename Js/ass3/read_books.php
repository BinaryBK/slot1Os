<?php
// Load the XML file into a SimpleXMLElement object
$xml = simplexml_load_file('books.xml');

// Check if the file was loaded successfully
if ($xml === false) {
    echo "Failed to load XML file.";
    exit;
}

// Display the attributes and elements
foreach ($xml->book as $book) {
    echo "Book ID: " . $book['id'] . "<br>"; // Displaying the attribute 'id'
    echo "Title: " . $book->title . "<br>"; // Displaying the 'title' element
    echo "Author: " . $book->author . "<br>"; // Displaying the 'author' element
    echo "Year: " . $book->year . "<br>"; // Displaying the 'year' element
    echo "Genre: " . $book->genre . "<br><br>"; // Displaying the 'genre' element
}
?>