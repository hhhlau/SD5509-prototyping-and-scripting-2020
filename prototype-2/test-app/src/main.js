import Vue from 'vue'
import VueMqtt from 'vue-mqtt';
import App from './App.vue'

Vue.config.productionTip = false
Vue.use(VueMqtt, 'mqtt://b9155527:881fabd58c0f4d8e@broker.shiftr.io');

new Vue({
  render: h => h(App),
}).$mount('#app')
