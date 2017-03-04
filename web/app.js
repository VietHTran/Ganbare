var tag = document.createElement('script');
tag.src = "https://www.youtube.com/iframe_api";
var firstScriptTag = document.getElementsByTagName('script')[0];
firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);

var socket = io.connect('http://127.0.0.1:5000');
socket.on('connect', function connect() {
		console.log("Sucessfully connect to Flask.");
        socket.emit('message', "Connected to FLASK");
});

socket.on('message', function (data) {
	console.log("Data: "+data);
	if (data==="1") {
		player.setVolume(80);
		player.playVideo();
	} else if (data==="0") {
		player.pauseVideo();
	} else {
		console.log("Unrecognized data");
	}
    socket.emit('message', "send next");
});

//Youtube API stuff

var player;
function onYouTubeIframeAPIReady() {
    player = new YT.Player('player', {
        height: '390',
        width: '640',
        videoId: 'o2BE3IILRto',
        events: {
            'onReady': onPlayerReady
        }
    });
}

function onPlayerReady(event) {
    event.target.setVolume(80);
    event.target.playVideo();
}

