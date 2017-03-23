//Put youtube API script to html file
var tag = document.createElement('script');
tag.src = 'https://www.youtube.com/iframe_api';
var firstScriptTag = document.getElementsByTagName('script')[0];
firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);

var uri = 'ws://localhost:1234';
var webSocket=null;
var isConnected=false;

function getQuery(name) {
    var url = window.location.href;
    name = name.replace(/[\[\]]/g, '\\$&');
    var regex = new RegExp('[?&]' + name + '(=([^&#]*)|&|#|$)'),
        results = regex.exec(url);
    if (!results) return null;
    if (!results[2]) return '';
    return decodeURIComponent(results[2].replace(/\+/g, ' '));
}

function initSocket() {
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
            console.log('disconnected');
        }
        webSocket.onmessage = function (e) {
            console.log('Message: '+e.data);
            if (e.data==='1') {
                player.setVolume(100);
                player.playVideo();
            } else if (e.data==='0') {
                player.pauseVideo();
            } else if (e.data==='2') {
                webSocket.close();
            } else {
                console.log('Data not recognized');
            }
        }
    } catch (exception) {
        console.log('Error: '+exception);
    }
}

var key = getQuery('key');
if (key === '' || key === null) {
    key='o2BE3IILRto';
}
console.log('key: '+key);

//Youtube API stuff

var player;
function onYouTubeIframeAPIReady() {
    player = new YT.Player('player', {
        height: '390',
        width: '640',
        videoId: key,
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

