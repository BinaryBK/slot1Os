<?php
// Define a variable to hold the error message
$error = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Check if email is empty
    if (empty($_POST["email"])) {
        $error = "Email is required.";
    } else {
        $email = $_POST["email"];
        // Validate email format
        if (filter_var($email, FILTER_VALIDATE_EMAIL)) {
            $error = "$email is a valid email address.";
        } else {
            $error = "$email is not a valid email address.";
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Email Validation</title>
</head>
<body>

    <h2>Email Validation Form</h2>
    <form method="POST" action="">
        <label for="email">Enter your email:</label>
        <input type="email" id="email" name="email" required>
        <input type="submit" value="Validate Email">
    </form>

    <!-- Display error or success message -->
    <?php
    if (!empty($error)) {
        echo "<p>$error</p>";
    }
    ?>

</body>
</html>
