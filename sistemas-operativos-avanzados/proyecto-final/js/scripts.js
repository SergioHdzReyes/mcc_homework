let usernameInput = $('#username-input');
let pathInput = $('#path-input');
let userInput = $('input#user-input');
let history = $('.history');

$(document).ready(function() {
    $(".terminal").on('click', function() {
	userInput.focus();
    });

    userInput.keypress(function (e) {
	var key = e.which;
	if(key == 13)  // Enter
	{
	    if (userInput.val() == 'clear') {
		history.empty();
	    } else {
		send_command();
	    }

	    // Se resetea comando de usuario
	    $("#user-input").val('');
	}
    });
});

function send_command()
{
    let serverResponse = '';

    $.ajax({
        type: 'POST',
        url: 'https://maps.googleapis.com/maps/api/geocode/json?address=1600+Amphitheatre+Parkway,+Mountain+View,+CA&key=YOUR_API_KEY',
        data: {},
	dataType: 'json',
        success: function (response) {
	    console.log('RESPUESTA-GOOGLE:');
	    console.log(response);
            if (response) {
		
            } else {
		
            }
	    serverResponse = 'Respuesta de servidor';
        },
        error: function (error) {
	    console.log(error);
            alert('Ocurrio un error al procesar la informacion.');
        },
        complete: function () {
            console.log('Solicitud completa');
        }
    });

    // Se agrega a historial
    history.append(
	$('<div/>', {class: 'history-row'}).append(
	    $('<span/>', {text: usernameInput.text() + ' ', class: 'username'}),
	    $('<span/>', {text: pathInput.text() + ' ', class: 'path'}),
	    $('<span/>', {text: userInput.val()}),
	    $('<p/>', {text: serverResponse}),
	)
    );
}
