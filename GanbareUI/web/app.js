//Put youtube API script to html file
var tag = document.createElement('script');
tag.src = 'https://www.youtube.com/iframe_api';
var firstScriptTag = document.getElementsByTagName('script')[0];
firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);

var uri = 'ws://localhost:1234';
var webSocket=null;
var isConnected=false;

function initSocket() {
    //console.log("Run");
    try {
        if (typeof MozWebSocket=='function') {
            WebSocket=MozWebSocket;
        }
        if (webSocket && webSocket.readyState===1) {
            webSocket.close();
        }
        webSocket= new WebSocket(uri);
        webSocket.onopen=function(e){
            console.log('connected');
            isConnected=true;
        }
        webSocket.onclose=function(e){
            //console.log('disconnected');
        }
        webSocket.onmessage = function (e) {
            console.log('Message: '+e.data);
            if (e.data==="1") {
                player.setVolume(100);
                player.playVideo();
            } else if (e.data==="0") {
                player.pauseVideo();
            } else {
                console.log('Data not recognized');
            }
        }
    } catch (exception) {
        console.log('Error: '+exception);
    }
}

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
    event.target.pauseVideo();
    initSocket();
}

