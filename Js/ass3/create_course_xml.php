<?php
// Define the XML structure
$xmlContent = '<?xml version="1.0" encoding="UTF-8"?>' . "\n";
$xmlContent .= '<Course>' . "\n";
$xmlContent .= '    <ComputerScience>' . "\n";

// Array of students
$students = [
    [
        'name' => 'Alice Johnson',
        'class' => 'TYBSc',
        'percentage' => '85.5'
    ],
    [
        'name' => 'Bob Smith',
        'class' => 'TYBSc',
        'percentage' => '78.0'
    ],
    [
        'name' => 'Charlie Brown',
        'class' => 'TYBSc',
        'percentage' => '92.0'
    ],
    [
        'name' => 'Diana Prince',
        'class' => 'TYBSc',
        'percentage' => '88.5'
    ],
    [
        'name' => 'Ethan Hunt',
        'class' => 'TYBSc',
        'percentage' => '90.0'
    ]
];

// Loop through each student and add to XML
foreach ($students as $student) {
    $xmlContent .= '        <Student name="' . htmlspecialchars($student['name']) . '"/>' . "\n";
    $xmlContent .= '        <Class name="' . htmlspecialchars($student['class']) . '"/>' . "\n";
    $xmlContent .= '        <percentage>' . htmlspecialchars($student['percentage']) . '</percentage>' . "\n";
}

// Close the XML tags
$xmlContent .= '    </ComputerScience>' . "\n";
$xmlContent .= '</Course>';

// Specify the file name
$filename = 'Course.xml';

// Write the XML content to the file
if (file_put_contents($filename, $xmlContent) !== false) {
    echo "XML file '$filename' created successfully.";
} else {
    echo "Error creating XML file.";
}
?>