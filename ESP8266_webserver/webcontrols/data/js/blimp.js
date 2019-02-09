// globals used for state of buttons
alt=0;
yaw=0;

ch1=0;
ch2=0;
ch3=0;
ch4=0;
ch5=0;
ch6=0;
ch7=0;
ch8=0;

var connection = new WebSocket('ws://'+location.hostname+':81');
//var connection = new WebSocket('ws://'+location.hostname+':8001/');


connection.onopen = function () {
    console.log('onopen Connect ' + new Date());
};
connection.onerror = function (error) {
    console.log('WebSocket Error ', error);
    alert("WebSocket ERROR, This should never happen. WTF?");
};
connection.onmessage = function (e) {
    console.log('Server: ', e.data);
    $("#text").html(e.data);
};
connection.onclose = function(){i
    console.log('WebSocket connection closed');
    alert("Websocket CLOSED");
};


function sendData() {
    var datastr =  ch1 + " " + ch2 + " " + ch3 + " " + ch4 + " " + ch5 + " " + ch6 +  " " + ch7 + " " + ch8;
    console.log('sending: ' + datastr);
    connection.send(datastr);
    setTimeout(sendData,100);
}




function setChan(chan,val)
{
           if(chan==1) ch1 = val;
           if(chan==2) ch2 = val;
           if(chan==3) ch3 = val;
           if(chan==4) ch4 = val;
           if(chan==5) ch5 = val;
           if(chan==6) ch6 = val;
           if(chan==7) ch7 = val;
           if(chan==8) ch8 = val;
   
//           $(".channels .ch"+chan).html(val ); 

}


function resizeControls()
{

ww= jQuery(window).width();
wh= jQuery(window).height();


$("#fullscreen").width(ww);
$("#fullscreen").height(wh);

maxv=450;
minv=300;


new_width=ww-300;
if(new_width > maxv) new_width=maxv;
if(new_width < minv) new_width=minv;

new_height=wh-300;
if(new_height > maxv) new_height=maxv;
if(new_height < minv) new_height=minv;


console.log("setting width to: " + new_width);
console.log("setting height to: " + new_height);

$("#channel1").width(new_width);
$("#channel2").height(new_height);
$("#bottom").css("top",wh-60);



//portrait mode
if(ww<wh)
{
 $("#channel2").css("top","200px")
}
else
{
  $("#channel2").css("top","40px")
}


}



// setup all the elements in the DOM once the html is loaded
$().ready(function(){


resizeControls();

// check if we are on mobile device, if so try to force fullscreen


document.addEventListener("fullscreenchange", function (event) {
    if (document.fullscreenElement) {
        // fullscreen is activated
    } else {
        // fullscreen is cancelled
 $( "#controls" ).hide();
 $( "#esel" ).hide();
 $( "#fullscreen" ).show();
    }
});



var isMobile = false; //initiate as false
// device detection
if(/(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|ipad|iris|kindle|Android|Silk|lge |maemo|midp|mmp|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows (ce|phone)|xda|xiino/i.test(navigator.userAgent) 
    || /1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|yas\-|your|zeto|zte\-/i.test(navigator.userAgent.substr(0,4))) { 
    isMobile = true;
}



// show fullscreen button on mobile devices
if(isMobile)
{
 $( "#controls" ).hide();
 $( "#esel" ).hide();

$( "#fullscreen" ).on( "click", function( event, ui ) {
 document.body.requestFullscreen();
 $( "#fullscreen" ).hide();
 $( "#controls" ).show();
 $( "#esel" ).show();
 resizeControls();
} );





$( "#up" ).on( "touchstart", function( event, ui ) {setChan(3,"20");} );
$( "#down" ).on( "touchstart", function( event, ui ) {setChan(3,"-20");} );
$( "#up" ).on( "touchend", function( event, ui ) {setChan(3,"0");} );
$( "#down" ).on( "touchend", function( event, ui ) {setChan(3,"0");} );




}
else
{
 // not a mobile device

$( "#up" ).on( "mousedown", function( event, ui ) {setChan(3,"20");} );
$( "#down" ).on( "mousedown", function( event, ui ) {setChan(3,"-20");} );
$( "#up" ).on( "mouseup", function( event, ui ) {setChan(3,"0");} );
$( "#down" ).on( "mouseup", function( event, ui ) {setChan(3,"0");} );




 $( "#fullscreen" ).hide();
}


// check orientation







$( "button" ).button();


$( "#alt" ).on( "click", function( event, ui ) {
if(alt){ 
 alt=0;
 $(this).css("background-color","white");
} else{ 
 alt=1;
 $(this).css("background-color","red");
}
setChan(5,(alt+yaw));
$(this).blur();
} );

$( "#yaw" ).on( "click", function( event, ui ) {
if(yaw){ 
 yaw=0;
 $(this).css("background-color","white");
} else{ 
 $(this).css("background-color","red");
 yaw=2;
}
setChan(5,(alt+yaw));
$(this).blur();
} );








$("#channel2").each(function() {

    $(this).slider({
        value: 0,
        orientation: "vertical",
        min: parseInt($(this).attr('min')),
        max:  parseInt($(this).attr('max')),
        range: "min",
        slide: function(event, ui) {
           setChan(1,ui.value);
        },
        stop: function(event, ui) {
           $(this).slider( "option", "value", 0 );
           setChan(1,0);
        }
    });
  });


$("#channel1").each(function() {

    $(this).slider({
        value: 0,
        min: parseInt($(this).attr('min')),
        max:  parseInt($(this).attr('max')),
        range: "min",
        slide: function(event, ui) {
           setChan(2,ui.value);

        },
        stop: function(event, ui) {
           $(this).slider( "option", "value", 0 );
           setChan(2,0);
}
    });
  });



$( window ).resize(function() {
 resizeControls();
});









// first transmit 1 second after loading of page
setTimeout(sendData,1000);

}); // on ().ready
