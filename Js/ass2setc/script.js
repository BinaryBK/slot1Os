$(document).ready(function() {
    $('#validateBtn').click(function() {
        // Get the value of the username input
        var username = $('#username').val().trim();
        var message = '';

        // Validate the username
        if (username === '') {
            message = 'Enter username';
        } else if (username.length < 3) {
            message = 'Username is too short';
        } else {
            message = 'Valid username';
        }

        // Display the message
        $('#message').text(message);
    });
});