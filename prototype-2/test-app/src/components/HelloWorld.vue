<template>
  <div class="hello">
    <h1>{{ msg }}</h1>
<p>{{data}}</p>
<p>{{lastUpdate}}</p>
</div>
</template>

<script>
export default {
  name: 'HelloWorld',
  props: {
    msg: String
  },
  data(){
	return {
	data: null,
	topic: null,
	lastUpdate: null
}
},
mounted(){
	const mqtt = require("mqtt")
	let client = mqtt.connect("mqtt://b9155527:881fabd58c0f4d8e@broker.shiftr.io") 
	client.on('sensor-update',function(topic, msg){
	this.topic = topic
	let _msg = JSON.parse(msg.toString())
	this.lastUpdate = _msg.timestamp
	this.msg = _msg
})
}
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
h3 {
  margin: 40px 0 0;
}
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
a {
  color: #42b983;
}
</style>
