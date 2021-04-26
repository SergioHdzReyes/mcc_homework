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
		send_command($(this).val());
	    }

	    // Se resetea comando de usuario
	    $("#user-input").val('');
	}
    });
});

function send_command(command)
{
    let serverResponse = '';

    $.ajax({
        type: 'put',
	url: 'http://localhost/commands',
	data: {command: command},
	dataType: 'jsonp',
	jsonp: 'callback_shr',
        success: function (response) {
	    console.log('success');
        },
        error: function (error) {
	    console.log('error');
        },
        complete: function (resp) {
	    console.log('complete');
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

function callback_shr(param)
{
    console.log('callback_shr');
    console.log(param);
}
