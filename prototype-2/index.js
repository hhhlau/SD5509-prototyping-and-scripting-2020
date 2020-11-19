const { Gpio } = require ('onoff')
const dhtSensor = require("node-dht-sensor").promises;
const mqtt = require('mqtt');


const mqttEndpoint = "mqtt://6977ff4e:5589e974aa4558be@broker.shiftr.io";
const mqttSecret = {
	username: "6977ff4e",
	secret: "5589e974aa4558be"
};

const deviceMeta = {
	deviceId: "test-001",
	location: {
		lat: 123.123,
		long: 1233.123,
		name: "PolyU Innovation Tower, V1121"
	}
}
// Set up DHT 22
dhtSensor.setMaxRetries(10);
dhtSensor.initialize(22, 4);


// Set up mqtt client
const client = mqtt.connect(mqttEndpoint);
client.on('connect', function () {
	console.log("Connected with Shiftr!")
})




setInterval(async function() {
	try {
		    const res = await dhtSensor.read(22, 4);
		client.publish('sensor-update', JSON.stringify({res, deviceMeta, timestamp: Date.now() }));
		client.publish(`sensor-update/${deviceMeta.deviceId}`,JSON.stringify({res, deviceMeta, timestamp: Date.now()}))
		console.log(
			          `temp: ${res.temperature.toFixed(1)}°C, ` +
			            `humidity: ${res.humidity.toFixed(1)}%`
			        );
		  } catch (err) {
			      console.error("Failed to read sensor data:", err);
			    }
}, 5000);
