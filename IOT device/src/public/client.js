var socket = io();


function ledON() {
  console.log ("sending a message to the web server to turn on the LED");
  // this is how we send a message back to the web server
  socket.emit('ledON'); 
}
