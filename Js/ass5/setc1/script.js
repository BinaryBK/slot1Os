$(document).ready(function() {
    const suggestionsArray = [
        "Apple",
        "Banana",
        "Cherry",
        "Date",
        "Grape",
        "Kiwi",
        "Mango",
        "Orange",
        "Peach",
        "Pineapple",
        "Strawberry",
        "Watermelon"
    ];

    $('#search').on('input', function() {
        const query = $(this).val().toLowerCase();
        $('#suggestions').empty();

        if (query.length > 0) {
            const filteredSuggestions = suggestionsArray.filter(item => item.toLowerCase().includes(query));

            if (filteredSuggestions.length > 0) {
                filteredSuggestions.forEach(item => {
                    $('#suggestions').append(`<div class="suggestion-item">${item}</div>`);
                });
                $('#suggestions').show();
            } else {
                $('#suggestions').hide();
            }
        } else {
            $('#suggestions').hide();
        }
    });

    $(document).on('click', '.suggestion-item', function() {
        $('#search').val($(this).text());
        $('#suggestions').hide();
    });

    $(document).on('click', function() {
        $('#suggestions').hide();
    });
});