load('api_aws.js');
load('api_timer.js');
load('api_gpio.js');
load('api_sys.js');

let motor = 26;
let led = 13;
let state = { led: "off", dispense: 'DISPIDLE' };

GPIO.set_mode(led, GPIO.MODE_OUTPUT);
GPIO.set_mode(motor, GPIO.MODE_OUTPUT);
GPIO.write(motor, 0);

let handleLED = function(value) {
  state.led = value;
  if (state.led === "off") {
    print('Turning LED off');
    GPIO.write(led, false);
  } else if (state.led === "on") {
    print('Turning LED on');
    GPIO.write(led, true);
  }
  AWS.Shadow.update(0, {reported: state});
};

let handleDispense = function(value) {
  //state.dispense = value;
  //print('next is set to:', value);
  //AWS.Shadow.update(0, {reported: state});
  print('Activating motor for dispense!');
  GPIO.write(motor, 1);
  Sys.usleep(3000000);
  GPIO.write(motor, 0);
};

// Main event loop
// ***************

AWS.Shadow.setStateHandler(function(data, event, reported, desired) {
  if (event === AWS.Shadow.CONNECTED) {
    print('Connected to shadow')
    AWS.Shadow.update(0, {reported: state});
  } else if (event === AWS.Shadow.UPDATE_DELTA) {
    for (let key in state) {
      if (desired[key] === undefined) continue;
      if (key === 'led') {
        handleLED(desired[key]);
      } else if ((key === 'dispense') && (desired[key] === 'DISPREQ')) {
        handleDispense(desired[key]);
        state.dispense = "DISPREQ";
        AWS.Shadow.update(0, {reported: state});
        AWS.Shadow.update(0, {desired: {dispense: 'DISPACK'}});
      } else if ((key === 'dispense') && (desired[key] === 'DISPIDLE')) {
        state.dispense = 'DISPIDLE';
        AWS.Shadow.update(0, {reported: state});
      } else if ((key === 'dispense') && (desired[key] === 'DISPACK')) {
        state.dispense = 'DISPACK';
        print('updated shadow with ACK')
        AWS.Shadow.update(0, {reported: state});
        AWS.Shadow.update(0, {desired: {dispense: 'DISPIDLE'}});
      }
    }
  }
  print('aws handler, event', event, 'reported:', JSON.stringify(reported),
        'desired:', JSON.stringify(desired));
}, null);
