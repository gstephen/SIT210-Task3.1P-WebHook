// The following line is optional, but recommended in most firmware. 
// It allows your code to run before the cloud is connected.
SYSTEM_THREAD(ENABLED);

// This uses the USB serial port for debugging logs.
SerialLogHandler logHandler;

//LED pin
const pin_t LED_PIN = D6; 

// This is where your photoresistor or phototransistor is plugged in.
const pin_t SENSOR_PIN = A0; 

//Variable to store the value of the photo transistor
int analogvalue;


int ledToggle(String command);


void setup() {
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);

	// We are going to declare a Particle.variable() here so that we can 
    // access the value of the photosensor from the cloud.
	Particle.variable("analogvalue", analogvalue);

	// We are also going to declare a Particle.function so that we can turn 
    // the LED on and off from the cloud.
	Particle.function("led",ledToggle);
}

void loop() {
	// Check to see what the value of the phototransistor is 
    // and store it in the int variable analogvalue
	analogvalue = analogRead(SENSOR_PIN);

	// This prints the value to the USB debugging serial port
	Log.info("analogvalue=%d", analogvalue);
	
	//Create a String varriable sendData to convert the int analogvalue to sendable data
	String sendData;
	sendData = String::format("%d C", analogvalue);
	//Send the value to created webhook for display in ThingSpeak
	Particle.publish("light", sendData, PRIVATE);

	delay(30000ms);
}


// This function is called when the Particle.function is called
int ledToggle(String command) {
	if (command.equals("on")) {
        digitalWrite(LED_PIN, HIGH);
        return 1;
    }
    else if (command.equals("off")) {
        digitalWrite(LED_PIN, LOW);
        return 0;
    }
    else {
		// Unknown option
        return -1;
    }
}
