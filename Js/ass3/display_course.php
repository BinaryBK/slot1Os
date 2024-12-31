<?php
// Load the XML file
$xml = simplexml_load_file('Course.xml') or die("Error: Cannot create object");

// Output the HTML structure
echo '<!DOCTYPE html>';
echo '<html lang="en">';
echo '<head>';
echo '<meta charset="UTF-8">';
echo '<meta name="viewport" content="width=device-width, initial-scale=1.0">';
echo '<title>Course Details</title>';
echo '<link rel="stylesheet" type="text/css" href="styles.css">';
echo '</head>';
echo '<body>';
echo '<h1>Course Details</h1>';

// Start the table
echo '<table>';
echo '<tr>';
echo '<th>Student Name</th>';
echo '<th>Class Name</th>';
echo '<th>Percentage</th>';
echo '</tr>';

// Loop through each student and display their details
foreach ($xml->ComputerScience->Student as $student) {
    echo '<tr>';
    echo '<td>' . htmlspecialchars($student) . '</td>';
    echo '<td>' . htmlspecialchars($student->Class) . '</td>';
    echo '<td>' . htmlspecialchars($student->percentage) . '</td>';
    echo '</tr>';
}

// Close the table
echo '</table>';

// Close the HTML tags
echo '</body>';
echo '</html>';
?>
